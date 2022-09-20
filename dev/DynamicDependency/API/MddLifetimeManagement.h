// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MDDLIFETIMEMANAGEMENT_H)
#define MDDLIFETIMEMANAGEMENT_H

/// Remove unnecessary Dynamic Dependency Lifetime Management (DDLM) packages.
///
/// A DDLM package can be removed if it's not in-use and a newer version is available.
STDAPI MddLifetimeManagementGC() noexcept;

#endif // MDDLIFETIMEMANAGEMENT_H
