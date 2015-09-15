#include <iostream>
using namespace std;

#include "LoadFile.h"
#include "basis.h"

using std::vector;

class Nurbs :
	public LoadFile
{
public:
	Nurbs();
	~Nurbs();
	void RatCurveDerivs(float Aders[], float wders[], int d, float CK[]);

private:
	vector<point>  Cw;

};
