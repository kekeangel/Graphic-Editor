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

BOOL ELLipse::getselectPoint(CPoint top, CPoint bottom){
	POSITION pos = m_points.GetHeadPosition();
	CPoint p1, p2;
	p1 = m_points.GetNext(pos);
	while (pos != NULL) {
		p2 = m_points.GetNext(pos);
		if (p1.x >= top.x && p1.x <= bottom.x){
			if (p2.y >= top.y && p2.y <= bottom.y)
				return TRUE;

		}
		p1 = p2;
	}
	return FALSE;
}