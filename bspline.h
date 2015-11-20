#ifndef BSPLINE_H
#define BSPLINE_H

#include <iostream>


#include "LoadFile.h"
#include "Nurbs-DS.h"

using std::vector;





class Bspline :public LoadFile
{

public:
    Bspline();
    void Load(QString filename);
	void Draw() ;
	int sizex(){ return m_iNumOfcontrolPoint; }
	int sizey(){ return m_iNumOfknots; }
	void CurvePoint(const float u);

	void BasisFuns(int i, float u, int p, vector<float> U, vector<float>& N);

	//void RefineKnotVectCurve(int n, int p);
	void output();

private:

	
    int    m_iDegreeOfCurve;                  //次数
    int    m_iNumOfcontrolPoint;                //控制点个数
    int    m_iNumOfknots;                   //节点个数
	//int    Xknots;                  //需要插入的节点个个数

	vector<point> m_VpControlPointOfBspline;				//控制点 x,y,z
    vector<float> m_VfKnotsVector;				//节点矢量
	vector<point> m_VpOutPoint;         //NURBS最终绘制点
	vector<point> CP;				//拟合点
};

#endif // BSPLINE_H
