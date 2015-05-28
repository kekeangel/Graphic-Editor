
// WinProg2View.cpp : CWinProg2View 클래스의 구현
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinProg2View

IMPLEMENT_DYNCREATE(CWinProg2View, CView)

BEGIN_MESSAGE_MAP(CWinProg2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinProg2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DrawPoly, &CWinProg2View::OnDrawpoly)
	ON_UPDATE_COMMAND_UI(ID_DrawPoly, &CWinProg2View::OnUpdateDrawpoly)
	ON_COMMAND(ID_DRAW_ELLIPSE, CWinProg2View::OnButtonEllipse)
	ON_COMMAND(ID_DRAW_RECTANGLE, CWinProg2View::OnButtonRectangle)
	END_MESSAGE_MAP()

// CWinProg2View 생성/소멸

CWinProg2View::CWinProg2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bDrawMode = FALSE; 
}

CWinProg2View::~CWinProg2View()
{
}

BOOL CWinProg2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWinProg2View 그리기

void CWinProg2View::OnDraw(CDC* pDC)
{
	CWinProg2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	if (GetDocument()->select == ELLIPSE){
	}
	else if (GetDocument()->select == RECTANGLE) {
	}
	else if (GetDocument()->select == TEXT) {
	}
	else if (GetDocument()->select == POLYLINE) {
	}
	else if (GetDocument()->select == LINE) {
	}
	else;

}


// CWinProg2View 인쇄


void CWinProg2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWinProg2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWinProg2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWinProg2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CWinProg2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinProg2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWinProg2View 진단

#ifdef _DEBUG
void CWinProg2View::AssertValid() const
{
	CView::AssertValid();
}

void CWinProg2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinProg2Doc* CWinProg2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinProg2Doc)));
	return (CWinProg2Doc*)m_pDocument;
}
#endif //_DEBUG


// CWinProg2View 메시지 처리기


void CWinProg2View::OnLButtonDown(UINT nFlags, CPoint point)

{
	m_bDrawMode = TRUE;				// 그리기 모드
	if (GetDocument()->select) {
		SetCapture();
		m_PointStart = m_PointEnd = point;	// 현재 포인트 좌표 저장
	}

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	

	CView::OnLButtonDown(nFlags, point);
}


void CWinProg2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	str.Format(_T("%4d,%4d"), point.x, point.y);
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText(1, str);

	if (m_bDrawMode) {
		if (GetDocument()->select == ELLIPSE){
			OnEllipse(point);
		}
		else if (GetDocument()->select == RECTANGLE) {
			OnRectangle(point);
		}
		else if (GetDocument()->select == TEXT) {
		}
		else if (GetDocument()->select == POLYLINE) {
		}
		else if (GetDocument()->select == LINE) {
		}
		else;
	}

	CView::OnMouseMove(nFlags, point);
}


void CWinProg2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrawMode) {
		if (GetDocument()->select == ELLIPSE){
			DrawEllipseEnd();
		}
		else if (GetDocument()->select == RECTANGLE) {
			DrawRectangleEnd();
		}
		else if (GetDocument()->select == TEXT) {
		}
		else if (GetDocument()->select == POLYLINE) {
		}
		else if (GetDocument()->select == LINE) {
		}
		else;
	}
	CView::OnLButtonUp(nFlags, point);
}




//Polyline 메뉴 선택
void CWinProg2View::OnDrawpoly()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString str;

	if (GetDocument()->select == EMPTY){
		GetDocument()->select = POLYLINE;
		str = _T("Polyline");
	}
	else{
		GetDocument()->select = EMPTY;
		str.LoadStringW(ID_INDICATOR_TOOL);
	}
	pMainFrame->m_wndStatusBar.SetPaneText(2, str);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//Polyline 선택시 체크 설정 확인
void CWinProg2View::OnUpdateDrawpoly(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (GetDocument()->select == POLYLINE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2View::OnEllipse(CPoint &point)
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	CPen m_penDot(PS_DOT, 1, RGB(0, 0, 0));
	dc.SelectObject(&m_penDot);
	dc.SetROP2(R2_XORPEN);

	
	dc.Ellipse(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);			// 이전 직선 지움
	
	dc.Ellipse(m_PointStart.x, m_PointStart.y, point.x, point.y);					// 새로운 직선
	
	m_PointEnd = point;																// 직선의 끝점 좌표 갱신
}



void CWinProg2View::OnRectangle(CPoint &point)
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	CPen m_penDot(PS_DOT, 1, RGB(0, 0, 0));
	dc.SelectObject(&m_penDot);
	dc.SetROP2(R2_XORPEN);

	
	dc.Rectangle(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);		// 이전 직선 지움
	
	dc.Rectangle(m_PointStart.x, m_PointStart.y, point.x, point.y);					// 새로운 직선
	
	m_PointEnd = point;																// 직선 끝점 좌표 갱신
}

void CWinProg2View::DrawEllipseEnd()
{
	CClientDC dc(this);

	CPen pen;
	CBrush brush;
	
	dc.SetROP2(R2_COPYPEN);															// 최종적인 직선
	dc.Ellipse(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);
	m_bDrawMode = FALSE;															// 그리기 모드 해제

	::ReleaseCapture();
}

void CWinProg2View::DrawRectangleEnd()
{
	CClientDC dc(this);

	CPen pen;
	CBrush brush;
	
	dc.SetROP2(R2_COPYPEN);															// 최종적인 직선을 그린다.
	dc.Rectangle(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);
	m_bDrawMode = FALSE;															// 그리기 모드를 해제한다.

	::ReleaseCapture();
}

void CWinProg2View::OnButtonEllipse()
{
	// TODO: Add your command handler code here
	GetDocument()->select = ELLIPSE;
}

void CWinProg2View::OnButtonRectangle()
{
	// TODO: Add your command handler code here
	GetDocument()->select = RECTANGLE;
}