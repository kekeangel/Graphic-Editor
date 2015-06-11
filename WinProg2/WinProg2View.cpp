
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
#include "TextEdit.h"

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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_DeleteAll, &CWinProg2View::OnDeleteall)
	ON_WM_CHAR()
	ON_COMMAND(ID_Object_Delete, &CWinProg2View::OnObjectDelete)
	ON_COMMAND(ID_ObjSelectDel, &CWinProg2View::OnObjselectdel)
	ON_UPDATE_COMMAND_UI(ID_Object_Delete, &CWinProg2View::OnUpdateObjectDelete)
	ON_UPDATE_COMMAND_UI(ID_ObjSelectDel, &CWinProg2View::OnUpdateObjselectdel)
END_MESSAGE_MAP()

// CWinProg2View 생성/소멸

CWinProg2View::CWinProg2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	//GetClientRect(&m_rect);
	Drawing = FALSE;
	Writable = FALSE;
	pOldbitmap = NULL;
	top = bottom = 0;
	m_Tracker = NULL; 
	cmd = NONE;
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

void CWinProg2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	//더블버퍼링 이용 출력 설정

	CClientDC dc(this);

	GetClientRect(m_rect);

	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, m_rect.Width(), m_rect.Height());

	pOldbitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, m_rect.Width(), m_rect.Height(), WHITENESS);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


