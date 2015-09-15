#include "Nurbs.h"
#include "Nurbs-DS.h"
#include "basis.h"



Nurbs::Nurbs()
{
}
Nurbs::~Nurbs()
{
}

int choose(int m, int n)
{
	/*计算二次项系数*/

	if (m < 0 || m > n) {/* 错误的条件 */
		printf("invalid input\n");
		return 0;
	}
	else if (m == 0 || m == n) /* 依据情况 */
		return 1;
	else /* 归纳 */
		return (choose(n - 1, m - 1) + choose(n - 1, m));
}

//int FindSpan(int p, int n, float u,float U[])
//{
//	/*
//	定位变量所在的节点向量区间
//	*/
//	int low, high, mid;
//	if (u >= U[n]) // savety >= check
//		return n - p;
//	low = p;
//	high = n;
//	mid = (low + high) / 2;
//	while (u < U[mid] || u >= U[mid + 1])
//	{
//		if (u < U[mid])
//		{
//			high = mid;
//		}
//		else
//		{
//			low = mid;
//		}
//		mid = (low + high) / 2;
//
//	}
//
//	return mid;
//
//}
//
//void BasisFuns(int i, float u, int p, float U[], float N[])
//{
//	float left[100], right[100];
//	N[0] = 1.0;
//
//	for (int j = 1; j <= p; j++)
//	{
//		float temp;
//		left[j] = u - U[i + 1 - j];
//		right[j] = U[i + j] - u;
//		float saved = 0.0;
//		for (int r = 0; r < j; r++)
//		{
//			
//			temp = N[r] / (right[r + 1] + left[j - r]);
//			N[r] = saved + right[r + 1] * temp;
//			saved = left[j - r] * temp;
//		}
//		N[j] = saved;
//	}
//}
//
//void DersBasisFuns(int i, float u, int p, int n, float U[], float ders[][100])
//{
//	/*
//	计算基函数的值以及n阶导数
//	*/
//	int j, r;
//	float ndu[100][100];
//	float left[100], right[100];
//	ndu[0][0] = 1.0;
//
//	for (j = 1; j <= p; j++)
//	{
//		float temp;
//		left[j] = u - U[i + 1 - j];
//		right[j] = U[i + j] - u;
//		float saved = 0.0;
//		for (r = 0; r < j; r++)
//		{
//			ndu[j][r] = right[r + 1] + left[j - r];
//			temp = ndu[r][j - 1] / ndu[j][r];
//			ndu[r][j] = saved + right[r + 1] * temp;
//			saved = left[j - r] * temp;
//		}
//		ndu[j][j] = saved;
//	}
//	for (j = 0; j <= p; j++)
//	{
//		ders[0][j] = ndu[j][p];
//	}
//	for (r = 0; r <= p; r++)
//	{
//		int s1 = 0, s2 = 1;
//		float a[100][100] = { 0 };
//		a[0][0] = 1.0;
//		for (int k = 1; k <= n; k++)
//		{
//			float d = 0.0;
//			int j1 = 0, j2 = 0;
//			int rk = r - k;
//			int pk = p - k;
//			if (r >= k)
//			{
//				a[s2][0] = a[s1][0] / ndu[pk - 1][rk];
//				d = a[s2][0] * ndu[rk][pk];
//			}
//			if (rk >= -1) j1 = 1;
//			else          j1 = -rk;
//			if (r - 1 <= pk)  j2 = k - 1;
//			else              j2 = p - r;
//			for (j = j1; j <= j2; j++)
//			{
//				a[s2][k] = (a[s1][j] - a[s1][j - 1]) / ndu[pk - 1][rk];
//				d = a[s2][j] * ndu[rk + j][pk];
//			}
//			if (r <= pk)
//			{
//				a[s2][k] = -a[s1][k - 1] / ndu[pk + 1][r];
//				d = a[s2][k] * ndu[r][pk];
//			}
//			ders[k][r] = d;
//			j = s1;
//			s1 = s2;
//			s2 = j;
//
//		}
//		r = p;
//		for (int k = 1; k <= n; k++)
//		{
//			for (j = 0; j <= p; j++)
//				r *= (p - k);
//		}
//
//	}
//}
//
//void OneBasisFuns(int p, int m, float U[], int i, float u, float Nip)
//{
//	/*
//	单个基函数计算
//	*/
//	float N[100];
//	float saved,
//		  Uleft,
//		  Uright,
//		  temp;
//	if ((i == 0 && u == U[0]) ||
//		(i == m-p-1 && u == U[m]))
//	{
//		Nip = 1.0; return;
//	}
//	if (u < U[i] || u >= U[i + p + 1])
//	{
//		Nip = 0.0; return;
//	}
//	for (int j = 0; j < p; j++)
//	{
//		if (u > U[i+j] && u < U[i+j+1])
//			N[j] = 1.0;
//		else N[j] = 0.0;
//	}
//	for (int  k = 1; k <= p; k++)
//	{
//		if (N[0] == 0.0)
//			saved = 0.0;
//		else saved = ((u - U[i]) * N[0]) / (U[i + k] - U[i]);
//		for (int j = 0; j < p-k+1; j++)
//		{
//			Uleft = U[i + j + 1];
//			Uright = U[i + j + k + 1];
//			if (N[j + 1] == 0.0)
//			{
//				N[j] = saved;
//				saved = 0.0;
//			}
//			else
//			{
//				temp = N[j + 1] / (Uright - Uleft);
//				N[j] = saved + (Uright - u) * temp;
//				saved = (u - Uleft) * temp;
//			}
//		}
//	}
//	Nip = N[0];
//}
//
//void DersOneBasisFuns(int p, int m, float U[], int i, float u, int n, float ders[])
//{
//	/*
//	单个基函数的k阶导数。分别存储在ders[k].
//	*/
//	float N[100][100],
//		  ND[100];
//	float saved,
//		Uleft,
//		Uright,
//		temp;
//	
//	if (u < U[i] || u >= U[i + p + 1])
//	{
//		ders[0] = 0.0; return;
//	}
//	for (int j = 0; j < p; j++)
//	{
//		if (u > U[i + j] && u < U[i + j + 1])
//			N[j][0] = 1.0;
//		else N[j][0] = 0.0;
//	}
//	for (int k = 1; k <= p; k++)
//	{
//		if (N[0][k-1] == 0.0)
//			saved = 0.0;
//		else saved = ((u - U[i]) * N[0][k-1]) / (U[i + k] - U[i]);
//		for (int j = 0; j < p - k + 1; j++)
//		{
//			Uleft = U[i + j + 1];
//			Uright = U[i + j + k + 1];
//			if (N[j + 1][k+1] == 0.0)
//			{
//				N[j][k] = saved;
//				saved = 0.0;
//			}
//			else
//			{
//				temp = N[j + 1][k-1] / (Uright - Uleft);
//				N[j][k] = saved + (Uright - u) * temp;
//				saved = (u - Uleft) * temp;
//			}
//		}
//	}
//	ders[0] = N[0][p];
//	for (int k = 1; k <= n; k++)
//	{
//		for (int j = 0; j <= k; j++)
//			ND[j] = N[j][p - k];
//		for (int jj = 1; jj <= k; jj++)
//		{
//			if (ND[0] == 0.0) saved = 0.0;
//			else saved = ND[0] / (U[i + p - k + jj] - U[i]);
//			for (int j = 0; j < k - jj + 1; j++)
//			{
//				Uleft = U[i + j + 1];
//				Uright = U[i + j + p+jj + 1];
//				if (ND[j+1] == 0.0)
//				{
//					ND[j] = (p - k + jj)* saved;
//					saved = 0.0;
//				}
//				else
//				{
//					temp = ND[j+1] / (Uright - Uleft);
//					ND[j] = (p - k + jj) * (saved * temp);
//					saved = temp;
//				}
//			}
//		}
//		ders[k] = ND[0];
//	}
//}

