// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace winrt::Microsoft::Windows::AppNotifications::Builder;

namespace Test::AppNotification::Builder
{
    inline const winrt::Windows::Foundation::Uri c_sampleUri{ L"http://www.microsoft.com" };

    class APITests
    {
    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::Cleanup();
            return true;
        }

       TEST_METHOD_SETUP(MethodSetup)
        {

            ::Test::Bootstrap::SetupBootstrap();
            ::WindowsAppRuntime::VersionInfo::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
            return true;
        }

        TEST_METHOD_CLEANUP(MethodCleanup)
        {
            ::WindowsAppRuntime::VersionInfo::TestShutdown();
            ::Test::Bootstrap::CleanupBootstrap();
            return true;
        }

        TEST_METHOD(AppNotificationContentDefault)
        {
            auto builder{ AppNotificationContent() };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual></toast>)"};
            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddOneArgument)
        {
            auto builder{ AppNotificationContent().AddArgument(L"key", L"value") };
            auto expected{ LR"(<toast launch="key=value"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddTwoArguments)
        {
            auto builder{ AppNotificationContent().AddArgument(L"key1", L"value1").AddArgument(L"key2", L"value2") };
            auto expected{ LR"(<toast launch="key1=value1;key2=value2"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddArgumentEmptyValue)
        {
            auto builder{ AppNotificationContent().AddArgument(L"key", L"") };
            auto expected{ LR"(<toast launch="key"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddArgumentEmptyKey)
        {
            VERIFY_THROWS_HR(AppNotificationContent().AddArgument(L"", L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationContentSetReminderScenario)
        {
            auto builder{ AppNotificationContent().SetScenario(Scenario::Reminder) };
            auto expected{ LR"(<toast scenario="reminder"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetAlarmScenario)
        {
            auto builder{ AppNotificationContent().SetScenario(Scenario::Alarm) };
            auto expected{ LR"(<toast scenario="alarm"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetIncomingCallScenario)
        {
            auto builder{ AppNotificationContent().SetScenario(Scenario::IncomingCall) };
            auto expected{ LR"(<toast scenario="incomingCall"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetUrgentScenario)
        {
            auto builder{ AppNotificationContent().SetScenario(Scenario::Urgent) };
            auto expected{ LR"(<toast scenario="urgent"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetLongDuration)
        {
            auto builder{ AppNotificationContent().SetDuration(Duration::Long) };
            auto expected{ LR"(<toast duration="long"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetShortDuration)
        {
            auto builder{ AppNotificationContent().SetDuration(Duration::Short) };
            auto expected{ LR"(<toast duration="short"><visual><binding template="ToastGeneric"></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddText)
        {
            auto builder{ AppNotificationContent().AddText(L"content") };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><text>content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddTextWithLanguage)
        {
            auto builder{ AppNotificationContent()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetLanguage(L"en-US"))
            };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><text lang="en-US">content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddTextWithMaxLines)
        {
            auto builder{ AppNotificationContent()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetMaxLines(2))
            };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><text hint-maxLines="2">content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddTextWithCallScenarioAlign)
        {
            auto builder{ AppNotificationContent()
                            .AddText(L"content", AppNotificationTextProperties()
                                .UsesCallScenarioAlign())
            };
            auto expected{ LR"(<toast scenario="incomingCall"><visual><binding template="ToastGeneric"><text hint-callScenarioCenterAlign="true">content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddTextWithAllProperties)
        {
            auto builder{ AppNotificationContent()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetLanguage(L"en-US")
                                .SetMaxLines(2)
                                .UsesCallScenarioAlign())
            };
            auto expected{ LR"(<toast scenario="incomingCall"><visual><binding template="ToastGeneric"><text lang="en-US" hint-maxLines="2" hint-callScenarioCenterAlign="true">content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddTextThrows)
        {
            VERIFY_THROWS_HR(AppNotificationContent()
                .AddText(L"content")
                .AddText(L"content")
                .AddText(L"content")
                .AddText(L"content"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationContentAddAttributionText)
        {
            auto builder{ AppNotificationContent().SetAttributionText(L"content") };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><text placement="attribution">content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddAttributionTextWithLanguage)
        {
            auto builder{ AppNotificationContent().SetAttributionText(L"content", L"en-US")};
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><text placement="attribution" lang="en-US">content</text></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetInlineImage)
        {
            auto builder{ AppNotificationContent().SetInlineImage(c_sampleUri) };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><image src="http://www.microsoft.com/"/></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetInlineImageWithProperties)
        {
            auto builder{ AppNotificationContent().SetInlineImage(c_sampleUri, ImageCrop::Circle, L"altText")};
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><image src="http://www.microsoft.com/" alt="altText" hint-crop="circle"/></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetAppLogoOverride)
        {
            auto builder{ AppNotificationContent().SetAppLogoOverride(c_sampleUri) };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><image placement="appLogoOverride" src="http://www.microsoft.com/"/></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetAppLogoOverrideProperties)
        {
            auto builder{ AppNotificationContent().SetAppLogoOverride(c_sampleUri, ImageCrop::Circle, L"altText") };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><image placement="appLogoOverride" src="http://www.microsoft.com/" alt="altText" hint-crop="circle"/></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetHeroImage)
        {
            auto builder{ AppNotificationContent().SetHeroImage(c_sampleUri) };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><image placement="hero" src="http://www.microsoft.com/"/></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentSetHeroImageWithAlt)
        {
            auto builder{ AppNotificationContent().SetHeroImage(c_sampleUri, L"altText") };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><image placement="hero" src="http://www.microsoft.com/" alt="altText"/></binding></visual></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddButton)
        {
            auto builder{ AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                .AddArgument(L"key", L"value"))
            };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual><actions><action content="content" arguments="key=value"/></actions></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddButtonWithPlacement)
        {
            auto builder{ AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .UseContextMenuPlacement())
            };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual><actions><action content="content" arguments="key=value" placement="contextMenu"/></actions></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentTooManyButtons)
        {
            VERIFY_THROWS_HR(AppNotificationContent()
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key1", L"value1"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key2", L"value2"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key3", L"value3"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key4", L"value4"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key5", L"value5"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key6", L"value6")), E_INVALIDARG);
        }

        TEST_METHOD(AddButtonWithProtocolActivation)
        {
            auto builder{ AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                .SetProtocolActivation(c_sampleUri))
            };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual><actions><action content="content" arguments="http://www.microsoft.com/" activationType="protocol"/></actions></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddButtonWithProperties)
        {
            auto builder{ AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetButtonStyle(ButtonStyle::Success)
                .SetIconUri(c_sampleUri)
                .SetInputId(L"inputId")
                .SetToolTip(L"toolTip"))
            };
            auto expected{ LR"(<toast useButtonStyle="true"><visual><binding template="ToastGeneric"></binding></visual><actions><action content="content" arguments="key=value" imageUri="http://www.microsoft.com/" hint-inputId="inputId" hint-buttonStyle="Success" hint-toolTip="toolTip"/></actions></toast>)"};

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(AppNotificationContentAddButtonWithEmptyKey)
        {
            VERIFY_THROWS_HR(AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                    .AddArgument(L"", L"value")), E_INVALIDARG);
        }

        TEST_METHOD(AddButtonWithArgumentAndProtocol)
        {
            VERIFY_THROWS_HR(AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                    .AddArgument(L"key", L"value")
                    .SetProtocolActivation(c_sampleUri)), E_INVALIDARG);

            VERIFY_THROWS_HR(AppNotificationContent()
                .AddButton(AppNotificationButton(L"content")
                    .SetProtocolActivation(c_sampleUri)
                    .AddArgument(L"key", L"value")), E_INVALIDARG);
        }

        TEST_METHOD(SetAudioWithUri)
        {
            auto builder{ AppNotificationContent()
                    .SetAudio(c_sampleUri) };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual><audio src="http://www.microsoft.com/"/></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(SetAudioWithUriAndDuration)
        {
            auto builder{ AppNotificationContent()
                    .SetAudio(c_sampleUri, Duration::Long) };
            auto expected{ LR"(<toast duration="long"><visual><binding template="ToastGeneric"></binding></visual><audio src="http://www.microsoft.com/" loop="true"/></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(SetAudioWithMSWinSoundEvent)
        {
            auto builder{ AppNotificationContent()
                    .SetAudio(MSWinSoundEvent::Reminder) };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual><audio src="ms-winsoundevent:Notification.Reminder"/></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(SetAudioWithMSWinSoundEventAndDuration)
        {
            auto builder{ AppNotificationContent()
                    .SetAudio(MSWinSoundEvent::Reminder, Duration::Long) };
            auto expected{ LR"(<toast duration="long"><visual><binding template="ToastGeneric"></binding></visual><audio src="ms-winsoundevent:Notification.Reminder" loop="true"/></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(MuteAudio)
        {
            auto builder{ AppNotificationContent().MuteAudio() };
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"></binding></visual><audio silent="true"/></toast>)" };

            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
        }

        TEST_METHOD(ProgressBar)
        {
            auto expected{ LR"(<toast><visual><binding template="ToastGeneric"><text>Downloading this week's new music...</text><progress title = "{progressTitle}" valueStringOverride = "{progressValueString}"/></binding></visual></toast>)" };

            auto builder{ AppNotificationContent()
                .AddText(L"Downloading this week's new music...")
                .AddProgressBar(AppNotificationProgressBar()
                    .BindTitle()
                    .BindValueStringOverride())
            };

            auto x{ builder.GetXml() };
            VERIFY_ARE_EQUAL(builder.GetXml(), expected);
            }
    };
}
