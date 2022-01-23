
// Renderer.h : main header file for the Renderer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRendererApp:
// See Renderer.cpp for the implementation of this class
//

class CRendererApp : public CWinApp
{
public:
	CRendererApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRendererApp theApp;
