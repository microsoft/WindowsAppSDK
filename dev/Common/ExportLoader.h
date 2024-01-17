// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(__EXPORTLOADER_H)
#define __EXPORTLOADER_H

namespace ExportLoader
{
inline HMODULE Load(PCWSTR moduleName)
{
    auto hmodule{ ::LoadLibraryExW(moduleName, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32) };
    if (!hmodule)
    {
        const auto rc{ GetLastError() };
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(rc), rc != ERROR_MOD_NOT_FOUND, "%ls", moduleName);
        THROW_HR(E_NOTIMPL);
    }
    return hmodule;
}

template <typename T>
inline T GetFunction(HMODULE module, PCSTR functionName)
{
    auto function{ reinterpret_cast<T>(::GetProcAddress(module, functionName)) };
    if (!function)
    {
        const auto rc{ GetLastError() };
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(rc), rc != ERROR_PROC_NOT_FOUND, "%hs", functionName);
        THROW_HR(E_NOTIMPL);
    }
    return function;
}
}

#endif // defined(__EXPORTLOADER_H)
