// Manilla2D-DevTools-DisableM2D-SettingsDlg.h : header file
//

#pragma once

// CManilla2DDevToolsDisableM2DSettingsDlg dialog
class CManilla2DDevToolsDisableM2DSettingsDlg : public CDialog
{
// Construction
public:
	CManilla2DDevToolsDisableM2DSettingsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MANILLA2DDEVTOOLSDISABLEM2DSETTINGS_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
};
