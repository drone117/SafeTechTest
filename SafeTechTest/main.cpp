#include "mainwindow.h"

#include <QApplication>
#include <QFont>
#include <QFontDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/Fonts/Resources/PTSerif-Bold.ttf");
    QFontDatabase::addApplicationFont(":/Fonts/Resources/SegoeUIVariableStaticText.ttf");
    MainWindow w;
    w.show();
    return a.exec();
}
