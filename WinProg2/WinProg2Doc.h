
// WinProg2Doc.h : CWinProg2Doc Ŭ������ �������̽�
//
#include "Object_Draw.h"
#include "PolyLine.h"
#include "RectAngle.h"
#include "TextBox.h"
#include "ELLipse.h"
#include "FreeLine.h"
#include "FillDraw.h"
#include "typedef.h"

#pragma once



class CWinProg2Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CWinProg2Doc();
	DECLARE_DYNCREATE(CWinProg2Doc)

// Ư���Դϴ�.
public:
	Object_Draw* m_Cur;
	CPtrList m_Object;
	CList<Select, Select> m_select;

// �۾��Դϴ�.
public:
	Select select, tmp_select;
	COLORREF color;
	//LINE, POLYLINE �����Լ�
	PolyLine* getPolyLineDraw(BOOL isNew = FALSE);
	//RECTANGLE �����Լ�
	RectAngle* getRectDraw(BOOL isNew = FALSE);
	//TEXTBOX �����Լ�
	TextBox* getTextBoxDraw(BOOL isNew = FALSE);
	//ELLIPSE �����Լ�
	ELLipse* getEllipseDraw(BOOL isNew = FALSE);
	//FREELINE �����Լ�
	FreeLine* getFreeLineDraw(BOOL isNew = FALSE);

	FillDraw* getFillDraw(bool bNew = FALSE);
	//�۾������� ����� �����͸���Ʈ ��ȯ
	CPtrList& getObject();

	Bold bold;
	int index;
	UINT pen_type;
	BOOL Empty, RE_Empty, start;
	CString str;
	CFont font;
	CArray<TCHAR, TCHAR> m_str;
	BOOL Obj_select;

	style font_style;

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
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
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnDrawpoly();
	afx_msg void OnUpdateDrawpoly(CCmdUI *pCmdUI);
	afx_msg void OnTextbox();
	afx_msg void OnUpdateTextbox(CCmdUI *pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnSelectobject();
	afx_msg void OnUpdateSelectobject(CCmdUI *pCmdUI);
	afx_msg void OnFreeline();
	afx_msg void OnUpdateFreeline(CCmdUI *pCmdUI);
};
