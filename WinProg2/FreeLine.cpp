#include "stdafx.h"
#include "FreeLine.h"
#include "WinProg2Doc.h"
#include "MainFrm.h"

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

BOOL FreeLine::getselectPoint(CPoint top, CPoint bottom){
	return NULL;
}