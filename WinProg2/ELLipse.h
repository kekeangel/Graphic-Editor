#pragma once

#include "Object_Draw.h"

class ELLipse : public Object_Draw
{
public:
	ELLipse();
	virtual ~ELLipse();

	virtual void Draw(CDC* pDc);

	COLORREF color, m_color;
	Bold bold, m_bold;
	UINT m_pen_type;

	CList<CPoint, CPoint> m_points;
	CList<CPoint, CPoint&> del_points;

	void addPoint(CPoint& point);

	void setPencel(int nWidth, COLORREF rgbColor);
	void delPoint();

	virtual BOOL getselectPoint(CPoint top, CPoint bottom);
};

