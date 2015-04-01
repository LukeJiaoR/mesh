#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "fileopen.h"
#include "objloader.h"
#include <QTextCodec>

#include <QtWidgets>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

/*
    glWidget = new GLWidget;

    button = createButton();

    //connect(button,
    //        &QPushButton::clicked,
     //       glWidget,
     //       SLOT(NewMesh())
      //      );


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(button);
    setLayout(mainLayout);
*/
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
                                                    tr("Mesh Files (*.obj *.ply);;ALL(*);;C++ Files (*.cpp *.h)")
                                                    );
    int *size;


    size  = ui->widget->NewMesh(fileName);
    ui->showFilename->setText(fileName);
    std::cout<< size[0] << std::endl;

    QString s = QString::number(size[0],10);
    ui->vertsnum->setText(s);


}

void MainWindow::mousePressEvent(QMouseEvent *e)
{

        QWidget::mousePressEvent(e);
}
/*
void MainWindow::wheelEvent(QWheelEvent *e)
{

        QWidget::wheelEvent(e);

        std::cout<< "do it"<<std::endl;
}
*/

void MainWindow::on_actionQUIT_triggered()
{
    close();
}
