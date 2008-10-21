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


#include "stdafx.h"
#include "Manilla2D-DevTools-DisableM2D-Util.h"

#include "tinyxml.h"
#include "tinystr.h"

std::string g_tempStr;

void DisableM2D()
{
    TodayScreenSettings settings;

    ReadTodayScreenSettingsFromXml(&settings);

    WriteTodayScreenSettingsToRegistry(&settings);

    ::SendMessage(HWND_BROADCAST, WM_WININICHANGE, 0xF2, 0);
}

const char* GetConstCharStarFromCString(CString str)
{
    CT2CA pszConvertedAnsiString(str);
	g_tempStr = pszConvertedAnsiString;

	return g_tempStr.c_str();
}

CString GetPathToRunningBinary()
{
	CString retVal("\\");

	TCHAR binaryPath[MAX_PATH];
	if(GetModuleFileName(NULL, binaryPath, MAX_PATH) > 0)
	{
		retVal = binaryPath;
	}

	TRACE(TEXT("GetPathToRunningBinary "));
	TRACE(retVal);
	TRACE(TEXT("\n"));

	return retVal;
}

bool FileExists(CString pathToFile)
{
    bool retVal = false;

    WIN32_FIND_DATA emptyStruct;

    HANDLE fileHndl = FindFirstFile(pathToFile, &emptyStruct);
    if(fileHndl != INVALID_HANDLE_VALUE)
    {
        FindClose(fileHndl);
        retVal = true;
    }

    return retVal;
}

CString GetDirectoryOfFile(CString fullFilePath)
{
	CString retVal = fullFilePath;

	int pos = retVal.ReverseFind('\\');

	if((pos > 0) && (pos < retVal.GetLength()))
	{
		retVal = retVal.Mid(0, pos);
	}

	TRACE(TEXT("GetDirectoryOfFile "));
	TRACE(fullFilePath);
	TRACE(TEXT(", "));
	TRACE(retVal);
	TRACE(TEXT("\n"));

	return retVal;
}

CString GetPathToInstallDirectory()
{
    CString retVal = GetDirectoryOfFile(GetPathToRunningBinary());

	TRACE(TEXT("GetPathToInstallDirectory "));
	TRACE(retVal);
	TRACE(TEXT("\n"));

	return retVal;
}

CString GetPathToTodaySettingsXmlFile()
{
	CString retVal = GetPathToInstallDirectory();
	retVal += "\\TodaySettings.xml";

    CString debugStr = TEXT("GetPathToTodaySettingsXmlFile ");
    debugStr += retVal;
    debugStr += "\n";

    TRACE(debugStr);

    return retVal;
}

void ReadTodayScreenSettingsFromRegistry(TodayScreenSettings* regSettings)
{
    if(regSettings == NULL)
    {
        return;
    }

    regSettings->dateEnabled = FALSE;
    regSettings->itemVector.clear();

    HKEY mainHKey;
    DWORD enabledState = 0;
    DWORD varSizeDword = sizeof(DWORD);
    DWORD varTypeDword = REG_DWORD;
    CString mainKeyName, subKeyName, valueName;

    // backup the date enabled state
    mainKeyName = "\\Software\\Microsoft\\Today";
    
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, mainKeyName, 0, 0, &mainHKey) == ERROR_SUCCESS)
    {
        valueName = "Date";

        RegQueryValueEx(mainHKey, valueName, NULL, &varTypeDword, (LPBYTE)&enabledState, &varSizeDword);

        RegCloseKey(mainHKey);
    }

    regSettings->dateEnabled = enabledState;

    // enumerate the sub items of the today screen
    mainKeyName = "\\Software\\Microsoft\\Today\\Items";

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

            subKeyName = "\\Software\\Microsoft\\Today\\Items\\";
            subKeyName += subKeyBuffer;

            if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKeyName, 0, 0, &subHKey) == ERROR_SUCCESS)
            {
                valueName = "Enabled";

                RegQueryValueEx(subHKey, valueName, NULL, &varTypeDword, (LPBYTE)&enabledState, &varSizeDword);

                RegCloseKey(subHKey);

                NameAndEnabledStateItem newRegEntry;
                newRegEntry.name = subKeyBuffer;
                newRegEntry.enabled = enabledState;

                regSettings->itemVector.push_back(newRegEntry);
            }

            subKeyIndex++;
            subKeyBufferSize = MAX_PATH;
            retVal = RegEnumKeyEx(mainHKey, subKeyIndex, subKeyBuffer, &subKeyBufferSize, NULL, NULL, NULL, NULL);
        }

        RegCloseKey(mainHKey);
    }
}

