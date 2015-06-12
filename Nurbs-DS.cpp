#include <iostream>
using namespace std;


/*定义通用数据类型 */
typedef int INDEX;   
typedef short FLAG;
typedef int INTEGER;
typedef double REAL;
typedef char * STRING;
typedef short DEGRSE;  
typedef double PARAMETER; 


/*通用数据结构*/
typedef struct point     //普通点
{
	REAL x,
		 y,
		 z;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; }
}POINT;

typedef struct cpoint    //带权点
{
	REAL x,
		 y,
		 z,
		 w;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; this->w = 0.0; }
}CPOINT;

typedef struct cpolygon   //面
{
	INDEX n;
	CPOINT *Pw;
}CPOLYGON;
 
typedef struct knotvector    //节点矢量
{
	INDEX m;
	REAL * U;
}KNOTVECTOR;

typedef struct curve     //曲线
{
	CPOLYGON *pol;
	DEGRSE p;
	KNOTVECTOR * knt;
}CURVE;

    