#pragma once
#include "Object_Draw.h"

class TextBox : public Object_Draw
{
protected:
	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;
	COLORREF m_color;

public:
	TextBox();
	virtual ~TextBox();

	virtual void Draw(CDC* pDc);

	void addPoint(CPoint& point);
	void setPencil(int nWidth, COLORREF rgbColor);
	void delPoint();
	CPoint getPoint(BOOL isDel);
};

