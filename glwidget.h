#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>


#include "objloader.h"



class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
     explicit GLWidget(QWidget *parent = 0);
     ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void NewMesh();



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



private:
    sp::ObjLoader *FileOpen;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;



    /*
    QtLogo *logo;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtGreen;*/
    //QColor qtPurple;
};

#endif // QGLWIDGET_H
