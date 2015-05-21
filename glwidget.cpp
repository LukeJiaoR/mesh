#include <iostream>
#include <QtOpenGL>
#include <math.h>
#include <gl/glu.h>


#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    xRot = 0;
    yRot = 0;
    zRot = 0;

    scaling =  1;


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

void GLWidget::scalingtheMesh(float x)
{

    std::cout<< "after"<< x << std::endl;


    scaling += x/2.0;
    updateGL();
}

void GLWidget::initializeGL()
{
   // initializeOpenGLFunctions();


    glClearColor(0.1,0.5,0.5,0.0);
    glClearDepth(1.0f);


    //FileOpen = new LoadFileFOr();
	FileOpen = new Bspline();



   //glEnable(GL_BLEND);	                             //混色
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_COLOR_MATERIAL);            //颜色追踪


    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);         // 真正精细的透视修正

    //static GLfloat lightPosition[4] = { 9.0, 9.0, 7.0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


    GLfloat LightPosition[]= { 0.0f, 0.0f, 10.0f, 1.0f };


    GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };          // 环境光参数
    GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };          // 漫射光参数
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


   // int facesize;
   // facesize = FileOpen->sizeOfFaces();

    glTranslatef(0.0, 0.0, 0.0);           //平移
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);  //旋转
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glScalef(scaling,scaling,scaling);      //放大缩小
    //glScalef(0.5,0.5,0.5);
    glColor3f(1.0f,0.7f,0.5f);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE   ); //画线模式



   // FileOpen->draw();
	FileOpen->DrawBSpline();





}


void GLWidget::resizeGL(int width, int height)
{


    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    //glViewport(0, 0, (GLint)width, (GLint)height);
    std::cout << width<<height<< std::endl;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();



    glOrtho(-2.00, +2.00, -2.00, +2.00, -2.01, 2.01);//设置显示三围裁切空间

    glMatrixMode(GL_MODELVIEW);

}

int* GLWidget::NewMesh(QString fileName)
{
	
   // if(fileName.section(".",-1,-1)=="nrb"){     //判断曲线NURBS文件nrb
       FileType = "nrb";
       std::cout <<2<<std::endl;
	   FileOpen = new Bspline();
       if (!fileName.isEmpty())
       {
		   FileOpen->Load(fileName);
           updateGL();
       }
       int *size;
       size = new int [2];
	   size[0] = FileOpen->sizeOfPi();
	   size[1] = FileOpen->sizeofknots();
       return size;
   // }
   /* if(fileName.section(".",-1,-1)=="ply"){         //判断网格mesh文件ply
        FileOpen = new LoadFileFOr();
        if (!fileName.isEmpty())
        {
            FileOpen->Load(fileName);
            updateGL();
        }
        int *size;
        size = new int [2];
        size[0]=FileOpen->sizeOfVerts();
        std::cout<< FileOpen->sizeOfVerts()<<std::endl;
        size[1]=FileOpen->sizeOfFaces();
        return size;   //返回需要填入UI的信息
    }*/

}
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);  
    }
    lastPos = event->pos();
}
void GLWidget::wheelEvent(QWheelEvent *event)
{

    QPoint numDegrees = event->angleDelta() / 8;

        if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
             scalingtheMesh(numSteps.ry());

        }
        event->accept();

}
