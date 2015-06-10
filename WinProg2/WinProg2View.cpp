
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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_DeleteAll, &CWinProg2View::OnDeleteall)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CWinProg2View ����/�Ҹ�

CWinProg2View::CWinProg2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	//GetClientRect(&m_rect);
	Drawing = FALSE;
	Writable = FALSE;
	pOldbitmap = NULL;
	Obj_select = FALSE;
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

void CWinProg2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	//������۸� �̿� ��� ����

	CClientDC dc(this);

	GetClientRect(m_rect);

	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, m_rect.Width(), m_rect.Height());

	pOldbitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, m_rect.Width(), m_rect.Height(), WHITENESS);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


// CWinProg2View �׸���

void CWinProg2View::OnDraw(CDC* pDC)
{
	CWinProg2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	CPtrList* list = &pDoc->getObject();

	POSITION pos = list->GetHeadPosition();
	while (pos != NULL) {
		((Object_Draw*)list->GetNext(pos))->Draw(pDC);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);

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
	CWinProg2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CPen pen(pDoc->pen_type, pDoc->bold, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	COLORREF p_color;
	switch (pDoc->select){
		case SELECT:
			if (Writable == FALSE){
				Writable = TRUE;
				old_point = cur_point = point;
				pDoc->Empty = FALSE;
			}
			break;

		case FILL:
			p_color = RGB(0, 0, 0);
			pDoc->getFillDraw(TRUE)->setPoint(point);
			pDoc->getFillDraw()->setColor(p_color);
			Invalidate();
			break;

		case LINE:
			//POLYLINE�κп��� ó��

		case POLYLINE:
			if (Writable == FALSE){
				Writable = TRUE;
				old_point = cur_point = point;
				pDoc->getPolyLineDraw(TRUE)->addPoint(FALSE, point);
				pDoc->getPolyLineDraw()->m_color = pDoc->color;
				pDoc->getPolyLineDraw()->m_bold = pDoc->bold;
				
				pDoc->Empty = FALSE;
			}
			else{
				
			}
			Drawing = TRUE;
			break;

		case TEXT:
			//Rectangle�κп��� ó��

		case RECTANGLE:
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

		case ELLIPSE:
			if (Writable == FALSE){
				Writable = TRUE;
				old_point = cur_point = point;
				pDoc->getEllipseDraw(TRUE)->addPoint(point);
				pDoc->Empty = FALSE;
			}
			else{

			}

			Drawing = TRUE;
			break;

		case FREELINE:
			if (Writable == FALSE){
				Writable = TRUE;
				old_point = cur_point = point;
				pDoc->getFreeLineDraw(TRUE)->addPoint(point);
				pDoc->Empty = FALSE;
			}
			else{

			}

			Drawing = TRUE;
			break;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CWinProg2View::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CWinProg2Doc* pDoc = GetDocument();
	CString str;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);
	
	str.Format(_T("%4d,%4d"), point.x, point.y);

	pMainFrame->m_wndStatusBar.SetPaneText(1, str);

	CPen cpen(PS_SOLID, pDoc->bold, RGB(0, 0, 0));
	CPen select_pen(PS_DASH, 1, RGB(0, 0, 0));
	CBrush cbrush(HS_CROSS, RGB(255, 255, 255));
	CPen *oldPen = dc.SelectObject(&cpen);
	CBrush *oldBrush = dc.SelectObject(&cbrush);
	COLORREF tmp_color;
	tmp_color = pDoc->color ^ 255;


	if (Writable == TRUE){
		CPen pen;/* (PS_SOLID, pDoc->bold, RGB(0 ^ 255, 0 ^ 255, 0 ^ 255));*/
		pen.CreatePen(PS_SOLID, pDoc->bold, pDoc->color);
		dc.SelectObject(GetStockObject(NULL_BRUSH));
		dc.SetROP2(R2_NOT);

		switch (pDoc->select){
		case LINE:
			//POLYLINE�κп��� ó��

		case POLYLINE:

			oldPen = (CPen *)dc.SelectObject(&pen);
			dc.MoveTo(old_point);
			dc.LineTo(cur_point);

			dc.MoveTo(old_point);
			dc.LineTo(point);
			cur_point = point;

			break;
		case TEXT:
			//Rectangle���� ó��

		case SELECT:
			//Rectangle���� ó��

		case RECTANGLE:
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_NOT);
			oldPen = (CPen *)dc.SelectObject(&pen);
			if (pDoc->select != SELECT)
				oldPen = (CPen*)dc.SelectObject(&pen);

			else{
				oldPen = (CPen*)dc.SelectObject(&select_pen);
			}

			dc.Rectangle(old_point.x, old_point.y, cur_point.x, cur_point.y);
			dc.Rectangle(old_point.x, old_point.y, point.x, point.y);
			cur_point = point;
			break;

		case ELLIPSE:
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_NOT);
			dc.Ellipse(old_point.x, old_point.y, cur_point.x, cur_point.y);
			dc.Ellipse(old_point.x, old_point.y, point.x, point.y);
			cur_point = point;
			break;

		case FREELINE:
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_NOT);
			dc.MoveTo(old_point);
			dc.LineTo(point);
			pDoc->getFreeLineDraw()->addPoint(point);
			old_point = point;
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CWinProg2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CWinProg2Doc* pDoc = (CWinProg2Doc*)GetDocument();

	CClientDC dc(this);
	CPen pen;
	CRect rect, text_rect;
	//StringDlg dlg(pDoc->str);
	CFont font;
	POSITION Obj_pos;
	CPtrList* list = &pDoc->getObject();

	pen.CreatePen(pDoc->pen_type, pDoc->bold, pDoc->color);
	dc.SelectObject(&pen);

	CPen select_pen(PS_DASH, 1, RGB(0, 0, 0));

	Object_Draw* Cur;
	Select ch_select;

	SetCapture();
	switch (pDoc->select){
	case LINE:
		dc.MoveTo(old_point);
		dc.LineTo(point);
		pDoc->getPolyLineDraw()->addPoint(FALSE, point);
		Writable = FALSE;
		pDoc->RE_Empty = FALSE;
		Invalidate();
		::ReleaseCapture();
		break;

	case POLYLINE:
		old_point = point;
		pDoc->getPolyLineDraw()->addPoint(FALSE, point);
		pDoc->RE_Empty = FALSE;
		break;

	case SELECT:

		Obj_pos = list->GetHeadPosition();
		while (Obj_pos != NULL) {
			BOOL OK;
			OK = ((Object_Draw*)list->GetNext(Obj_pos))->getselectPoint(old_point, point);
			if (OK == TRUE){
				Obj_select = TRUE;
				break;
			}
				
			
		}

		break;

	case TEXT:
		//Rectangle�κп��� ó��

	case RECTANGLE:
		if (pDoc->select == RECTANGLE){
			dc.Rectangle(old_point.x, old_point.y, point.x, point.y);
			pDoc->getRectDraw()->setRect(old_point, point);
			pDoc->getRectDraw()->addPoint(point);
			pDoc->m_select.AddTail(RECTANGLE);
			Invalidate();
		}

		else if (pDoc->select == TEXT){
			rect.SetRectEmpty();
			rect.SetRect(old_point, point);
			
			text_rect = rect;
			text_rect.left = 5;
			text_rect.right -= 5;
			text_rect.top = 5;
			text_rect.bottom -= 5;

			dc.Rectangle(&rect);
			
			//dlg.DoModal();

			font.CreateFontIndirectW(&pDoc->lf);
			dc.SetTextColor(pDoc->fontcolor);
			dc.SelectObject(&font);
			old_point.x += 5;
			old_point.y += 5;
			
			CreateSolidCaret(1, pDoc->fontsize);
			SetCaretPos(old_point);
			ShowCaret();

//			dc.DrawText(pDoc->m_str.GetData(), &text_rect, DT_LEFT);
			pDoc->getTextBoxDraw()->addPoint(point);
			pDoc->RE_Empty = FALSE;
			pDoc->m_select.AddTail(TEXT);
			Invalidate();
		}

		else{
			dc.SelectObject(select_pen);
			dc.Rectangle(old_point.x, old_point.y, point.x, point.y);
			Invalidate();

		}
		::ReleaseCapture();
		Writable = FALSE;
		break;

	case ELLIPSE:
		Writable = FALSE;
		dc.Ellipse(old_point.x, old_point.y, point.x, point.y);
		pDoc->getEllipseDraw()->addPoint(point);
		pDoc->RE_Empty = FALSE;
		pDoc->m_select.AddTail(ELLIPSE);
		Invalidate();
		::ReleaseCapture();
		break;

	case FREELINE:
		Writable = FALSE;
		dc.MoveTo(old_point);
		dc.LineTo(point);
		pDoc->getFreeLineDraw()->addPoint(point);
		pDoc->RE_Empty = FALSE;
		pDoc->m_select.AddTail(FREELINE);
		Invalidate();
		::ReleaseCapture();
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}

//����Ŭ��(POLYLINE����)
void CWinProg2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CWinProg2Doc* pDoc = GetDocument();
	CClientDC dc(this);

	if (pDoc->select == POLYLINE){
		dc.MoveTo(old_point);
		dc.LineTo(point);
		pDoc->getPolyLineDraw()->addPoint(FALSE, point);
		Writable = FALSE;
		pDoc->m_select.AddTail(POLYLINE);
		Invalidate();
	}
	::ReleaseCapture();
	CView::OnLButtonDblClk(nFlags, point);
}

