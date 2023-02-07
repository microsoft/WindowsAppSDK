// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "UnpackagedTests.h"

void UnpackagedTests::VerifyRegisterActivatorandUnregisterActivator()
{
    BaseTestSuite::VerifyRegisterActivatorandUnregisterActivator();
}

void UnpackagedTests::VerifyFailedMultipleRegister()
{
    BaseTestSuite::VerifyFailedMultipleRegister();
}

void UnpackagedTests::VerifyUnregisterAll()
{
    BaseTestSuite::VerifyUnregisterAll();
}

void UnpackagedTests::VerifyUnregisterTwice()
{
    BaseTestSuite::VerifyUnregisterTwice();
}

void UnpackagedTests::VerifyToastSettingEnabled()
{
    BaseTestSuite::VerifyToastSettingEnabled();
}

void UnpackagedTests::VerifyToastPayload()
{
    BaseTestSuite::VerifyToastPayload();
}

void UnpackagedTests::VerifyToastTag()
{
    BaseTestSuite::VerifyToastTag();
}

void UnpackagedTests::VerifyToastGroup()
{
    BaseTestSuite::VerifyToastGroup();
}

void UnpackagedTests::VerifyToastProgressDataFromToast()
{
    BaseTestSuite::VerifyToastProgressDataFromToast();
}

void UnpackagedTests::VerifyToastExpirationTime()
{
    BaseTestSuite::VerifyToastExpirationTime();
}

void UnpackagedTests::VerifyToastPriority()
{
    BaseTestSuite::VerifyToastPriority();
}

void UnpackagedTests::VerifyToastSuppressDisplay()
{
    BaseTestSuite::VerifyToastSuppressDisplay();
}

void UnpackagedTests::VerifyToastExpiresOnReboot()
{
    BaseTestSuite::VerifyToastExpiresOnReboot();
}

void UnpackagedTests::VerifyToastProgressDataSequence0Fail()
{
    BaseTestSuite::VerifyToastProgressDataSequence0Fail();
}

void UnpackagedTests::VerifyShowToast()
{
    BaseTestSuite::VerifyShowToast();
}

void UnpackagedTests::VerifyUpdateToastProgressDataUsingValidTagAndValidGroup()
{
    BaseTestSuite::VerifyUpdateToastProgressDataUsingValidTagAndValidGroup();
}

void UnpackagedTests::VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup()
{
    BaseTestSuite::VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup();
}

void UnpackagedTests::VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup()
{
    BaseTestSuite::VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup();
}

void UnpackagedTests::VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup()
{
    BaseTestSuite::VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup();
}

void UnpackagedTests::VerifyFailedUpdateNotificationDataWithoutPostToast()
{
    BaseTestSuite::VerifyFailedUpdateNotificationDataWithoutPostToast();
}

void UnpackagedTests::VerifyGetAllAsyncWithZeroActiveToast()
{
    BaseTestSuite::VerifyGetAllAsyncWithZeroActiveToast();
}

void UnpackagedTests::VerifyGetAllAsyncWithOneActiveToast()
{
    BaseTestSuite::VerifyGetAllAsyncWithOneActiveToast();
}

void UnpackagedTests::VerifyGetAllAsyncWithMultipleActiveToasts()
{
    BaseTestSuite::VerifyGetAllAsyncWithMultipleActiveToasts();
}

void UnpackagedTests::VerifyGetAllAsyncIgnoresUpdatesToProgressData()
{
    BaseTestSuite::VerifyGetAllAsyncIgnoresUpdatesToProgressData();
}

void UnpackagedTests::VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier()
{
    BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier();
}

void UnpackagedTests::VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow();
}

void UnpackagedTests::VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier()
{
    BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier();
}

void UnpackagedTests::VerifyRemoveWithTagAsyncUsingEmptyTagThrows()
{
    BaseTestSuite::VerifyRemoveWithTagAsyncUsingEmptyTagThrows();
}

void UnpackagedTests::VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow();
}

void UnpackagedTests::VerifyRemoveWithTagAsync()
{
    BaseTestSuite::VerifyRemoveWithTagAsync();
}

void UnpackagedTests::VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows()
{
    BaseTestSuite::VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows();
}

void UnpackagedTests::VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows()
{
    BaseTestSuite::VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows();
}

void UnpackagedTests::VerifyRemoveWithTagGroupAsync()
{
    BaseTestSuite::VerifyRemoveWithTagGroupAsync();
}

void UnpackagedTests::VerifyRemoveGroupAsyncUsingEmptyGroupThrows()
{
    BaseTestSuite::VerifyRemoveGroupAsyncUsingEmptyGroupThrows();
}

void UnpackagedTests::VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow();
}

void UnpackagedTests::VerifyRemoveGroupAsync()
{
    BaseTestSuite::VerifyRemoveGroupAsync();
}

void UnpackagedTests::VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow()
{
    BaseTestSuite::VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow();
}

void UnpackagedTests::VerifyRemoveAllAsync()
{
    BaseTestSuite::VerifyRemoveAllAsync();
}

void UnpackagedTests::VerifyIconPathExists()
{
    BaseTestSuite::VerifyIconPathExists();
}

void UnpackagedTests::VerifyExplicitAppId()
{
    BaseTestSuite::VerifyExplicitAppId();
}
