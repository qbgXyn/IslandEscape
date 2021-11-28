//Mainwindow ui for gui. It will call map constructor to build the map and start game loop.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Map/Map.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui { class MainWindow; }

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(Map *const map, QMediaPlayer *bgm, QWidget *parent = nullptr); //constructor
    ~MainWindow(); //destructor

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

private:
    // Initialization functions, called in constructor
    void init_Information();
    void init_Inventory();
    void init_Current_Item();

    void main_loop(); //basic settings

    Ui::MainWindow* ui;

    Map *const map;

    QTimer* loop_timer;

    friend class GameWidget;
    QMediaPlayer *bgm;
    QMediaPlaylist *bgmList;

    int game_time;
    int torch_time;
};
#endif // MAINWINDOW_H
