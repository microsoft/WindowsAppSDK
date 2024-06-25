// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(PackageManagementTelemetryProvider,
    "Microsoft.WindowsAppSDK.Deployment.PackageManagementTelemetry",
    // {90ffebd9-9489-473d-9b38-7658b4826270}
    (0x90ffebd9, 0x9489, 0x473d, 0x9b, 0x38, 0x76, 0x58, 0xb4, 0x82, 0x62, 0x70));

class PackageManagementTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PackageManagementTelemetry, PackageManagementTelemetryProvider);

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(AddPackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                AddPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                AddPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(AddPackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                AddPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                AddPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(AddPackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                AddPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                AddPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(DeprovisionPackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                DeprovisionPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                DeprovisionPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(DeprovisionPackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                DeprovisionPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                DeprovisionPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(DeprovisionPackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                DeprovisionPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                DeprovisionPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(EnsurePackageReadyAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                EnsurePackageReadyAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                EnsurePackageReadyAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(EnsurePackageReadyByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                EnsurePackageReadyByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                EnsurePackageReadyByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(EnsurePackageSetReadyAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                EnsurePackageSetReadyAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                EnsurePackageSetReadyAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(IsPackageRegistrationPending, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageFamilyName) noexcept try
        {
            TraceLoggingClassWriteStart(
                IsPackageRegistrationPending,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageFamilyName.c_str(), "PackageFamilyName"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageFamilyName) noexcept try
        {
            TraceLoggingClassWriteStop(
                IsPackageRegistrationPending,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageFamilyName.c_str(), "PackageFamilyName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(IsPackageRegistrationPendingForUser, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& userSecurityId, winrt::hstring const& packageFamilyName) noexcept try
        {
            TraceLoggingClassWriteStart(
                IsPackageRegistrationPendingForUser,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(userSecurityId.c_str(), "UserSecurityId"),
                TraceLoggingWideString(packageFamilyName.c_str(), "PackageFamilyName"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& userSecurityId, winrt::hstring const& packageFamilyName) noexcept try
        {
            TraceLoggingClassWriteStop(
                IsPackageRegistrationPendingForUser,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(userSecurityId.c_str(), "UserSecurityId"),
                TraceLoggingWideString(packageFamilyName.c_str(), "PackageFamilyName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ProvisionPackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                ProvisionPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                ProvisionPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ProvisionPackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                ProvisionPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                ProvisionPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ProvisionPackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                ProvisionPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                ProvisionPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RegisterPackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                RegisterPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                RegisterPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RegisterPackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                RegisterPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                RegisterPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RegisterPackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RegisterPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                RegisterPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RegisterPackageByPackageFamilyNameAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packagePackageFamilyName) noexcept try
        {
            TraceLoggingClassWriteStart(
                RegisterPackageByPackageFamilyNameAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packagePackageFamilyName.c_str(), "PackageFamilyName"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packagePackageFamilyName) noexcept try
        {
            TraceLoggingClassWriteStop(
                RegisterPackageByPackageFamilyNameAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packagePackageFamilyName.c_str(), "PackageFamilyName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RegisterPackageByPackageFullNameAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packagePackageFullName) noexcept try
        {
            TraceLoggingClassWriteStart(
                RegisterPackageByPackageFullNameAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packagePackageFullName.c_str(), "PackageFullName"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packagePackageFullName) noexcept try
        {
            TraceLoggingClassWriteStop(
                RegisterPackageByPackageFullNameAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packagePackageFullName.c_str(), "PackageFullName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemovePackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemovePackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                RemovePackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemovePackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemovePackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                RemovePackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RemovePackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RemovePackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                RemovePackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ResetPackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                ResetPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                ResetPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ResetPackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                ResetPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                ResetPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ResetPackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                ResetPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                ResetPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RepairPackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                RepairPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                RepairPackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RepairPackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                RepairPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                RepairPackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(RepairPackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                RepairPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                RepairPackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(StagePackageAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStart(
                StagePackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& package) noexcept try
        {
            TraceLoggingClassWriteStop(
                StagePackageAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(package.c_str(), "Package"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(StagePackageByUriAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStart(
                StagePackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageUri) noexcept try
        {
            TraceLoggingClassWriteStop(
                StagePackageByUriAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageUri.c_str(), "PackageUri"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(StagePackageSetAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStart(
                StagePackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
        DEFINE_ACTIVITY_STOP(winrt::hstring const& packageSetId) noexcept try
        {
            TraceLoggingClassWriteStop(
                StagePackageSetAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageSetId.c_str(), "PackageSetId"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
