#include <iostream>
#include "mainwindow.h"
#include <GL/gl.h>

#include "bspline.h"
using namespace std;

/*
*n：控制点的最大坐标
*Pw：控制点
*P：次数
*m：节点的最大坐标
*U[i]：节点
*/

float fordouble(float x)
{
	return x*x;
}

Bspline::Bspline(){
    controlp = 0;
    knots = 0;

	float num = 10.0;
	int sub = 20;  //r = sub -1
	int r = sub - 1;
	float subA = num / sub;

	/*填入拟合点*/
	for (int i = 0; i < sub; i++)
	{
		point out(i*subA, fordouble(i*subA), 0);
		this->CP.push_back(out);
	}
	point out(num, fordouble(num), 0);
	this->CP.push_back(out);

	/*确定基础数据*/
	this->controlp = 20;
	this->degree = 3;
	this->knots = this->controlp + this->degree + 2;

	cout << CP.size() << endl;
	/*计算U和Pi*/
	BsplineApp(this->CP, r,     //Q[]存储拟合的数据点Q的个数为r+1
		this->controlp - 1,                //预备用n+1个控制点来拟合
		this->degree,                //拟合曲线为p次
		this->U, this->Pi   //输出的节点向量U和控制点p.
		);
}


//计算点

//void Bspline::CurvePoint(const float u){  //得到outPoint
//    float w = 0.0;
//	vector<float> N;
//    point out;
//    out.init();
//    int i;
//	int span = FindSpan(0,knots-1, u,U);
//	BasisFuns(span,u,degree,U,N);
//    
//	for (i = 0; i <= degree; i++)
//    {
//		cpoint *p;
//		p = new cpoint;
//		float c = ndu[i][degree];
//		*p = Pw[span - degree + i] * c;
//		out.x = out.x + p->x;   //ndu[i][degree] * Pi[span - degree + i].x * Pi[span - degree + i].w;
//		out.y = out.y + p->y;   //ndu[i][degree] * Pi[span - degree + i].y * Pi[span - degree + i].w;
//		out.z = out.z + p->z;   //ndu[i][degree] * Pi[span - degree + i].z * Pi[span - degree + i].w;
//		w = w + p->w;           //ndu[i][degree] * Pi[span - degree + i].w;
//    } 
//	out = out / w;
//  
//
//    outPoint.push_back(out);
//   
//}


//void Bspline::RefineKnotVectCurve(int n, int p){
//	/*节点细化，根据插入的X[]向量*/
//	int j;
//	int m = n + p + 1;
//	
//	int a = FindSpan(0, knots, X[0]);
//	int b = FindSpan(0, knots, X[Xknots]);
//	b = b + 1;
//	for (j = 0; j < a - p; j++)
//	{
//		Qw[j] = Pw[j];
//	
//	}
//	for (j = b - 1; j <= n; j++)
//	{
//		Qw[j + Xknots + 1] = Pw[j];
//		
//	} 
//	for (j = 0; j <= a; j++) Ubar[j] = U[j];
//	for (j = b + p; j <= m; j++) Ubar[j + Xknots + 1] = U[j];
//	int i = b + p - 1;
//	int k = b + p + Xknots;
//	for (j = Xknots; j >= 0; j--)
//	{
//		while (X[j] <= U[i] && i>a)
//		{
//			Qw[k - p - 1] = Pw[i - p - 1];
//			Ubar[k] = U[i];
//			k = k - 1;
//			i = i - 1;
//		}
//		Qw[k - p - 1] = Qw[k - p];
//		
//		for (j = Xknots; j >= 0; j--)
//		{
//			int ind = k - p + 1;
//			float alfa = Ubar[k + 1] - X[j];
//			if (abs(alfa) == 0)
//			{
//				Qw[ind - 1] = Qw[ind];
//			}
//
//				
//			else
//			{
//				alfa = alfa / (Ubar[k + 1] - U[i - p + 1]);
//				Qw[ind - 1] = Qw[ind - 1] * alfa + Qw[ind] * (1.0 - alfa) ;
//				
//			}
//		}
//		Ubar[k] = X[j];
//		k = k + 1;
//	}
//	/*细化后节点矢量Ubar和插入后控制点Qw*/
//    
//}


void Bspline::output(){
	outPoint.clear();
	float iSpan, sub;
	float u = 0.0;
	for (int i = this->degree; i < this->knots - this->degree-1; i++)
	{
		iSpan = U[i + 1] - U[i];
		sub = iSpan / 5.0;
		u = U[i] ;
		
		for (int j= 0; j < 5; j++){
			float num = (float)j*sub;
			BSplineCurvePoint(knots, degree, U, Pi, u);
		}
	}
	//CurvePoint(U[knots-1]);

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
			point put;
			put.init();
			put.x = Line.section(" ", 0, 0).toFloat();
			put.y = Line.section(" ", 1, 1).toFloat();
			put.z = Line.section(" ", 2, 2).toFloat();
			Pi.push_back(put);
			
			putPi++;
			if (putPi == controlp) continue;
		}
		if (headerEndTag&&putPi >= controlp){
			for (int j = 0; j<knots; j++){
				U.push_back(Line.section(" ", j, j).toFloat());
			}
		}

	}
	inf.close();

	output();   // 计算outPoint

}

void Bspline::Draw()  
{
	if (CP.size()>0)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS);
			glVertex3f(CP[0].x, CP[0].y, CP[0].z); //预处理第一个点
		glEnd();
		for (int i = 1; i < controlp; i++)
		{
		/*绘制NURBS曲线的控制点线段*/
			glBegin(GL_POINTS);
				glVertex3f(CP[i].x, CP[i].y, CP[i].z);
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(CP[i - 1].x, CP[i - 1].y, CP[i - 1].z);
				glVertex3f(CP[i].x, CP[i].y, CP[i].z);
			glEnd();
		}
	}
	
	
	//vector<Point>::iterator curr;
	if (controlp>0)
	{

	
		glBegin(GL_POINTS);
			glVertex3f(Pi[0].x, Pi[0].y, Pi[0].z); //预处理第一个点
		glEnd();
		for (int i = 1; i < controlp; i++)
		{
			/*绘制NURBS曲线的控制点线段*/
			glBegin(GL_POINTS);
				glVertex3f(Pi[i].x, Pi[i].y, Pi[i].z);
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(Pi[i-1].x, Pi[i-1].y, Pi[i-1].z);
				glVertex3f(Pi[i].x, Pi[i].y, Pi[i].z);
			glEnd();
		}
	}
	
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
			if (!((i)%5))
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POINTS);		
					glVertex3f(outPoint[i].x, outPoint[i].y, outPoint[i].z);
				glEnd();
			}
		
			glColor3f(0.5f, 0.5f, 0.5f);
			glBegin(GL_LINES);
				glVertex3f(outPoint[i-1].x, outPoint[i-1].y, outPoint[i-1].z);
				glVertex3f(outPoint[i].x, outPoint[i].y, outPoint[i].z);
			glEnd();
		}
	}
}
