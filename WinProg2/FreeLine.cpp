#include "stdafx.h"
#include "FreeLine.h"


FreeLine::FreeLine()
{
}


FreeLine::~FreeLine()
{
}

void FreeLine::Draw(CDC* pDC){

}

void FreeLine::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void FreeLine::setPencel(int nWidth, COLORREF rgbColor){
	m_color = rgbColor;
}

CPoint FreeLine::getPoint(BOOL isDel){
	if (isDel){

		return del_points.GetHead();
	}
	else{
		return m_points.GetTail();
	}
}