// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "KnownResourceQualifierName.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
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
namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
{
    struct KnownResourceQualifierName : KnownResourceQualifierNameT<KnownResourceQualifierName, implementation::KnownResourceQualifierName>
    {
    };
}
