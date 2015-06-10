// TextEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WinProg2.h"
#include "TextEdit.h"
#include "afxdialogex.h"
#include "WinProg2Doc.h"
#include "MainFrm.h"


// TextEdit ��ȭ �����Դϴ�.

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


// TextEdit �޽��� ó�����Դϴ�.

void TextEdit::OnBnClickedProperty()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		dlg.GetCurrentFont(&pDoc->font_style.lf);
	}
}
