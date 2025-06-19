// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"
#include <StoragePickersTelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(StoragePickersTelemetryProvider,
    "Microsoft.WindowsAppSDK.Storage_PickersTelemetry",
    // {89a94de3-f004-5feb-7332-1cf297e987af}
    (0x89a94de3,0xf004,0x5feb,0x73,0x32,0x1c,0xf2,0x97,0xe9,0x87,0xaf));

class StoragePickersTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(StoragePickersTelemetry, StoragePickersTelemetryProvider);

public:
    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(FileOpenPickerPickSingleFile, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(StoragePickersTelemetryHelper& telemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                FileOpenPickerPickSingleFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName")
            );
        }
        CATCH_LOG()

        DEFINE_ACTIVITY_STOP(StoragePickersTelemetryHelper& telemetryHelper, bool const resultNotNull) noexcept try
        {
            TraceLoggingClassWriteStop(
                FileOpenPickerPickSingleFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(resultNotNull, "resultNotNull"),
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(FileOpenPickerPickMultipleFile, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(StoragePickersTelemetryHelper& telemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                FileOpenPickerPickMultipleFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()

        DEFINE_ACTIVITY_STOP(StoragePickersTelemetryHelper& telemetryHelper, bool const resultCancelled, bool const resultNotEmpty) noexcept try
        {
            TraceLoggingClassWriteStop(
                FileOpenPickerPickMultipleFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(resultCancelled, "resultCancelled"),
                TraceLoggingBool(resultNotEmpty, "resultNotEmpty"),
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(FileSavePickerPickSingleFile, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(StoragePickersTelemetryHelper& telemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                FileSavePickerPickSingleFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()

        DEFINE_ACTIVITY_STOP(StoragePickersTelemetryHelper& telemetryHelper, bool const resultNotNull) noexcept try
        {
            TraceLoggingClassWriteStop(
                FileSavePickerPickSingleFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(resultNotNull, "resultNotNull"),
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_CRITICAL_DATA_ACTIVITY_CLASS(FolderPickerPickSingleFolder, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(StoragePickersTelemetryHelper& telemetryHelper) noexcept try
        {
            TraceLoggingClassWriteStart(
                FolderPickerPickSingleFolder,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()

        DEFINE_ACTIVITY_STOP(StoragePickersTelemetryHelper& telemetryHelper, bool const resultNotNull) noexcept try
        {
            TraceLoggingClassWriteStop(
                FolderPickerPickSingleFolder,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingBool(resultNotNull, "resultNotNull"),
                TraceLoggingBool(telemetryHelper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingBool(telemetryHelper.IsRunningAsAdmin(), "IsRunningAsAdmin"),
                TraceLoggingBool(telemetryHelper.IsRunningInContainer(), "IsRunningInContainer"),
                TraceLoggingWideString(telemetryHelper.GetAppName().c_str(), "AppName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
