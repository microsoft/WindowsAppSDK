// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDBOOSTRAP_H)
#define MDDBOOSTRAP_H

STDAPI MddBootstrapInitialize(
    const PACKAGE_VERSION minVersion) noexcept;

STDAPI_(void) MddBootstrapShutdown() noexcept;

#endif // MDDBOOSTRAP_H
