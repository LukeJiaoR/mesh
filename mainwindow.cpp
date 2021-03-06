#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "fileopen.h"
#include <QTextCodec>

#include <QtWidgets>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionOPEN_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                                                    this,
                                                    tr("Open File"),
                                                    QString(),
                                                    tr("Mesh Files (*.ply);;ALL(*);;Nurbs Files(*.nrb)")
                                                    );



    int *size;
    //loadforobj loadFile;
    //loadFile.load(filename);
    size  = ui->widget->NewMesh(fileName);  //NewMesh中对文件进行处理
    ui->textFileName->setText(fileName);
    QString vertNum = QString::number(size[0],10);
    QString faceNum = QString::number(size[1],10);
    ui->textVertsNum-> setText(vertNum);
    ui->textFaceNum->setText(faceNum);



}

void MainWindow::mousePressEvent(QMouseEvent *e)
{

        QWidget::mousePressEvent(e);
}

void MainWindow::on_actionQUIT_triggered()
{
    close();
}

