/*
    This file is part of Manilla2D-DevTools.

    Manilla2D-DevTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Manilla2DCustomizer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Manilla2DCustomizer.  If not, see <http://www.gnu.org/licenses/>.
*/


// Manilla2D-DevTools-DisableM2D-Settings.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Manilla2D-DevTools-DisableM2D-Settings.h"
#include "Manilla2D-DevTools-DisableM2D-SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManilla2DDevToolsDisableM2DSettingsApp

BEGIN_MESSAGE_MAP(CManilla2DDevToolsDisableM2DSettingsApp, CWinApp)
END_MESSAGE_MAP()


// CManilla2DDevToolsDisableM2DSettingsApp construction
CManilla2DDevToolsDisableM2DSettingsApp::CManilla2DDevToolsDisableM2DSettingsApp()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CManilla2DDevToolsDisableM2DSettingsApp object
CManilla2DDevToolsDisableM2DSettingsApp theApp;

// CManilla2DDevToolsDisableM2DSettingsApp initialization

BOOL CManilla2DDevToolsDisableM2DSettingsApp::InitInstance()
{
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Windows Mobile specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CManilla2DDevToolsDisableM2DSettingsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
