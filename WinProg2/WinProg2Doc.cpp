
// WinProg2Doc.cpp : CWinProg2Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "WinProg2.h"
#endif

#include "WinProg2Doc.h"
#include "WinProg2View.h"
#include "MainFrm.h"
#include "StringDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinProg2Doc

IMPLEMENT_DYNCREATE(CWinProg2Doc, CDocument)

BEGIN_MESSAGE_MAP(CWinProg2Doc, CDocument)
	ON_COMMAND(ID_Color, &CWinProg2Doc::OnColor)
	ON_COMMAND(ID_Font, &CWinProg2Doc::OnFont)
	ON_COMMAND(ID_EDIT_UNDO, &CWinProg2Doc::OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CWinProg2Doc::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CWinProg2Doc::OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CWinProg2Doc::OnUpdateEditRedo)
	ON_COMMAND(ID_TextBox, &CWinProg2Doc::OnTextbox)
	ON_UPDATE_COMMAND_UI(ID_TextBox, &CWinProg2Doc::OnUpdateTextbox)
	ON_COMMAND(ID_RectAngle, &CWinProg2Doc::OnRectangle)
	ON_UPDATE_COMMAND_UI(ID_RectAngle, &CWinProg2Doc::OnUpdateRectangle)
	ON_COMMAND(ID_Line, &CWinProg2Doc::OnLine)
	ON_UPDATE_COMMAND_UI(ID_Line, &CWinProg2Doc::OnUpdateLine)
END_MESSAGE_MAP()


// CWinProg2Doc ����/�Ҹ�

CWinProg2Doc::CWinProg2Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	select = EMPTY;
	color = RGB(0, 0, 0);
	bold = ONE;
	index = 0;
	Empty = TRUE;
	RE_Empty = TRUE;
	str = _T("");
	pen_type = PS_SOLID;
}

CWinProg2Doc::~CWinProg2Doc()
{
}

BOOL CWinProg2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CWinProg2Doc serialization

void CWinProg2Doc::Serialize(CArchive& ar)
{
	POSITION pos = m_Object.GetHeadPosition();

	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		while (pos != NULL){
			m_Object.GetNext(pos);
			m_Object.Serialize(ar);
		}
		
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		while (pos != NULL){
			m_Object.GetNext(pos);
			m_Object.Serialize(ar);
		}
		
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CWinProg2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CWinProg2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWinProg2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWinProg2Doc ����

#ifdef _DEBUG
void CWinProg2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinProg2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinProg2Doc ���

//�������޴�
void CWinProg2Doc::OnColor()
{
	CColorDialog dlg(RGB(255,0,0),CC_FULLOPEN);
	dlg.DoModal();
	color = dlg.GetColor();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//�۲ü����޴�
void CWinProg2Doc::OnFont()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		color = dlg.GetColor();

		dlg.GetCurrentFont(&lf);
		fontsize = dlg.GetSize();
	}
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

PolyLine* CWinProg2Doc::getPolyLineDraw(BOOL isNew){

	if (isNew){
		m_Cur = new PolyLine();
		m_Object.AddTail(m_Cur);

		return (PolyLine*)m_Cur;
	}

	if (m_Cur != NULL && (select == POLYLINE || select == LINE)) {
		return (PolyLine*)m_Cur;
	}
	return NULL;
}

RectAngle* CWinProg2Doc::getRectDraw(BOOL isNew){
	if (isNew){
		m_Cur = new RectAngle();
		m_Object.AddTail(m_Cur);

		return (RectAngle*)m_Cur;
	}

	if (m_Cur != NULL && select == RECTANGLE)
		return (RectAngle*)m_Cur;

	return NULL;
}

TextBox* CWinProg2Doc::getTextBoxDraw(BOOL isNew){
	if (isNew){
		m_Cur = new TextBox();
		m_Object.AddTail(m_Cur);

		return (TextBox*)m_Cur;
	}

	if (m_Cur != NULL && select == TEXT){
		return (TextBox*)m_Cur;
	}

	return NULL;
}

//�۾������� ����� �����͸���Ʈ ��ȯ
CPtrList& CWinProg2Doc::getObject() {
	return m_Object;
}

//������� �޴�
void CWinProg2Doc::OnEditUndo()
{
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	getPolyLineDraw()->delPoint();
	pView->Invalidate();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//���ູ�� �޴�
void CWinProg2Doc::OnEditRedo()
{
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	CPoint point;
	point = getPolyLineDraw()->getPoint(TRUE);
	getPolyLineDraw()->addPoint(TRUE, point);
	pView->Invalidate();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (Empty == TRUE){
		pCmdUI->Enable(0);
	}
	else{
		pCmdUI->Enable(1);
	}

}


void CWinProg2Doc::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (RE_Empty == TRUE){
		pCmdUI->Enable(0);
	}
	else{
		pCmdUI->Enable(1);
	}
}

//TextBox����
void CWinProg2Doc::OnTextbox()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;

	if (select != TEXT){
		select = TEXT;
		strg = _T("TextBox");
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	else{
		select = EMPTY;
		strg.LoadStringW(ID_INDICATOR_TOOL);
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	
}

//�ؽ�Ʈ���ڸ޴� üũǥ�ÿ���
void CWinProg2Doc::OnUpdateTextbox(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == TEXT){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2Doc::OnRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;

	if (select != RECTANGLE){
		select = RECTANGLE;
		strg = _T("Rectangle");
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	else{
		select = EMPTY;
		strg.LoadStringW(ID_INDICATOR_TOOL);
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
}


void CWinProg2Doc::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == RECTANGLE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}



void CWinProg2Doc::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;

	if (select != LINE){
		select = LINE;
		strg = _T("Line");
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	else{
		select = EMPTY;
		strg.LoadStringW(ID_INDICATOR_TOOL);
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
}


void CWinProg2Doc::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == LINE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
