
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ToastNotificationUtility.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.h>
#include <externs.h>

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace Windows::ApplicationModel::Core;
}

std::wstring RetrieveUnpackagedToastGuid()
{
    wil::unique_cotaskmem_string processName;
    THROW_IF_FAILED(GetCurrentProcessPath(processName));

    std::wstring wideStringProcessName{ processName.get() };
    std::wstring subKey{ L"Software\\Classes\\AppUserModelId\\" + ConvertPathToKey(wideStringProcessName) };

    wil::unique_hkey hKey;
    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr,
        &hKey,
        nullptr));

    WCHAR registeredGuidBuffer[GUID_LENGTH + 4]; // GUID length + '{' + '}' + '\0'
    DWORD bufferLength = sizeof(registeredGuidBuffer);
    HRESULT status = RegGetValueW(
        hKey.get(),
        nullptr,
        L"ToastGUID",
        RRF_RT_REG_SZ,
        nullptr,
        &registeredGuidBuffer,
        &bufferLength);

    if (status == ERROR_FILE_NOT_FOUND)
    {
        GUID guidReference;
        THROW_IF_FAILED(CoCreateGuid(&guidReference));

        wil::unique_cotaskmem_string guidStr;
        THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

        std::wstring guidWideStr{ guidStr.get() };
        RegisterValue(hKey, L"ToastGUID", reinterpret_cast<const BYTE*>(guidWideStr.c_str()), REG_SZ, guidWideStr.size() * sizeof(wchar_t));
        return guidWideStr;
    }
    else
    {
        THROW_HR_IF(status, FAILED_WIN32(status));
    }
    return registeredGuidBuffer;
}

std::wstring RetrieveToastGuid()
{
    if (AppModel::Identity::IsPackagedProcess())
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize{ ARRAYSIZE(appUserModelId) };

        THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));
        return appUserModelId;
    }
    else
    {
        return RetrieveUnpackagedToastGuid();
    }
}

void RegisterAssets(std::wstring const& appId, winrt::hstring const& displayName, winrt::Uri const& iconUri, wil::unique_cotaskmem_string const& clsid)
{
    wil::unique_hkey hKey;
    std::wstring subKey{ appIdentifierPath + appId };

    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr,
        &hKey,
        nullptr));

    RegisterValue(hKey, L"DisplayName", reinterpret_cast<const BYTE*>(displayName.c_str()), REG_EXPAND_SZ, displayName.size() * sizeof(wchar_t));
    RegisterValue(hKey, L"IconUri", reinterpret_cast<const BYTE*>(iconUri.AbsoluteUri().c_str()), REG_EXPAND_SZ, iconUri.AbsoluteUri().size() * sizeof(wchar_t));

    std::wstring wideStringClsid{ clsid.get() };
    RegisterValue(hKey, L"CustomActivator", reinterpret_cast<const BYTE*>(wideStringClsid.c_str()), REG_SZ, wideStringClsid.size() * sizeof(wchar_t));

    return;
}

void RegisterComServer(wil::unique_cotaskmem_string const& processName, wil::unique_cotaskmem_string const& clsid)
{
    wil::unique_hkey hKey;
    std::wstring wideStringClsid = { clsid.get() };
    std::wstring subKey{ clsIdPath + wideStringClsid + L"\\LocalServer32" };
    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr,
        &hKey,
        nullptr));

    std::wstring comRegistrationExeString{ L"\"" };
    comRegistrationExeString.append(processName.get());
    comRegistrationExeString.append(L"\" ");
    comRegistrationExeString.append(L"----ToastActivated:");

    RegisterValue(hKey, nullptr, reinterpret_cast<const BYTE*>(comRegistrationExeString.c_str()), REG_SZ, (comRegistrationExeString.size() * sizeof(wchar_t)));
}

void UnRegisterComServer(std::wstring const& clsid)
{
    wil::unique_hkey hKey;
    std::wstring subKey{ clsIdPath + clsid + L"\\LocalServer32" };

    THROW_IF_FAILED(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        KEY_WOW64_64KEY,
        0));
}

void UnRegisterAppIdentifierFromRegistry(std::wstring const& appIdentifier)
{
    wil::unique_hkey hKey;
    std::wstring subKey{ appIdentifierPath + appIdentifier };

    THROW_IF_FAILED(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        KEY_WOW64_64KEY,
        0));
}

std::wstring RetrieveComActivatorGuid(std::wstring const& appId)
{
    wil::unique_hkey hKey;
    std::wstring subKey{ appIdentifierPath + appId };

    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr,
        &hKey,
        nullptr));

    WCHAR registeredGuidBuffer[GUID_LENGTH + 4]; // GUID length + '{' + '}' + '\0'
    DWORD bufferLength = sizeof(registeredGuidBuffer);
    HRESULT status = RegGetValueW(
        hKey.get(),
        nullptr,
        L"CustomActivator",
        RRF_RT_REG_SZ,
        nullptr,
        &registeredGuidBuffer,
        &bufferLength);

    if (status == ERROR_FILE_NOT_FOUND)
    {
        return L"";
    }
    else
    {
        THROW_HR_IF(status, FAILED_WIN32(status));
    }
    return registeredGuidBuffer;
}
