
// Connect6.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CConnect6App:
// �� Ŭ������ ������ ���ؼ��� Connect6.cpp�� �����Ͻʽÿ�.
//

class CConnect6App : public CWinApp
{
public:
	CConnect6App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CConnect6App theApp;