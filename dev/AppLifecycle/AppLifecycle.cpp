// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <AppLifecycle.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Windows::ApplicationModel::Activation::IActivatedEventArgs AppLifecycle::GetActivatedEventArgs()
    {
        return nullptr;
    }
}
