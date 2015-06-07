
// WinProg2Doc.h : CWinProg2Doc Ŭ������ �������̽�
//
#include "Object_Draw.h"
#include "PolyLine.h"
#include "RectAngle.h"
#include "TextBox.h"

#pragma once

enum Select{
	LINE, POLYLINE, TEXT, RECTANGLE, ELLIPSE, EMPTY, SELECT
};



class CWinProg2Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CWinProg2Doc();
	DECLARE_DYNCREATE(CWinProg2Doc)

// Ư���Դϴ�.
public:
	Object_Draw* m_Cur;
	CPtrList m_Object;

// �۾��Դϴ�.
public:
	Select select;
	COLORREF color;
	//LINE, POLYLINE �����Լ�
	PolyLine* getPolyLineDraw(BOOL isNew = FALSE);
	//RECTANGLE �����Լ�
	RectAngle* getRectDraw(BOOL isNew = FALSE);
	//TEXTBOX �����Լ�
	TextBox* getTextBoxDraw(BOOL isNew = FALSE);

	Bold bold;
	int index, fontsize=10;
	UINT pen_type;
	BOOL Empty, RE_Empty;
	CString str;
	CFont font;
	LOGFONT lf;

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
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnTextbox();
	afx_msg void OnUpdateTextbox(CCmdUI *pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
};
