/*
//This part is the main game running part. Nothing special. :)
*/
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
    a.setWindowIcon(QIcon(":/resources/images/UI/icon.ico"));

    return a.exec();
}
