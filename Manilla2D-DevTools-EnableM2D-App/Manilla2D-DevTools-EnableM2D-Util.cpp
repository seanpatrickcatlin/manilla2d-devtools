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

#include "Manilla2D-DevTools-EnableM2D-Util.h"

#include <windows.h>

void EnableM2D()
{
    //MessageBox(g_hWnd, TEXT("Enable M2D"), TEXT("Enable M2D"), MB_OK);

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
        enabledState = FALSE;
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

                if(_tcscmp(subKeyBuffer, TEXT("TouchFLO")) == 0)
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

    ::PostMessage(HWND_BROADCAST, WM_WININICHANGE, 0xF2, 0);
}
