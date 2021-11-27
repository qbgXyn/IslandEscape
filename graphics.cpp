#include "graphics.h"
#include "Map/Map.h"
#include "mainwindow.h"

#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTextFormat>
#include <QPixmap>

#include <cmath>
#include <regex>

GameWidget::GameWidget(QWidget* parent) :
    QWidget(parent),
    map(dynamic_cast<MainWindow *>(parent)->map),
    map_width(map->getMaxWidth()),
    map_height(map->getMaxHeight()),
    scroll_x(0), scroll_y(0),
    scale(1.0f),
    UP(false), DOWN(false), LEFT(false), RIGHT(false),
    tick(0),
    hovering_grid_x(-1), hovering_grid_y(-1)
{
    load_icons();
    setMouseTracking(true);
    grabKeyboard();
}

GameWidget::~GameWidget() {
    dealloc_icons();
}

void GameWidget::loop() {
    const int x_min = 0;
    const int x_max = map_width;
    const int y_min = 0;
    const int y_max = map_height;
    if (scroll_x >= x_min && scroll_x <= x_max) {
        scroll_x += (int) (5.0f * ((int) RIGHT - (int) LEFT));
    }
    if (scroll_x < x_min)
        scroll_x = x_min;
    if (scroll_x > x_max)
        scroll_x = x_max;
    if (scroll_y >= y_min && scroll_y <= y_max) {
        scroll_y += (int) (5.0f * ((int) DOWN - (int) UP));
    }
    if (scroll_y < y_min)
        scroll_y = y_min;
    if (scroll_y > y_max)
        scroll_y = y_max;

    repaint(0, 0, width(), height());
    ++tick;
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_Up:
        UP = true;
        break;
    case Qt::Key::Key_Down:
        DOWN = true;
        break;
    case Qt::Key::Key_Left:
        LEFT = true;
        break;
    case Qt::Key::Key_Right:
        RIGHT = true;
        break;
    case Qt::Key::Key_C:
        /*
        // Pick up function
        */
        break;
    case Qt::Key::Key_Space:
        /*
        // Attack function
        */
        break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_Up:
        UP = false;
        break;
    case Qt::Key::Key_Down:
        DOWN = false;
        break;
    case Qt::Key::Key_Left:
        LEFT = false;
        break;
    case Qt::Key::Key_Right:
        RIGHT = false;
        break;
    }
}

void GameWidget::wheelEvent(QWheelEvent* event) {
    scale = (float) (scale * exp(event->angleDelta().y() / 720.0));
    if (scale > 10.0f) {
        scale = 10.0f;
    }
    if (scale < 0.1f) {
        scale = 0.1f;
    }
}

void GameWidget::obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y) {
    x = (rx + map_width * 50) / 100;
    y = (ry + map_height * 50) / 100;
}

void GameWidget::obtain_grid_coordinates(int dispx, int dispy, int& x, int& y) {
    int rx, ry;
    to_real_coordinates(dispx, dispy, rx, ry);
    obtain_grid_coordinates_from_real(rx, ry, x, y);
}

void GameWidget::to_display_coordinates(int x, int y, int& dispx, int& dispy) {
    float fx = x, fy = y;
    dispx = (int)((fx - scroll_x) * scale) + width() / 2;
    dispy = (int)((fy - scroll_y) * scale) + height() / 2;
}

void GameWidget::to_real_coordinates(int dispx, int dispy, int& x, int& y) {
    float fx = dispx - width() / 2, fy = dispy - height() / 2;

    x = (int)(fx / scale + scroll_x);
    y = (int)(fy / scale + scroll_y);
}

void GameWidget::drawLine(QPainter& paint, int x1, int y1, int x2, int y2) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x1, y1, dispx1, dispy1);
    to_display_coordinates(x2, y2, dispx2, dispy2);

    paint.drawLine(dispx1, dispy1, dispx2, dispy2);
}

void GameWidget::fillRect(QPainter& paint, int x, int y, int w, int h, const QBrush& brush) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.fillRect(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, brush);
}

