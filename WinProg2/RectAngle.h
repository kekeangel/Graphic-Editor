#pragma once
#include "Object_Draw.h"

class RectAngle : public Object_Draw
{
public:
	RectAngle();
	virtual ~RectAngle();

protected:
	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;
	COLORREF m_color;

public:
	virtual void Draw(CDC* pDC);
	void addPoint(CPoint& point);
	void setPencel(int nWidth, COLORREF rgbColor);
	CPoint getPoint(BOOL isDel);
};

