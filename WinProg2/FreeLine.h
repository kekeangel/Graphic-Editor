#pragma once
#include "Object_Draw.h"
class FreeLine : public Object_Draw
{
public:
	FreeLine();
	virtual ~FreeLine();
	virtual void Draw(CDC* pDC);

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

