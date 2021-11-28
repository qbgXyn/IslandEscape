#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Map/Map.h"

#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMainWindow>

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
    loop_timer->start(GAME_INTERVAL);
}

MainWindow::~MainWindow() {
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete map;
}

// This is called 50 times per second
void MainWindow::main_loop() {
    game_time = map->getGameTime();
    torch_time = map->player->getTorchTime();
//    int torch_time = 10;
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
    ui->label_time->setText(": " + QString::number(game_time/GAME_TICK) + "s");
    ui->label_torch->setText(": " + QString::number(torch_time/GAME_TICK) + "s");
//    ui->label_torch->setText(": " + QString::number(50/GAME_TICK) + "s");
    ui->widget->loop();
}
