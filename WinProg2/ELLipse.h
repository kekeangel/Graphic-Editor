#pragma once

#include "Object_Draw.h"

class ELLipse : public Object_Draw
{
public:
	ELLipse();
	virtual ~ELLipse();

	virtual void Draw(CDC* pDc);

	COLORREF m_line_color, m_fill_color;
	Bold m_bold;
	UINT m_pen_type;
	Select m_select;

	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;

	void addPoint(CPoint& point);

	void setPencil(Bold bold, UINT pen_type, COLORREF color);
	void setFillColor(COLORREF color);
	void setDrawType(Select select);
	void delPoint();

	void movePoint(int t_x, int t_y, int b_x, int b_y);

	virtual Select getDrawType();
	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
};

