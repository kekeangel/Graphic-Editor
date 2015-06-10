
// WinProg2View.h : CWinProg2View 클래스의 인터페이스
//

#pragma once


class CWinProg2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CWinProg2View();
	DECLARE_DYNCREATE(CWinProg2View)

// 특성입니다.
public:
	CWinProg2Doc* GetDocument() const;

// 작업입니다.
public:
	CRect m_rect;
	BOOL Drawing;
	BOOL Writable;
	BOOL Obj_select;
	CPoint old_point;
	CPoint cur_point;
	//CPoint point;
	

	CDC memDC;
	CBitmap bitmap, *pOldbitmap;


// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CWinProg2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void OnInitialUpdate();
	afx_msg void OnDeleteall();
	// m_Object에 있는 데이터의 종류 파악 및 m_Cur에 저장
	void ret_ListData(Select select);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // WinProg2View.cpp의 디버그 버전
inline CWinProg2Doc* CWinProg2View::GetDocument() const
   { return reinterpret_cast<CWinProg2Doc*>(m_pDocument); }
#endif

