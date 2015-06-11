
// WinProg2View.h : CWinProg2View Ŭ������ �������̽�
//

#pragma once


class CWinProg2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CWinProg2View();
	DECLARE_DYNCREATE(CWinProg2View)

// Ư���Դϴ�.
public:
	CWinProg2Doc* GetDocument() const;

// �۾��Դϴ�.
public:
	CRect m_rect, select_rect;
	BOOL Drawing, Writable;
	CPoint old_point;
	CPoint cur_point;
	POSITION tmp_pos;
	CPoint top, bottom;
	Command cmd;

	CDC memDC;
	CBitmap bitmap, *pOldbitmap;
	CRectTracker* m_Tracker;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CWinProg2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void select_DrawObj(CPoint point);
	void move_Object();
	afx_msg void OnObjectDelete();
	afx_msg void OnObjselectdel();
	afx_msg void OnUpdateObjectDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateObjselectdel(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // WinProg2View.cpp�� ����� ����
inline CWinProg2Doc* CWinProg2View::GetDocument() const
   { return reinterpret_cast<CWinProg2Doc*>(m_pDocument); }
#endif

