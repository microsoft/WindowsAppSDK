// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDBOOSTRAPTEST_H)
#define MDDBOOSTRAPTEST_H

/// Initialize the Bootstrap API's test support. This will constrain DDLM enumeration
/// and matching for test purposes.
///
/// @param ddlmPackageNamePrefix only match DDLM packages with Name starting with this value
/// @param ddlmPackagePublisherId only match DDLM packages with this PublisherId
///
/// @note Not for product use. This is for for test purposes only to verify the implementation. 
STDAPI MddBootstrapTestInitialize(
    _In_ PCWSTR ddlmPackageNamePrefix,
    _In_ PCWSTR ddlPackagePublisherId) noexcept;

#endif // MDDBOOSTRAPTEST_H
