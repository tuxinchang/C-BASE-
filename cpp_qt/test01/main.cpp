#include "mainwindow.h"
#include "widget.h"
#include "widget_plus.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //Widget w;
    Widget_plus w;
    w.show();
    return a.exec();
}
