#include "mainwindow.h"
#include <QApplication>
#include<iostream>
#include<QTextStream>

#include "myclustering.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextStream out(stdout);

    MyClustering mc;
    mc.clustering();

    w.show();

    return a.exec();
}