// CWinProg2View 그리기

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

	if (m_Tracker){
		if ((m_Tracker->m_rect.Width() > 0) && (m_Tracker->m_rect.Height() > 0)){
				m_Tracker->Draw(pDC);
			}
	}
	
		

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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
	CWinProg2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPen pen(pDoc->pen_type, pDoc->bold, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);

	switch (pDoc->select){
		case SELECT:
			
			//범위설정
			if (m_Tracker->HitTest(point) < 0){
				CRectTracker track;

				if (track.TrackRubberBand(this, point, TRUE)){
					track.m_rect.NormalizeRect();
					m_Tracker->m_rect = track.m_rect;
					
					top.x = track.m_rect.left;
					top.y = track.m_rect.top;
					bottom.x = track.m_rect.right;
					bottom.y = track.m_rect.bottom;


					old_point = top;
					cur_point = bottom;

					Writable = TRUE;
					pDoc->Empty = FALSE;
					Drawing = FALSE;

					cmd = NONE;
					select_DrawObj(point);

				}
				else{
					m_Tracker->m_rect = CRect(0, 0, 0, 0);
					Writable = FALSE;
				}
			}
			else{
				if (m_Tracker->Track(this, point, true)){
					m_Tracker->m_rect.NormalizeRect();

					top.x = m_Tracker->m_rect.left;
					top.y = m_Tracker->m_rect.top;
					bottom.x = m_Tracker->m_rect.right;
					bottom.y = m_Tracker->m_rect.bottom;

					Writable = TRUE;
					Drawing = TRUE;
					pDoc->Empty = FALSE;

					cmd = MOVE;

					select_DrawObj(point);

					old_point = top;
					cur_point = bottom;
					Invalidate();
				}
				else{
					m_Tracker->m_rect = CRect(0, 0, 0, 0);
					Writable = FALSE;
				}
			}

			Invalidate();
			break;

		case LINE:
			//POLYLINE부분에서 처리

		case POLYLINE:
			if (Writable == FALSE){
				Writable = TRUE;
				old_point = cur_point = point;
				pDoc->getPolyLineDraw(TRUE)->addPoint(FALSE, point);
				pDoc->getPolyLineDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);
				pDoc->getPolyLineDraw()->setDrawType(pDoc->select);
				pDoc->Empty = FALSE;
			}
			else{

			}
			Drawing = TRUE;
			break;

		case TEXT:
			//Rectangle부분에서 처리

		case RECTANGLE:
			if (Writable == FALSE){
				Writable = TRUE;
				old_point = cur_point = point;
				if (pDoc->select == RECTANGLE){
					pDoc->getRectDraw(TRUE)->addPoint(point);
					pDoc->getRectDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);
					pDoc->getRectDraw()->setDrawType(pDoc->select);
					pDoc->getRectDraw()->setFillColor(pDoc->m_fill_color);
				}
				else if (pDoc->select == TEXT){
					pDoc->getTextBoxDraw(TRUE)->addPoint(point);
					pDoc->getTextBoxDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);
					pDoc->getTextBoxDraw()->setDrawType(pDoc->select);
					pDoc->getTextBoxDraw()->setFillColor(pDoc->m_fill_color);

				}
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
				pDoc->getEllipseDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);
				pDoc->getEllipseDraw()->setDrawType(pDoc->select);
				pDoc->getEllipseDraw()->setFillColor(pDoc->m_fill_color);
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
				pDoc->getFreeLineDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);
				pDoc->getFreeLineDraw()->setDrawType(pDoc->select);
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
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
		CPen pen;
		pen.CreatePen(PS_SOLID, pDoc->bold, pDoc->color);
		dc.SelectObject(GetStockObject(NULL_BRUSH));
		dc.SetROP2(R2_NOT);

		switch (pDoc->select){
		case LINE:
			//POLYLINE부분에서 처리

		case POLYLINE:

			oldPen = (CPen *)dc.SelectObject(&pen);
			dc.MoveTo(old_point);
			dc.LineTo(cur_point);

			dc.MoveTo(old_point);
			dc.LineTo(point);
			cur_point = point;

			break;	

		case SELECT:

			break;

		case TEXT:
					//Rectangle에서 처리

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CWinProg2Doc* pDoc = (CWinProg2Doc*)GetDocument();

	CClientDC dc(this);
	CPen pen;
	CRect rect, text_rect;
	TextEdit dlg(pDoc->str);
	CFont font;

	pen.CreatePen(pDoc->pen_type, pDoc->bold, pDoc->color);
	dc.SelectObject(&pen);

	CPen select_pen(PS_DASH, 3, RGB(255, 0, 0));

	switch (pDoc->select){
	case LINE:
		dc.MoveTo(old_point);
		dc.LineTo(point);
		pDoc->getPolyLineDraw()->addPoint(FALSE, point);
		Writable = FALSE;
		pDoc->RE_Empty = FALSE;
		Invalidate();
		break;

	case POLYLINE:
		old_point = point;
		pDoc->getPolyLineDraw()->addPoint(FALSE, point);
		pDoc->RE_Empty = FALSE;
		break;

	case SELECT:
		Invalidate();
		break;

	case TEXT:
		//Rectangle부분에서 처리

	case RECTANGLE:
		if (pDoc->select == RECTANGLE){
			dc.Rectangle(old_point.x, old_point.y, point.x, point.y);
			pDoc->getRectDraw()->setRect(old_point, point);
			pDoc->getRectDraw()->addPoint(point);
			Writable = FALSE;
			pDoc->RE_Empty = FALSE;
			pDoc->m_select.AddTail(RECTANGLE);
			Invalidate();
		}

		else if (pDoc->select == TEXT){
			rect.SetRectEmpty();
			rect.SetRect(old_point, point);
			
			text_rect = rect;
			text_rect.left += 5;
			text_rect.right -= 5;
			text_rect.top += 5;
			text_rect.bottom -= 5;

			dc.Rectangle(&rect);
			
			dlg.DoModal();

			//font.CreateFontIndirectW(&pDoc->font_style.lf);
			dc.SetTextColor(pDoc->font_style.font_color);
			dc.SelectObject(&font);
			old_point.x += 5;
			old_point.y += 5;

			dc.SelectObject(&font);
			pDoc->getTextBoxDraw()->setString(pDoc->str);
			dc.DrawText(pDoc->str, &text_rect, DT_LEFT);
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
		Writable = FALSE;
		break;

	case ELLIPSE:
		Writable = FALSE;
		dc.Ellipse(old_point.x, old_point.y, point.x, point.y);
		pDoc->getEllipseDraw()->addPoint(point);
		pDoc->RE_Empty = FALSE;
		pDoc->m_select.AddTail(ELLIPSE);
		Invalidate();
		break;

	case FREELINE:
		Writable = FALSE;
		dc.MoveTo(old_point);
		dc.LineTo(point);
		pDoc->getFreeLineDraw()->addPoint(point);
		pDoc->RE_Empty = FALSE;
		pDoc->m_select.AddTail(FREELINE);
		Invalidate();
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}

//더블클릭(POLYLINE종료)
void CWinProg2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	CView::OnLButtonDblClk(nFlags, point);
}

//마우스 커서 변경(그리기도구선택 -> 십자모양커서)
BOOL CWinProg2View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nHitTest == HTCLIENT){
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);

		if (Writable == TRUE && pDoc->select != SELECT){
			::SetCursor(LoadCursor(NULL, IDC_CROSS));
		}

		else if (Writable == TRUE && pDoc->select == SELECT &&
			m_Tracker->SetCursor(this, nHitTest))
			return TRUE;

		else{
			::SetCursor(LoadCursor(NULL, IDC_ARROW));
		}

		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

