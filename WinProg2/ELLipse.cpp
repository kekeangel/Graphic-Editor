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

	CPen pen(m_pen_type, m_bold, m_line_color);
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

void ELLipse::setPencil(Bold bold, UINT pen_type, COLORREF color){
	m_line_color = color;
	m_bold = bold;
	m_pen_type = pen_type;
}

void ELLipse::setFillColor(COLORREF color){
	m_fill_color = color;
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

Select ELLipse::getDrawType(){
	return m_select;
}

void ELLipse::setDrawType(Select select){
	m_select = select;
}

void ELLipse::movePoint(int t_x, int t_y, int b_x, int b_y){
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