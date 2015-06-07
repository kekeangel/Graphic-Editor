#include "stdafx.h"
#include "ELLipse.h"
#include "WinProg2Doc.h"
#include "MainFrm.h"

ELLipse::ELLipse()
{
}


ELLipse::~ELLipse()
{
}

void ELLipse::Draw(CDC* pDC){
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	m_color = pDoc->color;
	m_pen_type = pDoc->pen_type;
	m_bold = pDoc->bold;

	CPen pen(m_pen_type, m_bold, m_color);
	CPen *oldPen = pDC->SelectObject(&pen);
	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
	p1 = m_points.GetNext(pos);
	while (pos != NULL) {
		p2 = m_points.GetNext(pos);

		pDC->Ellipse(p1.x, p1.y, p2.x, p2.y);

		p1 = p2;
	}
	pDC->SelectObject(oldPen);
}

void ELLipse::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void ELLipse::setPencel(int nWidth, COLORREF rgbColor){
	m_color = rgbColor;
}

CPoint ELLipse::getPoint(BOOL isDel){
	if (isDel){

		return del_points.GetHead();
	}
	else{
		return m_points.GetTail();
	}
}