// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "AppNotification-Test-Constants.h"
#include "BaseTestSuite.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;
using namespace winrt::Microsoft::Windows::AppNotifications;

void BaseTestSuite::ClassSetup()
{
    ::Test::Bootstrap::Setup();
    bool isSelfContained{};
    VERIFY_SUCCEEDED(TestData::TryGetValue(L"SelfContained", isSelfContained));

    if (!isSelfContained)
    {
        ::WindowsAppRuntime::SelfContained::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName);
    }
}

void BaseTestSuite::ClassCleanup()
{
    ::Test::Bootstrap::Cleanup();
}

void BaseTestSuite::MethodCleanup()
{
    if (!m_unregisteredFully)
    {
        AppNotificationManager::Default().UnregisterAll();
        m_unregisteredFully = true;
    }
}

void BaseTestSuite::Test1()
{
    VERIFY_IS_TRUE(true);
}
