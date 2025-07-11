// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: Localization logic is intentionally separated from PickerCommon.cpp to avoid
// MRT Core dependencies in unit tests. Once unit tests are refactored to use component
// packages instead of mocked packages, this can be moved into CaptureParameters method.

#include "pch.h"
#include "PickerLocalization.h"
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>


const winrt::hstring priFileName = L"Microsoft.WindowsAppRuntime.pri";
winrt::hstring GetPriFilePath()
{
    HMODULE hModule = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<LPCWSTR>(&GetPriFilePath), &hModule))
    {
        wchar_t path[MAX_PATH];
        if (GetModuleFileNameW(hModule, path, MAX_PATH) > 0)
        {
            std::filesystem::path dllPath(path);
            std::filesystem::path parentDir = dllPath.parent_path();
            auto priFilePath = parentDir / std::wstring{ priFileName };
            auto priFilePathHstring = winrt::hstring{ priFilePath.wstring() };
            return priFilePathHstring;
        }
    }
    return priFileName;
}

namespace PickerLocalization {
    
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key, winrt::hstring fallback)
    {
        static winrt::hstring priPath = GetPriFilePath();
        auto manager = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(priPath);
        return manager.MainResourceMap().GetValue(key).ValueAsString();
    }
}


