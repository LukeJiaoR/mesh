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
    initializeOpenGLFunctions();


    glClearColor(0.1,0.5,0.5,0.0);
    glClearDepth(1.0f);

    FileOpen = new LoadFileFOr();



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


    int facesize;
    facesize = FileOpen->sizeOfFaces();

    glTranslatef(0.0, 0.0, 0.0);           //平移
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);  //旋转
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glScalef(scaling,scaling,scaling);      //放大缩小
    //glScalef(0.5,0.5,0.5);
    glColor3f(1.0f,0.7f,0.5f);
    glPolygonMode(GL_FRONT_AND_BACK   ,GL_LINE   ); //画线模式

    GLfloat vertices[] = {
    -1.0, -1.0, -1.0 ,
    -1.0, -1.0, 1.0 ,
    -1.0, 1.0, -1.0 ,
    -1.0, 1.0, 1.0 ,
    1.0, -1.0, -1.0 ,
    1.0, -1.0, 1.0 ,
    1.0, 1.0, -1.0 ,
    1.0, 1.0, 1.0 ,
    };
    static GLshort frontIndices[] = {0, 1, 3, 2};

    glGenBuffers(3,buffers);//创建3块buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);//先将第一块buffer绑定到当前
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);//将顶点数组放入这个buffer
    glVertexPointer(3, GL_FLOAT, 0, 0);//指定这个buffer的格式，3代表3个float值为一个顶点，第一个0代表跨度，这里数值是紧密排列的，最后一个是数组的入口地址*point，由于已经将buffer绑定到当前，所以填0
    glEnableClientState(GL_VERTEX_ARRAY);//使用这个buffer，一定不要忘记
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);//这里开始是将第二块buffer绑定到当前，上传color数据，和顶点的做法一样，不多赘述了
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);//将第三块buffer绑定到当前，用于上传存储顶点索引的数据，因此BUFFER类型变更为GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(frontIndices),frontIndices,GL_STATIC_DRAW);//同样是对buffer进行填充
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));//由于索引定义的是4个点，因此第一个参数mode是四边形，第二个是索引的size，第三个是索引的数据类型。
    /*
    glGenBuffers(2,buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glBufferData(GL_ARRAY_BUFFER,3*FileOpen->sizeOfVerts(),FileOpen->Verts);
    glVertexPointer(3,GLfloat,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,3*FileOpen->sizeOfFaces(),FileOpen->Faces );
    */




    for(int p =0;p < facesize;p++)  //画图

   {
         glBegin(GL_POLYGON);

           FileOpen->draw(p);
        glEnd();
    }




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
    return size;
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
void GLWidget::wheelEvent(QWheelEvent *event)
{

    QPoint numDegrees = event->angleDelta() / 8;

        if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
             scalingtheMesh(numSteps.ry());

        }
        event->accept();

}
