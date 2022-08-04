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

        TEST_METHOD(AppNotificationBuilderAddButtonWithProtocolActivation)
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

        TEST_METHOD(AppNotificationBuilderAddButtonWithArgumentAndProtocol)
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

        TEST_METHOD(AppNotificationBuilderSetAudioWithUri)
        {
            auto builder{ AppNotificationBuilder()
                    .SetAudioUri(c_sampleUri) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio src='http://www.microsoft.com/'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithUriAndDuration)
        {
            auto builder{ AppNotificationBuilder()
                    .SetDuration(AppNotificationDuration::Long)
                    .SetAudioUri(c_sampleUri, AppNotificationAudioLooping::Loop) };
            auto expected{ L"<toast duration='long'><visual><binding template='ToastGeneric'></binding></visual><audio src='http://www.microsoft.com/' loop='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithSoundEvent)
        {
            auto builder{ AppNotificationBuilder()
                    .SetAudioEvent(AppNotificationSoundEvent::Reminder) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio src='ms-winsoundevent:Notification.Reminder'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderSetAudioWithSoundEventAndDuration)
        {
            auto builder{ AppNotificationBuilder()
                    .SetDuration(AppNotificationDuration::Long)
                    .SetAudioEvent(AppNotificationSoundEvent::Reminder, AppNotificationAudioLooping::Loop) };
            auto expected{ L"<toast duration='long'><visual><binding template='ToastGeneric'></binding></visual><audio src='ms-winsoundevent:Notification.Reminder' loop='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderMuteAudio)
        {
            auto builder{ AppNotificationBuilder().MuteAudio() };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><audio silent='true'/></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderBuildNotificationWithTooLargePayload)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddText(std::wstring(5120, 'A').c_str())
                .BuildNotification(), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationAddProgressBar)
        {
            auto builder{ AppNotificationBuilder()
                .AddText(L"Downloading this week's new music...")
                .AddProgressBar(AppNotificationProgressBar()
                    .BindTitle()
                    .BindValueStringOverride()) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text>Downloading this week's new music...</text><progress title='{progressTitle}' status='{progressStatus}' value='{progressValue}' valueStringOverride='{progressValueString}'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationAddMoreThanOneProgressBar)
        {
            auto builder{ AppNotificationBuilder()
                .AddText(L"Downloading this week's new music...")
                .AddProgressBar(AppNotificationProgressBar()
                    .BindTitle()
                    .BindValueStringOverride())
                .AddProgressBar(AppNotificationProgressBar()
                    .SetValue(0.8)
                    .SetStatus(L"Still downloading...")) };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'><text>Downloading this week's new music...</text><progress title='{progressTitle}' status='{progressStatus}' value='{progressValue}' valueStringOverride='{progressValueString}'/><progress status='Still downloading...' value='0.8'/></binding></visual></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarDefaults)
        {
            auto progressBar{ AppNotificationProgressBar() };
            auto expected{ L"<progress status='{progressStatus}' value='{progressValue}'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarSetSpecificValue)
        {
            auto progressBar{ AppNotificationProgressBar() };
            progressBar.Value(0.8);
            auto expected{ L"<progress status='{progressStatus}' value='0.8'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarSetValueLargerThanOne)
        {
            auto progressBar{ AppNotificationProgressBar() };
            VERIFY_THROWS_HR(progressBar.Value(1.01), E_INVALIDARG);

            VERIFY_THROWS_HR(AppNotificationProgressBar().SetValue(1.01), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationProgressBarSetValueSmallerThanZero)
        {
            auto progressBar{ AppNotificationProgressBar() };
            VERIFY_THROWS_HR(progressBar.Value(-0.1), E_INVALIDARG);

            VERIFY_THROWS_HR(AppNotificationProgressBar().SetValue(-0.1), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationProgressBarSetSpecificValueThenChangeToBind)
        {
            auto progressBar{ AppNotificationProgressBar() };
            progressBar.Value(0.8);
            progressBar.BindValue();
            auto expected{ L"<progress status='{progressStatus}' value='{progressValue}'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationProgressBarBindTitleThenChangeToSpecificText)
        {
            auto progressBar{ AppNotificationProgressBar()
                .BindTitle()
                .SetTitle(L"Specific title") };
            auto expected{ L"<progress title='Specific title' status='{progressStatus}' value='{progressValue}'/>" };

            VERIFY_ARE_EQUAL(progressBar.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBox)
        {
            auto builder{ AppNotificationBuilder()
                .AddTextBox(L"input1") };
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><input id='input1' type='text'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBoxWithEmptyId)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddTextBox(L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBoxWithEmptyIdAndPlaceHolderTextAndTitle)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddTextBox(L"", L"placeholder text", L"title"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTooManyTextBoxes)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddTextBox(L"input1")
                .AddTextBox(L"input2")
                .AddTextBox(L"input3")
                .AddTextBox(L"input4")
                .AddTextBox(L"input5")
                .AddTextBox(L"input6"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTextBoxWithPlaceHolderTextAndTitle)
        {
            auto builder{ AppNotificationBuilder()
                .AddTextBox(L"some input id", L"Some placeholder text", L"A Title")};
            auto expected{ L"<toast><visual><binding template='ToastGeneric'></binding></visual><actions><input id='some input id' type='text' placeHolderContent='Some placeholder text' title='A Title'/></actions></toast>" };

            VERIFY_ARE_EQUAL(builder.BuildNotification().Payload(), expected);
        }

        TEST_METHOD(AppNotificationBuilderAddComboBox)
        {
            auto builder{ AppNotificationBuilder()
                .AddComboBox(AppNotificationComboBox(L"comboBox1")
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
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddTextBox(L"input1")
                .AddTextBox(L"input2")
                .AddTextBox(L"input3")
                .AddComboBox(AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox2")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox3")
                    .AddItem(L"item1", L"item1 text")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationBuilderAddTooManyInputElements)
        {
            VERIFY_THROWS_HR(AppNotificationBuilder()
                .AddComboBox(AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox2")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox3")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox4")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox5")
                    .AddItem(L"item1", L"item1 text"))
                .AddComboBox(AppNotificationComboBox(L"comboBox6")
                    .AddItem(L"item1", L"item1 text")), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationComboBoxAddTooManySelectionItems)
        {
            VERIFY_THROWS_HR(AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text")
                    .AddItem(L"item2", L"item2 text")
                    .AddItem(L"item3", L"item3 text")
                    .AddItem(L"item4", L"item4 text")
                    .AddItem(L"item5", L"item5 text")
                    .AddItem(L"item6", L"item6 text"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationComboBoxAddFiveSelectionItems)
        {
            auto comboBox{ AppNotificationComboBox(L"comboBox1")
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
            VERIFY_THROWS_HR(AppNotificationComboBox(L"comboBox1")
                .AddItem(L"", L"item text"), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationComboBoxAddTwoSelectionItemsWithSameId)
        {
            auto comboBox{ AppNotificationComboBox(L"comboBox1")
                    .AddItem(L"item1", L"item1 text")
                    .AddItem(L"item1", L"item2 text") };
            auto expected{ L"<input id='comboBox1' type='selection'><selection id='item1' content='item2 text'/></input>" };

            VERIFY_ARE_EQUAL(comboBox.as<winrt::Windows::Foundation::IStringable>().ToString(), expected);
        }

        TEST_METHOD(AppNotificationComboBoxSetSelectedItemWithoutAnId)
        {
            VERIFY_THROWS_HR(AppNotificationComboBox(L"comboBox1")
                .SetSelectedItem(L""), E_INVALIDARG);
        }

        TEST_METHOD(AppNotificationCreateComboBoxWithoutAnId)
        {
            VERIFY_THROWS_HR(AppNotificationComboBox(L""), E_INVALIDARG);
        }
    };
}
