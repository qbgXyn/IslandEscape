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

#include <QDebug>

#include "Handle/Handle.h"
#include "Handle/Decoration/Boat.h"
#include "Handle/Decoration/Campfire.h"
#include "Handle/Decoration/Chest.h"
#include "Handle/Decoration/Decoration.h"
#include "Handle/Decoration/Item_Handle.h"
#include "Handle/Decoration/Tree.h"

#include "Item/Item.h"
#include "Item/Item_data.h"

#include "util.h"
#include <math.h>

const QBrush NOT_VISIBLE{ QColor::fromRgb(0,0,0,233) };
const QBrush VISIBLE_LIT{ QColor::fromRgb(50,50,0,130) };
const QBrush VISIBLE{ QColor::fromRgb(00,00,0,160) };

GameWidget::GameWidget(QWidget* parent) : //basic set up
    QWidget(parent),
    map(dynamic_cast<MainWindow *>(parent)->map),
    map_width(map->getMaxWidth()),
    map_height(map->getMaxHeight()),
    scroll_x(0), scroll_y(0),
    scale(1.0f),
    UP(false), DOWN(false), LEFT(false), RIGHT(false),
    CAMPFIRE_COUNT(0)
{
    load_icons();
    grabKeyboard();
}

GameWidget::~GameWidget() {
    dealloc_icons();
}

