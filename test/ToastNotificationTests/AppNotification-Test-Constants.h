// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

inline const winrt::hstring c_rawNotificationPayload = L"<toast></toast>";
inline const std::chrono::seconds c_timeout = std::chrono::seconds(300);
inline IID c_toastComServerId = winrt::guid("1940dba9-0f64-4f0d-8a4b-5d207b812e61"); // Value from ToastNotificationsTestAppPackage ComActivator in appxmanifest.
