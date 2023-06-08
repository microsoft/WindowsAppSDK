// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

inline const winrt::hstring c_rawNotificationPayload = L"<toast></toast>";
inline const std::chrono::milliseconds c_timeout{ 500 };
inline IID c_toastComServerId = winrt::guid("1940dba9-0f64-4f0d-8a4b-5d207b812e61"); // Value from ToastNotificationsTestAppPackage ComActivator in appxmanifest.
inline const std::wstring c_localWindowsAppSDKFolder{ LR"(\Microsoft\WindowsAppSDK\)" };
inline const std::wstring c_pngExtension{ LR"(.png)" };
inline const std::wstring c_appUserModelId{ L"TaefTestAppId" };
inline const std::chrono::milliseconds c_sleepTimeout{ 5000 };
inline const std::chrono::milliseconds c_delay{ 25 };
constexpr PCWSTR c_nonExistentPackage{ L"NonExistentPackage" };
