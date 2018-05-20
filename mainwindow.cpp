#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init = mji.initializeJVM();
}

MainWindow::~MainWindow()
{
    mji.~MyJavaInterface();
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

        std::string path = ui->checkBox->isChecked() ? PATH_TO_ORIG_FILE : PATH_TO_SMALL_FILE;

        std::vector<double> numbers1 = myReader.findWord(word1.toStdString(), path);
        std::vector<double> numbers2 = myReader.findWord(word2.toStdString(), path);

        if(numbers1.size() == 300 && numbers2.size() == 300){
            double d = awv.getSimilarityMeasure(numbers1, numbers2);
            ui->lineResult->setText(QString::number(d));
        }else{
            ui->lineResult->setText("One or two word is missing");
        }
}

void MainWindow::on_buttonFile_clicked()
{
    ui->progressBar->setValue(0);
    QTextStream out(stdout);

    QString path = ui->linePathFile->text();

    if(path.isEmpty())
        return;

    ui->progressBar->setValue(5);

    if(this->init != 0){
        QMessageBox box;
        box.setText(QString("Error in inizialize JVM " + QString(init)));
        box.exec();
        return;
    }

    std::vector<MyWord*> words = mji.createVertex(path.toStdString());

    ui->progressBar->setValue(10);

    MyReadFile myReader;
    std::string pathToVocabulary = ui->checkBox->isChecked() ? PATH_TO_ORIG_FILE : PATH_TO_SMALL_FILE;
    myReader.findWords(words, pathToVocabulary, ui->progressBar);

    ui->progressBar->setValue(100);

    MyClustering mc;
    mc.clustering(words);

    for(int i = 0; i < words.size(); i++)
        delete words[i];
}
