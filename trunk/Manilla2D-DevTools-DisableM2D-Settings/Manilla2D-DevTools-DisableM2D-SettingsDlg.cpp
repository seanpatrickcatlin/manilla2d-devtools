// Manilla2D-DevTools-DisableM2D-SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manilla2D-DevTools-DisableM2D-Settings.h"
#include "Manilla2D-DevTools-DisableM2D-SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CManilla2DDevToolsDisableM2DSettingsDlg dialog

CManilla2DDevToolsDisableM2DSettingsDlg::CManilla2DDevToolsDisableM2DSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManilla2DDevToolsDisableM2DSettingsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManilla2DDevToolsDisableM2DSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManilla2DDevToolsDisableM2DSettingsDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CManilla2DDevToolsDisableM2DSettingsDlg message handlers

BOOL CManilla2DDevToolsDisableM2DSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CManilla2DDevToolsDisableM2DSettingsDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_MANILLA2DDEVTOOLSDISABLEM2DSETTINGS_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_MANILLA2DDEVTOOLSDISABLEM2DSETTINGS_DIALOG));
	}
}
#endif

