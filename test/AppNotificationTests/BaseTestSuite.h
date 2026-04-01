// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

class BaseTestSuite
{
    public:
        // Unit test environment functions
        void ClassSetup();
        void ClassCleanup();
        void MethodSetup();
        void MethodCleanup();

        // Base unit tests
        void VerifyRegisterActivatorandUnregisterActivator();
        void VerifyFailedMultipleRegister();
        void VerifyUnregisterAll();
        void VerifyUnregisterTwice();
        void VerifyToastSettingEnabled();
        void VerifyToastPayload();
        void VerifyToastTag();
        void VerifyToastGroup();
        void VerifyToastProgressDataFromToast();
        void VerifyToastExpirationTime();
        void VerifyToastPriority();
        void VerifyToastSuppressDisplay();
        void VerifyToastExpiresOnReboot();
        void VerifyShowToast();
        void VerifyUpdateToastProgressDataUsingValidTagAndValidGroup();
        void VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup();
        void VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup();
        void VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup();
        void VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup();
        void VerifyFailedUpdateNotificationDataWithoutPostToast();
        void VerifyGetAllAsyncWithZeroActiveToast();
        void VerifyGetAllAsyncWithOneActiveToast();
        void VerifyGetAllAsyncWithMultipleActiveToasts();
        void VerifyGetAllAsyncIgnoresUpdatesToProgressData();
        void VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier();
        void VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow();
        void VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier();
        void VerifyRemoveWithTagAsyncUsingEmptyTagThrows();
        void VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow();
        void VerifyRemoveWithTagAsync();
        void VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows();
        void VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows();
        void VerifyRemoveWithTagGroupAsync();
        void VerifyRemoveGroupAsyncUsingEmptyGroupThrows();
        void VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow();
        void VerifyRemoveGroupAsync();
        void VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow();
        void VerifyRemoveAllAsync();
        void VerifyToastProgressDataSequence0Fail();
        void VerifyIconPathExists();
        void VerifyExplicitAppId();
        void VerifyToastConferencingConfigAllDevicesSet();
        void VerifyToastConferencingConfigNotAllDevicesSet();
        void VerifyToastConferencingConfigNoDevicesSet();
        void VerifyToastConferencingConfigWithIsCallingPreviewSupportedFalse();

    private:
        void RegisterWithAppNotificationManager();
        void UnregisterAllWithAppNotificationManager();
        bool m_unregisteredFully{ true };
};
