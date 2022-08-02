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

        TEST_METHOD(AppNotificationBuilderDefault)
        {
            auto builder{ AppNotificationBuilder() };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual></toast>"};
            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetTimeStamp)
        {
            std::wstring dateTimeFormat{ L"%d/%m/%Y %H:%M:%S" };
            std::wistringstream ss(L"22/12/2016 01:12:10");

            struct tm dateTime {};
            ss >> std::get_time(&dateTime, dateTimeFormat.c_str());
            std::time_t time{ mktime(&dateTime) };
            auto timeStamp{ winrt::clock::from_time_t(time) };

            auto builder{ AppNotificationBuilder().SetTimeStamp(timeStamp) };
            auto expected{ L"<toast displayTimestamp='2016-12-22T09:12:10Z'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddOneArgument)
        {
            auto builder{ AppNotificationBuilder().AddArgument(L"key", L"value") };
            auto expected{ L"<toast launch='key=value'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTwoArguments)
        {
            auto builder{ AppNotificationBuilder().AddArgument(L"key1", L"value1").AddArgument(L"key2", L"value2") };
            auto expected{ L"<toast launch='key1=value1;key2=value2'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentEmptyValue)
        {
            auto builder{ AppNotificationBuilder().AddArgument(L"key", L"") };
            auto expected{ L"<toast launch='key'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentWithPercentChar)
        {
            auto builder{ AppNotificationBuilder().AddArgument(L"k%ey", L"") };
            auto expected{ L"<toast launch='k%25ey'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentWithEqualChar)
        {
            auto builder{ AppNotificationBuilder().AddArgument(L"k=ey", L"") };
            auto expected{ L"<toast launch='k%3Dey'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentWithSemicolonChar)
        {
            auto builder{ AppNotificationBuilder().AddArgument(L"k;ey", L"") };
            auto expected{ L"<toast launch='k%3Bey'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }
        TEST_METHOD(AppNotificationBuilderAddArgumentEmptyKey)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder().AddArgument(L"", L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderSetReminderScenario)
        {
            auto builder{ AppNotificationBuilder().SetScenario(AppNotificationScenario::Reminder) };
            auto expected{ L"<toast scenario='reminder'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAlarmScenario)
        {
            auto builder{ AppNotificationBuilder().SetScenario(AppNotificationScenario::Alarm) };
            auto expected{ L"<toast scenario='alarm'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetIncomingCallScenario)
        {
            auto builder{ AppNotificationBuilder().SetScenario(AppNotificationScenario::IncomingCall) };
            auto expected{ L"<toast scenario='incomingCall'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetUrgentScenario)
        {
            auto builder{ AppNotificationBuilder().SetScenario(AppNotificationScenario::Urgent) };
            auto expected{ L"<toast scenario='urgent'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddText)
        {
            auto builder{ AppNotificationBuilder().AddText(L"content") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithLanguage)
        {
            auto builder{ AppNotificationBuilder()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetLanguage(L"en-US"))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text lang='en-US'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithMaxLines)
        {
            auto builder{ AppNotificationBuilder()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetMaxLines(2))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text hint-maxLines='2'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithCallScenarioAlign)
        {
            auto builder{ AppNotificationBuilder()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetIncomingCallAlignment())
            };
            auto expected{ L"<toast scenario='incomingCall'><visual><binding template='ToastGeneric'><text hint-callScenarioCenterAlign='true'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithAllProperties)
        {
            auto builder{ AppNotificationBuilder()
                            .AddText(L"content", AppNotificationTextProperties()
                                .SetLanguage(L"en-US")
                                .SetMaxLines(2)
                                .SetIncomingCallAlignment())
            };
            auto expected{ L"<toast scenario='incomingCall'><visual><binding template='ToastGeneric'><text lang='en-US' hint-maxLines='2' hint-callScenarioCenterAlign='true'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextThrows)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddText(L"content")
                .AddText(L"content")
                .AddText(L"content")
                .AddText(L"content"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddAttributionText)
        {
            auto builder{ AppNotificationBuilder().SetAttributionText(L"content") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text placement='attribution'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddAttributionTextWithLanguage)
        {
            auto builder{ AppNotificationBuilder().SetAttributionText(L"content", L"en-US")};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text placement='attribution' lang='en-US'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetInlineImage)
        {
            auto builder{ AppNotificationBuilder().SetInlineImage(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image src='http://www.microsoft.com/'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetInlineImageWithProperties)
        {
            auto builder{ AppNotificationBuilder().SetInlineImage(c_sampleUri, AppNotificationImageCrop::Circle, L"altText")};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image src='http://www.microsoft.com/' alt='altText' hint-crop='circle'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAppLogoOverride)
        {
            auto builder{ AppNotificationBuilder().SetAppLogoOverride(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='appLogoOverride' src='http://www.microsoft.com/'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAppLogoOverrideProperties)
        {
            auto builder{ AppNotificationBuilder().SetAppLogoOverride(c_sampleUri, AppNotificationImageCrop::Circle, L"altText") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='appLogoOverride' src='http://www.microsoft.com/' alt='altText' hint-crop='circle'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetHeroImage)
        {
            auto builder{ AppNotificationBuilder().SetHeroImage(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='hero' src='http://www.microsoft.com/'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetHeroImageWithAlt)
        {
            auto builder{ AppNotificationBuilder().SetHeroImage(c_sampleUri, L"altText") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='hero' src='http://www.microsoft.com/' alt='altText'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButton)
        {
            auto builder{ AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                .AddArgument(L"key", L"value"))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='key=value'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithPlacement)
        {
            auto builder{ AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetContextMenuPlacement())
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='key=value' placement='contextMenu'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderTooManyButtons)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key1", L"value1"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key2", L"value2"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key3", L"value3"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key4", L"value4"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key5", L"value5"))
                .AddButton(AppNotificationButton(L"content").AddArgument(L"key6", L"value6")), E_INVALIDARG);
        }

        TEST_METHOD(AddButtonWithProtocolActivation)
        {
            auto builder{ AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                .SetInvokeUri(c_sampleUri))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='http://www.microsoft.com/' activationType='protocol'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithProperties)
        {
            auto builder{ AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetButtonStyle(AppNotificationButtonStyle::Success)
                .SetIcon(c_sampleUri)
                .SetInputId(L"inputId")
                .SetToolTip(L"toolTip"))
            };
            auto expected{ L"<toast useButtonStyle='true'><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='key=value' imageUri='http://www.microsoft.com/' hint-inputId='inputId' hint-buttonStyle='Success' hint-toolTip='toolTip'/></actions></toast>"};

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithEmptyKey)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                    .AddArgument(L"", L"value")), E_INVALIDARG);
        }

        TEST_METHOD(AddButtonWithArgumentAndProtocol)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                    .AddArgument(L"key", L"value")
                    .SetInvokeUri(c_sampleUri)), E_INVALIDARG);

            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddButton(AppNotificationButton(L"content")
                    .SetInvokeUri(c_sampleUri)
                    .AddArgument(L"key", L"value")), E_INVALIDARG);
        }

        TEST_METHOD(SetAudioWithUri)
        {
            auto builder{ AppNotificationBuilder()
                    .SetAudioUri(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio src='http://www.microsoft.com/'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(SetAudioWithUriAndDuration)
        {
            auto builder{ AppNotificationBuilder()
                    .SetDuration(AppNotificationDuration::Long)
                    .SetAudioUri(c_sampleUri, AppNotificationAudioLooping::Loop) };
            auto expected{ L"<toast duration='long'><visual><binding template='ToastGeneric'></binding></visual><audio src='http://www.microsoft.com/' loop='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(SetAudioWithSoundEvent)
        {
            auto builder{ AppNotificationBuilder()
                    .SetAudioEvent(AppNotificationSoundEvent::Reminder) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio src='ms-winsoundevent:Notification.Reminder'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(SetAudioWithSoundEventAndDuration)
        {
            auto builder{ AppNotificationBuilder()
                    .SetDuration(AppNotificationDuration::Long)
                    .SetAudioEvent(AppNotificationSoundEvent::Reminder, AppNotificationAudioLooping::Loop) };
            auto expected{ L"<toast duration='long'><visual><binding template='ToastGeneric'></binding></visual><audio src='ms-winsoundevent:Notification.Reminder' loop='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(MuteAudio)
        {
            auto builder{ AppNotificationBuilder().MuteAudio() };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio silent='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

    };
}
