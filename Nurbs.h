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
	/*Q[r+1]: �洢Ҫ��ϵ����ݵ�
	  r : Q[]����±꣬������r+1�����ݵ�
	  Wq[r+1]: Wq[i]> 0 ��ʾQ[i]�Ƿ�Լ���㣬������Ȩֵ��<0��ζ����Լ����
	  D[s+1]:�洢��ʸ  = -1 ��ʾû�е�ʸ
	  s:  D[]����±꣬��s+1������
	  I[s+1]: �ǵ�ʸD[]��Ӧ�����ݵ���q[]���±�
	  Wd[s+1]: >0 d[j] ��Լ�� ��ΪȨֵ <0 Լ��
	  n: ��n+1�����Ƶ������
	  p: ������ߴ���
	*/
	

private:
	int m_iNumofPoints;

};

