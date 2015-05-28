#include "stdafx.h"
#include "PolyLine.h"
#include "WinProg2Doc.h"
#include "WinProg2View.h"
#include "MainFrm.h"

PolyLine::PolyLine()
{
	m_color = RGB(0, 0, 0); 
	//m_bold = ONE;
}


PolyLine::~PolyLine()
{
}

void PolyLine::Draw(CDC *pDC){
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	m_color = pDoc->color;
	
	CPen pen(PS_SOLID, pDoc->bold, m_color);
	CPen *oldPen = pDC->SelectObject(&pen);
	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
	p1 = m_points.GetNext(pos);

	while (pos != NULL) {
		p2 = m_points.GetNext(pos);

		pDC->MoveTo(p1);
		pDC->LineTo(p2);
		p1 = p2;
	}
	pDC->SelectObject(oldPen);
}

void PolyLine::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void PolyLine::setPencil(int nWidth, COLORREF rgbColor){
	m_color = rgbColor;

}