// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "ActivationArguments.h"
#include "ActivationArguments.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Microsoft::ProjectReunion::ExtendedActivationKind ActivationArguments::Kind()
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::IInspectable ActivationArguments::Data()
    {
        throw hresult_not_implemented();
    }
}
