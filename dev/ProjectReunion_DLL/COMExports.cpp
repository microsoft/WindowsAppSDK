// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ExtensionContractHandler.h"
#include "NotificationActivationHandler.h"

using namespace winrt::Microsoft::ProjectReunion::implementation;

HRESULT __stdcall DllGetClassObject(GUID const& clsid, GUID const& iid, void** result)
{
    try
    {
        *result = nullptr;

        if (clsid == __uuidof(ExtensionContractHandlerFactory))
        {
            return winrt::make<ExtensionContractHandlerFactory>()->QueryInterface(iid, result);
        }

        if (clsid == __uuidof(NotificationActivationHandler))
        {
            return winrt::make<NotificationActivationHandler>()->QueryInterface(iid, result);
        }

        return winrt::hresult_class_not_available().to_abi();
    }
    catch (...)
    {
        return winrt::to_hresult();
    }

    return S_OK;
}

