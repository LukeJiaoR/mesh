#include "basis.h"

#include <armadillo>
#include <math.h>
#include <iostream>
#include <vector>




using namespace std;
using namespace arma;

const int NUM = 100;

inline int isMin(int a, int b)
{
	return a < b ? a : b;
}


inline int isMax(int a, int b)
{
	return a > b ? a : b;
}

int FindSpan(int n, int p, float u, vector<float> U)
{
	/*
	��λ�������ڵĽڵ���������
	*/
	int low, high, mid;
	if (u >= U[n]) // savety >= check
		return n - p ;
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

int FindSpan(int n, int p, float u, mat &U)
{
	int low, high, mid;
	if (u >= U(n)) // savety >= check
		return n - p;
	low = p;
	high = n+1;
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

void BasisFuns(int i, float u, int p, vector<float> U, vector<float>& N)
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
		left.push_back( u - U[i + 1 - j]);
		right.push_back(  U[i + j] - u);
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

//void BasisFuns(int i, float u, int p, vector<float> U, vector<vector<float>> ndu)
//{
//	int j, r;
//	float left[NUM], right[NUM];
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
//		ndu[0][j] = saved;
//	}
//}

//void BasisFuns(int i, float u, int p, vector<float> U, fmat &N)
//{
//	vector<float> left, right;
//	left.push_back(0.0);
//	right.push_back(0.0);
//	N(0,0) = 1.0;
//
//	for (int j = 1; j <= p; j++)
//	{
//		float temp;
//		left.push_back( u - U[i + 1 - j]);
//		right.push_back(  U[i + j] - u);
//		float saved = 0.0;
//		for (int r = 0; r < j; r++)
//		{
//
//			temp = N(0,r) / (right[r + 1] + left[j - r]);
//			N(0,r) = saved + right[r + 1] * temp;
//			saved = left[j - r] * temp;
//		}
//		N(0,j) = saved;
//	}
//}

void DersBasisFuns(int i, float u, int p, int n, vector<float> U, vector<vector<float> >& ders)
{
	/*
	�����������ֵ�Լ�n�׵���
	*/
	int j, r;
	vector<vector<float> > ndu(p+1);
	vector<float> left, right;
	left.push_back(0.0);
	right.push_back(0.0);
	ndu[0].push_back(1.0);

	cout << "here" << endl;

	for (j = 1; j <= p; j++)
	{
		float temp;
		left.push_back(u - U[i + 1 - j]);
		right.push_back(U[i + j] - u);
		float saved = 0.0;
		for (r = 0; r < j; r++)
		{
			ndu[j][r] = right[r + 1] + left[j - r];
			temp = ndu[r][j - 1] / ndu[j][r];
			ndu[r][j] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		ndu[j].push_back(saved);
	}
	for (j = 0; j <= p; j++)
	{
		ders[0].push_back(ndu[j][p]);
	}
	for (r = 0; r <= p; r++)
	{
		int s1 = 0, s2 = 1;
		vector<vector<float>> a(2);
		for (int i = 0; i < 3; i++)
			a[i].resize(p+1);
		a[0].push_back(1.0);
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
			ders[k].push_back(d);
			j = s1;    s1 = s2;   s2 = j;
		}	
	}
	r = p;
    for (int k = 1; k <= n; k++)
	{
		for (j = 0; j <= p; j++)
			ders[k][j] *= r;
		r *= (p - k);
	}
}

float OneBasisFuns(int p, int m, vector<float> U, int i, float u)
{
	/*
	��������������
	*/
	float Nip;
	vector<float> N;
	float saved,
		Uleft,
		Uright,
		temp;
	if ((i == 0 && u == U[0]) ||
		(i == m - p - 1 && u == U[m]))
	{
		Nip = 1.0; return Nip;
	}
	if (u < U[i] || u >= U[i + p + 1])
	{
		Nip = 0.0; return Nip;
	}
	for (int j = 0; j <= p; j++)
	{
		if (u > U[i + j] && u < U[i + j + 1])
			N.push_back(1.0);
		else N.push_back(0.0);
	}
	for (int k = 1; k <= p; k++)
	{
		if (N[0] == 0.0)
			saved = 0.0;
		else saved = ((u - U[i]) * N[0]) / (U[i + k] - U[i]);
		for (int j = 0; j < p - k + 1; j++)
		{
			Uleft = U[i + j + 1];
			Uright = U[i + j + k + 1];
			if (N[j + 1] == 0.0)
			{
				N[j] = saved;
				saved = 0.0;
			}
			else
			{
				temp = N[j + 1] / (Uright - Uleft);
				N[j] = saved + (Uright - u) * temp;
				saved = (u - Uleft) * temp;
			}
		}
	}
	Nip = N[0];

	return Nip;
	
}

void DersOneBasisFuns(int p, int m, vector<float> U, int i, float u, int n, vector<float>& ders)
{
	/*
	������������k�׵������ֱ�洢��ders[k].
	*/
	vector<float> ND;
	vector<vector<float>> N(p+1);
	float saved,
		Uleft,
		Uright,
		temp;

	if (u < U[i] || u >= U[i + p + 1])
	{
		ders.push_back(0.0); return;
	}
	for (int j = 0; j < p; j++)
	{
		if (u > U[i + j] && u < U[i + j + 1])
			N[j].push_back(1.0);
		else N[j].push_back(0.0);
	}
	for (int k = 1; k <= p; k++)
	{
		if (N[0][k - 1] == 0.0)
			saved = 0.0;
		else saved = ((u - U[i]) * N[0][k - 1]) / (U[i + k] - U[i]);
		for (int j = 0; j < p - k + 1; j++)
		{
			Uleft = U[i + j + 1];
			Uright = U[i + j + k + 1];
			if (N[j + 1][k + 1] == 0.0)
			{
				N[j].push_back(saved);
				saved = 0.0;
			}
			else
			{
				temp = N[j + 1][k - 1] / (Uright - Uleft);
				N[j].push_back( saved + (Uright - u) * temp);
				saved = (u - Uleft) * temp;
			}
		}
	}
	ders.push_back(N[0][p]);
	for (int k = 1; k <= n; k++)
	{
		for (int j = 0; j <= k; j++)
			ND.push_back(N[j][p - k]);
		for (int jj = 1; jj <= k; jj++)
		{
			if (ND[0] == 0.0) saved = 0.0;
			else saved = ND[0] / (U[i + p - k + jj] - U[i]);
			for (int j = 0; j < k - jj + 1; j++)
			{
				Uleft = U[i + j + 1];
				Uright = U[i + j + p + jj + 1];
				if (ND[j + 1] == 0.0)
				{
					ND[j] = (p - k + jj)* saved;
					saved = 0.0;
				}
				else
				{
					temp = ND[j + 1] / (Uright - Uleft);
					ND[j] = (p - k + jj) * (saved * temp);
					saved = temp;
				}
			}
		}
		ders.push_back(ND[0]);
	}
}


/*�㷨3.1 B�������ߵ�*/
point BSplineCurvePoint(int n,    //���Ƶ������±�	
				int p,            //���ߴ���
				vector<float> U,   //�ڵ�����
				vector<point> P,   //���Ƶ㣬�洢��vector��
				float u
				)
{  //�õ�outPoint
	//float w = 0.0;
	vector<float> N;
	point *out;
	out = new point();
	out->init();
	
	int i;
	int span = FindSpan(n, p, u, U);
	BasisFuns(span, u, p, U, N);

	
	for (i = 0; i <= p; i++)
	{
		*out = *out + P[span - p + i] * N[i];
	}

	return *out;    //��������ĵ�

}

/*�㷨3.2*/
void CurveDerivsAlgl(int n,	//���Ƶ������±�	
					 int p,  //���ߴ���
					 vector<float> U, //�ڵ�����
					 point P[],   //���Ƶ�
					 float u,     //ȡ�Ĳ���
					 int d,    //��Ľ���
					 vector<point> CK     //���
					 )
{
	/*���������ϵĵ�ʸ
	n:���Ƶ���������
	p:���ߵĴ���
	U:�ڵ�ʸ��
	P:���Ƶ�����
	CK[]:���.CK[k]����k�׵�ʸ
	*/
	//float nders[NUM][NUM];
	vector<vector<float>> nders;
	int du = min(d, p);
	point temp;  temp.init();
	int span = FindSpan(n, p, u, U);
	DersBasisFuns(span, u, p, du, U, nders);
	for (int k = 0; k <= du; k++)
	{
		temp.init();
		CK.push_back(temp);
		for (int j = 0; j <= p; j++)
		{
			CK[k] = CK[k] + P[span - p + j] * nders[k][j];
		}
	}
	for (int k = p+1; k <= d; k++)
		{
			temp.init();
			CK.push_back(temp);
		}
}

/*�㷨3.3*/
void CurveDerivCpts(int n, int p, vector<float> U, point P[], int d, int r2, int r1, point PK[][100])
{
	/*���㵼���ߵĿ��Ƶ�
	*/
	int r = r2 - r1;
	for (int i = 0; i <= r; i++)
	{
		PK[0][i] = P[r1 + 1];
	}
	for (int k = 1; k <= d; k++)
	{
		int tmp = p - k + 1;
		for (int i = 0; i <= r-k; i++)
		{
			PK[k][i] = ((PK[k - 1][i + 1] - PK[k - 1][i])/(U[r1+i+p+1]-U[r1+i+k]))*tmp;
		}
	}
}

/*�㷨3.4*/
void CurveDerivsAlg2(int n, int p, vector<float> U, point P[], float u, int d, point CK[])
{
	/*
	����B���������ϵĵ㼰ֱ��d�׵�ʸ
	*/
	//float N[NUM][NUM];
	vector<vector<float>> N;
    point PK[NUM][NUM];
	int du = min(d, p);
	for (int k = p + 1; k <= du; k++)
	{
		CK[k].init();
	}
	int span = FindSpan(n, p, u, U);
	DersBasisFuns(span, u, p, du, U, N);
	CurveDerivCpts(n, p, U, P, du, span - p, span, PK);
	for (int k = 0; k <= du; k++)
	{
		CK[k].init();
		for (int j = 0; j <= p-k; j++)
		{
			CK[k] = CK[k] + (  PK[k][j] * N[j][p-k]);
		}
	}
}



/*�㷨3.4*/
void BSplineSurfacePoint(int n, int p, vector<float> U, int m, int q, vector<float> V, point P[][3], float u, float v, point S)
{
	/*����B���������ϵĵ�*/
	/*����*/
	/*��� S*/
	vector<float> Nu,Nv;
	int uspan = FindSpan(n, p, u, U);
	BasisFuns(uspan, u, p, U, Nu);
	int vspan = FindSpan(n, p, u, V);
	BasisFuns(vspan, v, q, V, Nv);
	int uind = uspan - p;
	S.init();
	for (int l = 0; l <= q; l++)
	{
		point temp;
		temp.init();
		int vind = vspan - q + 1;
		for (int k = 0; k <= p; k++)
		{
			temp = temp + Nu[k] + P[uind + k][vind];
		}
		S = S + temp*Nv[1];
	}	
}


/*�㷨3.6*/
void SurfaceDerivsAlg1(int n, int p, vector<float> U, int m, int q, vector<float> V, point P[][3], float u, float v, const int d, point SKL[][NUM])
{
	/*�������浼��*/
	/*���룺*/
	/*���������SKL*/
	vector<vector<float>> Nu(p+1), Nv(p+1);
	int du = min(d, p);
	for (int k = p+1; k <=d; k++)
	{
		for (int l = 0; l <= d-k; l++)
		{
			SKL[k][l].init();
		}
	}
	int dv = min(d, q);
	for (int k = q+1; k <= d; k++)
	{
		for (int l = 0; l <= d-k; l++)
		{
			SKL[l][k].init();
		}
	}
	int uspan = FindSpan(n, p, u, U);
	DersBasisFuns(uspan, u, p, du, U, Nu);
	int vspan = FindSpan(m, q, v, V);
	DersBasisFuns(vspan, v, q, dv, V, Nv);
	point t;
	vector<point> temp;
	for (int k = 0; k <= du; k++)
	{
		for (int s = 0; s <= q; s++)
		{
			t.init();
			temp.push_back(t);
			for (int r = 0; r <= p; r++)
			{
				temp[s] = temp[s] +  P[uspan - p + r][vspan] * Nu[k][r] ;
			}
		}
		int dd = min(d - k, dv);
		for (int l = 0; l <= dd; l++)
		{
			SKL[k][l].init();
			for (int s = 0; s <= q; s++)
			{
				SKL[k][l] = SKL[k][l] + temp[s] * Nv[l][s];
			}
		}
	}
}


/*�㷨3.7*/
//void SurfaceDerivCpt(int n, int p, float U[], int m, int q, float V[], point P[], int d, int r1, int r2, int s1, int s2, point PKL[][NUM])
//{
//	/*������ƽ��Ŀ��Ƶ�*/
//
//}

float Distance3D(point a, point b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	float z = a.z - a.z;
	float c = x*x + y*y + z*z;
	return sqrt(c);
}
/*�㷨9.3 ������������������ݵ�*/
bool SurfMeshParams(int n, int m, point Q[][NUM], float uk[], float vl[])
{
	float cds[] = { 0 };
	int num = m + 1;
	uk[0] = 0.0; uk[n] = 1.0;
	

	/*����vk*/
	for (int l = 0; l <= m; l++)
	{
		float total = 0.0;
		for (int k = 1; k <= n; k++)
		{
			cds[k] = Distance3D(Q[k][l], Q[k - 1][l]);
			total = total + cds[k];
		}
		if (0.0 == total) num = num - 1;
		else
		{
			float d = 0.0;
			for (int k = 1; k < n; k++)
			{
				d = d + cds[k];
				uk[k] = uk[k] + d / total;
			}

		}
	}
	if (0 == num) return false; 
	for (int k = 1; k < n; k++)
	{
		uk[k] = uk[k] / num;
	}

	/*����vl*/
	vl[0] = 0.0; vl[m] = 1.0;
	num = n + 1;
	for (int l = 0; l <= n; l++)
	{
		float total = 0.0;
		for (int k = 1; k <= m; k++)
		{
			cds[k] = Distance3D(Q[k][l], Q[k][l]);
			total = total + cds[k];
		}
		if (0.0 == total) num = num - 1;
		else
		{
			float d = 0.0;
			for (int k = 1; k < m; k++)
			{
				d = d + cds[k];
				vl[k] = vl[k] + d / total;
			}
		}
	}
	if (0 == num) return false;
	for (int k = 1; k < m; k++)
	{
		vl[k] = vl[k] / num;
	}


	return true;

}

//��A[a][]����B[][]�ĵ�b��,��c��Ԫ�أ�
void MartixValue(vector<vector<float>> A, int a, mat &B, int b,int c)
{
	for (int i = 0; i < c; i++)
	{
		B(b,i) = A[a][i];
	}
}

/*���������ݵ�*/
void Getub(vector<point> Q, int r, vector<float>& ub)
{
	ub.push_back(0.0);
	vector<float>::iterator cerr = ub.begin();
	float d = 0.0;
	for (int i = 1; i <= r; i++)
	{
		d = d + Distance3D(Q[i], Q[i - 1]);
	}

	/*����ub[i]����ub��*/
	for (int i = 1  ; i <= r ; i++,cerr++)
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
	float d = static_cast<float>(m + 1) / (n - p + 1);
	for (int i = 0; i <= p; i++)  U.push_back(0);
	for (int j = 1; j <= n-p; j++)
	{
		int i = (int)(j*d);
		float a = j*d - i;
		U.push_back((1.0 - a)*ub[i - 1] + a*ub[i]);
	}
	for (int i = 0; i <= p; i++)
	{
		U.push_back(1);
	}
}


/*�㷨9.6*/
bool WCLeastSquaresCureve(vector<point> Q, int r,     //Q[]�洢��ϵ����ݵ�Q�ĸ���Ϊr+1
						  float Wq[],           //>0 �Ƿ�Լ����,<0��Լ���� ����С r+1
						  vector<point> D, int s, int I[],       // D[]�洢��ʸ����ʸ����Ϊs+1��s = -1��ʾû�е�ʸ,I[]�洢��Ӧ��k����ʸ��Ӧ�ĵ���Q�е��±�
						  float Wd[],           //����D[]�е�ʸ��Լ���ԡ�
						  int n,                //Ԥ����n+1�����Ƶ������
						  int p,                //�������Ϊp��
						  vector<float>& U, vector<cpoint>& P   //����Ľڵ�����U�Ϳ��Ƶ�p.
						  )
{
	int ru = -1, rc = -1;
	vector<vector<float> >
		funs(2);
		/*N[][NUM] = {0},
		M[][NUM] = {0}*/
		;
	
	/*float
		W[NUM] = { 0 }*/;
	/*point
		T[NUM] = {0},
		S[NUM] = {0},
		A[NUM] = {0};*/

	for (int i = 0; i <= r; i++)
	{

		if (Wq[i] > 0.0) ru = ru + 1; // Wq[]��СΪr+1��������r+1 = rc+ru;
		else rc = rc + 1;
	}
	int su = -1, sc = -1;
	for (int j = 0; j <= s; j++)
	{
		if (Wd[j] > 0.0) su = su + 1;   //Wd[]��СΪs+1��������s = sc+su;
		else sc = sc + 1;
	}
	int mu = ru + su + 1;   
	int mc = rc + sc + 1; 
	mat N(mu + 1, n + 1),         //N =[ NDip(uk)] ��i��������������һ�׵�����uk����ֵ
		M(mc + 1, n + 1),
		S(mu + 1, 3),      //��Լ��������
		T(mc + 1, 3),      //Լ��������Ŀ 
		W(mu + 1,mu+1)     //Ȩֵ �ԽǾ���
		;
	N.fill(0.0); M.fill(0.0); S.fill(0.0); T.fill(0.0); W.fill(0.0);
	//W.save("W.txt", raw_ascii);
	std::cout << " before 1" << endl;
	
	if ( mc >= n || mc + n >= mu + 1)
	{
		return false;//���ش���
	}
	vector<float> ub;
	std::cout << " before 2" << endl;
	//(9.5ʽ)���㣬����ub[]
	Getub(Q, n, ub);
	//9.68,9.69 ����U[]
	vector<float>::iterator cerr;
	for (cerr = ub.begin(); cerr != ub.end(); cerr++)
	{
		cout << *cerr << " ";
	}
	cout << endl;
	GetU(r, n, p, ub, U);
	for (cerr = U.begin(); cerr != U.end(); cerr++)
	{
		cout << *cerr << " ";
	}
	cout << endl;
	std::cout << " before 3" << endl;
	int j = 0;
	int mu2 = 0, mc2 = 0;
	int i;
	for (cerr = ub.begin(),i = 0; i <= r; i++,cerr++)
	{
		int span = FindSpan(n, p, *cerr, U);
		int dflag = 0;
		if (j <= s)
		{ 
			if (i == I[j])
			{
				dflag = 1;
			}
		}
		if (0 == dflag)  BasisFuns(span, *cerr, p, U, funs[0]);
		else DersBasisFuns(span, *cerr, p, 1, U, funs);
		cout << "here" << endl;
		if (Wq[i] > 0.0)
		{
			std::cout << "Wq[i] > 0.0" << endl;
			W(mu2,mu2) = Wq[i];
			//��funs[0][]����N[][]�ĵ�mc2�У�
			
			MartixValue(funs, 0, N, mc2, n + 1);
			S(mu2, 0) = Q[i].x * W(mu2);
			S(mu2, 1) = Q[i].y * W(mu2);
			S(mu2, 2) = Q[i].z * W(mu2);
			mu2 = mu2 + 1;
		}
		else
		{
			std::cout << "else Wq[i] > 0.0" << endl;
			/*Լ����*/
			//��funs[0][]����M[mc2][]
			MartixValue(funs, 0, M, mc2, n + 1);
			T(mc2, 0) = Q[i].x ;
			T(mc2, 1) = Q[i].y ;
			T(mc2, 2) = Q[i].z ;
			mc2 = mc2 + 1;
		}
		std::cout <<  " before 1 == dflag" << endl;
		if (1 == dflag)
		{
			std::cout << "1 == dflag" << endl;
			/*������һ��ĵ�ʸ*/
			if (Wd[j] > 0.0)
			{
				std::cout << "Wd[j] > 0.0" << endl;
				W(mu2, mu2) = Wd[i];
				//��funs[1][]����N[mu2][]
				MartixValue(funs, 1, N, mc2, n + 1);
				S(mu2, 0) = D[i].x * W(mu2);
				S(mu2, 1) = D[i].y * W(mu2);
				S(mu2, 2) = D[i].z * W(mu2);
				mu2 = mu2 + 1;
			}
			else
			{
				std::cout << "else Wd[j] > 0.0" << endl;
				/*Լ����ʸ*/
				//��funs[1][]����M[mu2][]
				MartixValue(funs, 1, M, mc2, n + 1);
				T(mc2, 0) = D[i].x;
				T(mc2, 1) = D[i].y;
				T(mc2, 2) = D[i].z;
				mc2 = mc2 + 1;
			}
			j = j + 1;
		}
	}/*forѭ������*/
	//����N*WN��N*WS��
	W.save("W.txt", raw_ascii);

	std::cout << " before 4" << endl;
	mat NWN = N.t()*W*N;
	mat NWS = N.t()*W*S;
	
	cout << det(NWN) << endl;
	NWN.save("NWN.txt", raw_ascii);
	//LUDecomposition(N*WN,n+1,p);
	if (mc < 0)
	{
		/*��Լ��*/
		/*��ʱ(9.71)ʽ�򻯳ɣ�N*WN��P = N*WS*/
		//��FowardBackward()�����Ƶ�P[];
		cout << NWN.n_rows << " " << NWS.n_rows << endl;
		mat CPo = arma::solve(NWN, NWS); //inv(NWN)*NWS;  
		//CPo.print("�������ݵ�:");
		//��p���뵽P[]��;
		for (int i = 0; i < n+1; i++)
		{
			cpoint out;

			out.x = CPo(i, 0);
			out.y = CPo(i, 1);
			out.z = CPo(i, 2);
			
			P.push_back(out);
 		}
		return true;
	}
	//��FowardBackward�������������N*WN��-1;
	//���о�������õ� �� M(N*WN)-1M* �� M(N*WN)-1(N*WS)-T
	//��⣨9.75���õ������������ӣ��������A[];
	mat A = inv(M*inv(NWN)*M.t())*inv(M*inv(NWN)*NWS - T);
	std::cout << " before 5" << endl;
	/*Ȼ�����P = ��N*WN��-1((N*WS)-M*A)  (9.74)*/
	mat CPo = inv(NWN)*NWS - inv(NWN)*M.t()*A;
	//CPo.print("�������ݵ�:");
	//��p���뵽P[]��
	for (int i = 0; i < n + 1; i++)
	{
		cpoint out;
		out.x = CPo(i, 0);
		out.y = CPo(i, 1);
		out.z = CPo(i, 2);
		P.push_back(out);
	}
	return true;
}




bool BsplineApp(vector<point> Q, int r,     //Q[]�洢��ϵ����ݵ�Q�ĸ���Ϊr+1
	int n,                //Ԥ����n+1�����Ƶ������
	int p,                //�������Ϊp��
	vector<float>& U, vector<point>& P   //����Ľڵ�����U�Ϳ��Ƶ�p.)
	)
{
	vector<vector<float> >
		funs(2);
	mat N(r + 1, n + 1),         //N =[ NDip(uk)] ��i��������������һ�׵�����uk����ֵ
		M(r + 1, n + 1),
		S(r + 1, 3),      //��Լ��������
		T(r + 1, 3)      //Լ��������Ŀ 
		//W(r + 1, r + 1)     //Ȩֵ �ԽǾ���
		;
	N.fill(0.0); M.fill(0.0); S.fill(0.0); T.fill(0.0); //W.fill(0.0);
	vector<float> ub;
	Getub(Q, r, ub);
	//9.68,9.69 ����U[]
	vector<float>::iterator cerr;
	cout << " UB[] :" << endl;
	for (cerr = ub.begin(); cerr != ub.end(); cerr++)
	{
		cout << *cerr << " ";
	}
	cout << endl;
	GetU(r, n, p, ub, U);
	cout << " U[] : " << endl;
	for (cerr = U.begin(); cerr != U.end(); cerr++)
	{
		cout << *cerr << " ";
	}
	cout << sizeof(U) - 1;
	cout << endl;
	for (int i = 0; i <= r;i++)
	{
		for (int j = 0; j <= n;j++)
		{
			N(i, j)=OneBasisFuns(p, sizeof(U) - 1, U, i, ub[j] );
			//cout << N(i, j) << endl;
		}
	}
	
	//N.save("N.txt", raw_ascii);
	for (int i = 0; i < r+1; i++)
	{
		S(i, 0) = Q[i].x;
		S(i, 1) = Q[i].y;
		S(i, 2) = Q[i].z;
	}
	//S.save("S.txt", raw_ascii);
	mat PO = solve(N, S);
	PO.save("OUT.txt", raw_ascii);
	cout << "Control Point : " << endl;
	for (int i = 0; i < n + 1; i++)
	{
		point out;
		out.x = PO(i, 0);
		cout << PO(i, 0) << " ";
		out.y = PO(i, 1);
		cout << PO(i, 1) << " ";
		out.z = PO(i, 2);
		cout << PO(i, 2) << " ";
		P.push_back(out);
	}
	return true;
}