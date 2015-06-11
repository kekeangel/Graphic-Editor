
// WinProg2Doc.cpp : CWinProg2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CWinProg2Doc 생성/소멸

CWinProg2Doc::CWinProg2Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CWinProg2Doc serialization

void CWinProg2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
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


//LINE, POLYLINE 생성 및 데이터 가져오기 함수
PolyLine* CWinProg2Doc::getPolyLineDraw(BOOL isNew){

	//새로 생성되는 경우
	if (isNew){
		m_Cur = new PolyLine();
		m_Object.AddTail(m_Cur);

		return (PolyLine*)m_Cur;
	}

	//기존 값의 위치를 얻는 경우
	if (m_Cur != NULL && (select == POLYLINE || select == LINE || tmp_select == POLYLINE || tmp_select == LINE)) {
		return (PolyLine*)m_Cur;
	}
	return NULL;
}

//Rectangle 생성 및 데이터 가져오기 함수
RectAngle* CWinProg2Doc::getRectDraw(BOOL isNew){
	//새로 생성
	if (isNew){
		m_Cur = new RectAngle();
		m_Object.AddTail(m_Cur);

		return (RectAngle*)m_Cur;
	}

	//기존 값의 위치를 얻을 때
	if (m_Cur != NULL && (select == RECTANGLE || tmp_select == RECTANGLE))
		return (RectAngle*)m_Cur;

	return NULL;
}

//TEXTBOX 생성 및 데이터 가져오기 함수
TextBox* CWinProg2Doc::getTextBoxDraw(BOOL isNew){
	//새로 생성
	if (isNew){
		m_Cur = new TextBox();
		m_Object.AddTail(m_Cur);

		return (TextBox*)m_Cur;
	}

	//기존 값 위치 얻음
	if (m_Cur != NULL && (select == TEXT || tmp_select == TEXT)){
		return (TextBox*)m_Cur;
	}

	return NULL;
}

//ELLIPSE 생성 및 데이터 가져오기 함수
ELLipse* CWinProg2Doc::getEllipseDraw(BOOL isNew){
	//새로 생성
	if (isNew){
		m_Cur = new ELLipse();
		m_Object.AddTail(m_Cur);
	}

	//기존 값 위치 얻음
	if (m_Cur != NULL && (select == ELLIPSE || tmp_select == ELLIPSE)){
		return (ELLipse*)m_Cur;
	}

	return NULL;
}

//FREELINE 생성 및 데이터 가져오기 함수
FreeLine* CWinProg2Doc::getFreeLineDraw(BOOL isNew){
	//새로 생성
	if (isNew){
		m_Cur = new FreeLine();
		m_Object.AddTail(m_Cur);
	}

	//기존 값 위치 얻음
	if (m_Cur != NULL && select == FREELINE){
		return (FreeLine*)m_Cur;
	}

	return NULL;
}

//작업정보가 저장된 포인터리스트 반환함수
CPtrList& CWinProg2Doc::getObject() {
	return m_Object;
}

//Line 설정
void CWinProg2Doc::OnLine()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
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

//Line 설정 체크 여부
void CWinProg2Doc::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == LINE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//Rectangle 선택
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


//Rectangle 체크 설정 여부
void CWinProg2Doc::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == RECTANGLE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//Polyline 메뉴 선택
void CWinProg2Doc::OnDrawpoly()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString str;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

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

//Polyline 선택시 체크 설정 확인
void CWinProg2Doc::OnUpdateDrawpoly(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == POLYLINE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
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

//Ellipse 설정
void CWinProg2Doc::OnEllipse()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

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

//Ellipse 설정 체크 여부
void CWinProg2Doc::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if (select != SELECT){
		select = SELECT;
		strg = _T("개체선택");

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
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == SELECT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2Doc::OnFreeline()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString strg;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if (select != FREELINE){
		select = FREELINE;
		strg = _T("자유곡선");
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
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (select == FREELINE)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
