
// ReadPcr.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CReadPcrApp:
// �� Ŭ������ ������ ���ؼ��� ReadPcr.cpp�� �����Ͻʽÿ�.
//

class CReadPcrApp : public CWinApp
{
public:
	CReadPcrApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CReadPcrApp theApp;