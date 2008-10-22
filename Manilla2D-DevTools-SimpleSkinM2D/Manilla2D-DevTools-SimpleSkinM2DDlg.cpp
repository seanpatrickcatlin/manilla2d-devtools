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


// Manilla2D-DevTools-SimpleSkinM2DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manilla2D-DevTools-SimpleSkinM2D.h"
#include "Manilla2D-DevTools-SimpleSkinM2DDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TITLE_HEADER_HEIGHT 24

// CManilla2DDevToolsSimpleSkinM2DDlg dialog

CManilla2DDevToolsSimpleSkinM2DDlg::CManilla2DDevToolsSimpleSkinM2DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManilla2DDevToolsSimpleSkinM2DDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManilla2DDevToolsSimpleSkinM2DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManilla2DDevToolsSimpleSkinM2DDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CManilla2DDevToolsSimpleSkinM2DDlg message handlers

BOOL CManilla2DDevToolsSimpleSkinM2DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    m_cmdBar.Create(this);
    m_cmdBar.InsertMenuBar(IDR_APPLY_CANCEL_MENU);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CManilla2DDevToolsSimpleSkinM2DDlg::OnOK()
{
    CDialog::OnOK();
}

void CManilla2DDevToolsSimpleSkinM2DDlg::OnCancel()
{
    CDialog::OnCancel();
}

void CManilla2DDevToolsSimpleSkinM2DDlg::OnPaint()
{
    CPaintDC dc(this);

    int nWidth = dc.GetDeviceCaps(HORZRES);

    // paint title
    CFont *pCurrentFont = dc.GetCurrentFont();
    LOGFONT lf;
    pCurrentFont->GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;

    CFont newFont;
    newFont.CreateFontIndirect(&lf);
    CFont *pSave = dc.SelectObject(&newFont);
    dc.SetTextColor(RGB(0, 0, 156));
    dc.DrawText(TEXT("Manilla 2D Simple Skinner"), CRect(8, 0, nWidth, TITLE_HEADER_HEIGHT), DT_VCENTER | DT_SINGLELINE);
    dc.SelectObject(pSave);

    // paint line
    CPen blackPen(PS_SOLID, 1, RGB(0,0,0));
    CPen *pOldPen = dc.SelectObject(&blackPen);

    dc.MoveTo(0, TITLE_HEADER_HEIGHT);
    dc.LineTo(nWidth, TITLE_HEADER_HEIGHT);

    dc.SelectObject(pOldPen);
}
