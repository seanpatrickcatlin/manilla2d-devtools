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

// Manilla2D-DevTools-EnableM2D.cpp : Defines the initialization routines for the DLL.
//

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <aygshell.h>
#include <todaycmn.h>
#include <DeviceResolutionAware.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PLUGIN_NAME "Manilla2D-DevTools-Enable"

#include "resource.h"

//global variables    
HICON               g_hIcon;
UINT                g_plugInHeight;
HINSTANCE           g_hInst;
HWND                g_hWnd;
BOOL                g_bFirstDisplay         = TRUE;


// forward function declarations
static INT InitializeClasses();

static void Call_Manilla2D_DevTools_EnableM2D_App();

/*************************************************************************/
/* Entry point for the dll                                                 */
/*************************************************************************/
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:            
        
        // The DLL is being loaded for the first time by a given process.
        // Perform per-process initialization here.  If the initialization
        // is successful, return TRUE; if unsuccessful, return FALSE.
        g_hInst = (HINSTANCE)hModule;

        //load the icon
        g_hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISPLAYICON), IMAGE_ICON, DRA::SCALEX(32), DRA::SCALEY(32) ,LR_DEFAULTCOLOR);
                
        //initilize the application class, and set the global window handle
        UnregisterClass(TEXT(PLUGIN_NAME), g_hInst);
        InitializeClasses();
        g_hWnd = 0;
        
        break;
        
    case DLL_PROCESS_DETACH:
        // The DLL is being unloaded by a given process.  Do any
        // per-process clean up here, such as undoing what was done in
        // DLL_PROCESS_ATTACH.    The return value is ignored.

        DestroyIcon(g_hIcon);
        
        UnregisterClass(TEXT(PLUGIN_NAME), g_hInst);
        g_hInst = NULL;
        break;           
    }
    
    return TRUE;
}

/*************************************************************************/
/* Handle any messages that may be needed for the plugin                 */
/* Handled messages:                                                     */
/*        WM_TODAYCUSTOM_QUERYREFRESHCACHE                                 */
/*        WM_CREATE                                                         */
/*        WM_LBUTTONUP                                                     */
/*        WM_PAINT                                                         */
/*        WM_DESTROY                                                         */
/*************************************************************************/
LRESULT CALLBACK WndProc (HWND hwnd, UINT uimessage, WPARAM wParam, LPARAM lParam) 
{
    switch (uimessage)
    {          
        //check to see if a refresh is required
    case WM_TODAYCUSTOM_QUERYREFRESHCACHE: 
        {   
            
            TODAYLISTITEM *ptliItem;
            INT iItemHeight;
            
            BOOL    bReturn = FALSE;
            
            // get the pointer to the item from the Today screen
            ptliItem = (TODAYLISTITEM*)wParam;

            if ((NULL == ptliItem) || (WaitForSingleObject(SHELL_API_READY_EVENT, 0) == WAIT_TIMEOUT))
            {
                return FALSE;
            }

            iItemHeight = DRA::SCALEY(36);

            if (0 == ptliItem->cyp)
            {
                ptliItem->cyp = iItemHeight;
                bReturn = TRUE;
            }


            return bReturn;
        }        
        
    case WM_CREATE:         
        break;
        
    case WM_LBUTTONUP: 
        Call_Manilla2D_DevTools_EnableM2D_App();
        break;          
        
    case WM_PAINT: 
        PAINTSTRUCT     ps;
        RECT            rcWindBounds; 
        RECT            rcMyBounds;
        HDC             hDC;
        HFONT            hFontOld;
        COLORREF        crText;

        GetWindowRect( hwnd, &rcWindBounds); 
        
        hDC = BeginPaint(hwnd, &ps);
        
        // create a custom rectangle relative to the client area
        rcMyBounds.left = 0;
        rcMyBounds.top = DRA::SCALEY(2);
        rcMyBounds.right = rcWindBounds.right - rcWindBounds.left;
        rcMyBounds.bottom = rcWindBounds.bottom - rcWindBounds.top;          
        
        // draw the icon on the screen
        SetBkMode(hDC, TRANSPARENT);
        DrawIcon(hDC, 2, 0, g_hIcon);
        
        BOOL bIsFarEast;
        LOGFONT lf;
        HFONT hSysFont;
        HFONT hFont;

        //determine if this is a Far East platform
        switch (PRIMARYLANGID(LANGIDFROMLCID(GetSystemDefaultLCID())))
        {
        case LANG_CHINESE:
        case LANG_KOREAN:
        case LANG_JAPANESE:
            bIsFarEast = TRUE;
            break;
            
        default:
            bIsFarEast = FALSE;
            break;
        }

        hSysFont = (HFONT) GetStockObject(SYSTEM_FONT);
        GetObject(hSysFont, sizeof(LOGFONT), &lf);
        // If it is far east, use a normal font at 9 points,
        //  otherwise use a bold font as 8 points
        if (bIsFarEast)
        {
            lf.lfWeight = FW_NORMAL;
            // Calculate the font size, making sure to round the result to the nearest integer
            lf.lfHeight = (long) -((9.0 * (double)GetDeviceCaps(hDC, LOGPIXELSY) / 72.0)+.5);
        }
        else
        {
            lf.lfWeight = FW_BOLD;
            // Calculate the font size, making sure to round the result to the nearest integer
            lf.lfHeight = (long) -((8.0 * (double)GetDeviceCaps(hDC, LOGPIXELSY) / 72.0)+.5);
        }

        // create the font
        hFont = CreateFontIndirect(&lf);
    
        // Select the system font into the device context
        hFontOld = (HFONT) SelectObject(hDC, hFont);

        // determine the theme's current text color
        //  this color will change when the user picks a new theme,
        //  so get it each time the display needs to be painted
        crText = SendMessage(GetParent(hwnd), TODAYM_GETCOLOR, (WPARAM) TODAYCOLOR_TEXT, NULL);

        // set that color
        SetTextColor(hDC, crText);

        rcMyBounds.left = rcMyBounds.left + DRA::SCALEX(35);
        DrawText(hDC, TEXT("*** Tap To Enable TouchFlo ***"), -1, &rcMyBounds, DT_LEFT);
        
        // Select the previous font back into the device context
        SelectObject(hDC, hFontOld);

        DeleteObject(hFont);

        EndPaint(hwnd, &ps);
        return 0;
        
    case WM_DESTROY :          
        return 0 ;
        
    // this fills in the background with the today screen image
    case WM_ERASEBKGND:
        TODAYDRAWWATERMARKINFO dwi;
        dwi.hdc = (HDC)wParam;
        GetClientRect(hwnd, &dwi.rc);
        
        dwi.hwnd = hwnd;
        SendMessage(GetParent(hwnd), TODAYM_DRAWWATERMARK, 0,(LPARAM)&dwi);
        return TRUE;
    }

    return DefWindowProc (hwnd, uimessage, wParam, lParam) ;
}


