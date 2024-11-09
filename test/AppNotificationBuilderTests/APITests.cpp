// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
    using namespace winrt::Microsoft::Windows::AppNotifications;
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
            auto time{ winrt::Windows::Foundation::DateTime::clock::now() };
            auto builder{ winrt::AppNotificationBuilder().SetTimeStamp(time) };

            struct tm dateTime {};
            auto timeAsTimeT{ winrt::clock::to_time_t(time) };
            localtime_s(&dateTime, &timeAsTimeT);

            std::wstringstream buffer;
            buffer << std::put_time(&dateTime, L"%FT%T%z");

            std::wstring expectedTimestamp{ buffer.str() };
            expectedTimestamp.insert(expectedTimestamp.size() - c_offsetIndexValue, L":");
            std::wstring expected{ wil::str_printf<std::wstring>(L"<toast displayTimestamp='%ls'><visual><binding template='ToastGeneric'></binding></visual></toast>", expectedTimestamp.c_str()) };

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

        TEST_METHOD(AppNotificationBuilderBuildNotificationWithTooLargePayload)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddText(std::wstring(5120, 'A').c_str())
                .BuildNotification(), E_FAIL);
        }

        TEST_METHOD(AppNotificationAddProgressBar)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddText(L"Downloading this week's new music...")
                .AddProgressBar(winrt::AppNotificationProgressBar()
                    .BindTitle()
                    .BindValueStringOverride()) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text>Downloading this week&apos;s new music...</text><progress title='{progressTitle}' status='{progressStatus}' value='{progressValue}' valueStringOverride='{progressValueString}'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationAddMoreThanOneProgressBar)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddText(L"Downloading this week's new music...")
                .AddProgressBar(winrt::AppNotificationProgressBar()
                    .BindTitle()
                    .BindValueStringOverride())
                .AddProgressBar(winrt::AppNotificationProgressBar()
                    .SetValue(0.8)
                    .SetStatus(L"Still downloading...")) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text>Downloading this week&apos;s new music...</text><progress title='{progressTitle}' status='{progressStatus}' value='{progressValue}' valueStringOverride='{progressValueString}'/><progress status='Still downloading...' value='0.8'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarDefaults)
        {
            auto progressBar{ winrt::AppNotificationProgressBar() };
            auto expected{ L"<progress status='{progressStatus}' value='{progressValue}'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarSetSpecificValue)
        {
            auto progressBar{ winrt::AppNotificationProgressBar() };
            progressBar.Value(0.8);
            auto expected{ L"<progress status='{progressStatus}' value='0.8'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarSetValueLargerThanOne)
        {
            auto progressBar{ winrt::AppNotificationProgressBar() };
            VERIFY_THROWS_HR(progressBar.Value(1.01), E_INVALIDARG);

            VERIFY_THROWS_HR(winrt::AppNotificationProgressBar().SetValue(1.01), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationProgressBarSetValueSmallerThanZero)
        {
            auto progressBar{ winrt::AppNotificationProgressBar() };
            VERIFY_THROWS_HR(progressBar.Value(-0.1), E_INVALIDARG);

            VERIFY_THROWS_HR(winrt::AppNotificationProgressBar().SetValue(-0.1), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationProgressBarSetSpecificValueThenChangeToBind)
        {
            auto progressBar{ winrt::AppNotificationProgressBar() };
            progressBar.Value(0.8);
            progressBar.BindValue();
            auto expected{ L"<progress status='{progressStatus}' value='{progressValue}'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarBindTitleThenChangeToSpecificText)
        {
            auto progressBar{ winrt::AppNotificationProgressBar()
                .BindTitle()
                .SetTitle(L"Specific title") };
            auto expected{ L"<progress title='Specific title' status='{progressStatus}' value='{progressValue}'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBox)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddTextBox(L"input1") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><input id='input1' type='text'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBoxWithEmptyId)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddTextBox(L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBoxWithEmptyIdAndPlaceHolderTextAndTitle)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddTextBox(L"", L"placeholder text", L"title"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTooManyTextBoxes)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddTextBox(L"input1")
                .AddTextBox(L"input2")
                .AddTextBox(L"input3")
                .AddTextBox(L"input4")
                .AddTextBox(L"input5")
                .AddTextBox(L"input6"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBoxWithPlaceHolderTextAndTitle)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddTextBox(L"some input id", L"Some placeholder text", L"A Title")};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><input id='some input id' type='text' placeHolderContent='Some placeholder text' title='A Title'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddComboBox)
        {
            auto builder{ winrt::AppNotificationBuilder()
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text")
                    .AddItem(L"item2", L"item2 text")
                    .AddItem(L"item3", L"item3 text")
                    .SetTitle(L"ComboBox Title")
                    .SetSelectedItem(L"item2"))};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><input id='comboBox1' type='selection' title='ComboBox Title' defaultInput='item2'><selection id='item1' content='item1 text'/><selection id='item2' content='item2 text'/><selection id='item3' content='item3 text'/></input></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTooManyComboBox)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddTextBox(L"input1")
                .AddTextBox(L"input2")
                .AddTextBox(L"input3")
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox2")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox3")
                    .AddItem(L"item1", L"item1 text")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTooManyInputElements)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationBuilder()
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox2")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox3")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox4")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox5")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(winrt::AppNotificationComboBox(L"comboBox6")
                    .AddItem(L"item1", L"item1 text")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationComboBoxAddTooManySelectionItems)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text")
                    .AddItem(L"item2", L"item2 text")
                    .AddItem(L"item3", L"item3 text")
                    .AddItem(L"item4", L"item4 text")
                    .AddItem(L"item5", L"item5 text")
                    .AddItem(L"item6", L"item6 text"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationComboBoxAddFiveSelectionItems)
        {
            auto comboBox{ winrt::AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text")
                    .AddItem(L"item2", L"item2 text")
                    .AddItem(L"item3", L"item3 text")
                    .AddItem(L"item4", L"item4 text")
                    .AddItem(L"item5", L"item5 text") };
            auto expected{ L"<input id='comboBox1' type='selection'><selection id='item1' content='item1 text'/><selection id='item2' content='item2 text'/><selection id='item3' content='item3 text'/><selection id='item4' content='item4 text'/><selection id='item5' content='item5 text'/></input>" };

            VERIFY_ARE_EQUAL(comboBox.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationComboBoxAddSelectionItemWithoutAnId)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationComboBox(L"comboBox1")
                .AddItem(L"", L"item text"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationComboBoxAddTwoSelectionItemsWithSameId)
        {
            auto comboBox{ winrt::AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text")
                    .AddItem(L"item1", L"item2 text") };
            auto expected{ L"<input id='comboBox1' type='selection'><selection id='item1' content='item2 text'/></input>" };

            VERIFY_ARE_EQUAL(comboBox.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationComboBoxSetSelectedItemWithoutAnId)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationComboBox(L"comboBox1")
                .SetSelectedItem(L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationCreateComboBoxWithoutAnId)
        {
            VERIFY_THROWS_HR(winrt::AppNotificationComboBox(L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderEscapeXmlCharacters)
        {
            auto builder{ winrt::AppNotificationBuilder().AddText(LR"(&"'<>)") };
            std::wstring expected{ L"<toast><visual><binding template='ToastGeneric'><text>&amp;&quot;&apos;&lt;&gt;</text></binding></visual></toast>"};

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderArgumentsWithXmlCharacters)
        {
            auto builder{ winrt::AppNotificationBuilder()
                            .AddArgument(LR"(&;"='%<>)", L"")
                            .AddArgument(LR"(&"'<>)", L";=%")};

            std::wstring expected{ L"<toast launch='&amp;%3B&quot;%3D&apos;%25&lt;&gt;;&amp;&quot;&apos;&lt;&gt;=%3B%3D%25'><visual><binding template='ToastGeneric'></binding></visual></toast>" };
            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);

            VERIFY_ARE_EQUAL(Decode(LR"(&%3B"%3D'%25<>)"), LR"(&;"='%<>)");
            VERIFY_ARE_EQUAL(Decode(L"%3B%3D%25"), L";=%");
        }

        TEST_METHOD(AppNotificationBuilderWithCameraPreview)
        {
            if (!winrt::AppNotificationConferencingConfig::IsCallingPreviewSupported())
            {
                return;
            }

            auto builder{ winrt::AppNotificationBuilder()
                .AddCameraPreview()
                .AddButton(winrt::AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetButtonStyle(winrt::AppNotificationButtonStyle::Success)
                .SetIcon(c_sampleUri)
                .SetInputId(L"inputId")
                .SetToolTip(L"toolTip"))
            };

            auto expected{ L"<toast useButtonStyle='true'><visual><binding template='ToastGeneric'><cameraPreview/></binding></visual><actions><action content='content' arguments='key=value' imageUri='http://www.microsoft.com/' hint-inputId='inputId' hint-buttonStyle='Success' hint-toolTip='toolTip'/></actions></toast>" };
            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderWithCameraPreviewAndVideoCallSettingsButton)
        {
            if (!winrt::AppNotificationConferencingConfig::IsCallingPreviewSupported())
            {
                return;
            }

            auto builder{ winrt::AppNotificationBuilder()
                .AddCameraPreview()
                .AddButton(winrt::AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetButtonStyle(winrt::AppNotificationButtonStyle::Success)
                .SetIcon(c_sampleUri)
                .SetInputId(L"inputId")
                .SetToolTip(L"toolTip")
                .SetSettingStyle(winrt::AppNotificationButtonSettingStyle::VideoCallConfig))
            };

            auto expected{ L"<toast useButtonStyle='true'><visual><binding template='ToastGeneric'><cameraPreview/></binding></visual><actions><action content='content' arguments='key=value' imageUri='http://www.microsoft.com/' hint-inputId='inputId' hint-buttonStyle='Success' hint-toolTip='toolTip' settingType='videoDevices'/></actions></toast>" };
            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderWithCameraPreviewAndAudioCallSettingsButton)
        {
            if (!winrt::AppNotificationConferencingConfig::IsCallingPreviewSupported())
            {
                return;
            }

            auto builder{ winrt::AppNotificationBuilder()
                .AddCameraPreview()
                .AddButton(winrt::AppNotificationButton(L"content")
                .AddArgument(L"key", L"value")
                .SetButtonStyle(winrt::AppNotificationButtonStyle::Success)
                .SetIcon(c_sampleUri)
                .SetInputId(L"inputId")
                .SetToolTip(L"toolTip")
                .SetSettingStyle(winrt::AppNotificationButtonSettingStyle::AudioCallConfig))
            };

            auto expected{ L"<toast useButtonStyle='true'><visual><binding template='ToastGeneric'><cameraPreview/></binding></visual><actions><action content='content' arguments='key=value' imageUri='http://www.microsoft.com/' hint-inputId='inputId' hint-buttonStyle='Success' hint-toolTip='toolTip' settingType='audioDevices'/></actions></toast>" };
            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderWithIsCallingPreviewSupportedIsFalse)
        {
            if (!winrt::AppNotificationConferencingConfig::IsCallingPreviewSupported())
            {
                VERIFY_THROWS_HR(winrt::AppNotificationBuilder().AddCameraPreview(), E_NOTIMPL);

                VERIFY_THROWS_HR(winrt::AppNotificationBuilder().AddButton(winrt::AppNotificationButton(L"content")
                    .SetSettingStyle(winrt::AppNotificationButtonSettingStyle::AudioCallConfig)), E_NOTIMPL);
            }
        }
    };
}
