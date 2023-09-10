// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.FindPackageSetOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct FindPackageSetOptions : FindPackageSetOptionsT<FindPackageSetOptions>
    {
        FindPackageSetOptions() = default;

        bool TODO_MustHaveAtLeastOneInterfaceOrStaticFactoryPlaceholder();
        void TODO_MustHaveAtLeastOneInterfaceOrStaticFactoryPlaceholder(bool value);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct FindPackageSetOptions : FindPackageSetOptionsT<FindPackageSetOptions, implementation::FindPackageSetOptions>
    {
    };
}
