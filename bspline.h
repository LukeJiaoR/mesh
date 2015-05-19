#ifndef BSPLINE_H
#define BSPLINE_H

#include <iostream>
#include <vector>
using namespace std;

struct Point{    
    float x;
    float y;
    float z;
  
    void init(){ x = 0.0;y =0.0;z = 0.0;}
    
};



class Bspline
{
public:
    Bspline();
    void Load(QString filename);
    int sizeOfPi(){ return controlp;}
    int sizeofknots(){ return knots;}
    void BasisFuns(int i,  int p,float u);
	int FindSpan(int n, int p, float u);
	void DrawBSpline();
protected:
    void CurvePoint(int n,const float u);




private:
    float  Pi[1000][4];           //控制点 x,y,z,w
    float  U[1000];            //节点矢量
    float  left[1000];         //left[j] = u - U[i+1-j];
    float  right[1000];        //right[j] = U[i+j] - u;
    float  ndu[100][100];      //存储基函数
    int    degree;                  //次数
    int    controlp;                 //控制点个数
    int    knots;
    vector<Point> outPoint;    //NURBS最终绘制点
};

#endif // BSPLINE_H
