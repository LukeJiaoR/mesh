#pragma once
#include "LoadFile.h"
class Nurbs :
	public LoadFile
{
public:
	Nurbs();
	~Nurbs();
	void Load(QString filename);
	void Draw();
	bool WCLeastSquareCurve(float q[], int r, float Wq[], float D[], int s, int I[], float Wd[], int n, int p);
	/*Q[r+1]: 存储要拟合的数据点
	  r : Q[]最大下标，给定了r+1个数据点
	  Wq[r+1]: Wq[i]> 0 表示Q[i]是非约束点，且是其权值，<0意味者是约束点
	  D[s+1]:存储导矢  = -1 表示没有导矢
	  s:  D[]最大下标，有s+1个数据
	  I[s+1]: 是导矢D[]对应的数据点在q[]的下标
	  Wd[s+1]: >0 d[j] 非约束 且为权值 <0 约束
	  n: 用n+1个控制点来拟合
	  p: 拟合曲线次数
	*/
	

private:
	int m_iNumofPoints;

};

