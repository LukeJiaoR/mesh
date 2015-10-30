
/*
提供一些基本的计算函数
1，FindSpan ：查找u对应所在的节点区间
2，BasisFuns：计算u的基函数
3，DersBasisFuns ： 计算u的基函数及其对应的导数
4，OneBasisFuns ：计算单个基函数
5，DersOneBaisFuns ： 计算单个基函数以及其n阶导数
*/



#include "Nurbs-DS.h"

/*************************第二章**********************************/
/*算法2.1*/
int FindSpan(int p, int n, float u, vector<float> U);

/*算法2.2*/
void BasisFuns(int i, float u, int p, vector<float> U, vector<float>& N);

/*算法2.3*/
void DersBasisFuns(int i, float u, int p, int n, vector<float> U, float ders[][100]);

/*算法2.4*/
void OneBasisFuns(int p, int m, float U[], int i, float u, float Nip);

/*算法2.5*/
void DersOneBasisFuns(int p, int m, float U[], int i, float u, int n, float ders[]);

/*************************第三章**********************************/

point BSplineCurvePoint(int n, int p, vector<float> U, vector<point> P, float u);
/*算法3.2*/
void CurveDerivsAlg1(int n, int p, float U[], point P[], float u, int d, point CK[]);

/*算法3.3*/
void CurveDerivCpts(int n, int p, float U[], point P[], int d, int r2, int r1, point PK[][100]);

/*算法3.4*/
void CurveDerivsAlg2(int n, int p, float U[], point P[], float u, int d, point CK[]);

/*算法3.5*/
void SurfacePoint(int n, int p, float U[], int m, int q, float V[], point P[][3], float u, float v, point S);

/*算法3.6*/
void SurfaceDerivsAlg1(int n, int p, float U[], int m, int q, float V[], point P[][3], float u, float v, const int d, point SKL[][100]);


/*算法9.6*/
bool WCLeastSquaresCureve(vector<point> Q, int r,     //Q[]存储拟合的数据点Q的个数为r+1
	float Wq[],           //>0 是非约束点,<0是约束点 ，大小 r+1
	vector<point> D, int s, int I[],       // D[]存储导矢。导矢个数为s+1，s = -1表示没有导矢,I[]存储对应第k个导矢对应的点在Q中的下标
	float Wd[],           //标明D[]中导矢的约束性。
	int n,                //预备用n个控制点来拟合
	int p,                //拟合曲线为p次
	vector<float>& U, vector<cpoint>& P   //输出的节点向量U和控制点p.
	);


bool BsplineApp(vector<point> Q, int r,     //Q[]存储拟合的数据点Q的个数为r+1
	//float Wq[],           //>0 是非约束点,<0是约束点 ，大小 r+1
	//vector<point> D, int s, int I[],       // D[]存储导矢。导矢个数为s+1，s = -1表示没有导矢,I[]存储对应第k个导矢对应的点在Q中的下标
	//float Wd[],           //标明D[]中导矢的约束性。
	int n,                //预备用n个控制点来拟合
	int p,                //拟合曲线为p次
	vector<float>& U, vector<point>& P   //输出的节点向量U和控制点p.)
	);