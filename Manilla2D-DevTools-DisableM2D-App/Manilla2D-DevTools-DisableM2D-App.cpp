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


// Manilla2D-DevTools-DisableM2D-App.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Manilla2D-DevTools-DisableM2D-App.h"
#include "Manilla2D-DevTools-DisableM2D-Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManilla2DDevToolsDisableM2DAppApp

BEGIN_MESSAGE_MAP(CManilla2DDevToolsDisableM2DAppApp, CWinApp)
END_MESSAGE_MAP()


// CManilla2DDevToolsDisableM2DAppApp construction
CManilla2DDevToolsDisableM2DAppApp::CManilla2DDevToolsDisableM2DAppApp()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CManilla2DDevToolsDisableM2DAppApp object
CManilla2DDevToolsDisableM2DAppApp theApp;

// CManilla2DDevToolsDisableM2DAppApp initialization

BOOL CManilla2DDevToolsDisableM2DAppApp::InitInstance()
{
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Windows Mobile specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    DisableM2D();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
