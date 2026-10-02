// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

#include "M.W.M.D.PackageDeploymentManager.h"

DECLARE_TRACELOGGING_CLASS(PackageVolumeTelemetryProvider,
    "Microsoft.WindowsAppSDK.Deployment.PackageVolumeTelemetry",
    // {e1647c65-18e6-413d-8f81-28ab44c0f4f0}
    (0xe1647c65, 0x18e6, 0x413d, 0x8f, 0x81, 0x28, 0xab, 0x44, 0xc0, 0xf4, 0xf0));

class PackageVolumeTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PackageVolumeTelemetry, PackageVolumeTelemetryProvider);

public:
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Add, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageStorePath) noexcept try
        {
            TraceLoggingClassWriteStart(
                Add,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageStorePath.c_str(), "PackageStorePath"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& mountPoint, winrt::hstring const& name, winrt::hstring const& packageStorePath) noexcept try
        {
            TraceLoggingClassWriteStop(
                Add,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(mountPoint.c_str(), "MountPoint"),
                TraceLoggingWideString(name.c_str(), "Name"),
                TraceLoggingWideString(packageStorePath.c_str(), "PackageStorePath"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(Remove, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& mountPoint, winrt::hstring const& name, winrt::hstring const& packageStorePath) noexcept try
        {
            TraceLoggingClassWriteStart(
                Remove,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(mountPoint.c_str(), "MountPoint"),
                TraceLoggingWideString(name.c_str(), "Name"),
                TraceLoggingWideString(packageStorePath.c_str(), "PackageStorePath"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP() noexcept try
        {
            TraceLoggingClassWriteStop(
                Remove,
                _GENERIC_PARTB_FIELDS_ENABLED);
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetOffline, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& mountPoint, winrt::hstring const& name, winrt::hstring const& packageStorePath) noexcept try
        {
            TraceLoggingClassWriteStart(
                SetOffline,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(mountPoint.c_str(), "MountPoint"),
                TraceLoggingWideString(name.c_str(), "Name"),
                TraceLoggingWideString(packageStorePath.c_str(), "PackageStorePath"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP() noexcept try
        {
            TraceLoggingClassWriteStop(
                SetOffline,
                _GENERIC_PARTB_FIELDS_ENABLED);
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(SetOnline, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& mountPoint, winrt::hstring const& name, winrt::hstring const& packageStorePath) noexcept try
        {
            TraceLoggingClassWriteStart(
                SetOnline,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(mountPoint.c_str(), "MountPoint"),
                TraceLoggingWideString(name.c_str(), "Name"),
                TraceLoggingWideString(packageStorePath.c_str(), "PackageStorePath"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP() noexcept try
        {
            TraceLoggingClassWriteStop(
                SetOnline,
                _GENERIC_PARTB_FIELDS_ENABLED);
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(GetAvailableSpace, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& mountPoint, winrt::hstring const& name, winrt::hstring const& packageStorePath) noexcept try
        {
            TraceLoggingClassWriteStart(
                GetAvailableSpace,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(mountPoint.c_str(), "MountPoint"),
                TraceLoggingWideString(name.c_str(), "Name"),
                TraceLoggingWideString(packageStorePath.c_str(), "PackageStorePath"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(const uint64_t availableSpace) noexcept try
        {
            TraceLoggingClassWriteStop(
                GetAvailableSpace,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingUInt64(availableSpace, "AvailableSpace"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
