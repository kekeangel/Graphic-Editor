#pragma once
#include "Object_Draw.h"

class RectAngle : public Object_Draw
{
public:
	RectAngle();
	virtual ~RectAngle();

	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;

	COLORREF m_line_color, m_font_color, m_fill_color;
	Select m_select;
	Bold m_bold;
	CPoint text_point;
	UINT m_pen_type, hatch_pattern;
	CPoint m_top, m_bottom;
	CRect rect, text_rect;

public:
	virtual void Draw(CDC* pDC);
	void addPoint(CPoint& point);

	void setDrawType(Select select);
	void setPencil(Bold bold, UINT pen_type, COLORREF color);
	void setFillColor(COLORREF color);

	void setPoint(CPoint& point);
	void setRect(CPoint& topLeft, CPoint& bottomRight);
	void movePoint(int t_x, int t_y, int b_x, int b_y);

	virtual Select getDrawType();
	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
};

