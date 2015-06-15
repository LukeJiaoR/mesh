#include <iostream>
using namespace std;


/*����ͨ���������� */
typedef int INDEX;   
typedef short FLAG;
typedef int INTEGER;
typedef float REAL;
typedef char * STRING;
typedef short DEGRSE;  
typedef double PARAMETER; 


/*ͨ�����ݽṹ*/

struct point     //��ͨ��
{
	REAL x,
		 y,
		 z;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; }
	template<typename T>
	inline point & operator * (const T &p)
	{   //����*���㣬����point�������ĳ˷����㣬ʹ����ʽ�� point*p;
		this->x *= p;
		this->y *= p;
		this->z *= p;   //*this->w
		return *this;
	}
	inline point & operator + (const point &p)
	{
		//����+���㣬��������point���
		this->x += p.x;
		this->y += p.y;
		this->z += p.z;
		return *this;
	}
};
struct cpoint    //��Ȩ��
{
	REAL x,
		 y,
		 z,
		 w;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; this->w = 0.0; }
	template<typename T>
	inline cpoint & operator * (const T &p) 
	{   //����*���㣬����cpoint�������ĳ˷����㣬ʹ����ʽ�� cpoint*p;
		this->x *= p;
		this->y *= p;
		this->z *= p;
		this->w *= p;  //*this->w
		return *this; } 
	
	
	
	inline cpoint & operator + (const cpoint &p)
	       { 
			   //����+���㣬��������cpoint���
			   this->x += p.x;
			   this->y += p.y;
			   this->z += p.z;
			   this->w += p.w;
			   return *this;
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

    