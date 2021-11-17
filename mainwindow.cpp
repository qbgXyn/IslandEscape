/* #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "City.h"

#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMainWindow>

const QString BTN_RELEASED_STYLE = "background-color: rgba(50, 127, 127, 255);";
const QString BTN_SELECTED_STYLE = "background-color: rgba(255, 255, 255, 255);";

MainWindow::MainWindow(City *const city, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        city(city),
        selected_side_menu_button(SideMenuButton::NAVIGATE),
        selected_overlay_button(OverlayButton::NORMAL),
        side_menu_status(SideMenuStatus::HIDDEN)
{
    ui->setupUi(this);

    initialize_overlay_buttons();
    initialize_side_menu_buttons();

    // Run main loop
    loop_timer = new QTimer{this };
    connect(loop_timer, &QTimer::timeout, this, &MainWindow::main_loop);
    // 20 updates per second
    loop_timer->start(20);

    ui->side_menu_move->move(303,0);
    ui->side_menu->setMaximumWidth(0);
}

void MainWindow::initialize_side_menu_buttons() {
    ui->btn_clinic->setText(ui->btn_clinic->text() + " $" + QString::number(Clinic::cost));
    ui->btn_hospital->setText(ui->btn_hospital->text() + " $" + QString::number(Hospital::cost));
    ui->btn_silver->setText(ui->btn_silver->text() + " $" + QString::number(SilverMine::cost));
    ui->btn_gold->setText(ui->btn_gold->text() + " $" + QString::number(GoldMine::cost));
    ui->btn_house->setText(ui->btn_house->text() + " $" + QString::number(House::cost));
    ui->btn_apartment->setText(ui->btn_apartment->text() + " $" + QString::number(Apartment::cost));

    // START OF YOUR IMPLEMENTATION

    // END OF YOUR IMPLEMENTATION
}

void MainWindow::initialize_overlay_buttons() {
    // START OF YOUR IMPLEMENTATION

    // END OF YOUR IMPLEMENTATION
}

MainWindow::~MainWindow() {
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete city;
}

MainWindow::SideMenuButton MainWindow::get_selected_side_menu_button() {
    return selected_side_menu_button;
}

MainWindow::OverlayButton MainWindow::get_selected_overlay_button() {
    return selected_overlay_button;
}

MainWindow::SideMenuStatus MainWindow::get_side_menu_status() {
    return side_menu_status;
}

void MainWindow::set_side_menu_status(SideMenuStatus status) {
    side_menu_status = status;
}

void MainWindow::on_side_menu_button_clicked(SideMenuButton button) {
    // START OF YOUR IMPLEMENTATION

    // END OF YOUR IMPLEMENTATION
}

void MainWindow::on_overlay_button_clicked(OverlayButton button) {
    // START OF YOUR IMPLEMENTATION

    // END OF YOUR IMPLEMENTATION
}

// This is called 20 times per second
void MainWindow::main_loop() {
    switch (side_menu_status) {
        case SideMenuStatus::HIDDEN:
            break;
        case SideMenuStatus::HIDDEN_TO_VISIBLE:
            ui->side_menu->setMaximumWidth(400);

            // START OF YOUR IMPLEMENTATION

            // END OF YOUR IMPLEMENTATION
            break;
        case SideMenuStatus::VISIBLE:
            break;
        case SideMenuStatus::VISIBLE_TO_HIDDEN:
            // START OF YOUR IMPLEMENTATION

            // END OF YOUR IMPLEMENTATION
            break;
    }
    ui->side_menu_move->setFixedWidth(ui->side_menu->width());
    ui->side_menu_move->setFixedHeight(ui->side_menu->height());

    ui->widget->loop();
}
*/
