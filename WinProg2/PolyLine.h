#pragma once
class PolyLine
{
protected:
	CList<CPoint, CPoint> m_points;
	COLORREF m_color;

public:
	PolyLine();
	virtual ~PolyLine();

	void Draw(CDC* pDc);

	void addPoint(CPoint& point);
	void setPencil(int nWidth, COLORREF rgbColor);
};