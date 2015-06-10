#include "stdafx.h"
#include "RectAngle.h"
//#include "WinProg2View.h"
#include "WinProg2Doc.h"
#include "MainFrm.h"


RectAngle::RectAngle()
{
}


RectAngle::~RectAngle()
{
}

void RectAngle::Draw(CDC* pDC){
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	CPen pen(m_pen_type, m_bold, m_line_color);
	CPen *oldPen = pDC->SelectObject(&pen);
	POSITION pos = m_points.GetHeadPosition();

	CPoint p1, p2;
	p1 = m_points.GetNext(pos);

	while (pos != NULL) {
		p2 = m_points.GetNext(pos);

		pDC->Rectangle(p1.x, p1.y, p2.x, p2.y);
		p1 = p2;

		if (pDoc->select == TEXT){
			text_rect.SetRect(p1.x + 5, p1.y + 5, p2.x - 5, p2.y - 5);
			pDC->DrawText(pDoc->m_str.GetData(), pDoc->m_str.GetSize(), 
				&text_rect, DT_LEFT);
		}
	}
	pDC->SelectObject(oldPen);
}

void RectAngle::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void RectAngle::setPencil(Bold bold, UINT pen_type, COLORREF color){
	m_line_color = color;
	m_bold = bold;
	m_pen_type = pen_type;
}

BOOL RectAngle::getselectPoint(CPoint top, CPoint bottom){
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

void RectAngle::setPoint(CPoint& point){

}

void RectAngle::setRect(CPoint& top, CPoint& bottom){
	m_top = top;
	m_bottom = bottom;
}

void RectAngle::setDrawType(Select select){
	m_select = select;
}

Select RectAngle::getDrawType(){
	return m_select;
}

void RectAngle::movePoint(int t_x, int t_y, int b_x, int b_y){
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

	//text_rect.SetRect(p1.x + 5, p1.y + 5, p2.x - 5, p2.y - 5);
}