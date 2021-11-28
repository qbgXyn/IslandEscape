#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "Map/Map.h"

#include <QString>
#include <QPixmap>
#include <QFileDialog>
#include <string>

#include <iostream>
#include <QTextStream>
#include <QStringList>

#include <QRegularExpression>
//#include <QRegularExpressionMatch>

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

    bgm  = new QMediaPlayer();
    bgm->setMedia(QUrl("qrc:/resources/sound/main_bgm.mp3"));
    bgm->setVolume(40);
    bgm->play();

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

void MenuWindow::start_game(int selected_level, string filename) {
    Map* map;
    QString filePath;
    int width, height;
    switch (selected_level) {
        case 1: {
            width = 60;
            height = 60;
            filePath = ":/resources/world/Map1.txt";
            break;
        }
        case 2: {
            width = 12;
            height = 10;
            filePath = ":/resources/world/Map2.txt";
            break;
        }
        default: {
            width = 1;
            height = 1;
            break;
        }
    }
    map = new Map(width, height);
    map->player = reinterpret_cast<Survivor*>(map->createHandle(Handle::Type::SURVIVOR, 0, 0));
    MainWindow *m = new MainWindow{map, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    QFile file(filePath);
    QStringList numlist;
    QString match;

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!file.atEnd())
    {
        match = file.readLine();
//        qDebug() << match;
        numlist << match.split(' ');
    }
    file.close();
    // qDebug() << numlist;
    int x = 0, y = 0;
    foreach(QString num, numlist) {
        // std::cout << num.toInt();
        map->grid[y][x] = static_cast<Terrain::Type>(num.toInt());
        cout << y << " " << x << " " << num.toInt() << endl;
        ++x;
        if (x == width) {
            ++y;
            x = 0;
        }
    }

    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         cout << array[j][i] << " ";
    //     }
    //     cout << endl;
    // }


    close();
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

void MenuWindow::on_btn_start_clicked() {
    ui->pages->setCurrentWidget(ui->page_level_selection);
}

void MenuWindow::on_btn_level_1_clicked() {
    selected_level = 1;
    start_game(selected_level, "Map1.txt");
}
void MenuWindow::on_btn_level_2_clicked() {
    selected_level = 2;
    start_game(selected_level, "Map2.txt");
}
void MenuWindow::on_btn_level_3_clicked() {
    selected_level = 3;
    start_game(selected_level, "Map3.txt");
}
void MenuWindow::on_btn_level_4_clicked() {
    selected_level = 4;
    start_game(selected_level, "Map4.txt");
}
void MenuWindow::on_btn_level_5_clicked() {
    selected_level = 5;
    start_game(selected_level, "Map5.txt");
}
