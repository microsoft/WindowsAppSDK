// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/base.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class ExecuteCommandBase : public winrt::implements<ExecuteCommandBase, IExecuteCommand, IObjectWithSite,
        IObjectWithSelection>
    {
    public:
        // IObjectWithSite
        IFACEMETHODIMP SetSite(_In_opt_::IUnknown* site) noexcept try
        {
            copy_from_abi(m_site, site);
            return S_OK;
        }
        CATCH_RETURN()

        IFACEMETHODIMP GetSite(_In_ REFIID riid, _COM_Outptr_ void** site) noexcept try
        {
            *site = nullptr;
            return m_site ? static_cast<HRESULT>(m_site.as(riid, site)) : E_NOTIMPL;
        }
        CATCH_RETURN()

        // IObjectWithSelection
        IFACEMETHODIMP SetSelection(_In_ IShellItemArray* shellItemArray) noexcept try
        {
            winrt::copy_from_abi(m_selection, shellItemArray);
            return S_OK;
        }
        CATCH_RETURN()

        IFACEMETHODIMP GetSelection(_In_ REFIID riid, _COM_Outptr_ void** ppv) noexcept try
        {
            *ppv = nullptr;
            return m_selection ? static_cast<HRESULT>(m_selection.as(riid, ppv)) : E_NOINTERFACE;
        }
        CATCH_RETURN()

        // IExecuteCommand
        IFACEMETHOD(Execute)() = 0;

        IFACEMETHODIMP SetDirectory(PCWSTR directory)
        {
            m_directory = directory;
            return S_OK;
        }

        IFACEMETHODIMP SetKeyState(DWORD keyState)
        {
            m_keyState = keyState;
            return S_OK;
        }

        IFACEMETHODIMP SetNoShowUI(BOOL noShowUI)
        {
            m_noShowUI = noShowUI;
            return S_OK;
        }

        IFACEMETHODIMP SetParameters(PCWSTR parameters)
        {
            m_parameters = parameters;
            return S_OK;
        }

        IFACEMETHODIMP SetPosition(POINT position)
        {
            m_pos = position;
            return S_OK;
        }

        IFACEMETHODIMP SetShowWindow(int showWindowState)
        {
            m_showWindowState = showWindowState;
            return S_OK;
        }

    protected:
        winrt::com_ptr<IUnknown> m_site;
        winrt::com_ptr<IShellItemArray> m_selection;
        std::wstring m_directory;
        DWORD m_keyState;
        BOOL m_noShowUI;
        std::wstring m_parameters;
        POINT m_pos;
        int m_showWindowState;
    };
}
