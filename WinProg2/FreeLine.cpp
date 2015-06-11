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
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();


	CPen pen(m_pen_type, m_bold, m_color);
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

void FreeLine::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void FreeLine::setPencil(Bold bold, UINT pen_type, COLORREF color){
	m_color = color;
	m_bold = bold;
	m_pen_type = pen_type;
}

BOOL FreeLine::getselectPoint(CPoint top, CPoint bottom){
	return NULL;
}

void FreeLine::setDrawType(Select select){
	m_select = select;
}

Select FreeLine::getDrawType(){
	return m_select;
}

void FreeLine::movePoint(int t_x, int t_y, int b_x, int b_y){
	POSITION pos = m_points.GetHeadPosition();
	POSITION prev_pos = m_points.GetHeadPosition();

	CPoint p1, p2;

	p1 = m_points.GetNext(pos);
	while (pos != NULL) {
		p2 = m_points.GetNext(pos);
		p1.x -= t_x;
		p1.y -= t_y;

		m_points.SetAt(prev_pos, p1);
		p1 = p2;
		m_points.GetNext(prev_pos);
	}

	p1.x -= b_x;
	p1.y -= b_y;
	m_points.SetAt(prev_pos, p1);
}