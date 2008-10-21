// Manilla2D-DevTools-DisableM2D-Settings.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

// CManilla2DDevToolsDisableM2DSettingsApp:
// See Manilla2D-DevTools-DisableM2D-Settings.cpp for the implementation of this class
//

class CManilla2DDevToolsDisableM2DSettingsApp : public CWinApp
{
public:
	CManilla2DDevToolsDisableM2DSettingsApp();
	
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CManilla2DDevToolsDisableM2DSettingsApp theApp;
