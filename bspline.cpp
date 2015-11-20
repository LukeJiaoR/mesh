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
*m_VfKnotsVector[i]：节点
*/

float fordouble(float x)
{
	return x*x;
}

Bspline::Bspline(){
    m_iNumOfcontrolPoint = 0;
    m_iNumOfknots = 0;

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
	this->m_iNumOfcontrolPoint = 20;
	this->m_iDegreeOfCurve = 3;
	this->m_iNumOfknots = this->m_iNumOfcontrolPoint + this->m_iDegreeOfCurve + 2;

	cout << CP.size() << endl;
	/*计算m_VfKnotsVector和m_VpControlPointOfBspline*/
	BsplineApp(this->CP, r,     //Q[]存储拟合的数据点Q的个数为r+1
		this->m_iNumOfcontrolPoint - 1,                //预备用n+1个控制点来拟合
		this->m_iDegreeOfCurve,                //拟合曲线为p次
		this->m_VfKnotsVector, this->m_VpControlPointOfBspline   //输出的节点向量m_VfKnotsVector和控制点p.
		);
}

int FindSpan(int n, int p, float u, mat &U)
{
	int low, high, mid;
	if (u == U(n)) // savety >= check
		return n - p;
	low = p;
	high = n;
	mid = (low + high) / 2;
	while (u < U(mid) || u >= U(mid + 1))
	{
		if (u < U(mid))
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
void Bspline::BasisFuns(int i, float u, int p, vector<float> U, vector<float>& N)
{
	//float left[NUM], right[NUM];
	vector<float> left, right;
	left.push_back(0.0);
	right.push_back(0.0);
	N.push_back(1.0);
	vector<float>::iterator cerr = N.begin();
	for (int j = 1; j <= p; j++)
	{
		float temp;
		left.push_back(u - U[i + 1 - j]);
		right.push_back(U[i + j] - u);
		float saved = 0.0;
		for (int r = 0; r < j; r++)
		{
			/*vector<float>::iterator cerr1 = cerr;
			temp = *cerr / (right[r + 1] + left[j - r]);
			*cerr = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
			cerr1++;*/
			temp = N[r] / (right[r + 1] + left[j - r]);
			N[r] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		//std::cout << " N[" << j << "]:" << temp << " " << endl;

		N.push_back(saved);
	}
}


float Distance3D(point a, point b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	float z = a.z - a.z;
	float c = x*x + y*y + z*z;
	return sqrt(c);
}


void Getub(vector<point> Q, int n, vector<float>& ub)
{
	ub.push_back(0.0);
	vector<float>::iterator cerr = ub.begin();
	float d = 0.0;
	for (int i = 0; i < n; i++)
		d = d + Distance3D(Q[i], Q[i + 1]);

	/*计算ub[i]放入ub中*/
	for (int i = 1; i <= n; i++, cerr++)
	{
		//ub[i] = ub[i - 1] + Distance3D(Q[i], Q[i - 1]) / d;
		//cout << " ub[" << i-1 << "]:" << ub[i - 1] << endl;
		//float temp = ub[i-1]+ Distance3D(Q[i], Q[i - 1]) / d  ;
		//cout << " ub[" << i << "]:" << temp << endl;
		ub.push_back(ub[i - 1] + Distance3D(Q[i], Q[i - 1]) / d);
	}
	//ub.push_back(1.0);
}


void GetU(int m, int n, int p, vector<float> ub, vector<float>& U)
{
	float d = static_cast<float>(m + 1) / static_cast<float>(n - p + 1);
	cout << "D :" << d << typeid(d).name() << endl;
	for (int i = 0; i <= p; i++)  U.push_back(0);
	for (int j = 1; j <= n - p; j++)
	{
		int i = (int)(j*d);
		cout << "j*d :" << j*d << endl;
		float a = j*d - i; cout << "a:" << a << endl;
		U.push_back((1.0 - a)*ub[i - 1] + a*ub[i]);
	}
	for (int i = 0; i <= p; i++)
	{
		U.push_back(1);
	}
}

void Bspline::CurvePoint(const float m_VfKnotsVector){  //得到 m_VpOutPoint
    float w = 0.0;
	vector<float> n;
    point out;
    out.init();
    int i;
	int span = FindSpan(0,m_iNumOfknots-1, m_VfKnotsVector,m_VfKnotsVector);
	basisfuns(span,m_VfKnotsVector,m_iDegreeOfCurve,m_VfKnotsVector,n);
    
	for (i = 0; i <= m_iDegreeOfCurve; i++)
    {
		cpoint *p;
		p = new cpoint;
		float c = ndu[i][m_iDegreeOfCurve];
		*p = pw[span - m_iDegreeOfCurve + i] * c;
		out.x = out.x + p->x;   //ndu[i][m_iDegreeOfCurve] * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].x * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].w;
		out.y = out.y + p->y;   //ndu[i][m_iDegreeOfCurve] * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].y * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].w;
		out.z = out.z + p->z;   //ndu[i][m_iDegreeOfCurve] * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].z * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].w;
		w = w + p->w;           //ndu[i][m_iDegreeOfCurve] * m_VpControlPointOfBspline[span - m_iDegreeOfCurve + i].w;
    } 
	out = out / w;
	m_VpOutPoint.push_back(out);
   
}


//void Bspline::RefineKnotVectCurve(int n, int p){
//	/*节点细化，根据插入的X[]向量*/
//	int j;
//	int m = n + p + 1;
//	
//	int a = FindSpan(0, m_iNumOfknots, X[0]);
//	int b = FindSpan(0, m_iNumOfknots, X[Xknots]);
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
//	for (j = 0; j <= a; j++) Ubar[j] = m_VfKnotsVector[j];
//	for (j = b + p; j <= m; j++) Ubar[j + Xknots + 1] = m_VfKnotsVector[j];
//	int i = b + p - 1;
//	int k = b + p + Xknots;
//	for (j = Xknots; j >= 0; j--)
//	{
//		while (X[j] <= m_VfKnotsVector[i] && i>a)
//		{
//			Qw[k - p - 1] = Pw[i - p - 1];
//			Ubar[k] = m_VfKnotsVector[i];
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
//				alfa = alfa / (Ubar[k + 1] - m_VfKnotsVector[i - p + 1]);
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
	m_VpOutPoint.clear();
	float iSpan, sub;
	float m_VfKnotsVector = 0.0;
	for (int i = this->m_iDegreeOfCurve; i < this->m_iNumOfknots - this->m_iDegreeOfCurve-1; i++)
	{
		iSpan = m_VfKnotsVector[i + 1] - m_VfKnotsVector[i];
		sub = iSpan / 5.0;
		m_VfKnotsVector = m_VfKnotsVector[i] ;
		
		for (int j= 0; j < 5; j++){
			float num = (float)j*sub;
			BSplineCurvePoint(m_iNumOfknots, m_iDegreeOfCurve, m_VfKnotsVector, m_VpControlPointOfBspline, m_VfKnotsVector);
		}
	}
	//CurvePoint(m_VfKnotsVector[m_iNumOfknots-1]);

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
		if (Line.section(" ", 0, 0) == "m_iDegreeOfCurve"){
			m_iDegreeOfCurve = Line.section(" ", 1, 1).toInt();
		}
		if (Line.section(" ", 0, 0) == "control"){
			m_iNumOfcontrolPoint = Line.section(" ", 2, 2).toInt();

		}
		if (Line.section(" ", 0, 0) == "m_iNumOfknots"){
			m_iNumOfknots = Line.section(" ", 1, 1).toInt();
		}
		if (Line.section(" ", 0, 0) == "end_header"){
			headerEndTag = true;
			continue;
		}
		if (Line.section(" ", 0, 0) == "#"){
			continue;
		}
		if (Line == NULL) continue;
		if (headerEndTag&&putPi<m_iNumOfcontrolPoint&&m_iNumOfcontrolPoint){
			point put;
			put.init();
			put.x = Line.section(" ", 0, 0).toFloat();
			put.y = Line.section(" ", 1, 1).toFloat();
			put.z = Line.section(" ", 2, 2).toFloat();
			m_VpControlPointOfBspline.push_back(put);
			
			putPi++;
			if (putPi == m_iNumOfcontrolPoint) continue;
		}
		if (headerEndTag&&putPi >= m_iNumOfcontrolPoint){
			for (int j = 0; j<m_iNumOfknots; j++){
				m_VfKnotsVector.push_back(Line.section(" ", j, j).toFloat());
			}
		}

	}
	inf.close();

	output();   // 计算 m_VpOutPoint

}

void Bspline::Draw()  
{
	if (CP.size()>0)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS);
			glVertex3f(CP[0].x, CP[0].y, CP[0].z); //预处理第一个点
		glEnd();
		for (int i = 1; i < m_iNumOfcontrolPoint; i++)
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
	if (m_iNumOfcontrolPoint>0)
	{

	
		glBegin(GL_POINTS);
			glVertex3f(m_VpControlPointOfBspline[0].x, m_VpControlPointOfBspline[0].y, m_VpControlPointOfBspline[0].z); //预处理第一个点
		glEnd();
		for (int i = 1; i < m_iNumOfcontrolPoint; i++)
		{
			/*绘制NURBS曲线的控制点线段*/
			glBegin(GL_POINTS);
				glVertex3f(m_VpControlPointOfBspline[i].x, m_VpControlPointOfBspline[i].y, m_VpControlPointOfBspline[i].z);
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_VpControlPointOfBspline[i-1].x, m_VpControlPointOfBspline[i-1].y, m_VpControlPointOfBspline[i-1].z);
				glVertex3f(m_VpControlPointOfBspline[i].x, m_VpControlPointOfBspline[i].y, m_VpControlPointOfBspline[i].z);
			glEnd();
		}
	}
	
	if ( m_VpOutPoint.size()>0)
	{ 
		glPointSize(8.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f( m_VpOutPoint[0].x,  m_VpOutPoint[0].y,  m_VpOutPoint[0].z);
		glEnd();
		for (int i = 1; i <  m_VpOutPoint.size(); i++)
		{
			/*绘制NURBS曲线*/
			if (!((i)%5))
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POINTS);		
				glVertex3f(m_VpOutPoint[i].x, m_VpOutPoint[i].y, m_VpOutPoint[i].z);
				glEnd();
			}
		
			glColor3f(0.5f, 0.5f, 0.5f);
			glBegin(GL_LINES);
			glVertex3f(m_VpOutPoint[i - 1].x, m_VpOutPoint[i - 1].y, m_VpOutPoint[i - 1].z);
				glVertex3f(m_VpOutPoint[i].x, m_VpOutPoint[i].y, m_VpOutPoint[i].z);
			glEnd();
		}
	}
}
