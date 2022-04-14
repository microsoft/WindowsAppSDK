// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <TestDef.h>
#include "Base.h"

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
using namespace winrt::Microsoft::Windows::PushNotifications;

class PackagedTests : public WEX::TestClass<PackagedTests>
{
    private:
        Base m_base{};

    public:
        BEGIN_TEST_CLASS(PackagedTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")
            TEST_CLASS_PROPERTY(L"Data:SelfContained", L"{true, false}")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCWA")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"PushNotifications-AppxManifest.xml")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            m_base.ClassSetup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            m_base.ClassCleanup();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            m_base.MethodCleanup();
            return true;
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId)
        {
            m_base.ChannelRequestUsingNullRemoteId();
        }

        TEST_METHOD(ChannelRequestUsingNullRemoteId2)
        {
            VERIFY_IS_TRUE(true);
        }
};

