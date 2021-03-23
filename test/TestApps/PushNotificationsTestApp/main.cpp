// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

#include <wil/win32_helpers.h>

using namespace winrt::Microsoft::ApplicationModel::Activation;
using namespace winrt::Microsoft::ProjectReunion;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;

bool IsPackagedProcess()
{
    UINT32 n{};
    return ::GetCurrentPackageFullName(&n, nullptr) == ERROR_INSUFFICIENT_BUFFER;;
}

bool NeedDynamicDependencies()
{
    return !IsPackagedProcess();
}

HRESULT BootstrapInitialize()
{
    if (!NeedDynamicDependencies())
    {
        return S_OK;
    }

    constexpr PCWSTR c_PackageNamePrefix{ L"ProjectReunion.Test.DDLM" };
    constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
    RETURN_IF_FAILED(MddBootstrapTestInitialize(c_PackageNamePrefix, c_PackagePublisherId));

    // Version <major>.0.0.0 to find any framework package for this major version
    const UINT64 c_Version_Major{ 4 };
    PACKAGE_VERSION minVersion{ static_cast<UINT64>(c_Version_Major) << 48 };
    RETURN_IF_FAILED(MddBootstrapInitialize(minVersion));

    return S_OK;
}

void BootstrapShutdown()
{
    if (!NeedDynamicDependencies())
    {
        return;
    }

    MddBootstrapShutdown();
}

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

int main()
{
    RETURN_IF_FAILED(BootstrapInitialize());
    bool succeeded = true;
    if (!succeeded)
    {
        SignalPhase(c_testFailureEventName);
    }

    BootstrapShutdown();
    return 0;
}
