// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef MICROSOFT_WINDOWSAPPSDK_ML_DISABLE_AUTOINITIALIZE

#include <Windows.h>
#include <memory>
#include <string>

struct OrtApiBase;

// Maximum path buffer size set to 32768 (2^15) to handle extended-length path scenarios.
constexpr DWORD MAX_PATH_BUFFER_SIZE = 32768;

extern "C" const OrtApiBase* __cdecl OrtGetApiBase() noexcept
{
    // Static local variable with guaranteed one-time initialization (C++11)
    static const OrtApiBase* s_ortApiBase = []() -> const OrtApiBase* {

        // In self-contained mode, onnxruntime.dll should be deployed in the same directory
        // as the current module (not the executable), for simplified deployment
        // Try to load from the same directory as the current module

        // Get the current module path (not the executable path) with dynamic buffer sizing to handle long paths
        std::wstring modulePath;

        // Get handle to the current module (the module containing this code)
        HMODULE currentModule = nullptr;
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                               reinterpret_cast<LPCWSTR>(&OrtGetApiBase), &currentModule))
        {
            return nullptr;
        }

        for (DWORD size = 260; size < MAX_PATH_BUFFER_SIZE; size *= 2)
        {
            modulePath.resize(size, L'\0');
            DWORD pathLength = GetModuleFileNameW(currentModule, modulePath.data(), size);
            if (pathLength == 0)
            {
                return nullptr;
            }
            if (pathLength < size)
            {
                modulePath.resize(pathLength);
                break;
            }
            // If pathLength == size, buffer was too small, continue with larger size
        }

        if (modulePath.empty())
        {
            return nullptr;
        }

        // Find the last backslash to get the directory
        size_t lastBackslashPos = modulePath.find_last_of(L'\\');
        if (lastBackslashPos == std::wstring::npos)
        {
            return nullptr;
        }

        // Get the directory path (including the trailing backslash)
        std::wstring moduleDir = modulePath.substr(0, lastBackslashPos + 1);

        // Build path to onnxruntime.dll in the same directory as the current module
        // This provides simplified deployment for self-contained scenarios
        std::wstring onnxRuntimePath = moduleDir + L"onnxruntime.dll";

        // Try to load onnxruntime.dll from the module directory
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
