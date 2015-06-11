
// WinProg2.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "WinProg2.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "WinProg2Doc.h"
#include "WinProg2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinProg2App

BEGIN_MESSAGE_MAP(CWinProg2App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CWinProg2App::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_Color, &CWinProg2App::OnColor)
	ON_COMMAND(ID_Font, &CWinProg2App::OnFont)
	ON_COMMAND(ID_PS_SOLID, &CWinProg2App::OnPsSolid)
	ON_UPDATE_COMMAND_UI(ID_PS_SOLID, &CWinProg2App::OnUpdatePsSolid)
	ON_COMMAND(ID_PS_DASH, &CWinProg2App::OnPsDash)
	ON_UPDATE_COMMAND_UI(ID_PS_DASH, &CWinProg2App::OnUpdatePsDash)
	ON_COMMAND(ID_PS_DOT, &CWinProg2App::OnPsDot)
	ON_UPDATE_COMMAND_UI(ID_PS_DOT, &CWinProg2App::OnUpdatePsDot)
	ON_COMMAND(ID_PS_DASHDOT, &CWinProg2App::OnPsDashdot)
	ON_UPDATE_COMMAND_UI(ID_PS_DASHDOT, &CWinProg2App::OnUpdatePsDashdot)
	ON_COMMAND(ID_PS_DASHDOTDOT, &CWinProg2App::OnPsDashdotdot)
	ON_UPDATE_COMMAND_UI(ID_PS_DASHDOTDOT, &CWinProg2App::OnUpdatePsDashdotdot)
	ON_COMMAND(ID_Bold1, &CWinProg2App::OnBold1)
	ON_UPDATE_COMMAND_UI(ID_Bold1, &CWinProg2App::OnUpdateBold1)
	ON_COMMAND(ID_Bold2, &CWinProg2App::OnBold2)
	ON_UPDATE_COMMAND_UI(ID_Bold2, &CWinProg2App::OnUpdateBold2)
	ON_COMMAND(ID_Bold3, &CWinProg2App::OnBold3)
	ON_UPDATE_COMMAND_UI(ID_Bold3, &CWinProg2App::OnUpdateBold3)
	ON_COMMAND(ID_Bold4, &CWinProg2App::OnBold4)
	ON_UPDATE_COMMAND_UI(ID_Bold4, &CWinProg2App::OnUpdateBold4)
	ON_COMMAND(ID_Bold5, &CWinProg2App::OnBold5)
	ON_UPDATE_COMMAND_UI(ID_Bold5, &CWinProg2App::OnUpdateBold5)
	ON_COMMAND(ID_Bold6, &CWinProg2App::OnBold6)
	ON_UPDATE_COMMAND_UI(ID_Bold6, &CWinProg2App::OnUpdateBold6)
	ON_COMMAND(ID_FillColor, &CWinProg2App::OnFillcolor)
	ON_COMMAND(ID_HS_BDIAGONAL, &CWinProg2App::OnHsBdiagonal)
	ON_COMMAND(ID_CROSS, &CWinProg2App::OnCross)
	ON_COMMAND(ID_DIAGCROSS, &CWinProg2App::OnDiagcross)
	ON_COMMAND(ID_FDIAGONAL, &CWinProg2App::OnFdiagonal)
	ON_COMMAND(ID_HORIZONTAL, &CWinProg2App::OnHorizontal)
	ON_COMMAND(ID_VERTICAL, &CWinProg2App::OnVertical)
END_MESSAGE_MAP()


// CWinProg2App ����

CWinProg2App::CWinProg2App()
{
	m_bHiColorIcons = TRUE;

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("WinProg2.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CWinProg2App ��ü�Դϴ�.

CWinProg2App theApp;


// CWinProg2App �ʱ�ȭ

BOOL CWinProg2App::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	EnableTaskbarInteraction();

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_WinProg2TYPE,
		RUNTIME_CLASS(CWinProg2Doc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CWinProg2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	// ��� ���⿡ ���� ���⸦ Ȱ��ȭ�մϴ�.
	m_pMainWnd->DragAcceptFiles();

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE Execute ���⸦ Ȱ��ȭ�մϴ�.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CWinProg2App::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	return CWinAppEx::ExitInstance();
}

// CWinProg2App �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CWinProg2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CWinProg2App ����� ���� �ε�/���� �޼���

void CWinProg2App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CWinProg2App::LoadCustomState()
{
}

void CWinProg2App::SaveCustomState()
{
}

// CWinProg2App �޽��� ó����

//���� �� ���� �޼��� �ڵ鷯 �� ����

//���������޴�
void CWinProg2App::OnColor()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CColorDialog dlg(RGB(0, 0, 0), CC_FULLOPEN);
	CPoint point;
	dlg.DoModal();

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	if (pDoc->select == SELECT){
		pView->cmd = LINECOLOR;
		pDoc->color = dlg.GetColor();

		pView->select_DrawObj(point);
	}
	else{
		pDoc->color = dlg.GetColor();
	}
}

//�۲ü����޴�
void CWinProg2App::OnFont()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CFontDialog dlg;
	if (dlg.DoModal() == IDOK){
		pDoc->font_style.fontsize = dlg.GetSize();
		pDoc->font_style.font_color = dlg.GetColor();
		dlg.GetCurrentFont(&pDoc->font_style.lf);
		pDoc->font_style.isBold = dlg.IsBold();
		pDoc->font_style.isItalic = dlg.IsItalic();
		pDoc->font_style.isStrikeout = dlg.IsStrikeOut();
		pDoc->font_style.isUnderline = dlg.IsUnderline();
		
	}
}