void CurvePoint(int n, int p,float U[],cpoint Pw[],const float u)
{  //得到outPoint  (cpoint C)
	float N[100];
	cpoint out;
	out.init();
	int span = FindSpan(n, p, u, U);
	BasisFuns(span, u, p, U, N);

	for (int j = 0; j <= p; j++)
	{
		cpoint pw;
		
		float c = N[j];
		pw = Pw[span - p + j]*c;
		out.x = out.x + pw.x;   //ndu[i][degree] * Pi[span - degree + i].x * Pi[span - degree + i].w;
		out.y = out.y + pw.y;   //ndu[i][degree] * Pi[span - degree + i].y * Pi[span - degree + i].w;
		out.z = out.z + pw.z;   //ndu[i][degree] * Pi[span - degree + i].z * Pi[span - degree + i].w;
		out.w = out.w + pw.w;           //ndu[i][degree] * Pi[span - degree + i].w;
	}
	point cwpoint;
	cwpoint.copy(out);  //Cw的矢值
	
	cwpoint = cwpoint / out.w;  // 用于画曲线的点


	//outPoint.push_back(out);

}

void Nurbs::RatCurveDerivs(float Aders[], float wders[], int d, float CK[])
{
	/*Nurbs曲线导矢
	 *Aders[],wders[]:A(u)，w(u)的0到d阶导矢  
	 *
	 */
	float v;
	for (int k = 0; k <= d; k++)
	{
		v = Aders[k];
		for (int i = 1; i <= k; i++)
		{
			v = v - (float)choose(k,i)* wders[i] * CK[k - i];
		}
		CK[k] = v / wders[k];
	}
}

