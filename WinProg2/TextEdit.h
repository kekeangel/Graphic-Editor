#pragma once


// TextEdit ��ȭ �����Դϴ�.

class TextEdit : public CDialog
{
	DECLARE_DYNAMIC(TextEdit)

public:
	TextEdit(CString& str, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TextEdit();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEXTEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedProperty();
	CString& m_string;
};
