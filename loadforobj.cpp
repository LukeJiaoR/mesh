#include "loadforobj.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <map>


using namespace std;



int vertsize = 0;
int facesize = 0;
loadforobj::loadforobj()
{
}
void loadforobj::load(char* filename)
{
    ifstream inf;
    inf.open(filename,ios_base::in);
    if(!inf.is_open()){
        cerr<<"[!] Failed to load file:"<< filename <<endl;
    }
    std::cout << "Success to load file " <<filename<<endl;
    vertsize = 0;
    facesize = 0;
    bool tag = false;
    int i = 0;
    int j = 0;

    char *delims = " \n\r";
    const unsigned int CHARACTER_COUNT = 500;
    char line[CHARACTER_COUNT] = {0};

    while(inf.good()){

        memset((void*)line,0,CHARACTER_COUNT);
        inf.getline(line,CHARACTER_COUNT);
        if(inf.eof()) break;

        char *token = strtok(line,delims);
        char *tokenElement = strtok(line+8,delims);



        if(token ==NULL
                ||strcmp(token,"property") == 0
                ||strcmp(token,"comment") == 0
                ||strcmp(token,"format") == 0
                )

            continue;
        else

        if(strcmp(token,"end_header") == 0){
            std::cout << "while " <<token<<endl;
            tag = true;
            continue;
        }


        else
        if(strcmp(token,"element") == 0){
            //
            std::cout << "while" <<token<<endl;
            if(strcmp(tokenElement,"vertex")== 0){
                sscanf(line+15,"%d",&vertsize);
                std::cout << "while " <<tokenElement<<endl;
            }

            else if(strcmp(tokenElement,"face")== 0){
                 sscanf(line+13,"%d",&facesize);
                 std::cout << "while " <<tokenElement<<endl;
            }

        }
        /*
        else
        if(strcmp(token,"element face")==0)
            sscanf(line+13,"%d",&facesize);
            */
        else
        if(tag && i <vertsize){
            //std::cout << "vertsize " <<endl;


            //sscanf(line,"%f* %f %f",&Verts[i][0],&Verts[i][1],&Verts[i][2]);
            sscanf(line,"%f ",&Verts[i][0]);
            sscanf(line," %f %f %f %f",&Verts[i][1]);
            sscanf(line," %f %f %f",&Verts[i][0],&Verts[i][1],&Verts[i][2]);



            i++;

        }

        else
        if(tag && i >= vertsize && j < facesize){
            sscanf(line,"%d %d %d",&Faces[j][0],&Faces[j][1],&Faces[j][2]);
            j++;
        }


    }

std::cout << vertsize << i <<endl;
std::cout << facesize << j <<endl;

      for(int f=0;f<i;f++)
      {

         for (int g=0; g<3;g++)
           {   std::cout<<g <<":"<< Verts[f][g];}
         std::cout<<"~~"<< endl;
      }



}
void loadforobj::draw() const
{

    for(int p =0;p < facesize;p++){

        glColor3f(0.5f,0.5f,0.5f);
        glBegin(GL_TRIANGLES);


        for(int u  = 0; u<3; u++){

            int k =Faces[p][u];

             glVertex3f(Verts[k][0],Verts[k][1],Verts[k][2]);
             //if(Verts[k][0]==0)
             //    std::cout<< k << endl;



        }
        glEnd();
       // std::cout << "Success to DRAW GL_TRIANGLES " <<endl;
    }

    //std::cout << "Success to DRAW glDrawElements "<< endl;


}
