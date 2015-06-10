#include "stdafx.h"
#include "TextBox.h"
#include "WinProg2Doc.h"
#include "MainFrm.h"

TextBox::TextBox()
{
}


TextBox::~TextBox()
{
}

void TextBox::Draw(CDC* pDC){
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	m_color = pDoc->color; 
	m_lf = pDoc->lf;
	m_fontsize = pDoc->fontsize;
	
	CPen pen(PS_SOLID, pDoc->bold, color);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	CFont font;
	font.CreateFontIndirectW(&m_lf);

	pDC->SetTextColor(m_color);
	pDC->SelectObject(&font);
	POSITION pos = m_points.GetHeadPosition();
	CRect rect;


	CPoint p1, p2;
	p1 = m_points.GetNext(pos);

	while (pos != NULL) {
		p2 = m_points.GetNext(pos);
		rect.SetRect(p1, p2);

		pDC->Rectangle(rect);
		p1 = p2;
	}
	pDC->SelectObject(oldPen);
}

void TextBox::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void TextBox::setPencil(int nWidth, COLORREF rgbColor){
	color = rgbColor;
}

BOOL TextBox::getselectPoint(CPoint top, CPoint bottom){
	return NULL;
}