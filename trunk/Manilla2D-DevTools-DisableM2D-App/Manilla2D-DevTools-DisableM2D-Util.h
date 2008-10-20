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

#pragma once

#include <vector>
using std::vector;

struct NameAndEnabledStateItem
{
    CString name;
    BOOL enabled;
};

typedef std::vector<NameAndEnabledStateItem> NameAndEnabledState_vector_t;

struct TodayScreenSettings
{
    BOOL dateEnabled;
    NameAndEnabledState_vector_t itemVector;
};

void DisableM2D();

bool FileExists(CString pathToFile);
CString GetPathToRunningBinary();
CString GetDirectoryOfFile(CString fullFilePath);
CString GetPathToInstallDirectory();
CString GetPathToTodaySettingsXmlFile();

void ReadTodayScreenSettingsFromRegistry(TodayScreenSettings* regSettings);
void WriteTodayScreenSettingsToRegistry(TodayScreenSettings* regSettings);

void ReadTodayScreenSettingsFromXml(TodayScreenSettings* regSettings);
void WriteTodayScreenSettingsToXml(TodayScreenSettings* regSettings);
