
// WinProg2Doc.cpp : CWinProg2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CWinProg2Doc 생성/소멸

CWinProg2Doc::CWinProg2Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CWinProg2Doc serialization

void CWinProg2Doc::Serialize(CArchive& ar)
{
	POSITION pos = m_Object.GetHeadPosition();

	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		while (pos != NULL){
			m_Object.GetNext(pos);
			m_Object.Serialize(ar);
		}
		
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		while (pos != NULL){
			m_Object.GetNext(pos);
			m_Object.Serialize(ar);
		}
		
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CWinProg2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CWinProg2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CWinProg2Doc 진단

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


// CWinProg2Doc 명령

//색상설정메뉴
void CWinProg2Doc::OnColor()
{
	CColorDialog dlg(RGB(255,0,0),CC_FULLOPEN);
	dlg.DoModal();
	color = dlg.GetColor();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//글꼴설정메뉴
void CWinProg2Doc::OnFont()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		color = dlg.GetColor();

		dlg.GetCurrentFont(&lf);
		fontsize = dlg.GetSize();
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

//작업정보가 저장된 포인터리스트 반환
CPtrList& CWinProg2Doc::getObject() {
	return m_Object;
}

//실행취소 메뉴
void CWinProg2Doc::OnEditUndo()
{
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	getPolyLineDraw()->delPoint();
	pView->Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//실행복구 메뉴
void CWinProg2Doc::OnEditRedo()
{
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	CPoint point;
	point = getPolyLineDraw()->getPoint(TRUE);
	getPolyLineDraw()->addPoint(TRUE, point);
	pView->Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (Empty == TRUE){
		pCmdUI->Enable(0);
	}
	else{
		pCmdUI->Enable(1);
	}

}


void CWinProg2Doc::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (RE_Empty == TRUE){
		pCmdUI->Enable(0);
	}
	else{
		pCmdUI->Enable(1);
	}
}

//TextBox선택
void CWinProg2Doc::OnTextbox()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

//텍스트상자메뉴 체크표시여부
void CWinProg2Doc::OnUpdateTextbox(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == TEXT){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2Doc::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == RECTANGLE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}



void CWinProg2Doc::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == LINE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
