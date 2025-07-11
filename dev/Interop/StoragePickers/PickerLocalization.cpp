// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: Localization logic is intentionally separated from PickerCommon.cpp to avoid
// MRT Core dependencies in unit tests. Once unit tests are refactored to use component
// packages instead of mocked packages, this can be moved into CaptureParameters method.

#include "pch.h"
#include "PickerLocalization.h"
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>
#include <vector>


const winrt::hstring priFileName = L"Microsoft.WindowsAppRuntime.pri";
winrt::hstring GetPriFilePath()
{
    HMODULE hModule = nullptr;
    // use GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, the module handle does not need to be released
    // GetPriFilePath should only be called once to initialize the static priFilePath variable, thus thread safe
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        reinterpret_cast<LPCWSTR>(&GetPriFilePath), &hModule))
    {
        auto buffer = std::make_unique<wchar_t[]>(MAX_PATH + 1);
        auto pathLength = GetModuleFileName(hModule, buffer.get(), MAX_PATH + 1);
        if (pathLength > 0)
        {
            auto dllPathString = std::wstring(buffer.get(), pathLength);
            std::filesystem::path dllPath(dllPathString);
            if (!std::filesystem::is_regular_file(dllPath))
            {
                return priFileName;
            }
            std::filesystem::path parentDir = dllPath.parent_path();
            auto priFilePath = parentDir / std::wstring{ priFileName };
            if (std::filesystem::exists(priFilePath))
            {
                return winrt::hstring{ priFilePath.wstring() };
            }
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


