#include <iostream>
using namespace std;


/*����ͨ���������� */
typedef int INDEX;   
typedef short FLAG;
typedef int INTEGER;
typedef double REAL;
typedef char * STRING;
typedef short DEGRSE;  
typedef double PARAMETER; 


/*ͨ�����ݽṹ*/
typedef struct point     //��ͨ��
{
	REAL x,
		 y,
		 z;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; }
}POINT;

typedef struct cpoint    //��Ȩ��
{
	REAL x,
		 y,
		 z,
		 w;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; this->w = 0.0; }
}CPOINT;

typedef struct cpolygon   //��
{
	INDEX n;
	CPOINT *Pw;
}CPOLYGON;
 
typedef struct knotvector    //�ڵ�ʸ��
{
	INDEX m;
	REAL * U;
}KNOTVECTOR;

typedef struct curve     //����
{
	CPOLYGON *pol;
	DEGRSE p;
	KNOTVECTOR * knt;
}CURVE;

    