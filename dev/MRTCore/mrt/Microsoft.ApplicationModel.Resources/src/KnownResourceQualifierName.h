// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "KnownResourceQualifierName.g.h"

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{
    struct KnownResourceQualifierName
    {
        KnownResourceQualifierName() = default;

        static hstring Contrast();
        static hstring Custom();
        static hstring DeviceFamily();
        static hstring HomeRegion();
        static hstring Language();
        static hstring LayoutDirection();
        static hstring Scale();
        static hstring TargetSize();
        static hstring Theme();
    };
}
namespace winrt::Microsoft::ApplicationModel::Resources::factory_implementation
{
    struct KnownResourceQualifierName : KnownResourceQualifierNameT<KnownResourceQualifierName, implementation::KnownResourceQualifierName>
    {
    };
}
