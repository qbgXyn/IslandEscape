#include "graphics.h"
#include "Map.h"
#include "mainwindow.h"

#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTextFormat>

#include <cmath>
#include <regex>

GameWidget::GameWidget(QWidget* parent) :
    QWidget(parent),
    city(dynamic_cast<MainWindow *>(parent)->city),
    grid_size(city->get_grid_size()),
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
    scroll_x += (int) (15.0f * ((int) RIGHT - (int) LEFT) / scale);
    scroll_y += (int) (15.0f * ((int) DOWN - (int) UP) / scale);
    repaint(0, 0, width(), height());
    ++tick;
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_W:
        UP = true;
        break;
    case Qt::Key::Key_S:
        DOWN = true;
        break;
    case Qt::Key::Key_A:
        LEFT = true;
        break;
    case Qt::Key::Key_D:
        RIGHT = true;
        break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_W:
        UP = false;
        break;
    case Qt::Key::Key_S:
        DOWN = false;
        break;
    case Qt::Key::Key_A:
        LEFT = false;
        break;
    case Qt::Key::Key_D:
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

void GameWidget::mouseReleaseEvent(QMouseEvent* event) {
    int screen_x = event->x();
    int screen_y = event->y();
    int x, y;
    obtain_grid_coordinates(screen_x, screen_y, x, y);// Check if selected point lies on the grid
    if (x >= 0 && y >= 0 && x < grid_size && y < grid_size) {
        MainWindow *main_window = dynamic_cast<MainWindow *>(window());
        MainWindow::SideMenuButton button_selected = main_window->get_selected_side_menu_button();
        if (button_selected != MainWindow::SideMenuButton::NAVIGATE) {
            if (event->button() == Qt::MouseButton::RightButton) {
                main_window->on_side_menu_button_clicked(MainWindow::SideMenuButton::NAVIGATE);
            } else if (event->button() == Qt::MouseButton::LeftButton) {
                // If the selected button are buildings
                if (button_selected != MainWindow::SideMenuButton::DEMOLISH && city->is_empty_at(x, y)) {
                    city->construct_at(static_cast<Building::Type>(button_selected), x, y);

                    // Trick to jump back to navigation if player does not have enough budget for the building
                    main_window->on_side_menu_button_clicked(button_selected);
                }

                // Selected button is delete
                else if (button_selected == MainWindow::SideMenuButton::DEMOLISH && !city->is_empty_at(x, y)) {
                    city->demolish_at(x, y);
                }
            }
        } else if (!city->is_empty_at(x, y)) {
            QMessageBox *mb = new QMessageBox{window()};
            mb->setWindowTitle("Simple City");
            mb->setStyleSheet("font: 14pt \"Comic Sans MS\";");

            if (event->button() == Qt::MouseButton::LeftButton) {
                mb->setText(QString::fromStdString(
                        "<p style='text-align: center;'>" +
                        std::regex_replace(city->get_at(x, y)->get_short_information(), std::regex{"\n"}, "<br>") +
                        "</p>"
                ));
            } else if (event->button() == Qt::MouseButton::RightButton) {
                mb->setText(QString::fromStdString(
                        "<p style='text-align: center;'>" +
                        std::regex_replace(city->get_at(x, y)->get_long_information(), std::regex{"\n"}, "<br>") +
                        "</p>"
                ));
            }
            mb->setAttribute(Qt::WA_DeleteOnClose, true);
            mb->show();
        }
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent* event) {
    int screen_x = event->x();
    int screen_y = event->y();

    MainWindow *main_window = dynamic_cast<MainWindow *>(window());
    MainWindow::SideMenuStatus button_group_status = main_window->get_side_menu_status();
    if (screen_x > width() - 100) {
        if (button_group_status == MainWindow::SideMenuStatus::HIDDEN) {
            main_window->set_side_menu_status(MainWindow::SideMenuStatus::HIDDEN_TO_VISIBLE);
        }
    } else if (screen_x < width() - 420){
        if (button_group_status == MainWindow::SideMenuStatus::VISIBLE) {
            main_window->set_side_menu_status(MainWindow::SideMenuStatus::VISIBLE_TO_HIDDEN);
        }
    }

    if (screen_x > width() - 420 || button_group_status == MainWindow::SideMenuStatus::HIDDEN){ // Does handle only if the cursor is on the to-be menu
        int x, y;

        obtain_grid_coordinates(screen_x, screen_y, x, y);

        hovering_grid_x = x;
        hovering_grid_y = y;
    }
}

void GameWidget::obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y) {
    x = (rx + grid_size * 50) / 100;
    y = (ry + grid_size * 50) / 100;
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

// Helper function
int contains_type(Building* b1, Building* b2) {
    if (b1 == nullptr || b2 == nullptr) {
        return -2;
    }

    Building::Category t1 = b1->get_category();
    Building::Category t2 = b2->get_category();

    if (t1 == Building::Category::RESIDENTIAL) {
        return (b2->get_type() == Building::Type::GOLD_MINE) ? 0 : 1;
    }
    if (t2 == Building::Category::RESIDENTIAL) {
        return (b1->get_type() == Building::Type::GOLD_MINE) ? 0 : 1;
    }
    if (t1 == t2 && t2 == Building::Category::HEALTH) {
        return -1;
    }

    return -2;
}

// Helper function
void tsetColor(QPainter& paint, int dcolor) {
    QPen p = paint.pen();
    p.setWidth(7);
    switch (dcolor) {
    case -1:
        p.setColor(QColor::fromRgb(255, 0, 0));
        break;
    case 0:
        p.setColor(QColor::fromRgb(255, 255, 255));
        break;
    case 1:
        p.setColor(QColor::fromRgb(0, 255, 0));
        break;
    }
    paint.setPen(p);
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter paint{ this };

    // Set green background
    paint.fillRect(0, 0, width(), height(), QBrush{ QColor::fromRgb(100,200,100) });

    QFont ft;
    ft.setPixelSize(25);
    ft.setBold(true);
    ft.setFamily("Comic Sans MS");
    paint.setFont(ft);

    const int min = -grid_size * 50;
    const int max = grid_size * 50;// Draw special overlays on the grid
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
    }// Draw buildings on the grid
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (!city->is_empty_at(x, y)) {
                drawPixmap(paint, (x - grid_size / 2) * 100, (y - grid_size / 2) * 100, 100, 100,
                           ICONS[static_cast<int>(city->get_at(x, y)->get_type()) - 1]);
            }
        }
    }// Render extra effects on the grid, depending on the build mode
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
        }// Draw grid lines
    for (int x = 0; x <= grid_size; x++) {
        int xpos = (x - grid_size / 2) * 100;
        drawLine(paint, xpos, min, xpos, max);
    }
    for (int y = 0; y <= grid_size; y++) {
        int ypos = (y - grid_size / 2) * 100;
        drawLine(paint, min, ypos, max, ypos);
    }// Draw player statistics
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
}

void GameWidget::load_icons() {
    ICONS = new QPixmap[6]{ {":/resources/images/clinic.png"},
                            {":/resources/images/hospital.png"},
                            {":/resources/images/silver_mine.png"},
                            {":/resources/images/gold_mine.png"},
                            {":/resources/images/house.png"},
                            {":/resources/images/apartment.png"} };
}

void GameWidget::dealloc_icons() {
    delete[] ICONS;
}
