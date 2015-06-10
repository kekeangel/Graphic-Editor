#pragma once
#include "Object_Draw.h"

class TextBox : public Object_Draw
{
protected:
	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;
	COLORREF m_line_color, m_fill_color;
	CFont m_font;
	CRect rect, text_rect;
	Select m_select;
	Bold m_bold;
	UINT m_pen_type;
	style m_font_style;


public:
	TextBox();
	virtual ~TextBox();

	virtual void Draw(CDC* pDc);

	void addPoint(CPoint& point);
	void setPencil(Bold bold, UINT pen_type, COLORREF color);
	void setFillColor(COLORREF color);
	void setFontColor(style font_style);
	void setDrawType(Select select);

	void movePoint(int t_x, int t_y, int b_x, int b_y);

	void delPoint();

	virtual Select getDrawType();
	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
};

