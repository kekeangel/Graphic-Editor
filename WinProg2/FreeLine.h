#pragma once
#include "Object_Draw.h"
class FreeLine : public Object_Draw
{
public:
	FreeLine();
	virtual ~FreeLine();
	virtual void Draw(CDC* pDC);

	COLORREF m_color;
	Bold m_bold;
	UINT m_pen_type;
	Select m_select;

	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;

	void addPoint(CPoint& point);
	void setPencil(Bold bold, UINT pen_type, COLORREF color);
	void delPoint();
	void setDrawType(Select select);

	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
	virtual Select getDrawType();

	void movePoint(int t_x, int t_y, int b_x, int b_y);

};

