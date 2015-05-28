
// WinProg2Doc.cpp : CWinProg2Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "WinProg2.h"
#endif

#include "WinProg2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinProg2Doc

IMPLEMENT_DYNCREATE(CWinProg2Doc, CDocument)

BEGIN_MESSAGE_MAP(CWinProg2Doc, CDocument)
	ON_COMMAND(ID_Color, &CWinProg2Doc::OnColor)
	ON_COMMAND(ID_Font, &CWinProg2Doc::OnFont)
	ON_COMMAND(ID_Bold_1, &CWinProg2Doc::OnBold1)
	ON_COMMAND(ID_Bold_2, &CWinProg2Doc::OnBold2)
	ON_COMMAND(ID_Bold_3, &CWinProg2Doc::OnBold3)
	ON_COMMAND(ID_Bold_4, &CWinProg2Doc::OnBold4)
	ON_COMMAND(ID_Bold_5, &CWinProg2Doc::OnBold5)
	ON_COMMAND(ID_Bold_6, &CWinProg2Doc::OnBold6)
	ON_UPDATE_COMMAND_UI(ID_Bold_1, &CWinProg2Doc::OnUpdateBold1)
	ON_UPDATE_COMMAND_UI(ID_Bold_2, &CWinProg2Doc::OnUpdateBold2)
	ON_UPDATE_COMMAND_UI(ID_Bold_3, &CWinProg2Doc::OnUpdateBold3)
	ON_UPDATE_COMMAND_UI(ID_Bold_4, &CWinProg2Doc::OnUpdateBold4)
	ON_UPDATE_COMMAND_UI(ID_Bold_5, &CWinProg2Doc::OnUpdateBold5)
	ON_UPDATE_COMMAND_UI(ID_Bold_6, &CWinProg2Doc::OnUpdateBold6)
END_MESSAGE_MAP()


// CWinProg2Doc ����/�Ҹ�

CWinProg2Doc::CWinProg2Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	select = EMPTY;
	color = RGB(0, 0, 0);
	bold = ONE;
}

CWinProg2Doc::~CWinProg2Doc()
{
}

BOOL CWinProg2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CWinProg2Doc serialization

void CWinProg2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CWinProg2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CWinProg2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWinProg2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWinProg2Doc ����

#ifdef _DEBUG
void CWinProg2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinProg2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinProg2Doc ���


void CWinProg2Doc::OnColor()
{
	CColorDialog dlg(RGB(255,0,0),CC_FULLOPEN);
	dlg.DoModal();
	color = dlg.GetColor();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnFont()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		COLORREF color = dlg.GetColor();

		LOGFONT lf;
		dlg.GetCurrentFont(&lf);
	}
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

PolyLine* CWinProg2Doc::getPolyLineDraw(BOOL isNew){

	if (isNew){
		m_Cur = new PolyLine();
		m_Object.AddTail(m_Cur);

		return (PolyLine*)m_Cur;
	}

	if (m_Cur != NULL && select == POLYLINE) {
		return (PolyLine*)m_Cur;
	}
	return NULL;
}

CPtrList& CWinProg2Doc::getObject() {
	return m_Object;
}

void CWinProg2Doc::OnBold1()
{
	bold = ONE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnBold2()
{
	bold = TWO;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnBold3()
{
	bold = THREE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnBold4()
{
	bold = FOUR;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnBold5()
{
	bold = FIVE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnBold6()
{
	bold = SIX;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateBold1(CCmdUI *pCmdUI)
{
	if (bold == ONE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateBold2(CCmdUI *pCmdUI)
{
	if (bold == TWO){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateBold3(CCmdUI *pCmdUI)
{
	if (bold == THREE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateBold4(CCmdUI *pCmdUI)
{
	if (bold == FOUR){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateBold5(CCmdUI *pCmdUI)
{
	if (bold == FIVE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CWinProg2Doc::OnUpdateBold6(CCmdUI *pCmdUI)
{
	if (bold == SIX){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}
