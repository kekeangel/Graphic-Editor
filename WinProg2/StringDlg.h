#pragma once


// StringDlg ��ȭ �����Դϴ�.

class StringDlg : public CDialog
{
	DECLARE_DYNAMIC(StringDlg)

public:
	StringDlg(CString& str, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~StringDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_STRINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	
	// ���ڿ� �Էº���
	CString& m_str;
};
