
// MainProgram.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMainProgramApp:
// �� Ŭ������ ������ ���ؼ��� MainProgram.cpp�� �����Ͻʽÿ�.
//

class CMainProgramApp : public CWinApp
{
public:
	CMainProgramApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMainProgramApp theApp;