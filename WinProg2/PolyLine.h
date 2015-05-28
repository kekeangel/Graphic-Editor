#pragma once
#include "Object_Draw.h"

class PolyLine : public Object_Draw
{
protected:
	CList<CPoint, CPoint> m_points;
	COLORREF m_color;
//	Bold m_bold;

public:
	PolyLine();
	virtual ~PolyLine();

	virtual void Draw(CDC* pDc);

	void addPoint(CPoint& point);
	void setPencil(int nWidth, COLORREF rgbColor);
};