// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EncodedLaunchExecuteCommand.h"
#include "Association.h"

using namespace winrt::Microsoft::ProjectReunion::implementation;

std::wstring GetDllModulePath();
std::wstring GetCoClassPath(const GUID& iid);
void RegisterCoClass(const GUID& iid);
void UnregisterCoClass(const GUID& iid);

extern "C" HRESULT __stdcall DllGetClassObject(GUID const& clsid, GUID const& iid, void** result)
{
    try
    {
        *result = nullptr;

        if (clsid == __uuidof(EncodedLaunchExecuteCommandFactory))
        {
            return winrt::make<EncodedLaunchExecuteCommandFactory>()->QueryInterface(iid, result);
        }

        return winrt::hresult_class_not_available().to_abi();
    }
    catch (...)
    {
        return winrt::to_hresult();
    }

    return S_OK;
}

extern "C" HRESULT __stdcall DllRegisterServer() noexcept try
{
    RegisterCoClass(__uuidof(EncodedLaunchExecuteCommandFactory));
    return S_OK;
}
CATCH_RETURN()

extern "C" HRESULT __stdcall DllUnregisterServer() noexcept try
{
    std::wstring scheme = L"ms-launch";
    UnregisterProtocol(scheme);
    UnregisterCoClass(__uuidof(EncodedLaunchExecuteCommandFactory));
    return S_OK;
}
CATCH_RETURN()

// TODO: Merge with other GetModulePath and make create parameter for variations.
std::wstring GetDllModulePath()
{
    std::wstring path(100, L'?');
    uint32_t path_size{};
    DWORD actual_size{};

    do
    {
        // Get the handle of the module containing this code, not the module of the process hosting it.
        wil::unique_hmodule moduleHandle;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
            reinterpret_cast<LPCWSTR>(GetDllModulePath), &moduleHandle));

        path_size = static_cast<uint32_t>(path.size());
        actual_size = ::GetModuleFileName(moduleHandle.get(), path.data(), path_size);

        if (actual_size + 1 > path_size)
        {
            path.resize(path_size * 2, L'?');
        }
    } while (actual_size + 1 > path_size);

    path.resize(actual_size);
    return path;
}

std::wstring GetCoClassPath(const GUID& iid)
{
    std::wstring path{ LR"(SOFTWARE\Classes\CLSID\{????????-????-????-????-????????????})" };
    ::StringFromGUID2(iid, path.data() + 23, 39);
    return path;
}

void RegisterCoClass(const GUID& iid)
{
    std::wstring key_path{ GetCoClassPath(iid) };
    key_path += LR"(\InProcServer32)";
    wil::unique_hkey key;

    THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
        KEY_WRITE, nullptr, key.put(), nullptr));
    ::RegDeleteValue(key.get(), nullptr);

    std::wstring path{ GetDllModulePath() };
    THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
        reinterpret_cast<BYTE const*>(path.c_str()), static_cast<uint32_t>((path.size() + 1)
            * sizeof(wchar_t))));
}

void UnregisterCoClass(const GUID& iid)
{
    std::wstring key_path{ GetCoClassPath(iid) };
    ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
}
