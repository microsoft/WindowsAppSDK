// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef MICROSOFT_WINDOWSAPPSDK_ML_DISABLE_AUTOINITIALIZE

#include <Windows.h>
#include <memory>
#include <string>
#include <appmodel.h>
#include <WindowsAppSDK-VersionInfo.h>

struct OrtApiBase;

extern "C" const OrtApiBase* __cdecl OrtGetApiBase() noexcept
{
    // Static local variable with guaranteed one-time initialization (C++11)
    static const OrtApiBase* s_ortApiBase = []() -> const OrtApiBase* {
        // Find framework package in current process dependency graph
        UINT32 bufferLength = 0;
        LONG rc = GetCurrentPackageInfo(PACKAGE_FILTER_DYNAMIC | PACKAGE_FILTER_STATIC, &bufferLength, nullptr, nullptr);
        if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            return nullptr;
        }

        auto buffer = std::make_unique<BYTE[]>(bufferLength);
        UINT32 count = 0;
        rc = GetCurrentPackageInfo(PACKAGE_FILTER_DYNAMIC | PACKAGE_FILTER_STATIC, &bufferLength, buffer.get(), &count);
        if (rc != ERROR_SUCCESS)
        {
            return nullptr;
        }

        // Look for framework package in dependency graph
        auto packageInfos = reinterpret_cast<PACKAGE_INFO*>(buffer.get());
        const WCHAR* frameworkPackagePath = nullptr;
        constexpr auto expectedFrameworkFamilyName = WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W;

        for (UINT32 i = 0; i < count; ++i)
        {
            const PACKAGE_INFO& packageInfo = packageInfos[i];
            if (packageInfo.packageFamilyName && packageInfo.path &&
                _wcsicmp(packageInfo.packageFamilyName, expectedFrameworkFamilyName) == 0)
            {
                frameworkPackagePath = packageInfo.path;
                break;
            }
        }

        if (!frameworkPackagePath)
        {
            return nullptr;
        }

        // Build path to onnxruntime.dll and load it
        std::wstring onnxRuntimePath = std::wstring(frameworkPackagePath) + L"\\onnxruntime.dll";
        HMODULE onnxruntimeModule = LoadLibraryExW(onnxRuntimePath.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (!onnxruntimeModule)
        {
            return nullptr;
        }

        // Get the real OrtGetApiBase function and call it
        using OrtGetApiBaseFunc = OrtApiBase* (*)();
        auto ortGetApiBase = reinterpret_cast<OrtGetApiBaseFunc>(GetProcAddress(onnxruntimeModule, "OrtGetApiBase"));
        if (ortGetApiBase)
        {
            return ortGetApiBase();
        }

        return nullptr;
    }();

    return s_ortApiBase;
}

#endif // MICROSOFT_WINDOWSAPPSDK_ML_DISABLE_AUTOINITIALIZE
