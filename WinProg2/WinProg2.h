
// WinProg2.h : WinProg2 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CWinProg2App:
// 이 클래스의 구현에 대해서는 WinProg2.cpp을 참조하십시오.
//

class CWinProg2App : public CWinAppEx
{
public:
	CWinProg2App();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBold1();
	afx_msg void OnUpdateBold1(CCmdUI *pCmdUI);
	afx_msg void OnBold2();
	afx_msg void OnUpdateBold2(CCmdUI *pCmdUI);
	afx_msg void OnBold3();
	afx_msg void OnUpdateBold3(CCmdUI *pCmdUI);
	afx_msg void OnBold4();
	afx_msg void OnUpdateBold4(CCmdUI *pCmdUI);
	afx_msg void OnBold5();
	afx_msg void OnUpdateBold5(CCmdUI *pCmdUI);
	afx_msg void OnBold6();
	afx_msg void OnUpdateBold6(CCmdUI *pCmdUI);
	afx_msg void OnPsSolid();
	afx_msg void OnUpdatePsSolid(CCmdUI *pCmdUI);
	afx_msg void OnPsDash();
	afx_msg void OnUpdatePsDash(CCmdUI *pCmdUI);
	afx_msg void OnPsDot();
	afx_msg void OnUpdatePsDot(CCmdUI *pCmdUI);
	afx_msg void OnPsDashdot();
	afx_msg void OnUpdatePsDashdot(CCmdUI *pCmdUI);
	afx_msg void OnPsDashdotdot();
	afx_msg void OnUpdatePsDashdotdot(CCmdUI *pCmdUI);
};

extern CWinProg2App theApp;