//���콺 Ŀ�� ����(�׸��⵵������ -> ���ڸ��Ŀ��)
BOOL CWinProg2View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nHitTest == HTCLIENT){
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);

		if (Writable == TRUE && pDoc->select != SELECT){
			::SetCursor(LoadCursor(NULL, IDC_CROSS));
		}
		else if (Writable == TRUE && pDoc->select == SELECT){
			::SetCursor(LoadCursor(NULL, IDC_HAND));
		}

		else{
			::SetCursor(LoadCursor(NULL, IDC_ARROW));
		}

		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

//ȭ����ü�����
void CWinProg2View::OnDeleteall()
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	pDoc->m_Object.RemoveAll();
	Invalidate();
}


// m_Object�� �ִ� �������� ���� �ľ� �� m_Cur�� ����
void CWinProg2View::ret_ListData(Select select)
{
	CWinProg2Doc* pDoc = GetDocument();

	switch (select){
		case POLYLINE:
			//LINE���� ó��

		case LINE:
			pDoc->m_Cur = (PolyLine*)pDoc->m_Cur;
			break;

		case TEXT:
			//RECTANGLE���� ó��

		case RECTANGLE:
			pDoc->m_Cur = (RectAngle*)pDoc->m_Cur;
			break;

		case ELLIPSE:
			pDoc->m_Cur = (ELLipse*)pDoc->m_Cur;
			break;

		case FREELINE:
			pDoc->m_Cur = (FreeLine*)pDoc->m_Cur;
			break;

	}
}


void CWinProg2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (pDoc->select == TEXT){
		if (nChar == _T('\b')){
			if (pDoc->m_str.GetSize() > 0)
				pDoc->m_str.RemoveAt(pDoc->m_str.GetSize() - 1);
		}
		else{
			pDoc->m_str.Add(nChar);
		}
	}
	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}
