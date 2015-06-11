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
	
	CPen pen(m_pen_type, m_bold, m_line_color);
	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush brush(m_fill_color);
	CBrush *oldBrush = pDC->SelectObject(&brush);
	
	CFont font;
	font.CreateFontIndirectW(&m_font_style.lf);
	pDC->SelectObject(&font);
	POSITION pos = m_points.GetHeadPosition();
	
	CPoint p1, p2;
	p1 = m_points.GetNext(pos);

	while (pos != NULL) {
		p2 = m_points.GetNext(pos);
		rect.SetRect(p1, p2);

		pDC->Rectangle(rect);
		p1 = p2;
	}
	text_rect = rect;
	text_rect.left += 5;
	text_rect.right -= 5;
	text_rect.top += 5;
	text_rect.bottom -= 5;

	
	pDC->DrawTextW(m_str, &text_rect, DT_LEFT);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void TextBox::addPoint(CPoint& point){
	m_points.AddTail(point);
}

void TextBox::setPencil(Bold bold, UINT pen_type, COLORREF color){
	m_line_color = color;
	m_pen_type = pen_type;
	m_bold = bold;
}

BOOL TextBox::getselectPoint(CPoint top, CPoint bottom){
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

Select TextBox::getDrawType(){
	return m_select;
}

void TextBox::setDrawType(Select select){
	m_select = select;
}

void TextBox::setFontColor(style font_style){
	m_font_style.fontsize = font_style.fontsize;
	m_font_style.font_color = font_style.font_color;
	m_font_style.isBold = font_style.isBold;
	m_font_style.isItalic = font_style.isItalic;
	m_font_style.isStrikeout = font_style.isStrikeout;
	m_font_style.isUnderline = font_style.isUnderline;
	m_font_style.lf = font_style.lf;

}

void TextBox::movePoint(int t_x, int t_y, int b_x, int b_y){
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

void TextBox::setFillColor(COLORREF color){
	m_fill_color = color;
}

void TextBox::setString(CString str){
	m_str = str;
}