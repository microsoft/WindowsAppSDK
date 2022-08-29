// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once

static const std::wstring c_appNotificationFakeAUMID = L"AUMID";

// COM server values in NotificationActivationPackage appxmanifest
inline IID c_appNotificationComServerId = winrt::guid("FE8C7374-A28F-4CBE-8D28-4288CBDFD431");
inline IID c_pushNotificationComServerId = winrt::guid("ccd2ae3f-764f-4ae3-be45-9804761b28b2");

// COM server values in NotificationActivation-AppxManifest.xml
inline IID c_taefAppNotificationComServerId = winrt::guid("6EDF15AA-220A-40A2-824F-E508523911EB");
inline IID c_taefPushNotificationComServerId = winrt::guid("9A1B4D2C-B5BE-49DC-A3C3-49CD690D3BEE");
