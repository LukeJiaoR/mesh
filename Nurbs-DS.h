#pragma once

#include <iostream>
#include <armadillo>
using namespace arma;
using namespace std;
/*定义通用数据类型  */
typedef int INDEX;   
typedef short FLAG;
typedef int INTEGER;
typedef float REAL;
typedef char * STRING;
typedef short DEGRSE;  
typedef double PARAMETER; 


/*通用数据结构*/


struct cpoint    //带权点
{
	REAL x,
		y,
		z,
		w;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; this->w = 0.0; }
	void copy(cpoint p){ this->x = p.x; this->y = p.y; this->z = p.z; this->w = p.w; }
	template<typename T>
	inline cpoint & operator * (const T &p)
	{   //重载*运算，进行cpoint和其他的乘法运算，使用形式如 cpoint*p  cpoint类型在前;
		cpoint *q;
		q = new cpoint;
		q->x = this->x * p;
		q->y = this->y * p;
		q->z = this->z * p;
		q->w = this->w * p; //*this->w
		return *q;
	}


	inline cpoint & operator + (const cpoint &p)
	{
		//重载+运算，进行两个cpoint相加
		cpoint *q;
		q = new cpoint;
		q->x = this->x + p.x;
		q->y = this->y + p.y;
		q->z = this->z + p.z;
		q->w = this->w + p.w; //*this->w
		return *q;
	}
};


struct point     //普通点
{
	REAL x,
		 y,
		 z;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; }
	void copy(cpoint p){ this->x = p.x; this->y = p.y; this->z = p.z; }
	template<typename T>
	inline point & operator * (const T &p)
	{   //重载*运算，进行point和其他的乘法运算，使用形式如 point*p point类型在前;
		point *q;
		q = new point;
		q->x = this->x * p;
		q->y = this->y * p;
		q->z = this->z * p;   //*this->w
		return *q;
	}
	template<typename C>
	inline point & operator / (const C &p)
	{   //重载*运算，进行point和其他的乘法运算，使用形式如 point*p point类型在前;
		point *q;
		q = new point;
		q->x = this->x / p;
		q->y = this->y / p;
		q->z = this->z / p;   //*this->w
		return *q;
	}
	inline point & operator + (const point &p)
	{
		//重载+运算，进行两个point相加
		point *q;
		q = new point;
		q->x = this->x + p.x;
		q->y = this->y + p.y;
		q->z = this->z + p.z;   //*this->w
		return *q;
	}
	inline point & operator - (const point &p)
	{
		//重载+运算，进行两个point相加
		point *q;
		q = new point;
		q->x = this->x - p.x;
		q->y = this->y - p.y;
		q->z = this->z - p.z;   //*this->w
		return *q;
	}
	inline point & operator + (const float &p)
	{
		//重载+运算，进行两个point相加
		point *q;
		q = new point;
		q->x = this->x + p;
		q->y = this->y + p;
		q->z = this->z + p;   //*this->w
		return *q;
	}
	
};




struct cpolygon   //面
{
	INDEX n;
	cpoint *Pw;
};
 

struct knotvector    //节点矢量
{
	INDEX m;
	REAL * U;
};


struct curve     //曲线
{
	cpolygon *pol;
	DEGRSE p;
	knotvector * knt;
};

    