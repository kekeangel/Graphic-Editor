
// WinProg2Doc.h : CWinProg2Doc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CWinProg2Doc();
	DECLARE_DYNCREATE(CWinProg2Doc)

// 특성입니다.
public:
	Object_Draw* m_Cur;
	CPtrList m_Object;

// 작업입니다.
public:
	Select select;
	COLORREF color;
	//LINE, POLYLINE 생성함수
	PolyLine* getPolyLineDraw(BOOL isNew = FALSE);
	//RECTANGLE 생성함수
	RectAngle* getRectDraw(BOOL isNew = FALSE);
	//TEXTBOX 생성함수
	TextBox* getTextBoxDraw(BOOL isNew = FALSE);

	Bold bold;
	int index, fontsize=10;
	UINT pen_type;
	BOOL Empty, RE_Empty;
	CString str;
	CFont font;
	LOGFONT lf;

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	CPtrList& getObject();

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CWinProg2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
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
