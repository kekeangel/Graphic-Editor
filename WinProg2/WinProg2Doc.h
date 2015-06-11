
// WinProg2Doc.h : CWinProg2Doc Ŭ������ �������̽�
//


#pragma once

enum Select{
	POLYLINE, TEXT, ELLIPSE, RECTANGLE, LINE, EMPTY
};

class CWinProg2Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CWinProg2Doc();
	DECLARE_DYNCREATE(CWinProg2Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	Select select;
	//RECTANGLE �����Լ�
	RectAngle* getRectDraw(BOOL isNew = FALSE);
	//ELLIPSE �����Լ�
	ELLipse* getEllipseDraw(BOOL isNew = FALSE);

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CWinProg2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColor();
	afx_msg void OnFont();
};
