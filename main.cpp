#include "mainwindow.h"
#include <QApplication>
#include<iostream>
#include<QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextStream out(stdout);

    w.show();

    return a.exec();
}
