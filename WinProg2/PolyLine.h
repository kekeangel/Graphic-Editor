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
	Select m_select;
	BOOL mov_select;

public:
	PolyLine();
	virtual ~PolyLine();

	virtual void Draw(CDC* pDc);

	void addPoint(BOOL isDel, CPoint& point);
	void getTopBottomPoint(CPoint& top, CPoint& bottom);
	
	void setPencil(Bold bold, UINT pen_type, COLORREF color);
	void setDrawType(Select select);
	void movePoint(int t_x, int t_y, int b_x, int b_y);
	
	void delPoint();

	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
	virtual Select getDrawType();

	void setMove();
};