#ifndef LOADFOROBJ_H
#define LOADFOROBJ_H

#include <QtOpenGL>

class loadforobj
{
public:
    loadforobj();

    void load(char* filename);
    void draw() const;

protected:

private:
    float Verts[100000][5];
    int   Faces[100000][3];

    int vertsize;
    int facesize;
};




#endif // LOADFOROBJ_H
