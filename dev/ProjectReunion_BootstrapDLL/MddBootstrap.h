// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MSIXDYNAMICDEPENDENCY_H)
#define MSIXDYNAMICDEPENDENCY_H

STDAPI MddBootstrapInitialize(
    const CLSID& appDynamicDependencyLifetimeManager);

STDAPI MddBootstrapShutdown();

#endif // MSIXDYNAMICDEPENDENCY_H