//�Ǽ� �����޴�
void CWinProg2App::OnPsSolid()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->pen_type = PS_SOLID;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//�Ǽ� üũ���� ����
void CWinProg2App::OnUpdatePsSolid(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->pen_type == PS_SOLID)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//�ļ� �����޴�
void CWinProg2App::OnPsDash()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->pen_type = PS_DASH;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//�ļ� üũ���� ����
void CWinProg2App::OnUpdatePsDash(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	if (pDoc->pen_type == PS_DASH)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//���� �����޴�
void CWinProg2App::OnPsDot()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->pen_type = PS_DOT;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//���� üũ���� ����
void CWinProg2App::OnUpdatePsDot(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	if (pDoc->pen_type == PS_DOT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//�����⼱ �����޴�
void CWinProg2App::OnPsDashdot()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->pen_type = PS_DASHDOT;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//�����⼱ üũ���� ����
void CWinProg2App::OnUpdatePsDashdot(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->pen_type == PS_DASHDOT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//�����⼱ �����޴�
void CWinProg2App::OnPsDashdotdot()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->pen_type = PS_DASHDOTDOT;


	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//�����⼱ üũ���� ����
void CWinProg2App::OnUpdatePsDashdotdot(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	if (pDoc->pen_type == PS_DASHDOTDOT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//���� �� ���� �޼��� �ڵ鷯 �� ����

//������1
void CWinProg2App::OnBold1()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->bold = ONE;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//������1 üũ����
void CWinProg2App::OnUpdateBold1(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->bold == ONE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//������2
void CWinProg2App::OnBold2()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);
	pDoc->bold = TWO;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//������2 üũ����
void CWinProg2App::OnUpdateBold2(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->bold == TWO){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//������3
void CWinProg2App::OnBold3()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);
	pDoc->bold = THREE;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//������3 üũ����
void CWinProg2App::OnUpdateBold3(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->bold == THREE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//������4
void CWinProg2App::OnBold4()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);	pDoc->bold = FOUR;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}

}

//������4 üũ����
void CWinProg2App::OnUpdateBold4(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->bold == FOUR){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);

}

//������5
void CWinProg2App::OnBold5()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);
	pDoc->bold = FIVE;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}

}

//������5 üũ����
void CWinProg2App::OnUpdateBold5(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->bold == FIVE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//������6
void CWinProg2App::OnBold6()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);
	pDoc->bold = SIX;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = SETBOLD;

		pView->select_DrawObj(point);
	}
	else{

	}
}

//������6 üũ����
void CWinProg2App::OnUpdateBold6(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (pDoc->bold == SIX){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2App::OnFillcolor()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);
	CPoint point;
	dlg.DoModal();
	
	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = FILLCOLOR;
		pDoc->m_fill_color = dlg.GetColor();

		pView->select_DrawObj(point);
	}
	else{
		pDoc->m_fill_color = dlg.GetColor();
	}

}

//���� �귯������ ���� �޼��� �ڵ鷯
void CWinProg2App::OnHsBdiagonal()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->hatch_pattern = HS_BDIAGONAL;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = BRUSH;

		pView->select_DrawObj(point);
	}
	else{

	}
}


void CWinProg2App::OnCross()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->hatch_pattern = HS_CROSS;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = BRUSH;

		pView->select_DrawObj(point);
	}
	else{

	}
}


void CWinProg2App::OnDiagcross()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->hatch_pattern = HS_DIAGCROSS;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = BRUSH;

		pView->select_DrawObj(point);
	}
	else{

	}
}


void CWinProg2App::OnFdiagonal()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->hatch_pattern = HS_FDIAGONAL;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = BRUSH;

		pView->select_DrawObj(point);
	}
	else{

	}
}


void CWinProg2App::OnHorizontal()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->hatch_pattern = HS_HORIZONTAL;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = BRUSH;

		pView->select_DrawObj(point);
	}
	else{

	}
}


void CWinProg2App::OnVertical()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	CWinProg2View* pView = (CWinProg2View*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CPoint point;

	::GetCursorPos(&point);
	pView->ScreenToClient(&point);

	pDoc->hatch_pattern = HS_VERTICAL;

	if (pDoc->select == SELECT && pView->Writable == TRUE){
		pView->cmd = BRUSH;

		pView->select_DrawObj(point);
	}
	else{

	}
}
