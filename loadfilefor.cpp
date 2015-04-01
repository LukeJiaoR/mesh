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
    QTextStream in(&inf);
    bool headerEndTag = false;

    int putVert = 0;
    int putFace = 0;
    while(!in.atEnd()){
        QString Line = in.readLine();

        if(Line.section(" ",0,0)=="element"){
            if(Line.section(" ",1,1) == "vertex"){
                vertsize = Line.section(" ",2,2).toInt();
                //std::cout<<"vertsize"<<vertsize<< std::endl;

            }
            if(Line.section(" ",1,1)=="face"){
                facesize = Line.section(" ",2,2).toInt();
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
            //std::cout<<"11"<< std::endl;
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

            //std::cout<<"22"<< std::endl;
        }


    }
/*
    for(int f=0;f<putVert;f++)
    {

       for (int g=0; g<3;g++)
         {   std::cout<<g <<":"<< Verts[f][g]<<" ";}
       std::cout<<"~~"<< std::endl;
    }
    for(int f=0;f<putFace;f++)
    {

       for (int g=0; g<5;g++)
         {   std::cout<<g <<":"<< Faces[f][g]<<" ";}
       std::cout<<"~~"<< std::endl;
    }
*/

    inf.close();

}
void LoadFileFOr::draw(int p) const
{
    /*
    for(int p =0;p < this->facesize;p++){


        glBegin(GL_POLYGON);
        int vertsNumOfFace = Faces[p][0];
        for(int u  = 1; u<=vertsNumOfFace; u++){

            int k =Faces[p][u];

             glVertex3f(Verts[k][0],Verts[k][1],Verts[k][2]);
             //if(Verts[k][0]==0)
             //    std::cout<< k << endl;

        }
        glEnd();
    }
    */
    int vertsNumOfFace = Faces[p][0];
    for(int u  = 1; u<=vertsNumOfFace; u++){

        int k =Faces[p][u];

         glVertex3f(Verts[k][0],Verts[k][1],Verts[k][2]);
         //if(Verts[k][0]==0)
         //    std::cout<< k << endl;

    }
}
