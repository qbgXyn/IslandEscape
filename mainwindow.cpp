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
    // If need initialize

    // Run main loop
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &MainWindow::main_loop);
    // 20 updates per second
    loop_timer->start(20);
}

MainWindow::~MainWindow() {
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete map;
}

// This is called 20 times per second
void MainWindow::main_loop() {

}
