
// MIPL.h : main header file for the MIPL application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMIPLApp:
// See MIPL.cpp for the implementation of this class
//

class CMIPLApp : public CWinApp
{
public:
	CMIPLApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMIPLApp theApp;
