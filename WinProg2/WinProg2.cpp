
// WinProg2.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_Bold_1, &CWinProg2App::OnBold1)
	ON_UPDATE_COMMAND_UI(ID_Bold_1, &CWinProg2App::OnUpdateBold1)
	ON_COMMAND(ID_Bold_2, &CWinProg2App::OnBold2)
	ON_UPDATE_COMMAND_UI(ID_Bold_2, &CWinProg2App::OnUpdateBold2)
	ON_COMMAND(ID_Bold_3, &CWinProg2App::OnBold3)
	ON_UPDATE_COMMAND_UI(ID_Bold_3, &CWinProg2App::OnUpdateBold3)
	ON_COMMAND(ID_Bold_4, &CWinProg2App::OnBold4)
	ON_UPDATE_COMMAND_UI(ID_Bold_4, &CWinProg2App::OnUpdateBold4)
	ON_COMMAND(ID_Bold_5, &CWinProg2App::OnBold5)
	ON_UPDATE_COMMAND_UI(ID_Bold_5, &CWinProg2App::OnUpdateBold5)
	ON_COMMAND(ID_Bold_6, &CWinProg2App::OnBold6)
	ON_UPDATE_COMMAND_UI(ID_Bold_6, &CWinProg2App::OnUpdateBold6)
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
END_MESSAGE_MAP()


// CWinProg2App 생성

CWinProg2App::CWinProg2App()
{
	m_bHiColorIcons = TRUE;

	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 응용 프로그램을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("WinProg2.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CWinProg2App 개체입니다.

CWinProg2App theApp;


// CWinProg2App 초기화

BOOL CWinProg2App::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면  AfxInitRichEdit2()가 있어야 합니다.	
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_WinProg2TYPE,
		RUNTIME_CLASS(CWinProg2Doc),
		RUNTIME_CLASS(CChildFrame), // 사용자 지정 MDI 자식 프레임입니다.
		RUNTIME_CLASS(CWinProg2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 주 MDI 프레임 창을 만듭니다.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 주 창이 초기화되었으므로 이를 표시하고 업데이트합니다.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CWinProg2App::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	return CWinAppEx::ExitInstance();
}

// CWinProg2App 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CWinProg2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CWinProg2App 사용자 지정 로드/저장 메서드

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

// CWinProg2App 메시지 처리기

//선굵기1
void CWinProg2App::OnBold1()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->bold = ONE;
}

//선굵기1 체크여부
void CWinProg2App::OnUpdateBold1(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->bold == ONE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//선굵기2
void CWinProg2App::OnBold2()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	pDoc->bold = TWO;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//선굵기2 체크여부
void CWinProg2App::OnUpdateBold2(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->bold == TWO){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//선굵기3
void CWinProg2App::OnBold3()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	pDoc->bold = THREE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//선굵기3 체크여부
void CWinProg2App::OnUpdateBold3(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->bold == THREE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//선굵기4
void CWinProg2App::OnBold4()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	pDoc->bold = FOUR;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//선굵기4 체크여부
void CWinProg2App::OnUpdateBold4(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->bold == FOUR){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);

}

//선굵기5
void CWinProg2App::OnBold5()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	pDoc->bold = FIVE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//선굵기5 체크여부
void CWinProg2App::OnUpdateBold5(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->bold == FIVE){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//선굵기6
void CWinProg2App::OnBold6()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	pDoc->bold = SIX;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//선굵기6 체크여부
void CWinProg2App::OnUpdateBold6(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();

	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->bold == SIX){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//실선 설정메뉴
void CWinProg2App::OnPsSolid()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	pDoc->pen_type = PS_SOLID;
}

//실선 체크여부
void CWinProg2App::OnUpdatePsSolid(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (pDoc->pen_type == PS_SOLID){
		pCmdUI->SetCheck(1);
	}
	else
		pCmdUI->SetCheck(0);
}

//파선 설정메뉴
void CWinProg2App::OnPsDash()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	pDoc->pen_type = PS_DASH;
}

//파선 체크여부
void CWinProg2App::OnUpdatePsDash(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (pDoc->pen_type == PS_DASH)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//점선 설정메뉴
void CWinProg2App::OnPsDot()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	pDoc->pen_type = PS_DOT;
}

//점선 체크여부
void CWinProg2App::OnUpdatePsDot(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (pDoc->pen_type == PS_DOT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

//일점쇄선 설정메뉴
void CWinProg2App::OnPsDashdot()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	pDoc->pen_type = PS_DASHDOT;

}

//일점쇄선 체크여부
void CWinProg2App::OnUpdatePsDashdot(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (pDoc->pen_type == PS_DASHDOT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


void CWinProg2App::OnPsDashdotdot()
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	pDoc->pen_type = PS_DASHDOTDOT;
}


void CWinProg2App::OnUpdatePsDashdotdot(CCmdUI *pCmdUI)
{
	CWinProg2Doc* pDoc = (CWinProg2Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (pDoc->pen_type == PS_DASHDOTDOT)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
