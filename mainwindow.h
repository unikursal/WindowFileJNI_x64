#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myjavainterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int getInit();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_buttonFile_clicked();

private:
    Ui::MainWindow *ui;
    MyJavaInterface mji;
    int init;

};

#endif // MAINWINDOW_H
