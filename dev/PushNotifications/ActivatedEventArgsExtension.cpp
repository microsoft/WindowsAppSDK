// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ActivatedEventArgsExtension.h"
#include "ActivatedEventArgsExtension.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    ActivatedEventArgsExtension::ActivatedEventArgsExtension(Windows::ApplicationModel::Activation::IActivatedEventArgs const& activatedEventArgs, Microsoft::ProjectReunion::ActivationKindExtension const& kind2)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::ActivationKindExtension ActivatedEventArgsExtension::Kind2()
    {
        throw hresult_not_implemented();
    }
    Windows::ApplicationModel::Activation::IActivatedEventArgs ActivatedEventArgsExtension::ActivatedArgs()
    {
        throw hresult_not_implemented();
    }
}