/*************************************************************************/
/* Create and register our window class for the today item                 */
/*************************************************************************/
INT InitializeClasses()
{
    WNDCLASS         wc; 
    memset(&wc, 0, sizeof(wc));
    
    wc.style         = 0;                   
    wc.lpfnWndProc     = (WNDPROC) WndProc;
    wc.hInstance     = g_hInst;
    wc.hIcon         = 0;
    wc.hCursor         = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = TEXT(PLUGIN_NAME);
    
    //register our window
    if(!RegisterClass(&wc))
    { 
        return 0 ;
    }
    return 1;
}

/*************************************************************************/
/* Initialize the DLL by creating a new window                             */
/*************************************************************************/
HWND InitializeCustomItem(TODAYLISTITEM *ptli, HWND hwndParent) 
{
    LPCTSTR appName = TEXT(PLUGIN_NAME);
    
    //create a new window
    g_hWnd = CreateWindow(appName,appName,WS_VISIBLE | WS_CHILD,
        CW_USEDEFAULT,CW_USEDEFAULT,240,0,hwndParent, NULL, g_hInst, NULL) ;
    
    // attach our winproc to the newly created window
    SetWindowLong(g_hWnd, GWL_WNDPROC, (LONG) WndProc);
    
    //display the window
    ShowWindow (g_hWnd, SW_SHOWNORMAL);
    UpdateWindow (g_hWnd) ;  
    
    return g_hWnd;
}

static void Call_Manilla2D_DevTools_EnableM2D_App()
{
    TCHAR binaryPath[MAX_PATH];
    if(GetModuleFileName(g_hInst, binaryPath, MAX_PATH) > 0)
    {
        // reverse search through the string, truncate it
        int strLen = _tcsclen(binaryPath);

        for(int i=strLen; i>0; i--)
        {
            if(binaryPath[i] == '\\')
            {
                binaryPath[i] = '\0';
                break;
            }
        }
    }
    else
    {
        wsprintf(binaryPath, TEXT("."));
    }

    TCHAR commandToRun[MAX_PATH];
    wsprintf(commandToRun, TEXT("%s\\%s"), binaryPath, TEXT("Manilla2D-DevTools-EnableM2D-App.exe"));

    CreateProcess(commandToRun, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, NULL, NULL);
}
