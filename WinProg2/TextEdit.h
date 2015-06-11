#pragma once


// TextEdit 대화 상자입니다.

class TextEdit : public CDialog
{
	DECLARE_DYNAMIC(TextEdit)

public:
	TextEdit(CString& str, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TextEdit();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEXTEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedProperty();
	CString& m_string;
};
