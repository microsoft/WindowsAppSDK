// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <cstdio>
#include <windows.h>
#include <winrt/Microsoft.Windows.AppLifecycle.h>
#include <winrt/Microsoft.Security.Authentication.OAuth.h>
#include <winrt/Windows.ApplicationModel.Activation.h>

using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::ApplicationModel::Activation;

int main()
{
    try
    {
        auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
        auto kind = args.Kind();
        if (kind == ExtendedActivationKind::Protocol)
        {
            auto uri = args.Data().as<IProtocolActivatedEventArgs>().Uri();
            if (!OAuth2Manager::CompleteAuthRequest(uri))
            {
                std::printf("WARNING: Failed to complete auth request with uri '%ls'.\n", uri.RawUri().c_str());
                std::printf("WARNING: This may or may not be expected depending on which test is running.\n");
            }
        }
        else
        {
            std::printf("WARNING: Application was launched with something other than protocol activation!\n");
        }
    }
    catch (const std::exception& ex)
    {
        std::printf("Standard exception: %s\n", ex.what());
    }
}
