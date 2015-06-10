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
	//m_color = pDoc->color;

	CPen pen(PS_SOLID, pDoc->bold, m_color);
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

void RectAngle::setPencel(int nWidth, COLORREF rgbColor){
	m_color = rgbColor;
}

BOOL RectAngle::getselectPoint(CPoint top, CPoint bottom){
	return NULL;
}

void RectAngle::setPoint(CPoint& point){

}

void RectAngle::setRect(CPoint& top, CPoint& bottom){
	m_top = top;
	m_bottom = bottom;
}