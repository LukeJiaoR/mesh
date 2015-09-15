#pragma once

#include <iostream>
#include <armadillo>
using namespace arma;
using namespace std;
/*����ͨ����������  */
typedef int INDEX;   
typedef short FLAG;
typedef int INTEGER;
typedef float REAL;
typedef char * STRING;
typedef short DEGRSE;  
typedef double PARAMETER; 


/*ͨ�����ݽṹ*/


struct cpoint    //��Ȩ��
{
	REAL x,
		y,
		z,
		w;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; this->w = 0.0; }
	void copy(cpoint p){ this->x = p.x; this->y = p.y; this->z = p.z; this->w = p.w; }
	template<typename T>
	inline cpoint & operator * (const T &p)
	{   //����*���㣬����cpoint�������ĳ˷����㣬ʹ����ʽ�� cpoint*p  cpoint������ǰ;
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
		//����+���㣬��������cpoint���
		cpoint *q;
		q = new cpoint;
		q->x = this->x + p.x;
		q->y = this->y + p.y;
		q->z = this->z + p.z;
		q->w = this->w + p.w; //*this->w
		return *q;
	}
};


struct point     //��ͨ��
{
	REAL x,
		 y,
		 z;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; }
	void copy(cpoint p){ this->x = p.x; this->y = p.y; this->z = p.z; }
	template<typename T>
	inline point & operator * (const T &p)
	{   //����*���㣬����point�������ĳ˷����㣬ʹ����ʽ�� point*p point������ǰ;
		point *q;
		q = new point;
		q->x = this->x * p;
		q->y = this->y * p;
		q->z = this->z * p;   //*this->w
		return *q;
	}
	template<typename C>
	inline point & operator / (const C &p)
	{   //����*���㣬����point�������ĳ˷����㣬ʹ����ʽ�� point*p point������ǰ;
		point *q;
		q = new point;
		q->x = this->x / p;
		q->y = this->y / p;
		q->z = this->z / p;   //*this->w
		return *q;
	}
	inline point & operator + (const point &p)
	{
		//����+���㣬��������point���
		point *q;
		q = new point;
		q->x = this->x + p.x;
		q->y = this->y + p.y;
		q->z = this->z + p.z;   //*this->w
		return *q;
	}
	inline point & operator - (const point &p)
	{
		//����+���㣬��������point���
		point *q;
		q = new point;
		q->x = this->x - p.x;
		q->y = this->y - p.y;
		q->z = this->z - p.z;   //*this->w
		return *q;
	}
	inline point & operator + (const float &p)
	{
		//����+���㣬��������point���
		point *q;
		q = new point;
		q->x = this->x + p;
		q->y = this->y + p;
		q->z = this->z + p;   //*this->w
		return *q;
	}
	
};




struct cpolygon   //��
{
	INDEX n;
	cpoint *Pw;
};
 

struct knotvector    //�ڵ�ʸ��
{
	INDEX m;
	REAL * U;
};


struct curve     //����
{
	cpolygon *pol;
	DEGRSE p;
	knotvector * knt;
};

    