
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
#include "StringDlg.h"

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
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CWinProg2View ����/�Ҹ�

CWinProg2View::CWinProg2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	Drawing = FALSE;
	Writable = FALSE;
	memDC = NULL;
	bitmap = NULL;
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
	CRect rect, rect1;
	GetClientRect(&rect);

	CWinProg2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->GetClipBox(&rect1);

	oldBitmap = memDC->SelectObject(bitmap);
	//CGdiObject* old = memDC->SelectStockObject(WHITE_BRUSH);
	//CGdiObject* oldPen = memDC->SelectStockObject(WHITE_PEN);
	memDC->SelectObject(CPen(PS_SOLID, pDoc->bold, RGB(0, 0, 0)));
	
	memDC->Rectangle(rect);
	//memDC->SelectObject(oldPen);

	CPtrList* list = &pDoc->getObject();

	POSITION pos = list->GetHeadPosition();
	while (pos != NULL) {
		((Object_Draw*)list->GetNext(pos))->Draw(memDC);
	}

	pDC->BitBlt(0, 0, rect1.bottom, rect1.right, memDC, 0, 0, SRCCOPY);

	//memDC->SelectObject(old);
	memDC->SelectObject(oldBitmap);


	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CWinProg2Doc* pDoc = GetDocument();

	CClientDC dc(this);

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);

	switch (pDoc->select){
	case POLYLINE:
		
		if (Writable == FALSE){
			Writable = TRUE;
			old_point = cur_point = point;
			pDoc->getPolyLineDraw(TRUE)->addPoint(FALSE, point);
			pDoc->Empty = FALSE;
		}
		else{
			//pDoc->getPolyLineDraw()->addPoint(point);
		}
		
		Drawing = TRUE;
		break;
	case TEXT:
		//Rectangle �κп��� ó��

	case RECTANGLE:
		//CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		//CPen *oldPne = dc.SelectObject(&pen);
		if (Writable == FALSE){
			Writable = TRUE;
			old_point = cur_point = point;
			if (pDoc->select == RECTANGLE)
				pDoc->getRectDraw(TRUE)->addPoint(point);
			else if (pDoc->select == TEXT)
				pDoc->getTextBoxDraw(TRUE)->addPoint(point);
			pDoc->Empty = FALSE;
		}
		else{

		}
		Drawing = TRUE;
		break;
	}


	CView::OnLButtonDown(nFlags, point);
}


void CWinProg2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CWinProg2Doc* pDoc = GetDocument();

	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, pDoc->color);
	CRect rect;
	StringDlg dlg(pDoc->str);

	switch (pDoc->select){
		case POLYLINE:
			old_point = point;
			pDoc->getPolyLineDraw()->addPoint(FALSE, point);
			pDoc->RE_Empty = FALSE;
			break;

		case TEXT:
			//Rectangle�κп��� ó��

		case RECTANGLE:
			if (pDoc->select == RECTANGLE){
				dc.Rectangle(old_point.x, old_point.y, point.x, point.y);
							pDoc->getRectDraw()->addPoint(point);
			}
			else if (pDoc->select == TEXT){
				rect.SetRectEmpty();
				rect.SetRect(old_point, point);
				dc.Rectangle(&rect);

				dlg.DoModal();

				dc.DrawText(pDoc->str, &rect, DT_SINGLELINE || DT_VCENTER);
			}

			Writable = FALSE;
			//Invalidate();
			break;
	}

	CView::OnLButtonUp(nFlags, point);
}


void CWinProg2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CWinProg2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CString str;
	str.Format(_T("%4d,%4d"), point.x, point.y);
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText(1, str);

	CPen cpen(PS_SOLID, pDoc->bold, RGB(0, 0, 0));
	CBrush cbrush(HS_CROSS, RGB(255, 255, 255));
	CPen *oldPen = dc.SelectObject(&cpen);
	CBrush *oldBrush = dc.SelectObject(&cbrush);

	if (Writable == TRUE){
		CPen pen(PS_SOLID, pDoc->bold, RGB(0 ^ 255, 0 ^ 255, 0 ^ 255));

		switch (pDoc->select){
			case POLYLINE:
				
				dc.SelectObject(GetStockObject(NULL_BRUSH));
				dc.SetROP2(R2_XORPEN);
				oldPen = (CPen *)dc.SelectObject(&pen);
				dc.MoveTo(old_point);
				dc.LineTo(cur_point);

				dc.MoveTo(old_point);
				dc.LineTo(point);
				cur_point = point;

				break;
			case TEXT:
				//Rectangle���� ó��

			case RECTANGLE:
				dc.SelectObject(GetStockObject(NULL_BRUSH));
				dc.SetROP2(R2_XORPEN);
				oldPen = (CPen*)dc.SelectObject(&pen);

				dc.Rectangle(old_point.x, old_point.y, cur_point.x, cur_point.y);
				dc.Rectangle(old_point.x, old_point.y, point.x, point.y);
				cur_point = point;
				break;
			}
	}
	

	dc.SelectObject(oldPen);

	CView::OnMouseMove(nFlags, point);
}

//Polyline �޴� ����
void CWinProg2View::OnDrawpoly()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString str;

	if (GetDocument()->select != POLYLINE){
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


void CWinProg2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CWinProg2Doc* pDoc = GetDocument();
	CClientDC dc(this);

	if (pDoc->select == POLYLINE){
		//old_point = point;
		dc.MoveTo(old_point);
		dc.LineTo(point);
		pDoc->getPolyLineDraw()->addPoint(FALSE, point);
		Writable = FALSE;
		
	}
	Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}


void CWinProg2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rect;
	GetClientRect(&rect);

	memDC = new CDC();
	bitmap = new CBitmap();

	memDC->CreateCompatibleDC(GetDC());
	bitmap->CreateCompatibleBitmap(GetDC(), rect.bottom, rect.right);

	oldBitmap = memDC->SelectObject(bitmap);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
