#ifndef LOADFILEFOR_H
#define LOADFILEFOR_H

#include <qfile.h>
#include <QtOpenGL>

/*
struct Point{
    float x;
    float y;
    float x;
    float other1;
    float other2;
};
*/

class LoadFileFOr
{
public:
    LoadFileFOr();
    void Load(QString filename);
    void draw(int p) const;
    int sizeOfVerts(){ return vertsize;}
    int sizeOfFaces(){ return facesize; }

protected:

private:
    GLfloat   Verts[100000][5];
    int   Faces[100000][5];

    int vertsize;
    int facesize;
};

#endif // LOADFILEFOR_H
