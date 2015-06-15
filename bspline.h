#ifndef BSPLINE_H
#define BSPLINE_H

#include <iostream>
#include <vector>

#include "LoadFile.h"
#include "Nurbs-DS.h"


using namespace std;





class Bspline :public LoadFile
{

public:
    Bspline();
    void Load(QString filename);
	void Draw() ;
	int sizex(){ return controlp; }
	int sizey(){ return knots; }
    void BasisFuns(int i, float u);
	void CurvePoint(const float u);
	int FindSpan(int n, int p, float u);
	void RefineKnotVectCurve(int n, int p);
	void output();
protected:
    void CurvePoint(int n,const float u);




private:
    //float  Pi[1000][4];         //控制点 x,y,z,w
	//float  Pw[1000][4];         //权值点
	//float  Qw[1000][4];         //插入后的控制点

	vector<cpoint> Pi;            //控制点 x,y,z,w
	vector<cpoint> Pw;            //权值点
	vector<cpoint> Qw;            //插入后的控制点
	

    float  U[1000];            //节点矢量
	float  Ubar[1000];         //细化后节点矢量
	float  X[1000];            //需要插入的节点矢量

	float  left[1000];         //left[j] = u - U[i+1-j];
    float  right[1000];        //right[j] = U[i+j] - u;

    float  ndu[100][100];      //存储基函数

    int    degree;                  //次数
    int    controlp;                //控制点个数
    int    knots;                   //节点个数
	int    Xknots;                  //需要插入的节点个个数
    vector<point> outPoint;         //NURBS最终绘制点
};

#endif // BSPLINE_H
