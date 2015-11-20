\
/*
�ṩһЩ�����ļ��㺯��
1��FindSpan ������u��Ӧ���ڵĽڵ�����
2��BasisFuns������u�Ļ�����
3��DersBasisFuns �� ����u�Ļ����������Ӧ�ĵ���
4��OneBasisFuns �����㵥��������
5��DersOneBaisFuns �� ���㵥���������Լ���n�׵���
*/



#include "Nurbs-DS.h"

/*************************�ڶ���**********************************/
/*�㷨2.1*/
int FindSpan(int p, int n, float u, vector<float> U);

/*�㷨2.2*/
void BasisFuns(int i, float u, int p, vector<float> U, vector<float>& N);

/*�㷨2.3*/
void DersBasisFuns(int i, float u, int p, int n, vector<float> U, float ders[][100]);

/*�㷨2.4*/
void OneBasisFuns(int p, int m, float U[], int i, float u, float Nip);

/*�㷨2.5*/
void DersOneBasisFuns(int p, int m, float U[], int i, float u, int n, float ders[]);

/*************************������**********************************/

point BSplineCurvePoint(int n, int p, vector<float> U, vector<point> P, float u);
/*�㷨3.2*/
void CurveDerivsAlg1(int n, int p, float U[], point P[], float u, int d, point CK[]);

/*�㷨3.3*/
void CurveDerivCpts(int n, int p, float U[], point P[], int d, int r2, int r1, point PK[][100]);

/*�㷨3.4*/
void CurveDerivsAlg2(int n, int p, float U[], point P[], float u, int d, point CK[]);

/*�㷨3.5*/
void SurfacePoint(int n, int p, float U[], int m, int q, float V[], point P[][3], float u, float v, point S);

/*�㷨3.6*/
void SurfaceDerivsAlg1(int n, int p, float U[], int m, int q, float V[], point P[][3], float u, float v, const int d, point SKL[][100]);


/*�㷨9.6*/
bool WCLeastSquaresCureve(vector<point> Q, int r,     //Q[]�洢��ϵ����ݵ�Q�ĸ���Ϊr+1
	float Wq[],           //>0 �Ƿ�Լ����,<0��Լ���� ����С r+1
	vector<point> D, int s, int I[],       // D[]�洢��ʸ����ʸ����Ϊs+1��s = -1��ʾû�е�ʸ,I[]�洢��Ӧ��k����ʸ��Ӧ�ĵ���Q�е��±�
	float Wd[],           //����D[]�е�ʸ��Լ���ԡ�
	int n,                //Ԥ����n�����Ƶ������
	int p,                //�������Ϊp��
	vector<float>& U, vector<cpoint>& P   //����Ľڵ�����U�Ϳ��Ƶ�p.
	);


bool BsplineApp(vector<point> Q, int r,     //Q[]�洢��ϵ����ݵ�Q�ĸ���Ϊr+1
	//float Wq[],           //>0 �Ƿ�Լ����,<0��Լ���� ����С r+1
	//vector<point> D, int s, int I[],       // D[]�洢��ʸ����ʸ����Ϊs+1��s = -1��ʾû�е�ʸ,I[]�洢��Ӧ��k����ʸ��Ӧ�ĵ���Q�е��±�
	//float Wd[],           //����D[]�е�ʸ��Լ���ԡ�
	int n,                //Ԥ����n�����Ƶ������
	int p,                //�������Ϊp��
	vector<float>& U, vector<point>& P   //����Ľڵ�����U�Ϳ��Ƶ�p.)
	);