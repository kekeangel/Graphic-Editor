
// WinProg2View.cpp : CWinProg2View Ŭ������ ����
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinProg2View

IMPLEMENT_DYNCREATE(CWinProg2View, CView)

BEGIN_MESSAGE_MAP(CWinProg2View, CView)
	// ǥ�� �μ� ����Դϴ�.
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

// CWinProg2View ����/�Ҹ�

CWinProg2View::CWinProg2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_bDrawMode = FALSE; 
}

CWinProg2View::~CWinProg2View()
{
}

BOOL CWinProg2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CWinProg2View �׸���

void CWinProg2View::OnDraw(CDC* pDC)
{
	CWinProg2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

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


// CWinProg2View �μ�


void CWinProg2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWinProg2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CWinProg2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CWinProg2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CWinProg2View ����

#ifdef _DEBUG
void CWinProg2View::AssertValid() const
{
	CView::AssertValid();
}

void CWinProg2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinProg2Doc* CWinProg2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinProg2Doc)));
	return (CWinProg2Doc*)m_pDocument;
}
#endif //_DEBUG


// CWinProg2View �޽��� ó����


void CWinProg2View::OnLButtonDown(UINT nFlags, CPoint point)

{
	m_bDrawMode = TRUE;				// �׸��� ���
	if (GetDocument()->select) {
		SetCapture();
		m_PointStart = m_PointEnd = point;	// ���� ����Ʈ ��ǥ ����
	}

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	

	CView::OnLButtonDown(nFlags, point);
}


void CWinProg2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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




//Polyline �޴� ����
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//Polyline ���ý� üũ ���� Ȯ��
void CWinProg2View::OnUpdateDrawpoly(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
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

	
	dc.Ellipse(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);			// ���� ���� ����
	
	dc.Ellipse(m_PointStart.x, m_PointStart.y, point.x, point.y);					// ���ο� ����
	
	m_PointEnd = point;																// ������ ���� ��ǥ ����
}



void CWinProg2View::OnRectangle(CPoint &point)
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	CPen m_penDot(PS_DOT, 1, RGB(0, 0, 0));
	dc.SelectObject(&m_penDot);
	dc.SetROP2(R2_XORPEN);

	
	dc.Rectangle(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);		// ���� ���� ����
	
	dc.Rectangle(m_PointStart.x, m_PointStart.y, point.x, point.y);					// ���ο� ����
	
	m_PointEnd = point;																// ���� ���� ��ǥ ����
}

void CWinProg2View::DrawEllipseEnd()
{
	CClientDC dc(this);

	CPen pen;
	CBrush brush;
	
	dc.SetROP2(R2_COPYPEN);															// �������� ����
	dc.Ellipse(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);
	m_bDrawMode = FALSE;															// �׸��� ��� ����

	::ReleaseCapture();
}

void CWinProg2View::DrawRectangleEnd()
{
	CClientDC dc(this);

	CPen pen;
	CBrush brush;
	
	dc.SetROP2(R2_COPYPEN);															// �������� ������ �׸���.
	dc.Rectangle(m_PointStart.x, m_PointStart.y, m_PointEnd.x, m_PointEnd.y);
	m_bDrawMode = FALSE;															// �׸��� ��带 �����Ѵ�.

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