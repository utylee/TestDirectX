
// TestDirectX.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTestDirectXApp:
// �� Ŭ������ ������ ���ؼ��� TestDirectX.cpp�� �����Ͻʽÿ�.
//

class CTestDirectXApp : public CWinApp
{
public:
	CTestDirectXApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestDirectXApp theApp;