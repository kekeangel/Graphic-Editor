#pragma once
#include "Object_Draw.h"

class PolyLine : public Object_Draw
{
protected:
	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;

public:
	COLORREF m_color;
	Bold m_bold;
	UINT m_pen_type;

public:
	PolyLine();
	virtual ~PolyLine();

	virtual void Draw(CDC* pDc);

	void addPoint(BOOL isDel, CPoint& point);
	void setPencil(int nWidth, COLORREF rgbColor);
	void delPoint();

	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
};