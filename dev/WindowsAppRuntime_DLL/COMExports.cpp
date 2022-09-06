// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ActivationRegistrationManager.h"
#include "EncodedLaunchExecuteCommand.h"
#include "Association.h"

using namespace winrt::Microsoft::Windows::AppLifecycle::implementation;

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
}
