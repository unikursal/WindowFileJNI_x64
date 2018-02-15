#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myreadfile.h"
#include "myjavainterface.h"
#include "actionswithvectors.h"

#include <QApplication>
#include <QMessageBox>
#include <QTextStream>

#include<iostream>
#include<cstring>
#include<windows.h>
#include<list>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init = mji.initializeJVM();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("");

        QString word1 = ui->lineFirstWord->text();
        QString word2 = ui->lineSecondaryWord->text();

        if(word1.isEmpty() || word2.isEmpty()){
            QMessageBox box;
            box.setText("Input all words");
            box.exec();
            return;
        }

        MyReadFile myReader;
        ActionsWithVectors awv;

        SYSTEMTIME t1, t2;

        std::string path = ui->checkBox->isChecked() ? PATH_TO_ORIG_FILE : PATH_TO_SMALL_FILE;

        GetSystemTime(&t1);
        std::vector<double> numbers1 = myReader.findWord(word1.toStdString(), path);
        std::vector<double> numbers2 = myReader.findWord(word2.toStdString(), path);

        if(numbers1.size() == 300 && numbers2.size() == 300){
            double d = awv.getSimilarityMeasure(numbers1, numbers2);
            ui->lineResult->setText(QString::number(d));
        }else{
            ui->lineResult->setText("One or two word is missing");
        }
        GetSystemTime(&t2);

        QString time = "milisecond : second : minute\n" +  QString::number(t1.wMilliseconds) + " : " +
                QString::number(t1.wSecond) + " : " + QString::number(t1.wMinute) + "\n" + QString::number(t2.wMilliseconds) + " : " +
                QString::number(t2.wSecond) + " : " + QString::number(t2.wMinute) + "\n";

        ui->label->setText(time);
}

void MainWindow::on_buttonFile_clicked()
{
    ui->progressBar->setValue(0);
    QTextStream out(stdout);
    SYSTEMTIME t1, t2;

    QString path = ui->linePathFile->text();

    if(path.isEmpty())
        return;

    GetSystemTime(&t1);

    ui->progressBar->setValue(5);

    if(init != 0){
        QMessageBox box;
        box.setText(QString("Error in inizialize JVM " + QString(init)));
        box.exec();
        return;
    }

    std::vector<std::vector<double>> weights;
    std::vector<Vertex*> vertex = mji.createVertex(path.toStdString());

    ui->progressBar->setValue(10);

    std::list<MyPair> words;
    for(int i = 0; i < vertex.size(); i++){
        if(vertex[i]->getWords().size() > 0){
            QString qstr = vertex[i]->getWords().at(0);
            words.push_back({i,qstr.toStdString()});
        }
    }

    mji.~MyJavaInterface();

    MyReadFile myReader;
    std::string pathToVocabulary = ui->checkBox->isChecked() ? PATH_TO_ORIG_FILE : PATH_TO_SMALL_FILE;
    weights = myReader.findWords(words, pathToVocabulary, ui->progressBar);

    GetSystemTime(&t2);
    QString time = "milisecond : second : minute\n" +  QString::number(t1.wMilliseconds) + " : " +
            QString::number(t1.wSecond) + " : " + QString::number(t1.wMinute) + "\n" + QString::number(t2.wMilliseconds) + " : " +
            QString::number(t2.wSecond) + " : " + QString::number(t2.wMinute) + "\n";
    ui->label->setText(time);

    ui->progressBar->setValue(100);

    int zero = 0, k = 0;

    for(int i = 0; i < weights.size(); i++){
        for(int j = 0; j < 300; j++){
            if(weights[i][j] == 0)
                k++;
        }

        if(k == 300){
            zero++;
            k = 0;
        }
    }

    for(int i = 0; i < vertex.size(); i++)
        delete vertex[i];

    out<<weights.size()<<"   size and zero " + QString::number(zero) + "\n";

}
