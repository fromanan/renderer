//
// Renderer.h : main header file for the Renderer application
//
#pragma once

#include "Resource.h"       // main symbols

// CRendererApp:
// See Renderer.cpp for the implementation of this class
//
class CRendererApp final : public CWinApp
{
public:
	CRendererApp() noexcept;

	#if _DEBUG
	int Run() override;
	#endif

// Overrides
public:
	BOOL InitInstance() override;
	int ExitInstance() override;

// Implementation
public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRendererApp Instance;