void GameWidget::loop() {
    // Player Movement
    double direction = map->player->getDirection();
    if (UP==true) { //because we use vector to make smooth movement, the player need to rotate
        direction = 90;
        if (LEFT==true)
            direction += 45;
        if (RIGHT==true)
            direction += -45;
    }
    else if (DOWN==true) {
        direction = -90;
        if (LEFT==true)
            direction += -45;
        if (RIGHT==true)
            direction += 45;
    }
    else if (LEFT==true)
        direction = 180;
    else if (RIGHT==true)
        direction = 0;

    map->player->setMoveDirection( (UP||DOWN||LEFT||RIGHT), direction );

    scroll_x = map->player->getX();
    scroll_y = map->player->getY();

    repaint(0, 0, width(), height());
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    Survivor* survivor = map->player;
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
        survivor->pickupItem();
        break;
    case Qt::Key::Key_Q:
        survivor->dropItem();
        break;
    case Qt::Key::Key_Space:
        survivor->useItem(map->player->Inventory[map->player->selectedItemIndex]);
        //map->player->attack()
        break;

    case Qt::Key::Key_1: //for switching buttom item bar
        survivor->Switch_selectedItem_Index(0);
        break;
    case Qt::Key::Key_2:
        survivor->Switch_selectedItem_Index(1);
        break;
    case Qt::Key::Key_3:
        survivor->Switch_selectedItem_Index(2);
        break;
    case Qt::Key::Key_4:
        survivor->Switch_selectedItem_Index(3);
        break;
    case Qt::Key::Key_5:
        survivor->Switch_selectedItem_Index(4);
        break;
    case Qt::Key::Key_6:
        survivor->Switch_selectedItem_Index(5);
        break;
    case Qt::Key::Key_7:
        survivor->Switch_selectedItem_Index(6);
        break;
    case Qt::Key::Key_8:
        survivor->Switch_selectedItem_Index(7);
        break;
    case Qt::Key::Key_9:
        survivor->Switch_selectedItem_Index(8);
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

void GameWidget::drawMap(QPainter& paint) {
    // Draw Terrain
    for (int x = 0; x < map_width; x+=map->grid_size) {
        for (int y = 0; y < map_height; y+=map->grid_size) {
            drawPixmap(paint, x, y, map->grid_size, map->grid_size,
                       ICONS[static_cast<int>(map->getTerrainOfGrid(x,y))]);
        }
    }

    // Draw Grid Lines
    for (int x = 0; x <= map_width; x+=map->grid_size) {
        drawLine(paint, x, 0, x, map_height);
    }
    for (int y = 0; y <= map_height; y+=map->grid_size) {
        drawLine(paint, 0, y, map_width, y);
    }
}

void GameWidget::drawHandle(QPainter& paint, Handle* Handle) {
    switch(Handle->getType()) {
        case Handle::Type::BOAT: {
            QPixmap boat(":/resources/images/Handle/Decoration/boat.png");
            drawPixmap(paint, Handle->getX()-64, Handle->getY()-3*64/2, 2*64, 3*64, boat);
            break;
        }
        case Handle::Type::CAMPFIRE: {
            drawPixmap(paint, Handle->getX()-32, Handle->getY()-32, 64, 64, CAMPFIRE[CAMPFIRE_COUNT]);
            CAMPFIRE_COUNT = (CAMPFIRE_COUNT+1)%12;
            break;
        }
        case Handle::Type::CHEST: {
            QPixmap chest(":/resources/images/Handle/Decoration/chest.png");
            drawPixmap(paint, Handle->getX()-32, Handle->getY()-32, 64, 64, chest);
            break;
        }
        case Handle::Type::ITEM: {
            QPixmap Item(QString::fromStdString(Handle->getCorrespondingItem()->getTexture()));
            drawPixmap(paint, Handle->getX()-32, Handle->getY()-32, 64, 64, Item);
            break;
        }
        case Handle::Type::TREE: {
            drawPixmap(paint, Handle->getX()-64, Handle->getY()-64, 128, 128, TREE[Handle->getSpecies()]);
            break;
        }
        case Handle::Type::GHOST: {
            QPixmap ghost = GHOST[Handle->getSpecies()];
            QMatrix rm;
            rm.rotate(90-Handle->getDirection());
            int w = ghost.width(), h = ghost.height();
            ghost = ghost.transformed(rm);
            ghost = ghost.copy((ghost.width()-w)/2, (ghost.height()-h)/2, w, h);
            drawPixmap(paint, Handle->getX()-64, Handle->getY()-64, 128, 128, ghost);
            break;
        }
    }
}

void GameWidget::drawPlayer(QPainter& paint) {
    Survivor * survivor = map->player;
    // Draw attack sector
    Item_inventory* Item = survivor->Inventory[survivor->selectedItemIndex];
    if(Item != nullptr && Item->item->getID() == Item::ID::SWORD) {
        int radius = survivor->base_attack_radius;
        int span = survivor->base_attack_sector_angle;
        int dispx1, dispx2, dispy1, dispy2;
        to_display_coordinates(-radius, -radius, dispx1, dispy1);
        to_display_coordinates(radius, radius, dispx2, dispy2);
        QRect rect(scroll_x+dispx1, scroll_y+dispy1, dispx2-dispx1, dispy2-dispy1);
        QBrush previous_brush = paint.brush();
        paint.setBrush(QBrush{ QColor::fromRgb(100,100,100,100) });

        paint.drawPie( rect, (map->player->getDirection()-span/2)*16, span*16);
        paint.setBrush(previous_brush);
    }


    // Draw player
    QPixmap player(":/resources/images/Handle/Unit/player.png");
    QMatrix rm;
    rm.rotate(90-map->player->getDirection());
    int w = player.width(), h = player.height();
    player = player.transformed(rm);
    player = player.copy((player.width()-w)/2, (player.height()-h)/2, w, h);
    drawPixmap(paint, scroll_x-64, scroll_y-64, 128, 128, player);
}

void GameWidget::drawVision(QPainter& paint) {
    int visible_size = map->player->getVisibleSize();
    int visible_radius = map->grid_size*visible_size;

    paint.fillRect(0, 0, width()/2-visible_radius, height(), NOT_VISIBLE);
    paint.fillRect(width(), height(), -(width()/2-visible_radius), -height(), NOT_VISIBLE);
    paint.fillRect(width()/2-visible_radius, 0, 2*visible_radius, height()/2-visible_radius, NOT_VISIBLE);
    paint.fillRect(width()/2-visible_radius, height(), 2*visible_radius, -(height()/2-visible_radius), NOT_VISIBLE);

    if(map->player->getItemInventoryIndex(Item::ID::TORCH_LIT) != ITEM_NOT_EXIST) {
        fillRect(paint, scroll_x-visible_radius, scroll_y-visible_radius, 2*visible_radius, 2*visible_radius, VISIBLE_LIT);
    }else {
        fillRect(paint, scroll_x-visible_radius, scroll_y-visible_radius, 2*visible_radius, 2*visible_radius, VISIBLE);
    }

    /* for (int i = 0; i < map->getMaxWidth(); ++i) {
        for(int j = 0; j < map->getMaxHeight(); ++j) {
            if (map->player->isGridVisible(i, j))
                fillRect(paint, i*64, j*64, 64, 64, VISIBLE);
        }
    } */
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter paint{this};

    // Make the Map Background
    paint.drawPixmap(0, 0, width(), height(), ICONS[2]);

    // Draw Terrain and Grid lines on the grid
    drawMap(paint);

    // Draw Decoration on grid
    for (vector<Handle*>::const_iterator p = map->List.begin(); p != map->List.end(); ++p)
        //if (map->List[i]->getCategory() == Handle::Category::DECORATION)
        drawHandle(paint, *p);

    // Draw Player
    drawPlayer(paint);

    // Draw Vision
    drawVision(paint);
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

    TREE = new QPixmap [4] {{":/resources/images/Handle/Decoration/tree1.png"},
                            {":/resources/images/Handle/Decoration/tree2.png"},
                            {":/resources/images/Handle/Decoration/tree3.png"},
                            {":/resources/images/Handle/Decoration/tree4.png"}};

    GHOST = new QPixmap [4] {{":/resources/images/Handle/Unit/ghost1.png"}, {":/resources/images/Handle/Unit/ghost2.png"},
                       {":/resources/images/Handle/Unit/ghost1.png"}, {":/resources/images/Handle/Unit/ghost3.png"}};
}

void GameWidget::dealloc_icons() {
    delete [] ICONS;
    delete [] CAMPFIRE;
    delete [] TREE;
    delete [] GHOST;
}
