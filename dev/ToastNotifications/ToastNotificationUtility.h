// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"
#include <winrt/Windows.Foundation.h>
#include <ToastActivatedEventArgs.h>

const std::wstring c_appIdentifierPath = L"Software\\Classes\\AppUserModelId\\";
const std::wstring c_clsIdPath = L"Software\\Classes\\CLSID\\";


winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::ToastNotifications::ToastActivatedEventArgs>>& GetToastHandlers();
int& GetToastHandleCount();

inline const int GUID_LENGTH = 36;

inline std::wstring ConvertPathToKey(std::wstring path)
{
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '\\')
        {
            path[i] = '.';
        }
    }
    return path;
}

inline void RegisterValue(wil::unique_hkey const& hKey, PCWSTR const& key, const BYTE* value, DWORD const& valueType, DWORD const& size)
{
    THROW_IF_FAILED(RegSetValueExW(hKey.get(), key, 0, valueType, value, size));
}

std::wstring RetrieveUnpackagedToastGuid();

std::wstring RetrieveToastGuid();

void RegisterAssets(std::wstring const& appId, winrt::Microsoft::Windows::ToastNotifications::ToastAssets const& activationInfo, wil::unique_cotaskmem_string const& clsid);

void RegisterComServer(wil::unique_cotaskmem_string const& processName, wil::unique_cotaskmem_string const& clsid);

void UnRegisterComServer(std::wstring const& clsid);

void UnRegisterAppIdentifierFromRegistry(std::wstring const& appIdentifier);

std::wstring RetrieveComActivatorGuid(std::wstring const& appId);
