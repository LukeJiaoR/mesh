#pragma once

#include <vector>
#include <qfile.h>

#include "basis.h"


class LoadFile
{
public:
	LoadFile();
	virtual ~LoadFile();
	virtual void Load(QString filename) = 0;
	virtual void Draw() = 0;
	virtual int sizex() = 0;
	virtual int sizey() = 0;

};