//화면전체지우기
void CWinProg2View::OnDeleteall()
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	pDoc->m_Object.RemoveAll();
	Invalidate();
}

void CWinProg2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

//도형객체선택
void CWinProg2View::select_DrawObj(CPoint point){
	CWinProg2Doc* pDoc = GetDocument();

	POSITION Obj_pos, prev_Obj_pos;
	CPtrList* list = &pDoc->getObject();
	CPoint tmp_top, tmp_bottom;
	
	BOOL OK;

	Obj_pos = list->GetHeadPosition();
	prev_Obj_pos = list->GetHeadPosition();
	
	while (Obj_pos != NULL) {
		OK = ((Object_Draw*)list->GetNext(Obj_pos))->getselectPoint(old_point, cur_point);
	
		if (OK == TRUE){
			pDoc->Obj_select = TRUE;

			pDoc->tmp_select = ((Object_Draw*)list->GetAt(prev_Obj_pos))->getDrawType();

			switch (cmd){
				case NONE:
					break;

				case MOVE:
					move_Object();
					break;

				case DEL:
					list->RemoveAt(prev_Obj_pos);
					Invalidate();
					break;

				case RESIZE:

					break;

				case SETTYPE:
					//SETTYPE, SETBOD, FILLCOLOR 작업동일

				case LINECOLOR:
					//SETTYPE, SETBOD, FILLCOLOR 작업동일

				case SETBOLD:
					if (pDoc->tmp_select == LINE || pDoc->tmp_select == POLYLINE)
						pDoc->getPolyLineDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);

					else if (pDoc->tmp_select == RECTANGLE)
						pDoc->getRectDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);

					else if (pDoc->tmp_select == TEXT)
						pDoc->getTextBoxDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);

					else if (pDoc->tmp_select == ELLIPSE)
						pDoc->getEllipseDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);

					else if (pDoc->tmp_select == FREELINE)
						pDoc->getFreeLineDraw()->setPencil(pDoc->bold, pDoc->pen_type, pDoc->color);

					Invalidate();
					break;
					
				case FILLCOLOR:
					if (pDoc->tmp_select == RECTANGLE){
						pDoc->getRectDraw()->setFillColor(pDoc->m_fill_color);
						
					}
					else if (pDoc->tmp_select == TEXT){
						pDoc->getTextBoxDraw()->setFillColor(pDoc->m_fill_color);
					}
					else if (pDoc->tmp_select == ELLIPSE){
						pDoc->getEllipseDraw()->setFillColor(pDoc->m_fill_color);
					}
					Invalidate();
					break;
			}
		}
		if ((Object_Draw*)list->GetNext(prev_Obj_pos) == NULL)
			break;
		

	}
}

//객체 전체 이동함수
void CWinProg2View::move_Object(){
	CWinProg2Doc* pDoc = GetDocument();

	int top_x, top_y, bot_x, bot_y;
	top_x = top_y = bot_x = bot_y = 0;

	top_x = old_point.x - top.x;
	top_y = old_point.y - top.y;
	bot_x = cur_point.x - bottom.x;
	bot_y = cur_point.y - bottom.y;

	switch (pDoc->tmp_select){
	case LINE:
		
		pDoc->getPolyLineDraw()->movePoint(top_x, top_y, bot_x, bot_y);
		break;

	case POLYLINE:
		pDoc->getPolyLineDraw()->movePoint(top_x, top_y, bot_x, bot_y);
		break;

	case RECTANGLE:
		pDoc->getRectDraw()->movePoint(top_x, top_y, bot_x, bot_y);
		break;

	case ELLIPSE:
		pDoc->getEllipseDraw()->movePoint(top_x, top_y, bot_x, bot_y);
		break;

	case TEXT:
		pDoc->getTextBoxDraw()->movePoint(top_x, top_y, bot_x, bot_y);
		break;

	case FREELINE:
		pDoc->getFreeLineDraw()->movePoint(top_x, top_y, bot_x, bot_y);
		break;
	}
}

//팝업메뉴 삭제메뉴
void CWinProg2View::OnObjectDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	cmd = DEL;
	select_DrawObj(point);

}

void CWinProg2View::OnUpdateObjectDelete(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->select == SELECT && Writable == TRUE)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}

//메뉴바 삭제명령
void CWinProg2View::OnObjselectdel()
{
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	cmd = DEL;
	select_DrawObj(point);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CWinProg2View::OnUpdateObjselectdel(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = GetDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->select == SELECT && Writable == TRUE)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}




