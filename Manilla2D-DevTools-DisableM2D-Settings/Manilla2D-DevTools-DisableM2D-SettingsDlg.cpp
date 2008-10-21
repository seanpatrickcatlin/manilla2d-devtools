// Manilla2D-DevTools-DisableM2D-SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manilla2D-DevTools-DisableM2D-Settings.h"
#include "Manilla2D-DevTools-DisableM2D-SettingsDlg.h"
#include "Manilla2D-DevTools-DisableM2D-Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TITLE_HEADER_HEIGHT 24

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
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CManilla2DDevToolsDisableM2DSettingsDlg message handlers

BOOL CManilla2DDevToolsDisableM2DSettingsDlg::OnInitDialog()
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

void CManilla2DDevToolsDisableM2DSettingsDlg::OnOK()
{
    CDialog::OnOK();
}

void CManilla2DDevToolsDisableM2DSettingsDlg::OnCancel()
{
    CDialog::OnCancel();
}

void CManilla2DDevToolsDisableM2DSettingsDlg::OnPaint()
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
    dc.DrawText(TEXT("Today Screen Items"), CRect(8, 0, nWidth, TITLE_HEADER_HEIGHT), DT_VCENTER | DT_SINGLELINE);
    dc.SelectObject(pSave);

    // paint line
    CPen blackPen(PS_SOLID, 1, RGB(0,0,0));
    CPen *pOldPen = dc.SelectObject(&blackPen);

    dc.MoveTo(0, TITLE_HEADER_HEIGHT);
    dc.LineTo(nWidth, TITLE_HEADER_HEIGHT);

    dc.SelectObject(pOldPen);
}
