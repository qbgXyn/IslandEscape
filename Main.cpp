#include "mainwindow.h"
#include "menuwindow.h"

#include <QApplication>

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
