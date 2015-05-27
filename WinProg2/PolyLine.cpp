#include "stdafx.h"
#include "PolyLine.h"


PolyLine::PolyLine()
{
}


PolyLine::~PolyLine()
{
}

void PolyLine::Draw(CDC *pDC){
	CPen pen(PS_SOLID, 1, m_color);
	CPen *oldPen = pDC->SelectObject(&pen);
	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
}

void addPoint(CPoint& point){
}

void setPencil(int nWidth, COLORREF rgbColor){
	
}