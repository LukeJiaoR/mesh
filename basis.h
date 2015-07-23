
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
int FindSpan(int p, int n, float u, float U[]);

/*算法2.2*/
void BasisFuns(int i, float u, int p, float U[], float N[]);

/*算法2.3*/
void DersBasisFuns(int i, float u, int p, int n, float U[], float ders[][100]);

/*算法2.4*/
void OneBasisFuns(int p, int m, float U[], int i, float u, float Nip);

/*算法2.5*/
void DersOneBasisFuns(int p, int m, float U[], int i, float u, int n, float ders[]);


/*************************第三章**********************************/
/*算法3.2*/
void CurveDerivsAlg1(int n, int p, float U[], point P[], float u, int d, point CK[]);

/*算法3.3*/
void CurveDerivCpts(int n, int p, float U[], point P[], int d, int r2, int r1, point PK[][100]);

/*算法3.4*/
void CurveDerivsAlg2(int n, int p, float U[], point P[], float u, int d, point CK[]);