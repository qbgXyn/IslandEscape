#include "mainwindow.h"
#include "menuwindow.h"

#include <QApplication>

const int GAME_TICK = 20; // update time per second (update once per 1/20 = 0.05s)

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    /**
    * Run menu window first
    */
    MenuWindow m;
    m.show();

    return a.exec();
}
