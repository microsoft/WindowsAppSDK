// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <TestDef.h>
#include "Shared.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

namespace Test::PushNotifications
{
    void InstallPackage(const std::wstring& packagePath)
    {
        // Deploy packaged app to register handler through the manifest.
        PackageManager manager;
        IVector<Uri> depPackagePaths;
        auto result = manager.AddPackageAsync(Uri(packagePath), depPackagePaths,
            DeploymentOptions::ForceApplicationShutdown).get();
        auto errorText = result.ErrorText();
        auto errorCode = result.ExtendedErrorCode();
        VERIFY_SUCCEEDED(errorCode, errorText.c_str());
    }

    void UninstallPackage(const std::wstring& packageFullName)
    {
        // Deploy packaged app to register handler through the manifest.
        PackageManager manager;
        IVector<Uri> depPackagePaths;
        auto result = manager.RemovePackageAsync(packageFullName).get();
        auto errorText = result.ErrorText();
        auto errorCode = result.ExtendedErrorCode();
        VERIFY_SUCCEEDED(errorCode, errorText.c_str());
    }
}
