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


// Manilla2D-DevTools-DisableM2D-App.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

// CManilla2DDevToolsDisableM2DAppApp:
// See Manilla2D-DevTools-DisableM2D-App.cpp for the implementation of this class
//

class CManilla2DDevToolsDisableM2DAppApp : public CWinApp
{
public:
	CManilla2DDevToolsDisableM2DAppApp();
	
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CManilla2DDevToolsDisableM2DAppApp theApp;
