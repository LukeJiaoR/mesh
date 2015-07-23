
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
int FindSpan(int p, int n, float u, float U[]);

/*�㷨2.2*/
void BasisFuns(int i, float u, int p, float U[], float N[]);

/*�㷨2.3*/
void DersBasisFuns(int i, float u, int p, int n, float U[], float ders[][100]);

/*�㷨2.4*/
void OneBasisFuns(int p, int m, float U[], int i, float u, float Nip);

/*�㷨2.5*/
void DersOneBasisFuns(int p, int m, float U[], int i, float u, int n, float ders[]);


/*************************������**********************************/
/*�㷨3.2*/
void CurveDerivsAlg1(int n, int p, float U[], point P[], float u, int d, point CK[]);

/*�㷨3.3*/
void CurveDerivCpts(int n, int p, float U[], point P[], int d, int r2, int r1, point PK[][100]);

/*�㷨3.4*/
void CurveDerivsAlg2(int n, int p, float U[], point P[], float u, int d, point CK[]);