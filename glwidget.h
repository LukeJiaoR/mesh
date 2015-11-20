#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <string>
#include <windows.h> 

#include "bspline.h"
#include "loadfilefor.h"
//#include <QOpenGLFunctions_4_3_Core>


class GLWidget : public QGLWidget    //protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

public:
     explicit GLWidget(QWidget *parent = 0);
     ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    int* NewMesh(QString fileName);



public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);



signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);



protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event );
	bool changepos0(double x, double);
    bool scalingtheMesh(float x);




private:
	LoadFile *FileOpen;
	std::string FileType;
    int xRot;
    int yRot;
    int zRot;
    float scaling;
	double pos0x, pos0y;
    QPoint lastPos;
    float y ;

};

#endif // QGLWIDGET_H
