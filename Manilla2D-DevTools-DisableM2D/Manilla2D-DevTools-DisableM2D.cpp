// Manilla2D-DevTools-DisableM2D.cpp : Defines the class behaviors for the application.
//

#ifdef _X86_
    #pragma comment(linker, "/nodefaultlib:libc.lib")
    #pragma comment(linker, "/nodefaultlib:libcd.lib")
    #pragma comment(linker, "/nodefaultlib:oldnames.lib")
#endif

// NOTE - this value is not strongly correlated to the Windows CE OS version being targeted
#define WINVER _WIN32_WCE

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define SHELL_AYGSHELL
#endif

#include <aygshell.h>
#pragma comment(lib, "aygshell.lib") 


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#include "DeviceResolutionAware.h"
#endif

#include <altcecrt.h>

#ifdef _DLL // /MD
    #if defined(_DEBUG)
        #pragma comment(lib, "msvcrtd.lib")
    #else
        #pragma comment(lib, "msvcrt.lib")
    #endif
#else // /MT
    #if defined(_DEBUG)
        #pragma comment(lib, "libcmtd.lib")
    #else
        #pragma comment(lib, "libcmt.lib")
    #endif
#endif

#if _WIN32_WCE < 0x500 && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
    #pragma comment(lib, "ccrtrtti.lib")
    #ifdef _X86_    
        #if defined(_DEBUG)
            #pragma comment(lib, "libcmtx86d.lib")
        #else
            #pragma comment(lib, "libcmtx86.lib")
        #endif
    #endif
#endif

#include "resourceppc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void DisableM2D();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    DisableM2D();

    return FALSE;
}


void DisableM2D()
{
    //MessageBox(NULL, TEXT("Disable M2D"), TEXT("Disable M2D"), MB_OK);

    HKEY mainHKey;
    DWORD enabledState = 0;
    TCHAR mainKeyName[MAX_PATH];
    TCHAR subKeyName[MAX_PATH];
    TCHAR valueName[MAX_PATH];

    // backup the date enabled state
    wsprintf(mainKeyName, TEXT("\\Software\\Microsoft\\Today"));
    
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, mainKeyName, 0, 0, &mainHKey) == ERROR_SUCCESS)
    {
        wsprintf(valueName, TEXT("Date"));
        enabledState = TRUE;
        RegSetValueEx(mainHKey, valueName, NULL, REG_DWORD, (CONST BYTE*)&enabledState, sizeof(DWORD));
        RegFlushKey(mainHKey);
        RegCloseKey(mainHKey);
    }

    // enumerate the sub items of the today screen
    wsprintf(mainKeyName, TEXT("\\Software\\Microsoft\\Today\\Items"));

    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, mainKeyName, 0, 0, &mainHKey) == ERROR_SUCCESS)
    {
        HKEY subHKey;
        DWORD subKeyIndex = 0;
        DWORD subKeyBufferSize = MAX_PATH;
        TCHAR subKeyBuffer[MAX_PATH];

        LONG retVal = RegEnumKeyEx(mainHKey, subKeyIndex, subKeyBuffer, &subKeyBufferSize, NULL, NULL, NULL, NULL);

        while(retVal == ERROR_SUCCESS)
        {
            enabledState = 0;

            wsprintf(subKeyName, TEXT("\\Software\\Microsoft\\Today\\Items\\%s"), subKeyBuffer);

            if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKeyName, 0, 0, &subHKey) == ERROR_SUCCESS)
            {
                wsprintf(valueName, TEXT("Enabled"));

                if(_tcscmp(subKeyBuffer, TEXT("EnableM2D-DevTool")) == 0)
                {
                    enabledState = TRUE;
                }
                else
                {
                    enabledState = FALSE;
                }

                RegSetValueEx(subHKey, valueName, NULL, REG_DWORD, (CONST BYTE*)&enabledState, sizeof(DWORD));
                RegFlushKey(subHKey);
                RegCloseKey(subHKey);
            }

            subKeyIndex++;
            subKeyBufferSize = MAX_PATH;
            retVal = RegEnumKeyEx(mainHKey, subKeyIndex, subKeyBuffer, &subKeyBufferSize, NULL, NULL, NULL, NULL);
        }

        RegFlushKey(mainHKey);
        RegCloseKey(mainHKey);
    }

    ::SendMessage(HWND_BROADCAST, WM_WININICHANGE, 0xF2, 0);
}
