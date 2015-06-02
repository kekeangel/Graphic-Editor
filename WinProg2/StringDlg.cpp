// StringDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WinProg2.h"
#include "StringDlg.h"
#include "afxdialogex.h"


// StringDlg 대화 상자입니다.

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


// StringDlg 메시지 처리기입니다.
