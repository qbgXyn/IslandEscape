#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Map/Map.h"

#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMainWindow>

const QString BTN_RELEASED_STYLE = "background-color: rgba(50, 127, 127, 255);";
const QString BTN_SELECTED_STYLE = "background-color: rgba(255, 255, 255, 255);";

MainWindow::MainWindow(Map *const map, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        map(map)
{
    ui->setupUi(this);

    // Run main loop
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &MainWindow::main_loop);
    // 50 updates per second
    loop_timer->start(20);
}

MainWindow::~MainWindow() {
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete map;
}

// This is called 50 times per second
void MainWindow::main_loop() {
    int game_time = map->getGameTime();
    int torch_time = map->player->getTorchTime();
    if (game_time > 0)
        map->setGameTime(game_time - 1);
    if (torch_time > 0 && map->player->hasItem(Item::ID::TORCH_LIT)) {
        if (torch_time - 1 >= 0) {
            map->player->setTorchTime(torch_time - 1);
        }else {
            map->player->switchTorchState();
        }

    }
    ui->label_health->setText(": 100");
    ui->label_time->setText(": " + QString::number(game_time/50) + "s");
    ui->label_torch->setText(": " + QString::number(torch_time/50) + "s");
    ui->widget->loop();
}
