#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Map/Map.h"

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(Map *const map, QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

private:
    // Initialization functions, called in constructor

    void main_loop();

    Ui::MainWindow* ui;

    Map* const map;

    QTimer* loop_timer;

    friend class GameWidget;
};
#endif // MAINWINDOW_H
