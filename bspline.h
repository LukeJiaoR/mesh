#ifndef BSPLINE_H
#define BSPLINE_H

#include <iostream>


#include "LoadFile.h"
#include "Nurbs-DS.h"
#include "basis.h"

using std::vector;





class Bspline :public LoadFile
{

public:
    Bspline();
    void Load(QString filename);
	void Draw() ;
	int sizex(){ return controlp; }
	int sizey(){ return knots; }
	//void CurvePoint(const float u);
	void RefineKnotVectCurve(int n, int p);
	void output();

private:

	
    int    degree;                  //次数
    int    controlp;                //控制点个数
    int    knots;                   //节点个数
	int    Xknots;                  //需要插入的节点个个数

	vector<point> Pi;				//控制点 x,y,z
    vector<float> U;				//节点矢量
    vector<point> outPoint;         //NURBS最终绘制点
	vector<point> CP;				//拟合点
};

#endif // BSPLINE_H
