#include "stdafx.h"
#include "PolyLine.h"
#include "WinProg2Doc.h"
#include "WinProg2View.h"
#include "MainFrm.h"

PolyLine::PolyLine()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	mov_select = FALSE;
}


PolyLine::~PolyLine()
{
}

void PolyLine::Draw(CDC *pDC){
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	
	CPen pen(m_pen_type, m_bold, m_color);
	CPen mov_pen(PS_SOLID, 6, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(0, 0, 0));
	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
	pDC->SelectObject(&brush);
	p1 = m_points.GetNext(pos);
	pDC->SelectObject(&pen);

	while (pos != NULL) {
		pDC->SelectObject(oldPen);
		p2 = m_points.GetNext(pos);

		pDC->MoveTo(p1);
		pDC->LineTo(p2);

		p1 = p2;
	}
	pDC->SelectObject(oldPen);
}

void PolyLine::addPoint(BOOL isDel, CPoint& point){
	if (isDel){
		m_points.AddTail(point);
		del_points.RemoveHead();
	}
	else{
		m_points.AddTail(point);
	}
	
}

void PolyLine::setPencil(Bold bold, UINT pen_type, COLORREF color){
	m_color = color;
	m_bold = bold;
	m_pen_type = pen_type;
}

void PolyLine::delPoint(){
	CPoint point;

	point = m_points.GetTail();
	del_points.AddTail(point);
	m_points.RemoveTail();

	
}

BOOL PolyLine::getselectPoint(CPoint top, CPoint bottom){
	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
	p1 = m_points.GetNext(pos);

	while (pos != NULL) {
		p2 = m_points.GetNext(pos);

		if (p1.x >= top.x && p1.y >= top.y){
			if (p2.x <= bottom.x && p2.y <= bottom.y){
				return TRUE;
			}
		}

		p1 = p2;
	}
	return FALSE;
}

Select PolyLine::getDrawType(){
	return m_select;
}

void PolyLine::setDrawType(Select select){
	m_select = select;
}

void PolyLine::getTopBottomPoint(CPoint& top, CPoint& bottom){

	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
	p1 = top = m_points.GetNext(pos);

	while (pos != NULL) {
		p2 = m_points.GetNext(pos);

		p1 = p2;
	}
	bottom = p2;

	mov_select = TRUE;
}

void PolyLine::setMove(){
	mov_select = FALSE;
}

void PolyLine::movePoint(int t_x, int t_y, int b_x, int b_y){
	POSITION pos = m_points.GetHeadPosition();
	POSITION old_pos = m_points.GetHeadPosition();
	CPoint p1, p2;
	

	p1 = m_points.GetNext(pos);
	while (pos != NULL) {
		p2 = m_points.GetNext(pos);
		
		p1.x -= t_x;
		p1.y -= t_y;
		m_points.SetAt(old_pos, p1);
		p1 = p2;
		m_points.GetNext(old_pos);
	}
	p1.x -= b_x;
	p1.y -= b_y;
	m_points.SetAt(old_pos, p1);
	
}