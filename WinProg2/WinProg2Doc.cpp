
// WinProg2Doc.cpp : CWinProg2Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "WinProg2.h"
#endif

#include "WinProg2Doc.h"
#include "MainFrm.h"
#include "WinProg2View.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinProg2Doc

IMPLEMENT_DYNCREATE(CWinProg2Doc, CDocument)

BEGIN_MESSAGE_MAP(CWinProg2Doc, CDocument)
	ON_COMMAND(ID_Line, &CWinProg2Doc::OnLine)
	ON_UPDATE_COMMAND_UI(ID_Line, &CWinProg2Doc::OnUpdateLine)
	ON_COMMAND(ID_RectAngle, &CWinProg2Doc::OnRectangle)
	ON_UPDATE_COMMAND_UI(ID_RectAngle, &CWinProg2Doc::OnUpdateRectangle)
	ON_COMMAND(ID_DrawPoly, &CWinProg2Doc::OnDrawpoly)
	ON_UPDATE_COMMAND_UI(ID_DrawPoly, &CWinProg2Doc::OnUpdateDrawpoly)
	ON_COMMAND(ID_TextBox, &CWinProg2Doc::OnTextbox)
	ON_UPDATE_COMMAND_UI(ID_TextBox, &CWinProg2Doc::OnUpdateTextbox)
	ON_COMMAND(ID_ELLipse, &CWinProg2Doc::OnEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELLipse, &CWinProg2Doc::OnUpdateEllipse)
	ON_COMMAND(ID_SelectObject, &CWinProg2Doc::OnSelectobject)
	ON_UPDATE_COMMAND_UI(ID_SelectObject, &CWinProg2Doc::OnUpdateSelectobject)
	ON_COMMAND(ID_FreeLine, &CWinProg2Doc::OnFreeline)
	ON_UPDATE_COMMAND_UI(ID_FreeLine, &CWinProg2Doc::OnUpdateFreeline)
END_MESSAGE_MAP()


// CWinProg2Doc ����/�Ҹ�

CWinProg2Doc::CWinProg2Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	select = EMPTY;
	bold = ONE;
	index = 0;
	Empty = TRUE;
	RE_Empty = TRUE;
	str = _T("");
	pen_type = PS_SOLID;
	start = FALSE;
	Obj_select = FALSE;
	font_style.font_color = RGB(0, 0, 0);
	color = RGB(0, 0, 0);
	m_fill_color = RGB(255, 255, 255);
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
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
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


//LINE, POLYLINE ���� �� ������ �������� �Լ�
PolyLine* CWinProg2Doc::getPolyLineDraw(BOOL isNew){

	//���� �����Ǵ� ���
	if (isNew){
		m_Cur = new PolyLine();
		m_Object.AddTail(m_Cur);

		return (PolyLine*)m_Cur;
	}

	//���� ���� ��ġ�� ��� ���
	if (m_Cur != NULL && (select == POLYLINE || select == LINE || tmp_select == POLYLINE || tmp_select == LINE)) {
		return (PolyLine*)m_Cur;
	}
	return NULL;
}

//Rectangle ���� �� ������ �������� �Լ�
RectAngle* CWinProg2Doc::getRectDraw(BOOL isNew){
	//���� ����
	if (isNew){
		m_Cur = new RectAngle();
		m_Object.AddTail(m_Cur);

		return (RectAngle*)m_Cur;
	}

	//���� ���� ��ġ�� ���� ��
	if (m_Cur != NULL && (select == RECTANGLE || tmp_select == RECTANGLE))
		return (RectAngle*)m_Cur;

	return NULL;
}

//TEXTBOX ���� �� ������ �������� �Լ�
TextBox* CWinProg2Doc::getTextBoxDraw(BOOL isNew){
	//���� ����
	if (isNew){
		m_Cur = new TextBox();
		m_Object.AddTail(m_Cur);

		return (TextBox*)m_Cur;
	}

	//���� �� ��ġ ����
	if (m_Cur != NULL && (select == TEXT || tmp_select == TEXT)){
		return (TextBox*)m_Cur;
	}

	return NULL;
}

//ELLIPSE ���� �� ������ �������� �Լ�
ELLipse* CWinProg2Doc::getEllipseDraw(BOOL isNew){
	//���� ����
	if (isNew){
		m_Cur = new ELLipse();
		m_Object.AddTail(m_Cur);
	}

	//���� �� ��ġ ����
	if (m_Cur != NULL && (select == ELLIPSE || tmp_select == ELLIPSE)){
		return (ELLipse*)m_Cur;
	}

	return NULL;
}

//FREELINE ���� �� ������ �������� �Լ�
FreeLine* CWinProg2Doc::getFreeLineDraw(BOOL isNew){
	//���� ����
	if (isNew){
		m_Cur = new FreeLine();
		m_Object.AddTail(m_Cur);
	}

	//���� �� ��ġ ����
	if (m_Cur != NULL && select == FREELINE){
		return (FreeLine*)m_Cur;
	}

	return NULL;
}

//�۾������� ����� �����͸���Ʈ ��ȯ�Լ�
CPtrList& CWinProg2Doc::getObject() {
	return m_Object;
}

//Line ����
void CWinProg2Doc::OnLine()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
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

//Line ���� üũ ����
void CWinProg2Doc::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == LINE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//Rectangle ����
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


//Rectangle üũ ���� ����
void CWinProg2Doc::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == RECTANGLE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//Polyline �޴� ����
void CWinProg2Doc::OnDrawpoly()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString str;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	if (select != POLYLINE){
		select = POLYLINE;
		str = _T("Polyline");
	}
	else{
		select = EMPTY;
		str.LoadStringW(ID_INDICATOR_TOOL);
	}
	pMainFrame->m_wndStatusBar.SetPaneText(2, str);
}

//Polyline ���ý� üũ ���� Ȯ��
void CWinProg2Doc::OnUpdateDrawpoly(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == POLYLINE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
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

//Ellipse ����
void CWinProg2Doc::OnEllipse()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	if (select != ELLIPSE){
		select = ELLIPSE;
		strg = _T("Ellipse");
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	else{
		select = EMPTY;
		strg.LoadStringW(ID_INDICATOR_TOOL);
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}

}

//Ellipse ���� üũ ����
void CWinProg2Doc::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == ELLIPSE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CWinProg2Doc::OnSelectobject()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();

	CString strg;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	if (select != SELECT){
		select = SELECT;
		strg = _T("��ü����");

		pView->m_Tracker = new CRectTracker();

		pView->m_Tracker->m_rect = pView->select_rect;
		pView->m_Tracker->m_nStyle = CRectTracker::hatchInside;
		pView->m_Tracker->m_nStyle = CRectTracker::resizeInside;

		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	else{
		select = EMPTY;
		delete pView->m_Tracker;
		pView->m_Tracker = NULL;
		strg.LoadStringW(ID_INDICATOR_TOOL);
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
}


void CWinProg2Doc::OnUpdateSelectobject(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == SELECT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2Doc::OnFreeline()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	if (select != FREELINE){
		select = FREELINE;
		strg = _T("�����");
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
	else{
		select = EMPTY;
		strg.LoadStringW(ID_INDICATOR_TOOL);
		pMainFrame->m_wndStatusBar.SetPaneText(2, strg);
	}
}


void CWinProg2Doc::OnUpdateFreeline(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (select == FREELINE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
