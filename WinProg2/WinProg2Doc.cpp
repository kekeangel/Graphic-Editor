
// WinProg2Doc.cpp : CWinProg2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinProg2.h"
#endif

#include "WinProg2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinProg2Doc

IMPLEMENT_DYNCREATE(CWinProg2Doc, CDocument)

BEGIN_MESSAGE_MAP(CWinProg2Doc, CDocument)
	ON_COMMAND(ID_Color, &CWinProg2Doc::OnColor)
	ON_COMMAND(ID_Font, &CWinProg2Doc::OnFont)
	ON_COMMAND(ID_Bold_1, &CWinProg2Doc::OnBold1)
	ON_COMMAND(ID_Bold_2, &CWinProg2Doc::OnBold2)
	ON_COMMAND(ID_Bold_3, &CWinProg2Doc::OnBold3)
	ON_COMMAND(ID_Bold_4, &CWinProg2Doc::OnBold4)
	ON_COMMAND(ID_Bold_5, &CWinProg2Doc::OnBold5)
	ON_COMMAND(ID_Bold_6, &CWinProg2Doc::OnBold6)
	ON_UPDATE_COMMAND_UI(ID_Bold_1, &CWinProg2Doc::OnUpdateBold1)
	ON_UPDATE_COMMAND_UI(ID_Bold_2, &CWinProg2Doc::OnUpdateBold2)
	ON_UPDATE_COMMAND_UI(ID_Bold_3, &CWinProg2Doc::OnUpdateBold3)
	ON_UPDATE_COMMAND_UI(ID_Bold_4, &CWinProg2Doc::OnUpdateBold4)
	ON_UPDATE_COMMAND_UI(ID_Bold_5, &CWinProg2Doc::OnUpdateBold5)
	ON_UPDATE_COMMAND_UI(ID_Bold_6, &CWinProg2Doc::OnUpdateBold6)
END_MESSAGE_MAP()


// CWinProg2Doc 생성/소멸

CWinProg2Doc::CWinProg2Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	select = EMPTY;
	color = RGB(0, 0, 0);
	bold = ONE;
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


void CWinProg2Doc::OnColor()
{
	CColorDialog dlg(RGB(255,0,0),CC_FULLOPEN);
	dlg.DoModal();
	color = dlg.GetColor();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnFont()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		COLORREF color = dlg.GetColor();

		LOGFONT lf;
		dlg.GetCurrentFont(&lf);
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

PolyLine* CWinProg2Doc::getPolyLineDraw(BOOL isNew){

	if (isNew){
		m_Cur = new PolyLine();
		m_Object.AddTail(m_Cur);

		return (PolyLine*)m_Cur;
	}

	if (m_Cur != NULL && select == POLYLINE) {
		return (PolyLine*)m_Cur;
	}
	return NULL;
}

CPtrList& CWinProg2Doc::getObject() {
	return m_Object;
}

void CWinProg2Doc::OnBold1()
{
	bold = ONE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnBold2()
{
	bold = TWO;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnBold3()
{
	bold = THREE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnBold4()
{
	bold = FOUR;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnBold5()
{
	bold = FIVE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnBold6()
{
	bold = SIX;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateBold1(CCmdUI *pCmdUI)
{
	if (bold == ONE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateBold2(CCmdUI *pCmdUI)
{
	if (bold == TWO){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateBold3(CCmdUI *pCmdUI)
{
	if (bold == THREE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateBold4(CCmdUI *pCmdUI)
{
	if (bold == FOUR){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateBold5(CCmdUI *pCmdUI)
{
	if (bold == FIVE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CWinProg2Doc::OnUpdateBold6(CCmdUI *pCmdUI)
{
	if (bold == SIX){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}
