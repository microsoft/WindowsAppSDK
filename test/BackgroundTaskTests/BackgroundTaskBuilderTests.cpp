#include "pch.h"

#include <winrt/Windows.Foundation.h>
#include <TerminalVelocityFeatures-BackgroundTask.h>
#include <winrt\windows.applicationmodel.background.h>
#include "winrt\Microsoft.Windows.ApplicationModel.Background.h"

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

            TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

		TEST_METHOD(TestMethod1)
		{
            if (!::Microsoft::Windows::ApplicationModel::Background::Feature_BackgroundTask::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"BackgroundTaskBuilder API Features are not enabled.");
                return;
            }
            winrt::Microsoft::Windows::ApplicationModel::Background::BackgroundTaskBuilder builder;
            builder.SetTrigger(TimeTrigger(15, false));
            builder.SetTaskEntryPointClsid(winrt::guid{ 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } });
            builder.AddCondition(SystemCondition(SystemConditionType::InternetAvailable));
            builder.Name(L"TestName");
            //auto task = builder.Register();
            //VERIFY_IS_NOT_NULL(task);
		}
	};
}
