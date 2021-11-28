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
    UP(false), DOWN(false), LEFT(false), RIGHT(false)
{
    load_icons();
    setMouseTracking(true);
    grabKeyboard();
}

GameWidget::~GameWidget() {
    dealloc_icons();
}

void GameWidget::loop() {
    // Player Movement
    int horizontal = (int)RIGHT - (int)LEFT;
    int vertical = (int)DOWN - (int)UP;
    if (horizontal != 0 && vertical != 0) {
        map->player->setVelocityX(horizontal*(7.071067));
        map->player->setVelocityY(vertical*(7.071067));
    }
    else {
        map->player->setVelocityX(horizontal*10);
        map->player->setVelocityY(vertical*10);
    }
    map->player->update();
    scroll_x = map->player->getX();
    scroll_y = map->player->getY();

    // Pickup

    // Iventory

    // Attack
    if (ATTACK)
        //map->player->attack()
        ;

    repaint(0, 0, width(), height());
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
    case Qt::Key::Key_E:
        /*
        // Inventory
        */
        break;
    case Qt::Key::Key_Space:
        ATTACK = true;
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
    case Qt::Key::Key_C:
        /*
        // Pick up function
        */
        break;
    case Qt::Key::Key_E:
        /*
        // Inventory
        */
        break;
    case Qt::Key::Key_Space:
        ATTACK = false;
        break;
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
    int visible_size = map->player->getVisibleSize();
//    if (map->player->getTorchTime() > 0 && map->player->hasItem(Item::ID::TORCH_LIT)) {
        paint.fillRect(0, 0, width()/2-map->grid_size*visible_size, height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(0, 0, width(), height()/2-map->grid_size*visible_size, QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width()/2+map->grid_size*visible_size, -height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width(), -height()/2+map->grid_size*visible_size, QBrush{ QColor::fromRgb(0,0,0) });
//    }
//    else {
//        paint.fillRect(0, 0, width()/2-64*3, height(), QBrush{ QColor::fromRgb(0,0,0) });
//        paint.fillRect(0, 0, width(), height()/2-64*3, QBrush{ QColor::fromRgb(0,0,0) });
//        paint.fillRect(width(), height(), -width()/2+64*3, -height(), QBrush{ QColor::fromRgb(0,0,0) });
//        paint.fillRect(width(), height(), -width(), -height()/2+64*3, QBrush{ QColor::fromRgb(0,0,0) });
//    }
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
