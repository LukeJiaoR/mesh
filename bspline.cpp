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
        return n-degree;
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

void Bspline::CurvePoint(const float u){  //得到outPoint
    float w = 0.0;
    point out;
    out.init();
    int i;
	int span = FindSpan(0,knots-1, u);
	BasisFuns(span, u);
    
	for (i = 0; i <= degree; i++)
    {
		out.x = out.x + ndu[i][degree] * Pi[span - degree + i].x * Pi[span - degree + i].w;
		out.y = out.y + ndu[i][degree] * Pi[span - degree + i].y * Pi[span - degree + i].w;
		out.z = out.z + ndu[i][degree] * Pi[span - degree + i].z * Pi[span - degree + i].w;
		w = w + ndu[i][degree] * Pi[span - degree + i].w;
    } 
    out.x = out.x/w;
    out.y = out.y/w;
    out.z = out.z/w;
    outPoint.push_back(out);
    //TRACE("CurvePoint: fraction %f  x y z: %f %f %f \n", u, outPoint.x, outPoint.y, outPoint.
}


void Bspline::RefineKnotVectCurve(int n, int p){
	/*节点细化，根据插入的X[]向量*/
	int j;
	int m = n + p + 1;
	int a = FindSpan(0, knots, X[0]);
	int b = FindSpan(0, knots, X[Xknots]);
	b = b + 1;
	for (j = 0; j < a - p; j++)
	{
		Qw[j] = Pw[j];
		/*
		for (int c; c < 4; c++)
		{
			Qw[j][c] = Pw[j][c];
		}
		*/
	}
	for (j = b - 1; j <= n; j++)
	{
		Qw[j + Xknots + 1] = Pw[j];
		/*
		for (int c; c < 4; c++)
		{
			Qw[j + Xknots + 1][c] = Pw[j][c];
		}*/
	} 
	for (j = 0; j <= a; j++) Ubar[j] = U[j];
	for (j = b + p; j <= m; j++) Ubar[j + Xknots + 1] = U[j];
	int i = b + p - 1;
	int k = b + p + Xknots;
	for (j = Xknots; j >= 0; j--)
	{
		while (X[j] <= U[i] && i>a)
		{
			Qw[k - p - 1] = Pw[i - p - 1];
			/*
			for (int c; c < 4; c++)
			{
				Qw[k - p - 1][c] = Pw[i - p - 1][c];
			}*/
			Ubar[k] = U[i];
			k = k - 1;
			i = i - 1;
		}
		Qw[k - p - 1] = Qw[k - p];
		/*
		for (int c; c < 4; c++)
		{
			Qw[k - p - 1][c] = Qw[k - p][c];
		}*/
		
		for (j = Xknots; j >= 0; j--)
		{
			int ind = k - p + 1;
			float alfa = Ubar[k + 1] - X[j];
			if (abs(alfa) == 0)
			{
				Qw[ind - 1] = Qw[ind];
				/*
				for (int c; c < 4; c++)
				{
					Qw[ind - 1][c] = Qw[ind][c];
				}*/
			}

				
			else
			{
				alfa = alfa / (Ubar[k + 1] - U[i - p + 1]);
				Qw[ind - 1] = Qw[ind - 1] * alfa + Qw[ind] * (1.0 - alfa) ;
				/*
				for (int c; c < 4; c++)
				{
					Qw[ind - 1][c] = alfa * Qw[ind - 1][c] + (1.0 - alfa) *Qw[ind][c];
				}*/
				
			}
		}
		Ubar[k] = X[j];
		k = k + 1;
	}
	/*细化后节点矢量Ubar和插入后控制点Qw*/
    
}


void Bspline::output(){
	outPoint.clear();
	float iSpan, sub;
	
	for (int i = degree; i < knots - degree-1; i++)
	{
		iSpan = U[i + 1] - U[i];
		sub = iSpan / 5.00000;
		float u = U[i] ;
		for (int j= 0; j < 5; j++){
			float num = (float)j*sub;
			CurvePoint(u+num);
		}
	}

}
void Bspline::Load(QString filename){
	QFile inf(filename);
	if (!inf.open(QIODevice::ReadWrite)) {
		std::cout << "[!] Failed to Open File!" << std::endl;
	}
	QTextStream in(&inf);
	bool headerEndTag = false;

	int putPi = 0; //存储控制点计数



	while (!in.atEnd())
	{
		QString Line = in.readLine();
		if (Line.section(" ", 0, 0) == "degree"){
			degree = Line.section(" ", 1, 1).toInt();
		}
		if (Line.section(" ", 0, 0) == "control"){
			controlp = Line.section(" ", 2, 2).toInt();

		}
		if (Line.section(" ", 0, 0) == "knots"){
			knots = Line.section(" ", 1, 1).toInt();
		}
		if (Line.section(" ", 0, 0) == "end_header"){
			headerEndTag = true;
			continue;
		}
		if (Line.section(" ", 0, 0) == "#"){
			continue;
		}
		if (Line == NULL) continue;
		if (headerEndTag&&putPi<controlp&&controlp){
			cpoint put;
			put.init();
			/*
			for (int j = 0; j < 4; j++){
				Pi[putPi][j] = Line.section(" ", j, j).toFloat();

			}*/
			put.x = Line.section(" ", 0, 0).toFloat();
			put.y = Line.section(" ", 1, 1).toFloat();
			put.z = Line.section(" ", 2, 2).toFloat();
			put.w = Line.section(" ", 3, 3).toFloat();
			Pi.push_back(put);
			/*
			for (int j = 0; j < 3; j++){
				Pw[putPi][j] = Pi[putPi][j] * Pi[putPi][3];  //权值点
			}
			Pw[putPi][3] = Pi[putPi][3];*/

			put.x = put.x * put.w;
			put.y = put.y * put.w;
			put.z = put.z * put.w;
			Pw.push_back(put);

			putPi++;
			if (putPi == controlp) continue;
		}
		if (headerEndTag&&putPi >= controlp){
			for (int j = 0; j<knots; j++){
				U[j] = Line.section(" ", j, j).toFloat();
			}
		}

	}
	inf.close();
	output();   // 计算outPoint

}
void Bspline::Draw()  
{
	//vector<Point>::iterator curr;
	if (controlp>0)
	{

	
	glBegin(GL_POINTS);
	glVertex3f(Pi[0].x, Pi[0].y, Pi[0].z); //预处理第一个点
	glEnd();
	for (int i = 1; i < controlp; i++){
		/*绘制NURBS曲线的控制点线段*/
		glBegin(GL_POINTS);
		glVertex3f(Pi[i].x, Pi[i].y, Pi[i].z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(Pi[i-1].x, Pi[i-1].y, Pi[i-1].z);
			glVertex3f(Pi[i].x, Pi[i].y, Pi[i].z);
		glEnd();
	}}
	
	if (outPoint.size()>0)
	{ 
	glPointSize(8.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3f(outPoint[0].x, outPoint[0].y, outPoint[0].z);
	glEnd();
	for (int i = 1; i < outPoint.size(); i++)
    {
        /*绘制NURBS曲线*/
		if (!((i+1)%5))
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POINTS);		
			glVertex3f(outPoint[i].x, outPoint[i].y, outPoint[i].z);
			glEnd();
		}
		
		glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
		   glVertex3f(outPoint[i-1].x, outPoint[i-1].y, outPoint[i-1].z);
		   glVertex3f(outPoint[i].x, outPoint[i].y, outPoint[i].z);
        glEnd();
    }
	}
}
