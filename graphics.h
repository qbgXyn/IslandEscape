/**
* Utilities for graphics and display
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Map.h"
#include "mainwindow.h"

#include <QPixmap>
#include <QWidget>

class GameWidget: public QWidget {
public:
    GameWidget(QWidget* parent = nullptr);
    ~GameWidget();

    GameWidget(const GameWidget&) = delete;
    GameWidget& operator=(const GameWidget&) = delete;

    // Loop, called by main_loop() in MainWindow
    void loop();

protected:
    // Handle drawing
    virtual void paintEvent(QPaintEvent* event) override;

    // Handle WASD keys for navigation
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

    // Handle mouse scrolling for magnification
    virtual void wheelEvent(QWheelEvent* event) override;

    // Handle mouse clicks
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    // Handle mouse movement
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    // Obtain the display coordinates from the 'real' coordinates
    void to_display_coordinates(int x, int y, int& dispx, int& dispy);

    // Obtain the 'real' coordinates from the display coordinates
    void to_real_coordinates(int dispx, int dispy, int& x, int& y);

    // Obtain the coordinates of the grid (2D array index) from display coordinates
    void obtain_grid_coordinates(int dispx, int dispy, int& x, int& y);

    // Obtain the coordinates of the grid (2D array index) from real coordinates
    void obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y);

    void drawLine(QPainter& paint, int x1, int y1, int x2, int y2);
    void drawPixmap(QPainter& paint, int x, int y, int w, int h, const QPixmap&);
    void fillRect(QPainter& paint, int x, int y, int w, int h, const QBrush&);

    // Load and unload icons
    void load_icons();
    void dealloc_icons();

    //City *const city;
    int grid_size;

    // Scrolling
    int scroll_x, scroll_y;
    // Magnification
    float scale;

    // Keys pressed
    bool UP, DOWN, LEFT, RIGHT;

    int tick; // City ticks (number of calls of loop function) elapsed since the beginning of the program
    // Used for animating blinking effects

    // The coordinates of the grid on which the mouse is hovering
    int hovering_grid_x;
    int hovering_grid_y;

    // Icons sorted according to the enum BuildingType
    QPixmap* ICONS;
};

#endif // GRAPHICS_H
