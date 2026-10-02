// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <TerminalVelocityFeatures-BackgroundTask.h>
#include <winrt\windows.storage.h>
#include <winrt\windows.applicationmodel.background.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Background.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage;

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace BackgroundTaskTests
{
	class BackgroundTaskBuilderTests
	{
    public:
        BEGIN_TEST_CLASS(BackgroundTaskBuilderTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"BackgroundTaskBuilder-AppxManifest.xml")
            END_TEST_CLASS()

        TEST_CLASS_SETUP(BackgroundTaskBuilderTestsClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(BackgroundTaskBuilderTestsClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(BackgroundTaskBuilderTestsMethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(BackgroundTaskBuilderTestsMethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

		TEST_METHOD(TestBackgroundTaskRegistration)
		{
            if (!::Microsoft::Windows::ApplicationModel::Background::Feature_BackgroundTask::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"BackgroundTaskBuilder API Features are not enabled.");
                return;
            }
            winrt::Microsoft::Windows::ApplicationModel::Background::BackgroundTaskBuilder builder;
            auto trigger = SystemTrigger(SystemTriggerType::TimeZoneChange, false);
            builder.SetTrigger(trigger);
            winrt::guid clsId{ 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
            builder.SetTaskEntryPointClsid(clsId);
            builder.AddCondition(SystemCondition(SystemConditionType::InternetAvailable));
            builder.Name(L"TestName");
            BackgroundTaskRegistration taskReg = builder.Register();
            // Verifying that BackgroundTask Registration is successful
            VERIFY_IS_NOT_NULL(taskReg);
            VERIFY_ARE_EQUAL(taskReg.Name(), L"TestName");
            VERIFY_IS_TRUE(taskReg.AllTasks().Size() > 0);

            winrt::hstring lookupStr = winrt::to_hstring(taskReg.TaskId());
            ApplicationDataContainer localSettings = ApplicationData::Current().LocalSettings();
            auto values = localSettings.Values();
            auto lookupobj = values.Lookup(lookupStr);
            winrt::guid comClsId = winrt::unbox_value<winrt::guid>(lookupobj);

            // Verifying that the CLSID is stored in the local settings
            VERIFY_IS_NOT_NULL(lookupobj);
            VERIFY_IS_TRUE(clsId == comClsId);
            taskReg.Unregister(true);
		}
	};
}
