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
typedef struct point
{
	REAL x,
		 y,
		 z;
}POINT;

typedef struct cpoint
{
	REAL x,
		 y,
		 z,
		 w;
}CPOINT;

typedef struct cpolygon
{
	INDEX n;
	CPOINT *Pw;
}CPOLYGON;

typedef struct knotvector
{
	INDEX m;
	REAL * U;
}KNOTVECTOR;

typedef struct curve
{
	CPOLYGON *pol;
	DEGRSE p;
	KNOTVECTOR * knt;
}CURVE;

