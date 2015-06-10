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
	CRect text_rect;
	CPoint text_point;
	CPoint m_top, m_bottom;

public:
	virtual void Draw(CDC* pDC);
	void addPoint(CPoint& point);
	void setPencel(int nWidth, COLORREF rgbColor);

	void setPoint(CPoint& point);
	void setRect(CPoint& topLeft, CPoint& bottomRight);

	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
};

