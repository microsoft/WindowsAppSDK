// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ProjectReunion;

using namespace std::chrono;

IAsyncAction WaitForActivations()
{
    co_await 120s;
    co_return;
}

void OnActivated(const winrt::Windows::Foundation::IInspectable&, const ActivationArguments& args)
{
    auto launchArgs = args.Data().as<ILaunchActivatedEventArgs>();
    wprintf(L"Activated via redirection with args: %s\n", launchArgs.Arguments().c_str());
}

int main()
{
    init_apartment();

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
            auto token = myKeyInstance.Activated(auto_revoke, [&myKeyInstance](const auto& sender, const ActivationArguments& args) { OnActivated(sender, args); });

            printf("Activated, waiting for redirections!\n");
            WaitForActivations().get();
        }
        else
        {
            printf("Redirecting to key owner!\n");
            myKeyInstance.RedirectTo(args);
            WaitForActivations().get();
        }
    }

    return 0;
}
