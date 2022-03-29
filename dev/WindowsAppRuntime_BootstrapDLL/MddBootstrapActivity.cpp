// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "MddBootstrapActivity.h"

WindowsAppRuntime::MddBootstrap::Activity::Context& WindowsAppRuntime::MddBootstrap::Activity::Context::Get()
{
    return g_bootstrapActivityContext;
}
