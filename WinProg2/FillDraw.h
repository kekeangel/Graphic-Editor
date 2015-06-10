#pragma once
#include "Object_Draw.h"

class FillDraw : public Object_Draw
{
private:
	CPoint m_point;
	COLORREF m_color;

public:
	FillDraw();
	virtual ~FillDraw();
	virtual void Draw(CDC* pDC);
	virtual BOOL getselectPoint(CPoint a, CPoint b);
	void setPoint(CPoint& point);
	void setColor(COLORREF& color);
};