void GameWidget::drawPixmap(QPainter& paint, int x, int y, int w, int h, const QPixmap& pixmap) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.drawPixmap(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, pixmap);
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter paint{this};

    // Make the Map Background
    paint.drawPixmap(0, 0, width(), height(), ICONS[2]);

    const int min = 0;
    const int max = map_width;
    const int minn = 0;
    const int maxx = map_height;

    // Draw Terrain on the grid
    for (int x = min; x < max; x+=map->grid_size) {
        for (int y = minn; y < maxx; y+=map->grid_size) {
            drawPixmap(paint, x, y, map->grid_size, map->grid_size,
                       ICONS[static_cast<int>(map->getTerrainOfGrid(x,y))]);
        }
    }

    // Draw Decoration on grid
    /*
    // Draw Draw Draw Draw Draw Draw Draw Draw Draw Draw Draw Draw Draw Draw Draw
    */

    // Draw CampFire on grid
    drawPixmap(paint, 64, 64, 64, 64, CAMPFIRE_ICONS[campfire_number]);
    campfire_number = (campfire_number+1)%12;

    // Draw Boat on grid
    QPixmap boat(":/resources/images/boat.png");
    drawPixmap(paint, 320, 64, 128, 256, boat);

    // Draw Grid Lines
    for (int x = min; x <= max; x+=map->grid_size) {
        drawLine(paint, x, minn, x, maxx);
    }
    for (int y = minn; y <= maxx; y+=map->grid_size) {
        drawLine(paint, min, y, max, y);
    }

    // Draw Player
    QPixmap player(":/resources/images/player.png");
    QMatrix rm;
    if (LEFT==true) {
        rm.rotate(-90);
        if (UP==true)
            rm.rotate(45);
        if (DOWN==true)
            rm.rotate(-45);
    }
    else if (RIGHT==true) {
        rm.rotate(90);
        if (UP==true)
            rm.rotate(-45);
        if (DOWN==true)
            rm.rotate(45);
    }
    else if (DOWN==true)
        rm.rotate(180);
    int w = player.width(), h = player.height();
    player = player.transformed(rm);
    player = player.copy((player.width()-w)/2, (player.height()-h)/2, w, h);
    drawPixmap(paint, scroll_x-64, scroll_y-64, 128, 128, player);

    // Draw Out of Vision
    if (true /*map->player->getTorchTime() > 0 && map->player->hasItem(Item::ID::TORCH_LIT)*/) {
        paint.fillRect(0, 0, width()/2-64*4, height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(0, 0, width(), height()/2-64*4, QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width()/2+64*4, -height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width(), -height()/2+64*4, QBrush{ QColor::fromRgb(0,0,0) });
    }
    else {
        paint.fillRect(0, 0, width()/2-64*3, height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(0, 0, width(), height()/2-64*3, QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width()/2+64*3, -height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width(), -height()/2+64*3, QBrush{ QColor::fromRgb(0,0,0) });
    }
}

void GameWidget::load_icons() {
    ICONS = new QPixmap [4] {{":/resources/images/Grass.png"},
                             {":/resources/images/Stone.png"},
                             {":/resources/images/Ocean.png"},
                             {":/resources/images/Sand.png"}};
    CAMPFIRE_ICONS = new QPixmap [12] {{":/resources/images/campfire01.png"},
                                       {":/resources/images/campfire02.png"},
                                       {":/resources/images/campfire03.png"},
                                       {":/resources/images/campfire04.png"},
                                       {":/resources/images/campfire05.png"},
                                       {":/resources/images/campfire06.png"},
                                       {":/resources/images/campfire07.png"},
                                       {":/resources/images/campfire08.png"},
                                       {":/resources/images/campfire09.png"},
                                       {":/resources/images/campfire10.png"},
                                       {":/resources/images/campfire11.png"},
                                       {":/resources/images/campfire12.png"}};
}

void GameWidget::dealloc_icons() {
    delete [] ICONS;
    delete [] CAMPFIRE_ICONS;
}

// Set green background
//paint.fillRect(0, 0, width(), height(), QBrush{ QColor::fromRgb(119,158,203) });

/*
for (int x = 0; x < grid_size; x++) {
    for (int y = 0; y < grid_size; y++) {
        drawPixmap(paint, (x - grid_size / 2) * 100, (y - grid_size / 2) * 100, 100, 100,
                   ICONS[0]);

    }
}*/

/* QFont ft;
ft.setPixelSize(25);
ft.setBold(true);
ft.setFamily("Comic Sans MS");
paint.setFont(ft); */

/* const int min = -grid_size * 50;
const int max = grid_size * 50;
// Draw special overlays on the grid
switch (dynamic_cast<MainWindow *>(window())->get_selected_overlay_button()) {
    case MainWindow::OverlayButton::NORMAL:
        break;
    case MainWindow::OverlayButton::TYPE: {
        for (int x = 0; x < grid_size; x++) {
            for (int y = 0; y < grid_size; y++) {
                if (!city->is_empty_at(x, y)) {
                    QBrush brush;
                    switch (city->get_at(x, y)->get_category()) {
                        case Building::Category::RESIDENTIAL:
                            brush.setColor(QColor::fromRgbF(0, 0, 1, 0.8f));
                            break;
                        case Building::Category::REVENUE:
                            brush.setColor(QColor::fromRgbF(1, 1, 0, 0.8f));
                            break;
                        case Building::Category::HEALTH:
                            brush.setColor(QColor::fromRgbF(1, 0, 0, 0.8f));
                            break;
                    }
                    brush.setStyle(Qt::SolidPattern);
                    fillRect(paint, (x - grid_size / 2) * 100, (y - grid_size / 2) * 100, 100, 100, brush);
                }
            }
        }
        break;
    }
    case MainWindow::OverlayButton::NEIGHBOR: {
        QPen original = paint.pen();
        for (int x = 0; x < grid_size; x++) {
            for (int y = 0; y < grid_size; y++) {
                // With bottom
                int dcolor = contains_type(city->get_at(x, y), city->get_at(x, y + 1));
                if (dcolor != -2) {
                    tsetColor(paint, dcolor);
                    drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                             (x - grid_size / 2) * 100 + 50, (y + 1 - grid_size / 2) * 100 + 50);
                }

                // With left
                dcolor = contains_type(city->get_at(x, y), city->get_at(x + 1, y));
                if (dcolor != -2) {
                    tsetColor(paint, dcolor);
                    drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                             (x + 1 - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50);
                }
            }
        }
        paint.setPen(original);
        break;
    }
} */
/*
// Render extra effects on the grid, depending on the build mode
if (hovering_grid_x >= 0 && hovering_grid_y >= 0 && hovering_grid_x < grid_size && hovering_grid_y < grid_size)
    if ((tick / 10) % 2 == 0) {
        MainWindow::SideMenuButton button_selected = dynamic_cast<MainWindow *>(window())->get_selected_side_menu_button();
        if (button_selected != MainWindow::SideMenuButton::DEMOLISH &&
            button_selected != MainWindow::SideMenuButton::NAVIGATE &&
            city->is_empty_at(hovering_grid_x, hovering_grid_y)) {
            drawPixmap(paint, (hovering_grid_x - grid_size / 2) * 100, (hovering_grid_y - grid_size / 2) * 100, 100,
                       100, ICONS[static_cast<int>(button_selected) - 1]);
        }else if (button_selected == MainWindow::SideMenuButton::DEMOLISH &&
                  !city->is_empty_at(hovering_grid_x, hovering_grid_y)) {
            fillRect(paint, (hovering_grid_x - grid_size / 2) * 100, (hovering_grid_y - grid_size / 2) * 100, 100,
                    100, QBrush{QColor::fromRgbF(1.0f, 0, 0, 0.5f)});
    }
} */
/*
// Draw player statistics
#define STAT_WIDTH 500
#define HEIGHT 40
paint.drawText(10, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
               "Turn " + QString::number(city->get_turn()) + ": $" + QString::number(city->get_budget()));
paint.drawText(10, 60 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "Revenue: " + QString::number(city->get_revenue()));
paint.drawText(10, 110 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
               "Max Population: " + QString::number(city->get_max_population()));
paint.drawText(10, 160 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
               "Population: " + QString::number(city->get_population()));
paint.drawText(10, 210 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
               "Population Change: " + QString::number(city->get_population_growth()));
paint.drawText(10, 260 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
               "Population Growth Rate: " + QString::number(city->get_population_growth_rate()));
*/
