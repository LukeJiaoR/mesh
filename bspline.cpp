#include <iostream>
#include <mainwindow.h>
#include <GL/gl.h>
#include "bspline.h"
using namespace std;





Bspline::Bspline(){
    controlp = 0;
    knots = 0;
}

//判断u所处的knot span 然后计算。返回初始下表
int Bspline::FindSpan(int p,int n,float u)
{

    int low, high, mid;
    if (u >= U[n]) // savety >= check
        return n;
    low = p;
    high = n ;
    mid = (low + high) / 2;
    while (u < U[mid] || u >= U[mid + 1])
    {
        if (u < U[mid])
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
        mid = (low + high) / 2;

    }

    return mid;

}

//计算非零B样条基函数，用Nr来存储计算过的前置基函数，去除重复计算
void  Bspline::BasisFuns(int i,  float u){
    int j,r;
    ndu[0][0]  = 1.0;
    for (j = 1; j <= degree; j++)
    {
        float temp;
        left[j] = u - U[i+1-j];
        right[j] = U[i+j] - u;
        float saved = 0.0;  
        for (r = 0;r < j ; r++)
        {
            ndu[j][r] = right[r+1] + left[j-r];
            temp = ndu[r][j-1]/ndu[j][r];
            ndu[r][j] = saved + right[r+1]*temp;
            saved = left[j-r]*temp;
        }
        ndu[j][j] = saved;
   }
}
//计算点

void Bspline::Load(QString filename){
    QFile inf(filename);
    if (!inf.open(QIODevice::ReadWrite)) {
         std::cout<< "[!] Failed to Open File!"<<std::endl;
    }
    QTextStream in(&inf);   
    bool headerEndTag = false;     

    int putPi = 0; //存储控制点计数



    while(!in.atEnd())
    {
        QString Line = in.readLine();
        if(Line.section(" ",0,0)=="degree"){
			degree = Line.section(" ", 1, 1).toInt();
        }
        if(Line.section(" ",0,0)=="control"){
             controlp = Line.section(" ",2,2).toInt();
        }
        if(Line.section(" ",0,0)=="knots"){
             knots = Line.section(" ",1,1).toInt();
        }
        if(Line.section(" ",0,0)=="end_header"){
            headerEndTag = true;
            continue;
        }
        if(Line ==NULL) continue;
        if(headerEndTag&&putPi<controlp&&controlp){
                for(int j=0;j < 4;j++){
                    Pi[putPi][j] = Line.section(" ",j,j).toFloat();
                }
                putPi++;
                if (putPi == controlp ) continue;
        }
        if(headerEndTag&&putPi>=controlp){
            for(int j=0;j<knots;j++){
                U[j] = Line.section(" ",j,j).toFloat();
            }
        }

     }

}
void Bspline::CurvePoint(const float u){  //得到outPoint
    float w = 0.0;
    Point out;
    out.init();
    int i;
	int span = FindSpan(0,knots-1, u);
	BasisFuns(span, u);
    
	for (i = 0; i <= degree; i++)
    {
		out.x = out.x + ndu[i][degree] * Pi[span - degree + i][0] * Pi[span - degree + i][3];
		out.y = out.y + ndu[i][degree] * Pi[span - degree + i][1] * Pi[span - degree + i][3];
		out.z = out.z + ndu[i][degree] * Pi[span - degree + i][2] * Pi[span - degree + i][3];
		w = w + ndu[i][degree] * Pi[span - degree + i][3];
    }
    out.x = out.x/w;
    out.y = out.y/w;
    out.z = out.z/w;
    outPoint.push_back(out);
    //TRACE("CurvePoint: fraction %f  x y z: %f %f %f \n", u, outPoint.x, outPoint.y, outPoint.
}
/*
void Bspline::CurvePoint2D(int n, int p,
                           const float *U, const float *P, const float *w,
                           const float u, Point &outPoint)
{
  
    //TRACE("CurvePoint: fraction %f  x y z: %f %f %f \n", u, outPoint.x, outPoint.y, outPoint.z);

}
bool Bspline::SurfacePoint(
    float u, float v, int uOrder, int vOrder, int uDimension, int vDimension,
    const float *uKnot, const float * vKnot,
    const Point *P, const float *W,
    float *dest // result
    )
{

  

}

void Bspline::ComputeUkVector(int N, float *t, float* uk)
{
    
}
//
// calculate the knotvector
// page 365
//
void Bspline::ComputeKnotVector(int N, int pdim, int m, float *uk, float *u)
{
   
}

*/
void Bspline::output(){
	float MAXspan = U[knots - 1] - U[0];
	int subNum = knots * 5;
	float sub = MAXspan / subNum;
	float u = 0.0;
	int i;
	for (i = 0; i < subNum; i++){
		u = i * sub;
		CurvePoint(u);
	}
}

void Bspline::DrawBSpline ()
{
	output();
	vector<Point>::iterator curr;
    for (curr = outPoint.begin();curr != outPoint.end(); ++curr)
    {
        /*绘制NURBS曲线*/
        glBegin(GL_LINE);
		glVertex3f(curr->x, curr->y, curr->z);
        glEnd();
    }
}
