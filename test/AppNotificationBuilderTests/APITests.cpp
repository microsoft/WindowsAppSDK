// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
}

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
            auto builder{ winrt::AppNotificationBuilder() };
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

            auto builder{ winrt::AppNotificationBuilder().SetTimeStamp(timeStamp) };
            auto expected{ L"<toast displayTimestamp='2016-12-22T09:12:10Z'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddOneArgument)
        {
            auto builder{ winrt::AppNotificationBuilder().AddArgument(L"key", L"value") };
            auto expected{ L"<toast launch='key=value'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTwoArguments)
        {
            auto builder{ winrt::AppNotificationBuilder().AddArgument(L"key1", L"value1").AddArgument(L"key2", L"value2") };
            auto expected{ L"<toast launch='key1=value1;key2=value2'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentEmptyValue)
        {
            auto builder{ winrt::AppNotificationBuilder().AddArgument(L"key", L"") };
            auto expected{ L"<toast launch='key'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentWithPercentChar)
        {
            auto builder{ winrt::AppNotificationBuilder().AddArgument(L"k%ey", L"v%alue") };
            auto expected{ L"<toast launch='k%25ey=v%25alue'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentWithEqualChar)
        {
            auto builder{ winrt::AppNotificationBuilder().AddArgument(L"k=ey", L"v=alue") };
            auto expected{ L"<toast launch='k%3Dey=v%3Dalue'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddArgumentWithSemicolonChar)
        {
            auto builder{ winrt::AppNotificationBuilder().AddArgument(L"k;ey", L"v;alue") };
            auto expected{ L"<toast launch='k%3Bey=v%3Balue'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(DecodeArguments)
        {
            VERIFY_ARE_EQUAL(Decode(L"key%3B"), L"key;");
            VERIFY_ARE_EQUAL(Decode(L"key%3D"), L"key=");
            VERIFY_ARE_EQUAL(Decode(L"key%25"), L"key%");
            VERIFY_ARE_EQUAL(Decode(L"key%3B%3D%25"), L"key;=%");
            VERIFY_ARE_EQUAL(Decode(L"%25%25%25"), L"%%%");

        }

        TEST_METHOD(AppNotificationBuilderAddArgumentEmptyKey)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder().AddArgument(L"", L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderSetReminderScenario)
        {
            auto builder{ winrt::AppNotificationBuilder().SetScenario(winrt::AppNotificationScenario::Reminder) };
            auto expected{ L"<toast scenario='reminder'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAlarmScenario)
        {
            auto builder{ winrt::AppNotificationBuilder().SetScenario(winrt::AppNotificationScenario::Alarm) };
            auto expected{ L"<toast scenario='alarm'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetIncomingCallScenario)
        {
            auto builder{ winrt::AppNotificationBuilder().SetScenario(winrt::AppNotificationScenario::IncomingCall) };
            auto expected{ L"<toast scenario='incomingCall'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetUrgentScenario)
        {
            auto builder{ winrt::AppNotificationBuilder().SetScenario(winrt::AppNotificationScenario::Urgent) };
            auto expected{ L"<toast scenario='urgent'><visual><binding template='ToastGeneric'></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddText)
        {
            auto builder{ winrt::AppNotificationBuilder().AddText(L"content") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithLanguage)
        {
            auto builder{ winrt::AppNotificationBuilder()
                            .AddText(L"content", winrt::AppNotificationTextProperties()
                                .SetLanguage(L"en-US"))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text lang='en-US'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithMaxLines)
        {
            auto builder{ winrt::AppNotificationBuilder()
                            .AddText(L"content", winrt::AppNotificationTextProperties()
                                .SetMaxLines(2))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text hint-maxLines='2'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithCallScenarioAlign)
        {
            auto builder{ winrt::AppNotificationBuilder()
                            .AddText(L"content", winrt::AppNotificationTextProperties()
                                .SetIncomingCallAlignment())
            };
            auto expected{ L"<toast scenario='incomingCall'><visual><binding template='ToastGeneric'><text hint-callScenarioCenterAlign='true'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextWithAllProperties)
        {
            auto builder{ winrt::AppNotificationBuilder()
                            .AddText(L"content", winrt::AppNotificationTextProperties()
                                .SetLanguage(L"en-US")
                                .SetMaxLines(2)
                                .SetIncomingCallAlignment())
            };
            auto expected{ L"<toast scenario='incomingCall'><visual><binding template='ToastGeneric'><text lang='en-US' hint-maxLines='2' hint-callScenarioCenterAlign='true'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextThrows)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddText(L"content")
                .AddText(L"content")
                .AddText(L"content")
                .AddText(L"content"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddAttributionText)
        {
            auto builder{ winrt::AppNotificationBuilder().SetAttributionText(L"content") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text placement='attribution'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddAttributionTextWithLanguage)
        {
            auto builder{ winrt::AppNotificationBuilder().SetAttributionText(L"content", L"en-US")};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text placement='attribution' lang='en-US'>content</text></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetInlineImage)
        {
            auto builder{ winrt::AppNotificationBuilder().SetInlineImage(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image src='http://www.microsoft.com/'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetInlineImageWithProperties)
        {
            auto builder{ winrt::AppNotificationBuilder().SetInlineImage(c_sampleUri, winrt::AppNotificationImageCrop::Circle, L"altText")};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image src='http://www.microsoft.com/' alt='altText' hint-crop='circle'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAppLogoOverride)
        {
            auto builder{ winrt::AppNotificationBuilder().SetAppLogoOverride(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='appLogoOverride' src='http://www.microsoft.com/'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAppLogoOverrideProperties)
        {
            auto builder{ winrt::AppNotificationBuilder().SetAppLogoOverride(c_sampleUri, winrt::AppNotificationImageCrop::Circle, L"altText") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='appLogoOverride' src='http://www.microsoft.com/' alt='altText' hint-crop='circle'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetHeroImage)
        {
            auto builder{ winrt::AppNotificationBuilder().SetHeroImage(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='hero' src='http://www.microsoft.com/'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetHeroImageWithAlt)
        {
            auto builder{ winrt::AppNotificationBuilder().SetHeroImage(c_sampleUri, L"altText") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><image placement='hero' src='http://www.microsoft.com/' alt='altText'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButton)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                .AddArgument(L"key", L"value"))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='key=value'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithPlacement)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetContextMenuPlacement())
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='key=value' placement='contextMenu'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderTooManyButtons)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content").AddArgument(L"key1", L"value1"))
                .AddButton(winrt::AppNotificationButton(L"content").AddArgument(L"key2", L"value2"))
                .AddButton(winrt::AppNotificationButton(L"content").AddArgument(L"key3", L"value3"))
                .AddButton(winrt::AppNotificationButton(L"content").AddArgument(L"key4", L"value4"))
                .AddButton(winrt::AppNotificationButton(L"content").AddArgument(L"key5", L"value5"))
                .AddButton(winrt::AppNotificationButton(L"content").AddArgument(L"key6", L"value6")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithProtocolActivation)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                .SetInvokeUri(c_sampleUri))
            };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='http://www.microsoft.com/' activationType='protocol'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithProperties)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetButtonStyle(winrt::AppNotificationButtonStyle::Success)
                .SetIcon(c_sampleUri)
                .SetInputId(L"inputId")
                .SetToolTip(L"toolTip"))
            };
            auto expected{ L"<toast useButtonStyle='true'><visual><binding template='ToastGeneric'></binding></visual><actions><action content='content' arguments='key=value' imageUri='http://www.microsoft.com/' hint-inputId='inputId' hint-buttonStyle='Success' hint-toolTip='toolTip'/></actions></toast>"};

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithEmptyKey)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                    .AddArgument(L"", L"value")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddButtonWithArgumentAndProtocol)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                    .AddArgument(L"key", L"value")
                    .SetInvokeUri(c_sampleUri)), E_INVALIDARG);

            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddButton(winrt::AppNotificationButton(L"content")
                    .SetInvokeUri(c_sampleUri)
                    .AddArgument(L"key", L"value")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithUri)
        {
            auto builder{ winrt::AppNotificationBuilder()
                    .SetAudioUri(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio src='http://www.microsoft.com/'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithUriAndDuration)
        {
            auto builder{ winrt::AppNotificationBuilder()
                    .SetDuration(winrt::AppNotificationDuration::Long)
                    .SetAudioUri(c_sampleUri, winrt::AppNotificationAudioLooping::Loop) };
            auto expected{ L"<toast duration='long'><visual><binding template='ToastGeneric'></binding></visual><audio src='http://www.microsoft.com/' loop='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithSoundEvent)
        {
            auto builder{ winrt::AppNotificationBuilder()
                    .SetAudioEvent(winrt::AppNotificationSoundEvent::Reminder) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio src='ms-winsoundevent:Notification.Reminder'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithSoundEventAndDuration)
        {
            auto builder{ winrt::AppNotificationBuilder()
                    .SetDuration(winrt::AppNotificationDuration::Long)
                    .SetAudioEvent(winrt::AppNotificationSoundEvent::Reminder, winrt::AppNotificationAudioLooping::Loop) };
            auto expected{ L"<toast duration='long'><visual><binding template='ToastGeneric'></binding></visual><audio src='ms-winsoundevent:Notification.Reminder' loop='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderMuteAudio)
        {
            auto builder{ winrt::AppNotificationBuilder().MuteAudio() };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio silent='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

    };
}
