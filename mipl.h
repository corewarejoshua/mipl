
// mipl.h : mipl ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CmiplApp:
// �� Ŭ������ ������ ���ؼ��� mipl.cpp�� �����Ͻʽÿ�.
//

class CmiplApp : public CWinApp
{
public:
	CmiplApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CmiplApp theApp;
