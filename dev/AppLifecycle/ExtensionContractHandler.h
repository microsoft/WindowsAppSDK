// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/base.h>

class ExtensionContractHandler :
    public winrt::implements<ExtensionContractHandler, IExecuteCommand>
{
    // IExecuteCommand
    HRESULT STDMETHODCALLTYPE Execute();
    HRESULT STDMETHODCALLTYPE SetDirectory(PCWSTR directory);
    HRESULT STDMETHODCALLTYPE SetKeyState(DWORD keyState);
    HRESULT STDMETHODCALLTYPE SetNoShowUI(BOOL noShowUI);
    HRESULT STDMETHODCALLTYPE SetParameters(PCWSTR parameters);
    HRESULT STDMETHODCALLTYPE SetPosition(POINT position);
    HRESULT STDMETHODCALLTYPE SetShowWindow(int showWindowState);

private:
    std::wstring m_directory;
    DWORD m_keyState;
    BOOL m_noShowUI;
    std::wstring m_parameters;
    POINT m_pos;
    int m_showWindowState;
};

class __declspec(uuid("FA2F222A-EC9D-437D-9760-2E2D73CB58EC")) ExtensionContractHandlerFactory :
    public winrt::implements<ExtensionContractHandlerFactory, IClassFactory>
{
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject) noexcept override
    {
        __debugbreak();
        try
        {
            return winrt::make<ExtensionContractHandler>()->QueryInterface(riid, ppvObject);
        }
        catch (...)
        {
            return winrt::to_hresult();
        }
    }

    HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock) noexcept override
    {
        // ...
        return S_OK;
    }

    // ...
};

