// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "BaseTestSuite.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

class PackagedTests : BaseTestSuite
{
    BEGIN_TEST_CLASS(PackagedTests)
        TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")
        TEST_CLASS_PROPERTY(L"Data:SelfContained", L"{true, false}")
        TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
        TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCWA")
        TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"AppNotifications-AppxManifest.xml")
    END_TEST_CLASS()

    TEST_CLASS_SETUP(ClassInit)
    {
        BaseTestSuite::ClassSetup();
        return true;
    }

    TEST_CLASS_CLEANUP(ClassUninit)
    {
        BaseTestSuite::ClassCleanup();
        return true;
    }

    TEST_METHOD_SETUP(MethodInit)
    {
        BaseTestSuite::MethodSetup();
        return true;
    }

    TEST_METHOD_CLEANUP(MethodUninit)
    {
        BaseTestSuite::MethodCleanup();
        return true;
    }

    TEST_METHOD(VerifyRegisterActivatorandUnregisterActivator);
    TEST_METHOD(VerifyFailedMultipleRegister);
    TEST_METHOD(VerifyUnregisterAll);
    TEST_METHOD(VerifyUnregisterTwice);
    TEST_METHOD(VerifyToastSettingEnabled);
    TEST_METHOD(VerifyToastPayload);
    TEST_METHOD(VerifyToastTag);
    TEST_METHOD(VerifyToastGroup);
    TEST_METHOD(VerifyToastProgressDataFromToast);
    TEST_METHOD(VerifyToastExpirationTime);
    TEST_METHOD(VerifyToastPriority);
    TEST_METHOD(VerifyToastSuppressDisplay);
    TEST_METHOD(VerifyToastExpiresOnReboot);
    TEST_METHOD(VerifyToastProgressDataSequence0Fail);
    TEST_METHOD(VerifyShowToast);
    TEST_METHOD(VerifyUpdateToastProgressDataUsingValidTagAndValidGroup);
    TEST_METHOD(VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup);
    TEST_METHOD(VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup);
    TEST_METHOD(VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup);
    TEST_METHOD(VerifyFailedUpdateNotificationDataWithoutPostToast);
    TEST_METHOD(VerifyGetAllAsyncWithZeroActiveToast);
    TEST_METHOD(VerifyGetAllAsyncWithOneActiveToast);
    TEST_METHOD(VerifyGetAllAsyncWithMultipleActiveToasts);
    TEST_METHOD(VerifyGetAllAsyncIgnoresUpdatesToProgressData);
    TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier);
    TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow);
    TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier);
    TEST_METHOD(VerifyRemoveWithTagAsyncUsingEmptyTagThrows);
    TEST_METHOD(VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow);
    TEST_METHOD(VerifyRemoveWithTagAsync);
    TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows);
    TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows);
    TEST_METHOD(VerifyRemoveWithTagGroupAsync);
    TEST_METHOD(VerifyRemoveGroupAsyncUsingEmptyGroupThrows);
    TEST_METHOD(VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow);
    TEST_METHOD(VerifyRemoveGroupAsync);
    TEST_METHOD(VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow);
    TEST_METHOD(VerifyRemoveAllAsync);
    TEST_METHOD(VerifyToastConferencingConfigAllDevicesSet);
    TEST_METHOD(VerifyToastConferencingConfigNotAllDevicesSet);
    TEST_METHOD(VerifyToastConferencingConfigNoDevicesSet);
    TEST_METHOD(VerifyToastConferencingConfigWithIsCallingPreviewSupportedFalse);
};

