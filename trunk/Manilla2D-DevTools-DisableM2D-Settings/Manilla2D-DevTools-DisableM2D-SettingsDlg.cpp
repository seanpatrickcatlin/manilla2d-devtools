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
    DDX_Control(pDX, IDC_TODAY_ITEMS_LIST, m_todayItemsListCtrl);
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

    m_todayItemsListCtrl.SetExtendedStyle(m_todayItemsListCtrl.GetExtendedStyle()|LVS_EX_CHECKBOXES);

    InitializeListControl();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CManilla2DDevToolsDisableM2DSettingsDlg::OnOK()
{
    int itemCount = m_todayItemsListCtrl.GetItemCount();

    TodayScreenSettings listControlSettings;

    listControlSettings.itemVector.clear();

    for(int i=0; i<itemCount; i++)
    {
        BOOL currentCheckState = m_todayItemsListCtrl.GetCheck(i);
        CString currentString = m_todayItemsListCtrl.GetItemText(i, 0);

        if(currentString.CompareNoCase(TEXT("Date")) == 0)
        {
            listControlSettings.dateEnabled = currentCheckState;
        }
        else
        {
            NameAndEnabledStateItem itemSetting;

            itemSetting.name = currentString;
            itemSetting.enabled = currentCheckState;

            listControlSettings.itemVector.push_back(itemSetting);
        }
    }

    WriteTodayScreenSettingsToXml(&listControlSettings);

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

void CManilla2DDevToolsDisableM2DSettingsDlg::InitializeListControl()
{
    // get teh registry settings
    TodayScreenSettings regSettings;
    ReadTodayScreenSettingsFromRegistry(&regSettings);

    // get any settings form the xml
    TodayScreenSettings xmlSettings = regSettings;
    ReadTodayScreenSettingsFromXml(&xmlSettings);

    // apply the xml settings to the reg settings
    regSettings.dateEnabled = xmlSettings.dateEnabled;

    for(size_t i=0; i<regSettings.itemVector.size(); i++)
    {
        NameAndEnabledStateItem* pRegItem = &regSettings.itemVector[i];

        for(size_t j=0; j<xmlSettings.itemVector.size(); j++)
        {
            NameAndEnabledStateItem xmlItem = xmlSettings.itemVector[j];

            if(pRegItem->name.Compare(xmlItem.name) == 0)
            {
                pRegItem->enabled = xmlItem.enabled;
                break;
            }
        }
    }

    // populate the list control with the reg settings
    m_todayItemsListCtrl.DeleteAllItems();

    CHeaderCtrl* pListHeaderCtrl = m_todayItemsListCtrl.GetHeaderCtrl();

    if(pListHeaderCtrl != NULL)
    {
        int headerItemCount = pListHeaderCtrl->GetItemCount();

        if(headerItemCount != 1)
        {
            // remove all items
            for(int i=headerItemCount; i > 0; i--)
            {
                pListHeaderCtrl->DeleteItem(i);
            }

            CRect lcRect;
            m_todayItemsListCtrl.GetClientRect(&lcRect);
            m_todayItemsListCtrl.InsertColumn(0, _T("Item Name"), LVCFMT_LEFT, lcRect.Width());
        }
    }

    for(size_t i=0; i<regSettings.itemVector.size(); i++)
    {
        LPCTSTR pItemStr(regSettings.itemVector[i].name);

        m_todayItemsListCtrl.InsertItem(i, pItemStr);
        
        m_todayItemsListCtrl.SetCheck(i, regSettings.itemVector[i].enabled);
    }

    LPCTSTR pDateStr(TEXT("Date"));
    m_todayItemsListCtrl.InsertItem(0, pDateStr);
    m_todayItemsListCtrl.SetCheck(0, regSettings.dateEnabled);

    m_todayItemsListCtrl.SetFocus();
}
