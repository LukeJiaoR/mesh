#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "fileopen.h"
#include "objloader.h"
#include <QTextCodec>

#include <QtWidgets>

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


/*
QPushButton *MainWindow::createButton()
{
    QPushButton *button = new QPushButton("Open");
    return button;

}
*/

/*
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);

    QFile out("out.txt");
    if(!out.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
        }
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
        }
    headerTag = true;
    while(headerTag) {
            QString line = file.readLine();

            if(line.indexOf ("element vert") == 0  ){
                vertexNumber = line.section(" ",2,2).toInt();

            }
            if(line.indexOf ("element face") == 0){
                faceNumber = line.section(" ",2,2).toInt();

            }
            if(line.indexOf ("end_header") == 0){
                headerTag = false;

            }
    }


    for(int k = 0; k<vertexNumber ;k++)
    {
        QString line = file.readLine();
        //ui->textEdit->setText(line);



        //outS<<str<<"\n";


        //for (int j=0;j<3;j++)
        vertex[k][0]=line.section(" ",0,0).toFloat();
        vertex[k][1]=line.section(" ",1,1).toFloat();
        vertex[k][2]=line.section(" ",2,2).toFloat();


    }*/
    /*
    int face[10000000][3];
    for(int k = 0; k<faceNumber ;k++)
    {
        QString line = file.readLine();
        //ui->textEdit->setText(line);



        //outS<<str<<"\n";

        for (int i=0; i<faceNumber;i++){
            for (int j=0;j<3;j++)
            face[i][j]=line.section(" ",j,j).toFloat();

        }
    }*/

/*
    QTextStream out(&file);
    out<<vertex[0][0];
    out<<vertex[2][2];*/

/*

    file.close();
    out.close();
    return ;

}
    */



void MainWindow::on_actionOPEN_triggered()
{

   ui->widget->NewMesh();

}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        close();
    else
        QWidget::mousePressEvent(e);
}
