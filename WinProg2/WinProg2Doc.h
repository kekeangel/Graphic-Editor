
// WinProg2Doc.h : CWinProg2Doc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CWinProg2Doc();
	DECLARE_DYNCREATE(CWinProg2Doc)

// 특성입니다.
public:
	Object_Draw* m_Cur;
	CPtrList m_Object;
	CList<Select, Select> m_select;

// 작업입니다.
public:
	Select select, tmp_select;
	COLORREF color;
	//LINE, POLYLINE 생성함수
	PolyLine* getPolyLineDraw(BOOL isNew = FALSE);
	//RECTANGLE 생성함수
	RectAngle* getRectDraw(BOOL isNew = FALSE);
	//TEXTBOX 생성함수
	TextBox* getTextBoxDraw(BOOL isNew = FALSE);
	//ELLIPSE 생성함수
	ELLipse* getEllipseDraw(BOOL isNew = FALSE);
	//FREELINE 생성함수
	FreeLine* getFreeLineDraw(BOOL isNew = FALSE);

	FillDraw* getFillDraw(bool bNew = FALSE);
	//작업정보가 저장된 포인터리스트 반환
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

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
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
