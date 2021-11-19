#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "Map.h"

#include <QString>
#include <QPixmap>
#include <QFileDialog>

const QString NOT_PASSED_STYLE = "background-color: rgba(168, 50, 50, 255);";
const QString PASSED_STYLE = "background-color: rgba(50, 127, 50, 255);";

MenuWindow::MenuWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    // Scale label logo pixmap
    /* const QPixmap *p = ui->label_logo->pixmap();
    const int SCALE = 4;
    ui->label_logo->setPixmap(p->scaled(p->width() * SCALE, p->height() * SCALE)); */
    initialize_level_btn();

    // Set pixmap for increase and decrease size buttons
    /* QPixmap increase {":/resources/images/next.png"};
    QPixmap decrease = increase.transformed(QTransform().rotate(180));
    ui->btn_increase_size->setIcon(increase);
    ui->btn_decrease_size->setIcon(decrease); */
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

/* void MenuWindow::start_game(City* city) {
    MainWindow *m = new MainWindow{city, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    close();
} */

void MenuWindow::initialize_level_btn() {
    ui->btn_level_1->setStyleSheet(NOT_PASSED_STYLE);
    ui->btn_level_2->setStyleSheet(NOT_PASSED_STYLE);
    ui->btn_level_3->setStyleSheet(NOT_PASSED_STYLE);
    ui->btn_level_4->setStyleSheet(NOT_PASSED_STYLE);
    ui->btn_level_5->setStyleSheet(NOT_PASSED_STYLE);
    if (level_1 == true)
        ui->btn_level_1->setStyleSheet(PASSED_STYLE);
    if (level_2 == true)
        ui->btn_level_2->setStyleSheet(PASSED_STYLE);
    if (level_3 == true)
        ui->btn_level_3->setStyleSheet(PASSED_STYLE);
    if (level_4 == true)
        ui->btn_level_4->setStyleSheet(PASSED_STYLE);
    if (level_5 == true)
        ui->btn_level_5->setStyleSheet(PASSED_STYLE);
}

void MenuWindow::on_btn_start_clicked() {
    ui->pages->setCurrentWidget(ui->page_level_selection);
    /* Map* map = new Map(12,12);
    start_game(map); */
}

void MenuWindow::on_btn_level_1_clicked() { selected_level = 1; }
void MenuWindow::on_btn_level_2_clicked() { selected_level = 2; }
void MenuWindow::on_btn_level_3_clicked() { selected_level = 3; }
void MenuWindow::on_btn_level_4_clicked() { selected_level = 4; }
void MenuWindow::on_btn_level_5_clicked() { selected_level = 5; }
