#pragma once


// StringDlg 대화 상자입니다.

class StringDlg : public CDialog
{
	DECLARE_DYNAMIC(StringDlg)

public:
	StringDlg(CString& str, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~StringDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STRINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	// 문자열 입력변수
	CString& m_str;
};
