#include "loadfilefor.h"
#include <QFile>

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <ui_mainwindow.h>
LoadFileFOr::LoadFileFOr()
{
    vertsize = 0;
    facesize = 0;
}
void LoadFileFOr::Load(QString filename)
{
    QFile inf(filename);
    if (!inf.open(QIODevice::ReadWrite)) {
         std::cout<< "[!] Failed to Open File!"<<std::endl;
    }
    if(filename.section(".",-1,-1)=="nrb"){
       std::cout <<2<<std::endl;
    }
    if(filename.section(".",-1,-1)=="ply"){
       std:: cout <<2<< std::endl;
    }

    QTextStream in(&inf);
    bool headerEndTag = false;

    int putVert = 0;
    int putFace = 0;
    while(!in.atEnd()){
        QString Line = in.readLine();

        if(Line.section(" ",0,0)=="element"){
            if(Line.section(" ",1,1) == "vertex"){
                vertsize = Line.section(" ",2,2).toInt();
                //std::cout<<"vertsize"<< vertsize << std::endl;


            }
            if(Line.section(" ",1,1)=="face"){
                facesize  = Line.section(" ",2,2).toInt();
                std::cout<<"facesize"<<facesize<< std::endl;
            }

        }
        if(Line.section(" ",0,0)=="end_header"){
            headerEndTag = true;
            continue;
        }
        if(Line ==NULL) continue;


        if(headerEndTag&&putVert<vertsize&&vertsize){

            for(int i=0;i < 3;i++){
                Verts[putVert][i] = Line.section(" ",i,i).toFloat();
            }
            putVert++;

            if(putVert == vertsize) continue;
        }

        if(headerEndTag&&putFace<facesize&&facesize&&putVert>=vertsize){
            Faces[putFace][0] = Line.section(" ",0,0).toInt();
            int vertNumOfFace = Faces[putFace][0];
            for(int i=1;i <= vertNumOfFace;i++){
                Faces[putFace][i] = Line.section(" ",i,i).toInt();
            }
            putFace ++;
            if(putFace == facesize) continue;
        }
    }


    inf.close();

}
void LoadFileFOr::Draw() 
{
    for(int p =0;p < facesize;p++)  //画图
    {
         glBegin(GL_POLYGON);
         int vertsNumOfFace = Faces[p][0];
         for(int u  = 1; u<=vertsNumOfFace; u++){

             int k =Faces[p][u];

              glVertex3f(Verts[k][0],Verts[k][1],Verts[k][2]);


         }

         glEnd();
    }



}
