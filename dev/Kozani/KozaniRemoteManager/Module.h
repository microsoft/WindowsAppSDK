// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "ConnectionManager.h"

namespace KozaniRemoteManagerModule
{
    void IncrementObjectCount();
    void DecrementObjectCount();

    Microsoft::Kozani::KozaniRemoteManager::ConnectionManager& GetConnectionManagerInstance();
};

