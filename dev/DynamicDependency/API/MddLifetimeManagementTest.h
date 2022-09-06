// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MDDLIFETIMEMANAGEMENTTEST_H)
#define MDDLIFETIMEMANAGEMENTTEST_H

/// Initialize the LifetimeManagement API's test support. This will constrain DDLM enumeration
/// and matching for test purposes.
///
/// @param ddlmPackageNamePrefix only match DDLM packages with Name starting with this value
/// @param ddlmPackagePublisherId only match DDLM packages with this PublisherId
///
/// @note Not for product use. This is for for test purposes only to verify the implementation.
STDAPI MddLifetimeManagementTestInitialize(
    _In_ PCWSTR ddlmPackageNamePrefix,
    _In_ PCWSTR ddlmPackagePublisherId) noexcept;

#endif // MDDLIFETIMEMANAGEMENTTEST_H
