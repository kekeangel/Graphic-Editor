
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
	BOOL m_bDrawMode;
	int m_btSelectMode;
	CPoint m_StartPoint, m_EndPoint;
	CPoint m_PointStart, m_PointEnd;

// �۾��Դϴ�.
public:

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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawpoly();
	afx_msg void OnUpdateDrawpoly(CCmdUI *pCmdUI);
	void OnEllipse(CPoint &point);
	void OnRectangle(CPoint &point);
	afx_msg void DrawEllipseEnd();
	afx_msg void DrawRectangleEnd();
	afx_msg void OnButtonRectangle();
	afx_msg void OnButtonEllipse();
	afx_msg void OnDrawellipse();
};

#ifndef _DEBUG  // WinProg2View.cpp�� ����� ����
inline CWinProg2Doc* CWinProg2View::GetDocument() const
   { return reinterpret_cast<CWinProg2Doc*>(m_pDocument); }
#endif

