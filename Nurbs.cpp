#include "Nurbs.h"


Nurbs::Nurbs()
{
}

int FindSpan(int n, int p , float u, float U[])
{
	/*p:次数
	  n:节点个数
	  u:传入的变量
	  u[]:节点矢量
	*/
	int low, high, mid;
	if (u >= U[n]) // savety >= check
		return n - p;
	low = p;
	high = n;
	mid = (low + high) / 2;
	while (u < U[mid] || u >= U[mid + 1])
	{
		if (u < U[mid])
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
void  BasisFuns(int i, float u, int p, float U[],float ndu[][4])
{
	

	ndu[0][0] = 1.0;
	float left[100], right[100];
	for (int j = 1; j <= p; j++)
	{
		float temp;
		left[j] = u - U[i + 1 - j];
		right[j] = U[i + j] - u;
		float saved = 0.0;
		for (int r = 0; r < j; r++)
		{
			ndu[j][r] = right[r + 1] + left[j - r];
			temp = ndu[r][j - 1] / ndu[j][r];
			ndu[r][j] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		ndu[j][j] = saved;
	}
}
void  DersBasisFuns(int i, float u,float p,int n ,float U[], float ders[][4])
{
	float ndu[100][100];
	int j, r;
	ndu[0][0] = 1.0;
	float left[100], right[100];
	for (j = 1; j <= p; j++)
	{
		float temp;
		left[j] = u - U[i + 1 - j];
		right[j] = U[i + j] - u;
		float saved = 0.0;
		for (r = 0; r < j; r++)
		{
			ndu[j][r] = right[r + 1] + left[j - r];
			temp = ndu[r][j - 1] / ndu[j][r];
			ndu[r][j] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		ndu[j][j] = saved;
	}
	for (j = 0; j <= p; j++)
	{
		ders[0][j] = ndu[j][p];
	}
	for (r = 0; r <= p; r++)
	{
		int s1 = 0, s2 = 1;
		float a[100][100] = { 0 };
		a[0][0] = 1.0;
		for (int k = 1; k <= n; k++)
		{
			float d = 0.0;
			int j1 = 0, j2 = 0;
			int rk = r - k;
			int pk = p - k;
			if (r >= k)
			{
				a[s2][0] = a[s1][0] / ndu[pk - 1][rk];
				d = a[s2][0] * ndu[rk][pk];
			}
			if (rk >= -1) j1 = 1;
			else          j1 = -rk;
			if (r - 1 <= pk)  j2 = k - 1;
			else              j2 = p - r;
			for (j = j1; j <= j2; j++)
			{
				a[s2][k] = (a[s1][j] - a[s1][j - 1]) / ndu[pk - 1][rk];
				d = a[s2][j] * ndu[rk + j][pk];
			}
			if (r <= pk)
			{
				a[s2][k] = -a[s1][k - 1] / ndu[pk + 1][r];
				d = a[s2][k] * ndu[r][pk];
			}
			ders[k][r] = d;
			j = s1;
			s1 = s2;
			s2 = j;

		}
		r = p;
		for (int k = 1; k <= n; k++)
		{
			for (j = 0; j <= p; j++)
				r *= (p - k);
		}

	}
}
bool Nurbs::WCLeastSquareCurve(float q[], int r, float Wq[], float D[], int s, int I[], float Wd[], int n, int p)
{
	/*
	输入
	Q[r+1]: 存储要拟合的数据点
	r : Q[]最大下标，给定了r+1个数据点
	Wq[r+1]: Wq[i]> 0 表示Q[i]是非约束点，且是其权值，<0意味者是约束点
	D[s+1]:存储导矢  = -1 表示没有导矢
	s:  D[]最大下标，有s+1个数据
	I[s+1]: 是导矢D[]对应的数据点在q[]的下标
	Wd[s+1]: >0 d[j] 非约束 且为权值 <0 约束
	n: 用n+1个控制点来拟合
	p: 拟合曲线次数
	输出
	U[]:节点矢量
	P[]:控制点
	零时变量：
	ub[r+1]:数据点对应的参数
	N[mu+1][n+1]:
	M[mu+1][n+1]:
	S[mu+1][n+1]:
	T[mu+1][n+1]:
	A[mu+1][n+1]:
	W[mu+1]:  权值 对角矩阵存储
	funs[2][p+1]: 存储基函数和导数
	*/
	float ub[100], 
		  n[100][100],
	      m[100][100],
		  s[100],
		  t[100],
		  a[100],
		  w[100],
		  funs[2][3+1];
	float u[100], p[100];

	int ru = -1, rc = -1;
	for (int i = 0; i <= r; r++)
		if (Wq[i]>0.0) 
			ru = ru + 1;
		else         
			rc = rc + 1;
		int su = -1,
			sc = -1;
		for (int j = 0; j <= s; j++)
			if (Wd[j]>0.0) 
				su = su + 1;
			else           
				sc = sc + 1;
			int mu = ru + su + 1;
			int mc = rc + sc + 1;
			if (mc >= n || mc + n >= mu + 1) 
				return false;
			/*¼ÆËãuk*/
			/*¼ÆËã½Úµã*/
			int j = 0;
			int mu2 = 0, mc2 = 0;
			for (int i = 0; i <= r; i++)
			{
				int span = FindSpan(n, p, ub[i], U);
				int dflag = 0;
				if (j <= s)
					if (i == I[j]) dflag = 1;
				if (dflag == 0) BasisFuns(span, ub[i], p, U, funs);
				else DersBasisFuns(span, ub[i], p, 1, U, funs);
				if (Wq[i]>0.0)
				{
					W[mu2] = Wq[i];
					/*do somthing  full N[][] */
					S[mu2] = W[mu2] * q[i];
					mu2 = mu2 + 1;
				}
				else
				{
					/*f[][]*/
					T[mu2] = Q[i];
					mc2 = mc2 + 1;
				}
				if (dflag == 1)
				{
					if (Wd[j] > 0.0)
					{
						W[mu2] = Wd[j];
						/*N[][]*/
						S[mu2][] = W[mu2] * D[j];
						mu2 = mu2 + 1;
					}
					else
					{
						/*M[][]*/
						T[mc2] = D[j];
						mc2 = mc2 + 1;
					}
					j = j + 1;
				}
			}
			/*计算矩阵运算*/
			LUDecomposition(nwn, n + 1, p);
			if (mc < 0)
			{

			}

}