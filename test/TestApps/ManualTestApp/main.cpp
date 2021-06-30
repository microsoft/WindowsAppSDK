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
    RETURN_IF_FAILED(MddBootstrapInitialize(c_Version_Major, nullptr, minVersion));

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

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto myKeyInstance = AppInstance::FindOrRegisterForKey(L"MyKey");

    for (const auto& instance : AppInstance::GetInstances())
    {
        wprintf(L"key: %s, isCurrent: %d\n", instance.Key().c_str(), instance.IsCurrent());
    }

    if (myKeyInstance)
    {
        if (myKeyInstance.IsCurrent())
        {
            printf("Key owner activated!\n");

            // Sign up for the activated event.
            auto token = myKeyInstance.Activated(auto_revoke, [&myKeyInstance](const auto& sender, const AppActivationArguments& args) { OnActivated(sender, args); });

            printf("Activated, waiting for redirections!\n");
            WaitForActivations().get();
        }
        else
        {
            printf("Redirecting to key owner!\n");
            myKeyInstance.RedirectActivationToAsync(args).get();
            printf("Finished redirecting!\n");
        }
    }

    BootstrapShutdown();
    return 0;
}
