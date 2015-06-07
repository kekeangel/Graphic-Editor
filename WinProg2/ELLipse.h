#pragma once

#include "Object_Draw.h"

class ELLipse : public Object_Draw
{
public:
	ELLipse();
	virtual ~ELLipse();
	virtual void Draw(CDC* pDC) = 0;

	COLORREF color;
	Bold bold;
};

