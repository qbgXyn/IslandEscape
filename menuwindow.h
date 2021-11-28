//The place where link buttom with functions
#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "Map/Map.h"

#include <QMainWindow>
#include <string>
#include <QMediaPlayer>

#include <QFile>

namespace Ui { class MenuWindow; }

class MenuWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    void start_game(int selected_level, string filename);

    void initialize_level_btn();

    Ui::MenuWindow *ui;

    QMediaPlayer *bgm;

    // Store the selected level in this variable
    int selected_level{0};

    bool level_1{false}; //set level to false first so that user need to click a level first before starting game
    bool level_2{false};
    bool level_3{false};
    bool level_4{false};
    bool level_5{false};

private slots: //buttom to click level and start game

    void on_btn_start_clicked();

    void on_btn_level_1_clicked();
    void on_btn_level_2_clicked();
    void on_btn_level_3_clicked();
    void on_btn_level_4_clicked();
    void on_btn_level_5_clicked();

};

#endif // MENUWINDOW_H
