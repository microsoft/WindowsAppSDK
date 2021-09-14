// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::Windows::AppLifecycle;

using namespace std::chrono;

std::wstring GetFullIdentityString()
{
    std::wstring identityString;
    WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH + 1];
    UINT32 idNameBufferLen = ARRAYSIZE(idNameBuffer);
    if (::GetCurrentPackageFullName(&idNameBufferLen, idNameBuffer) == ERROR_SUCCESS)
    {
        identityString = idNameBuffer;
    }

    return identityString;
}

bool HasIdentity()
{
    static bool hasIdentity = !(GetFullIdentityString()).empty();
    return hasIdentity;
}

bool NeedDynamicDependencies()
{
    return !HasIdentity();
}

HRESULT BootstrapInitialize()
{
    if (!NeedDynamicDependencies())
    {
        return S_OK;
    }

    constexpr PCWSTR c_PackageNamePrefix{ L"WindowsAppRuntime.Test.DDLM" };
    constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
    RETURN_IF_FAILED(MddBootstrapTestInitialize(c_PackageNamePrefix, c_PackagePublisherId));

    // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
    const UINT32 c_Version_MajorMinor{ 0x00040001 };
    const PACKAGE_VERSION minVersion{};
    RETURN_IF_FAILED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));

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

IAsyncAction WaitForActivations()
{
    co_await 120000s;
    co_return;
}

void OnActivated(const winrt::Windows::Foundation::IInspectable&, const AppActivationArguments& args)
{
    auto launchArgs = args.Data().as<ILaunchActivatedEventArgs>();
    wprintf(L"Activated via redirection with args: %s\n", launchArgs.Arguments().c_str());
}

int main()
{
    init_apartment();

    THROW_IF_FAILED(BootstrapInitialize());

    AppInstance::Activated_revoker token;

    AppInstance keyInstance = AppInstance::FindOrRegisterForKey(L"derp.txt");
    if (keyInstance.IsCurrent())
    {
        AppInstance thisInstance = AppInstance::GetCurrent();
        token = thisInstance.Activated(
            auto_revoke, [&thisInstance](
                const auto& sender, const AppActivationArguments& args)
            { OnActivated(sender, args); }
        );
    }
    else
    {
         printf("Redirecting to key owner!\n");
        keyInstance.RedirectActivationToAsync(AppInstance::GetCurrent().GetActivatedEventArgs()).get();
        printf("Finished redirecting!\n");
    }

    WaitForActivations().get();

    BootstrapShutdown();
    return 0;
}
