// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "PackagedTests.h"

void PackagedTests::VerifyRegisterActivatorandUnregisterActivator()
{
    BaseTestSuite::VerifyRegisterActivatorandUnregisterActivator();
}

void PackagedTests::VerifyFailedMultipleRegister()
{
    BaseTestSuite::VerifyFailedMultipleRegister();
}

void PackagedTests::VerifyUnregisterAll()
{
    BaseTestSuite::VerifyUnregisterAll();
}

void PackagedTests::VerifyUnregisterTwice()
{
    BaseTestSuite::VerifyUnregisterTwice();
}

void PackagedTests::VerifyToastSettingEnabled()
{
    BaseTestSuite::VerifyToastSettingEnabled();
}

void PackagedTests::VerifyToastPayload()
{
    BaseTestSuite::VerifyToastPayload();
}

void PackagedTests::VerifyToastTag()
{
    BaseTestSuite::VerifyToastTag();
}

void PackagedTests::VerifyToastGroup()
{
    BaseTestSuite::VerifyToastGroup();
}

void PackagedTests::VerifyToastProgressDataFromToast()
{
    BaseTestSuite::VerifyToastProgressDataFromToast();
}

void PackagedTests::VerifyToastExpirationTime()
{
    BaseTestSuite::VerifyToastExpirationTime();
}

void PackagedTests::VerifyToastPriority()
{
    BaseTestSuite::VerifyToastPriority();
}

void PackagedTests::VerifyToastSuppressDisplay()
{
    BaseTestSuite::VerifyToastSuppressDisplay();
}

void PackagedTests::VerifyToastExpiresOnReboot()
{
    BaseTestSuite::VerifyToastExpiresOnReboot();
}

void PackagedTests::VerifyToastProgressDataSequence0Fail()
{
    BaseTestSuite::VerifyToastProgressDataSequence0Fail();
}

void PackagedTests::VerifyShowToast()
{
    BaseTestSuite::VerifyShowToast();
}

void PackagedTests::VerifyUpdateToastProgressDataUsingValidTagAndValidGroup()
{
    BaseTestSuite::VerifyUpdateToastProgressDataUsingValidTagAndValidGroup();
}

void PackagedTests::VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup()
{
    BaseTestSuite::VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup();
}

void PackagedTests::VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup()
{
    BaseTestSuite::VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup();
}

void PackagedTests::VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup()
{
    BaseTestSuite::VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup();
}

void PackagedTests::VerifyFailedUpdateNotificationDataWithoutPostToast()
{
    BaseTestSuite::VerifyFailedUpdateNotificationDataWithoutPostToast();
}

void PackagedTests::VerifyGetAllAsyncWithZeroActiveToast()
{
    BaseTestSuite::VerifyGetAllAsyncWithZeroActiveToast();
}

void PackagedTests::VerifyGetAllAsyncWithOneActiveToast()
{
    BaseTestSuite::VerifyGetAllAsyncWithZeroActiveToast();
}

void PackagedTests::VerifyGetAllAsyncWithMultipleActiveToasts()
{
    BaseTestSuite::VerifyGetAllAsyncWithMultipleActiveToasts();
}

void PackagedTests::VerifyGetAllAsyncIgnoresUpdatesToProgressData()
{
    BaseTestSuite::VerifyGetAllAsyncIgnoresUpdatesToProgressData();
}

void PackagedTests::VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier()
{
    BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier();
}

void PackagedTests::VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow();
}

void PackagedTests::VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier()
{
    BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier();
}

void PackagedTests::VerifyRemoveWithTagAsyncUsingEmptyTagThrows()
{
    BaseTestSuite::VerifyRemoveWithTagAsyncUsingEmptyTagThrows();
}

void PackagedTests::VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow();
}

void PackagedTests::VerifyRemoveWithTagAsync()
{
    BaseTestSuite::VerifyRemoveWithTagAsync();
}

void PackagedTests::VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows()
{
    BaseTestSuite::VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows();
}

void PackagedTests::VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows()
{
    BaseTestSuite::VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows();
}

void PackagedTests::VerifyRemoveWithTagGroupAsync()
{
    BaseTestSuite::VerifyRemoveWithTagGroupAsync();
}

void PackagedTests::VerifyRemoveGroupAsyncUsingEmptyGroupThrows()
{
    BaseTestSuite::VerifyRemoveGroupAsyncUsingEmptyGroupThrows();
}

void PackagedTests::VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow();
}

void PackagedTests::VerifyRemoveGroupAsync()
{
    BaseTestSuite::VerifyRemoveGroupAsync();
}

void PackagedTests::VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow();
}

void PackagedTests::VerifyRemoveAllAsync()
{
    BaseTestSuite::VerifyRemoveAllAsync();
}

void PackagedTests::VerifyToastConferencingConfigAllDevicesSet()
{
    BaseTestSuite::VerifyToastConferencingConfigAllDevicesSet();
}

void PackagedTests::VerifyToastConferencingConfigNotAllDevicesSet()
{
    BaseTestSuite::VerifyToastConferencingConfigNotAllDevicesSet();
}

void PackagedTests::VerifyToastConferencingConfigNoDevicesSet()
{
    BaseTestSuite::VerifyToastConferencingConfigNoDevicesSet();
}

void PackagedTests::VerifyToastConferencingConfigWithIsCallingPreviewSupportedFalse()
{
    BaseTestSuite::VerifyToastConferencingConfigWithIsCallingPreviewSupportedFalse();
}
