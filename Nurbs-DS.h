#include <iostream>
using namespace std;


/*定义通用数据类型 */
typedef int INDEX;   
typedef short FLAG;
typedef int INTEGER;
typedef float REAL;
typedef char * STRING;
typedef short DEGRSE;  
typedef double PARAMETER; 


/*通用数据结构*/

struct point     //普通点
{
	REAL x,
		 y,
		 z;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; }
	template<typename T>
	inline point & operator * (const T &p)
	{   //重载*运算，进行point和其他的乘法运算，使用形式如 point*p;
		this->x *= p;
		this->y *= p;
		this->z *= p;   //*this->w
		return *this;
	}
	inline point & operator + (const point &p)
	{
		//重载+运算，进行两个point相加
		this->x += p.x;
		this->y += p.y;
		this->z += p.z;
		return *this;
	}
};
struct cpoint    //带权点
{
	REAL x,
		 y,
		 z,
		 w;
	void init() { this->x = 0.0; this->y = 0.0; this->z = 0.0; this->w = 0.0; }
	template<typename T>
	inline cpoint & operator * (const T &p) 
	{   //重载*运算，进行cpoint和其他的乘法运算，使用形式如 cpoint*p;
		this->x *= p;
		this->y *= p;
		this->z *= p;
		this->w *= p;  //*this->w
		return *this; } 
	
	
	
	inline cpoint & operator + (const cpoint &p)
	       { 
			   //重载+运算，进行两个cpoint相加
			   this->x += p.x;
			   this->y += p.y;
			   this->z += p.z;
			   this->w += p.w;
			   return *this;
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

    