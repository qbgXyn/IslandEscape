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

GameWidget::GameWidget(QWidget* parent) : //basic set up
    QWidget(parent),
    map(dynamic_cast<MainWindow *>(parent)->map),
    map_width(map->getMaxWidth()),
    map_height(map->getMaxHeight()),
    scroll_x(0), scroll_y(0),
    scale(1.0f),
    UP(false), DOWN(false), LEFT(false), RIGHT(false),
    Player_Direction(0),
    CAMPFIRE_COUNT(0)
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

    // Inventory Item Logos


    repaint(0, 0, width(), height());
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) { //connect key with corresponding function
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

    case Qt::Key::Key_C: //key for special functions
        map->player->pickupItem();
        break;
    case Qt::Key::Key_Q:
        map -> player -> dropItem(map -> player -> Inventory[map -> player -> selectedItemIndex]);
        break;
    case Qt::Key::Key_Space:
        map -> player -> useItem(map -> player -> Inventory[map -> player -> selectedItemIndex]);
        //map->player->attack()
        break;

    case Qt::Key::Key_1: //for switching buttom item bar
        map->player->Switch_selectedItem_Index(0);
        break;
    case Qt::Key::Key_2:
        map->player->Switch_selectedItem_Index(1);
        break;
    case Qt::Key::Key_3:
        map->player->Switch_selectedItem_Index(2);
        break;
    case Qt::Key::Key_4:
        map->player->Switch_selectedItem_Index(3);
        break;
    case Qt::Key::Key_5:
        map->player->Switch_selectedItem_Index(4);
        break;
    case Qt::Key::Key_6:
        map->player->Switch_selectedItem_Index(5);
        break;
    case Qt::Key::Key_7:
        map->player->Switch_selectedItem_Index(6);
        break;
    case Qt::Key::Key_8:
        map->player->Switch_selectedItem_Index(7);
        break;
    case Qt::Key::Key_9:
        map->player->Switch_selectedItem_Index(8);
        break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent* event) { //used for movement key to stop moving
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

void GameWidget::obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y) { //helper functions to convert between x, y and actual grid position
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

void GameWidget::drawLine(QPainter& paint, int x1, int y1, int x2, int y2) { //draw map coordinate lines
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x1, y1, dispx1, dispy1);
    to_display_coordinates(x2, y2, dispx2, dispy2);

    paint.drawLine(dispx1, dispy1, dispx2, dispy2);
}

void GameWidget::fillRect(QPainter& paint, int x, int y, int w, int h, const QBrush& brush) { //fill the grid with color
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.fillRect(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, brush);
}

void GameWidget::drawPixmap(QPainter& paint, int x, int y, int w, int h, const QPixmap& pixmap) { //put the png onto the grid
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
    drawPixmap(paint, 64, 64, 64, 64, CAMPFIRE[CAMPFIRE_COUNT]);
    CAMPFIRE_COUNT = (CAMPFIRE_COUNT+1)%12;


    // Draw Boat on grid
    QPixmap boat(":/resources/images/Handle/Decoration/boat.png");
    drawPixmap(paint, 320, 64, 128, 256, boat);

    // Draw Grid Lines
    for (int x = min; x <= max; x+=map->grid_size) {
        drawLine(paint, x, minn, x, maxx);
    }
    for (int y = minn; y <= maxx; y+=map->grid_size) {
        drawLine(paint, min, y, max, y);
    }

    // Draw Player
    QPixmap player(":/resources/images/Handle/Unit/player.png");
    QMatrix rm;
    if (LEFT==true) { //because we use vector to make smooth movement, the player need to rotate
        Player_Direction = -90;
        if (UP==true)
            Player_Direction += 45;
        if (DOWN==true)
            Player_Direction += -45;
    }
    else if (RIGHT==true) {
        Player_Direction = 90;
        if (UP==true)
            Player_Direction += -45;
        if (DOWN==true)
            Player_Direction += 45;
    }
    else if (UP==true)
        Player_Direction = 0;
    else if (DOWN==true)
        Player_Direction = 180;
    rm.rotate(Player_Direction);
    int w = player.width(), h = player.height();
    player = player.transformed(rm);
    player = player.copy((player.width()-w)/2, (player.height()-h)/2, w, h);
    drawPixmap(paint, scroll_x-64, scroll_y-64, 128, 128, player);

    // Draw Out of Vision
    int visible_size = map->player->getVisibleSize();
        paint.fillRect(0, 0, width()/2-map->grid_size*visible_size, height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(0, 0, width(), height()/2-map->grid_size*visible_size, QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width()/2+map->grid_size*visible_size, -height(), QBrush{ QColor::fromRgb(0,0,0) });
        paint.fillRect(width(), height(), -width(), -height()/2+map->grid_size*visible_size, QBrush{ QColor::fromRgb(0,0,0) });
        fillRect(paint, scroll_x-map->grid_size*visible_size, scroll_y-map->grid_size*visible_size, 2*map->grid_size*visible_size, 2*map->grid_size*visible_size,
                       QBrush{ QColor::fromRgb(0, 0, 0, 64) });
}

void GameWidget::load_icons() {
    ICONS = new QPixmap [4] {{":/resources/images/Terrain/Grass.png"},
                             {":/resources/images/Terrain/Stone.png"},
                             {":/resources/images/Terrain/Ocean.png"},
                             {":/resources/images/Terrain/Sand.png"}};
    CAMPFIRE = new QPixmap [12] {{":/resources/images/Handle/Decoration/campfire01.png"},
                                 {":/resources/images/Handle/Decoration/campfire02.png"},
                                 {":/resources/images/Handle/Decoration/campfire03.png"},
                                 {":/resources/images/Handle/Decoration/campfire04.png"},
                                 {":/resources/images/Handle/Decoration/campfire05.png"},
                                 {":/resources/images/Handle/Decoration/campfire06.png"},
                                 {":/resources/images/Handle/Decoration/campfire07.png"},
                                 {":/resources/images/Handle/Decoration/campfire08.png"},
                                 {":/resources/images/Handle/Decoration/campfire09.png"},
                                 {":/resources/images/Handle/Decoration/campfire10.png"},
                                 {":/resources/images/Handle/Decoration/campfire11.png"},
                                 {":/resources/images/Handle/Decoration/campfire12.png"}};
}

void GameWidget::dealloc_icons() {
    delete [] ICONS;
    delete [] CAMPFIRE;
}
