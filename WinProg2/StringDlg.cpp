// StringDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WinProg2.h"
#include "StringDlg.h"
#include "afxdialogex.h"


// StringDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(StringDlg, CDialog)

StringDlg::StringDlg(CString& str, CWnd* pParent/* = NULL*/)
	: CDialog(StringDlg::IDD, pParent),
	m_str(str)
{

}

StringDlg::~StringDlg()
{
}

void StringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(StringDlg, CDialog)
END_MESSAGE_MAP()


// StringDlg �޽��� ó�����Դϴ�.
