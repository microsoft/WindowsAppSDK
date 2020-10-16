// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include "ExtensionContractHandler.h"

HRESULT STDMETHODCALLTYPE ExtensionContractHandler::Execute()
{
    __debugbreak();
    return S_OK;
}
HRESULT STDMETHODCALLTYPE ExtensionContractHandler::SetDirectory(PCWSTR directory)
{
    m_directory = directory;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ExtensionContractHandler::SetKeyState(DWORD keyState)
{
    m_keyState = keyState;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ExtensionContractHandler::SetNoShowUI(BOOL noShowUI)
{
    m_noShowUI = noShowUI;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ExtensionContractHandler::SetParameters(PCWSTR parameters)
{
    m_parameters = parameters;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ExtensionContractHandler::SetPosition(POINT position)
{
    m_pos = position;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ExtensionContractHandler::SetShowWindow(int showWindowState)
{
    m_showWindowState = showWindowState;
    return S_OK;
}
