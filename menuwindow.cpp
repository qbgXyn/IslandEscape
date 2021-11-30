#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "Map/Map.h"

#include <QString>
#include <QPixmap>
#include <string>

#include <iostream>
#include <vector>

#include <QMessageBox>
//#include <QPainter>

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

    bgmList = new QMediaPlaylist();
    bgm = new QMediaPlayer();
    bgm->setPlaylist(bgmList);
    bgmList->addMedia(QUrl("qrc:/resources/sound/main_bgm.wav"));
    bgmList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    bgmList->setCurrentIndex(0);
    bgm->setVolume(40);
    bgm->play();

//    QPixmap pixmap;
//    QPainter paint(this);
//    pixmap.load(":/resources/images/UI/dark_background.png");
//    int w = ui->centralwidget->width();
//    int h = ui->centralwidget->height();
//    pixmap = pixmap.scaled(w, h, Qt::KeepAspectRatioByExpanding);
//    paint.drawPixmap(0, 0, pixmap);


    // Set pixmap for increase and decrease size buttons
    /* QPixmap increase {":/resources/images/next.png"};
    QPixmap decrease = increase.transformed(QTransform().rotate(180));
    ui->btn_increase_size->setIcon(increase);
    ui->btn_decrease_size->setIcon(decrease); */
}

MenuWindow::~MenuWindow()
{
    delete ui;
    delete bgm;
    delete bgmList;
}

void MenuWindow::start_game(int selected_level, string filename, string handleFilename) {
    Map* map;
    QString filePath;
    QString HandleFilePath;
    int width, height;
    filename = ":/resources/world/"+filename;
    handleFilename = ":/resources/world/"+handleFilename;
    switch (selected_level) {
        case 1: {
            width = 60;
            height = 60;
            filePath = QString::fromStdString(filename);
            HandleFilePath = QString::fromStdString(handleFilename);
            break;
        }
        case 2: {
            width = 60;
            height = 60;
            filePath = QString::fromStdString(filename);
            HandleFilePath = QString::fromStdString(handleFilename);
            break;
        }
        default: {
            width = 1;
            height = 1;
            break;
        }
    }
    map = new Map(width*64, height*64, filePath, HandleFilePath);
    MainWindow *m = new MainWindow{map, this, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    bgm->stop();
}

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

void MenuWindow::clear_level() {
    switch(selected_level) {
        case 1:
            level_1 = true;
            break;
        case 2:
            level_2 = true;
            break;
        case 3:
            level_3 = true;
            break;
        case 4:
            level_4 = true;
            break;
        case 5:
            level_5 = true;
            break;
    }
}

void MenuWindow::on_btn_start_clicked() {
    ui->pages->setCurrentWidget(ui->page_level_selection);
}

void MenuWindow::on_btn_level_1_clicked() {
//    selected_level = 1;
//    start_game(selected_level, "Map2.txt", "HandleList2.txt");
    QMessageBox *mb = new QMessageBox{window()};
    mb->setWindowTitle("Island escape");
    mb->setStyleSheet("font: 14pt \"Comic Sans MS\"; color : gray");
    mb->setText(QString::fromStdString("BACKGROUND:\n"
                                       "you're lost on an island\n"
                                       "but you realized that the island is not that \"normal\"...\n"
                                       "Be a survivor, find a boat and a key to turn it on in order to escape from the ghostly island."));
    mb->setAttribute(Qt::WA_DeleteOnClose, true);
    mb->exec();

}
void MenuWindow::on_btn_level_2_clicked() {
    selected_level = 2;
    start_game(selected_level, "Map1.txt", "HandleList1.txt");
}
void MenuWindow::on_btn_level_3_clicked() {
    return; // not finished, so cannot click
    selected_level = 3;
    start_game(selected_level, "Map3.txt", "HandleList3.txt");
}
void MenuWindow::on_btn_level_4_clicked() {
    return; // not finished, so cannot click
    selected_level = 4;
    start_game(selected_level, "Map4.txt", "HandleList4.txt");
}
void MenuWindow::on_btn_level_5_clicked() {
    return; // not finished, so cannot click
    selected_level = 5;
    start_game(selected_level, "Map5.txt", "HandleList5.txt");
}
