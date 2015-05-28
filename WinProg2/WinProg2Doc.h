
// WinProg2Doc.h : CWinProg2Doc Ŭ������ �������̽�
//
#include "Object_Draw.h"
#include "PolyLine.h"

#pragma once

enum Select{
	POLYLINE, TEXT, EMPTY
};

extern enum Bold{
	NON, ONE, TWO, THREE, FOUR, FIVE, SIX
};

class CWinProg2Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CWinProg2Doc();
	DECLARE_DYNCREATE(CWinProg2Doc)

// Ư���Դϴ�.
public:

protected:
	Object_Draw* m_Cur;
	CPtrList m_Object;

// �۾��Դϴ�.
public:
	Select select;
	COLORREF color;
	PolyLine* getPolyLineDraw(BOOL isNew = FALSE);
	Bold bold;

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	CPtrList& getObject();

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CWinProg2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColor();
	afx_msg void OnFont();
	afx_msg void OnBold1();
	afx_msg void OnBold2();
	afx_msg void OnBold3();
	afx_msg void OnBold4();
	afx_msg void OnBold5();
	afx_msg void OnBold6();
	afx_msg void OnUpdateBold1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBold2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBold3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBold4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBold5(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBold6(CCmdUI *pCmdUI);
};
