// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "BadgeNotification-Test-Constants.h"
#include "PackagedTests.h"

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
using namespace winrt::Microsoft::Windows::BadgeNotifications;

void PackagedTests::VerifyBadgeNotificationManagerCurrent()
{
    BadgeNotificationManager manager1 = BadgeNotificationManager::Current();

    VERIFY_IS_NOT_NULL(manager1);

    BadgeNotificationManager manager2 = BadgeNotificationManager::Current();
    VERIFY_IS_TRUE(manager1 == manager2);
}