void WriteTodayScreenSettingsToRegistry(TodayScreenSettings* regSettings)
{
    if(regSettings == NULL)
    {
        return;
    }

    HKEY hKey;
    DWORD enabledState = 0;
    CString keyName, valueName;

    // restore the date enabled state
    keyName = "\\Software\\Microsoft\\Today";
    
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyName, 0, 0, &hKey) == ERROR_SUCCESS)
    {
        valueName = "Date";
        enabledState = regSettings->dateEnabled;
        RegSetValueEx(hKey, valueName, NULL, REG_DWORD, (CONST BYTE*)&enabledState, sizeof(DWORD));
        RegFlushKey(hKey);
        RegCloseKey(hKey);
    }

    // cycle through ALL today screen items, and set their enabled flag to false
    keyName = "\\Software\\Microsoft\\Today\\Items";
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyName, 0, 0, &hKey) == ERROR_SUCCESS)
    {
        HKEY subHKey;
        DWORD subKeyIndex = 0;
        DWORD subKeyBufferSize = MAX_PATH;
        TCHAR subKeyBuffer[MAX_PATH];
        TCHAR subKeyName[MAX_PATH];

        LONG retVal = RegEnumKeyEx(hKey, subKeyIndex, subKeyBuffer, &subKeyBufferSize, NULL, NULL, NULL, NULL);

        while(retVal == ERROR_SUCCESS)
        {
            enabledState = 0;

            wsprintf(subKeyName, TEXT("\\Software\\Microsoft\\Today\\Items\\%s"), subKeyBuffer);

            if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKeyName, 0, 0, &subHKey) == ERROR_SUCCESS)
            {
                valueName =  TEXT("Enabled");
                enabledState = FALSE;

                RegSetValueEx(subHKey, valueName, NULL, REG_DWORD, (CONST BYTE*)&enabledState, sizeof(DWORD));
                RegFlushKey(subHKey);
                RegCloseKey(subHKey);
            }

            subKeyIndex++;
            subKeyBufferSize = MAX_PATH;
            retVal = RegEnumKeyEx(hKey, subKeyIndex, subKeyBuffer, &subKeyBufferSize, NULL, NULL, NULL, NULL);
        }

        RegFlushKey(hKey);
        RegCloseKey(hKey);
    }

    // cycle through the vector of today reg items and set them to the user defined values
    for(size_t i=0; i<regSettings->itemVector.size(); i++)
    {
        keyName = "\\Software\\Microsoft\\Today\\Items\\";
        keyName += regSettings->itemVector[i].name;

        if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyName, 0, 0, &hKey) == ERROR_SUCCESS)
        {
            valueName = "Enabled";
            enabledState = regSettings->itemVector[i].enabled;
            RegSetValueEx(hKey, valueName, NULL, REG_DWORD, (CONST BYTE*)&enabledState, sizeof(DWORD));
            RegFlushKey(hKey);
            RegCloseKey(hKey);
        }
    }
}

void ReadTodayScreenSettingsFromXml(TodayScreenSettings* regSettings)
{
    if(regSettings == NULL)
    {
        return;
    }

    CString xmlFilePath = GetPathToTodaySettingsXmlFile();

    if(!FileExists(xmlFilePath))
    {
        NameAndEnabledStateItem EnableM2D;

        EnableM2D.name = TEXT("EnableM2D-DevTool");
        EnableM2D.enabled = TRUE;

        regSettings->itemVector.clear();
        regSettings->itemVector.push_back(EnableM2D);

        regSettings->dateEnabled = TRUE;
    }
    else
    {
        TiXmlDocument doc(GetConstCharStarFromCString(xmlFilePath));
        bool loadOkay = doc.LoadFile();

        if(loadOkay)
        {
            TiXmlNode* todayNode = doc.FirstChild("TodaySettings");

            if(todayNode)
            {
                TiXmlElement* todayElement = todayNode->ToElement();

                if(todayElement != NULL)
                {
                    todayElement->QueryIntAttribute("DateEnabled", &regSettings->dateEnabled);

                    regSettings->itemVector.clear();

                    for(TiXmlElement* itemElement = todayElement->FirstChildElement("Item");
                        itemElement != NULL;
                        itemElement = itemElement->NextSiblingElement("Item"))
                    {
                        NameAndEnabledStateItem currentItem;

                        currentItem.name = itemElement->Attribute("Name");
                        itemElement->QueryIntAttribute("Enabled", &currentItem.enabled);

                        regSettings->itemVector.push_back(currentItem);
                    }
                }
            }
        }
    }
}

void WriteTodayScreenSettingsToXml(TodayScreenSettings* regSettings)
{
    if(regSettings == NULL)
    {
        return;
    }

    CString xmlFilePath = GetPathToTodaySettingsXmlFile();

    if(!FileExists(xmlFilePath))
    {
        TiXmlDocument newdoc;
        TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
        TiXmlElement* element = new TiXmlElement("TodaySettings");
        newdoc.LinkEndChild(decl);
        newdoc.LinkEndChild(element);

        newdoc.SaveFile(GetConstCharStarFromCString(xmlFilePath));
    }

    TiXmlDocument doc(GetConstCharStarFromCString(xmlFilePath));
    bool loadOkay = doc.LoadFile();

    if(loadOkay)
    {
        TiXmlNode* todayNode = doc.FirstChild("TodaySettings");

        if(todayNode)
        {
            todayNode->Clear(); 
            TiXmlElement* todayElement = todayNode->ToElement();

            if(todayElement != NULL)
            {
                todayElement->SetAttribute("DateEnabled", regSettings->dateEnabled);
            }

            for(size_t i=0; i<regSettings->itemVector.size(); i++)
            {
                NameAndEnabledStateItem currentItem = regSettings->itemVector[i];

                TiXmlElement* newItemElement = new TiXmlElement("Item");
                newItemElement->SetAttribute("Name", GetConstCharStarFromCString(currentItem.name));
                newItemElement->SetAttribute("Enabled", currentItem.enabled);

                todayElement->LinkEndChild(newItemElement);
            }

            doc.SaveFile();
        }
    }
}
