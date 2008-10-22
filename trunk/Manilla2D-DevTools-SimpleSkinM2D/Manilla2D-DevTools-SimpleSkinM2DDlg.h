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


// Manilla2D-DevTools-SimpleSkinM2DDlg.h : header file
//

#pragma once

// CManilla2DDevToolsSimpleSkinM2DDlg dialog
class CManilla2DDevToolsSimpleSkinM2DDlg : public CDialog
{
// Construction
public:
	CManilla2DDevToolsSimpleSkinM2DDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_M2D_DEVTOOLS_SIMPLESKIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

    void OnPaint();
    void OnOK();
    void OnCancel();

private:
    CCommandBar m_cmdBar;
};
