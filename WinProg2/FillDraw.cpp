#include "stdafx.h"
#include "FillDraw.h"


FillDraw::FillDraw()
{
}


FillDraw::~FillDraw()
{
}

void FillDraw::Draw(CDC* pDC){
	CBrush brush(m_color);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	pDC->ExtFloodFill(m_point.x, m_point.y, pDC->GetPixel(m_point), FLOODFILLSURFACE);
	pDC->SelectObject(oldBrush);
}

void FillDraw::setPoint(CPoint& point)
{
	m_point = point;
}

void FillDraw::setColor(COLORREF& color) {
	m_color = color;
}

BOOL FillDraw::getselectPoint(CPoint a, CPoint b){
	return FALSE;
}

Select FillDraw::getDrawType(){
	return m_select;
}

void FillDraw::setDrawType(Select select){
	m_select = select;
}