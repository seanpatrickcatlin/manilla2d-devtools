// Manilla2D-DevTools-DisableM2D-SettingsDlg.h : header file
//

#pragma once
#include "afxcmn.h"

// CManilla2DDevToolsDisableM2DSettingsDlg dialog
class CManilla2DDevToolsDisableM2DSettingsDlg : public CDialog
{
// Construction
public:
	CManilla2DDevToolsDisableM2DSettingsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_M2D_DEVTOOLS_SETTINGS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
    void OnPaint();
    void OnOK();
    void OnCancel();

	DECLARE_MESSAGE_MAP()

private:
    CCommandBar m_cmdBar;

    void InitializeListControl();

    CListCtrl m_todayItemsListCtrl;
};
