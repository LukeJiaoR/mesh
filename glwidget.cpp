#include <iostream>
#include <QtOpenGL>
#include <math.h>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    xRot = 0;
    yRot = 0;
    zRot = 0;
    //qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}
GLWidget::~GLWidget()
{
}
QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}
//! [2]

//! [3]
QSize GLWidget::sizeHint() const
//! [3] //! [4]
{
    return QSize(400, 400);
}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

//! [5]
void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}
//! [5]

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::initializeGL()
{

    glClearColor(1.0,1.0,1.0,1.0);
    FileOpen = new sp::ObjLoader();
    //FileOpen->load("F:\\model\\CUBE.obj");




    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, 0.0);
    /*
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin (GL_POLYGON);

          glVertex2i(40, 40);
          glVertex2i(10, 40);
          glVertex2i(10, 10);
          glVertex2i(40, 10);
          std::cout<<"hereGL-POLYGON"<<endl;
        glEnd ();*/
    //glClear(GL_COLOR_BUFFER_BIT);
   // glColor3f(1.0,1.0,1.0);
   // glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);



    //FileOpen = new sp::ObjLoader();
    //FileOpen->load("F:\\model\\obj.obj");
    FileOpen->draw();




}


void GLWidget::resizeGL(int width, int height)
{

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-50.0, +50.0, -50.0, +50.0, -50.0, 50.0);//设置显示三围裁切空间

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::NewMesh()
{
    QString fileName = QFileDialog::getOpenFileName(
                                                    this,
                                                    tr("Open File"),
                                                    QString(),
                                                    tr("Mesh Files (*.obj *.ply);;ALL(*);;C++ Files (*.cpp *.h)")
                                                    );
    FileOpen = new sp::ObjLoader();


   // QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
   // QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
   if (!fileName.isEmpty())
    {
    //将QString 转为 char 路径不能有中文
    char* file;
    QByteArray ba = fileName.toLatin1();
    file=ba.data();
    FileOpen->load(file);
    updateGL();

   }
}
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}
//! [9]

//! [10]
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::MiddleButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
