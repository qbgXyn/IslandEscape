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
    if (map->get_game_time() >= 1)
        map->set_game_time(map->get_game_time() - 1);
    if (map->get_torch_time() >= 1)
        map->set_torch_time(map->get_torch_time() - 1);
    ui->label_health->setText(": 100");
    ui->label_time->setText(": " + QString::number(map->get_game_time()/50) + "s");
    ui->label_torch->setText(": " + QString::number(map->get_torch_time()/50) + "s");
    ui->widget->loop();
}
