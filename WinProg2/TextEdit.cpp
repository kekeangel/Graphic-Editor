// TextEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WinProg2.h"
#include "TextEdit.h"
#include "afxdialogex.h"
#include "WinProg2Doc.h"
#include "MainFrm.h"


// TextEdit 대화 상자입니다.

IMPLEMENT_DYNAMIC(TextEdit, CDialog)

TextEdit::TextEdit(CString& str, CWnd* pParent /*=NULL*/)
	: m_string(str)
	,CDialog(TextEdit::IDD, pParent)

{

}

TextEdit::~TextEdit()
{
}

void TextEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_string);
}


BEGIN_MESSAGE_MAP(TextEdit, CDialog)
	ON_BN_CLICKED(IDC_PROPERTY, &TextEdit::OnBnClickedProperty)
END_MESSAGE_MAP()


// TextEdit 메시지 처리기입니다.

void TextEdit::OnBnClickedProperty()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		dlg.GetCurrentFont(&pDoc->font_style.lf);
	}
}
