
// WinProg2.h : WinProg2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CWinProg2App:
// �� Ŭ������ ������ ���ؼ��� WinProg2.cpp�� �����Ͻʽÿ�.
//

class CWinProg2App : public CWinAppEx
{
public:
	CWinProg2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
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
