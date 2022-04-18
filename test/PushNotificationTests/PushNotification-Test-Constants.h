// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

inline const winrt::hstring c_rawNotificationPayload = L"<toast></toast>";
static const std::chrono::seconds c_timeout = std::chrono::seconds(300);
inline IID c_azureRemoteId = winrt::guid(L"a2e4a323-b518-4799-9e80-0b37aeb0d225"); // Generated from ms.portal.azure.com
inline IID c_dummyRemoteId = winrt::guid(L"CA1A4AB2-AC1D-4EFC-A132-E5A191CA285A"); // Dummy guid from visual studio guid tool generator
inline IID c_remoteId = winrt::guid("A7652901-313C-4EFA-A303-95C371A00DAB");
inline IID c_comServerId = winrt::guid("ccd2ae3f-764f-4ae3-be45-9804761b28b2"); // Value from PushNotificationsTestAppPackage ComActivator in appxmanifest.
inline IID c_toastComServerId = winrt::guid("1940dba9-0f64-4f0d-8a4b-5d207b812e61"); // Value from ToastNotificationsTestAppPackage ComActivator in appxmanifest.
inline IID c_fakeComServerId = winrt::guid("00000000-0000-0000-0000-000000000001");
