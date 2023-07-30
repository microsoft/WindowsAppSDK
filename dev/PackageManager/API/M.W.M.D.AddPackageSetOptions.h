// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.AddPackageSetOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct AddPackageSetOptions : AddPackageSetOptionsT<AddPackageSetOptions>
    {
        AddPackageSetOptions() = default;

        bool TODO_MustHaveAtLeastOneInterfaceOrStaticFactoryPlaceholder();
        void TODO_MustHaveAtLeastOneInterfaceOrStaticFactoryPlaceholder(bool value);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct AddPackageSetOptions : AddPackageSetOptionsT<AddPackageSetOptions, implementation::AddPackageSetOptions>
    {
    };
}
