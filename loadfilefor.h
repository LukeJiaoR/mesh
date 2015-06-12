#ifndef LOADFILEFOR_H
#define LOADFILEFOR_H


#include <qfile.h>
#include <QtOpenGL>


#include "LoadFile.h"

class LoadFileFOr : public LoadFile
{
public:
    LoadFileFOr();
    void Load(QString filename);
    void Draw() ;
	int sizex(){ return vertsize; }
	int sizey(){ return facesize; }

protected:

private:
    GLfloat   Verts[100000][5];
    int   Faces[100000][5];

    int vertsize;
    int facesize;
};

#endif // LOADFILEFOR_H
