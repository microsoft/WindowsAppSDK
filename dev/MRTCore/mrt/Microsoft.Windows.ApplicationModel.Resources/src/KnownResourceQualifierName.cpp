// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "KnownResourceQualifierName.h"
#include "KnownResourceQualifierName.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
    hstring KnownResourceQualifierName::Contrast()
    {
        return hstring(L"Contrast");
    }
    hstring KnownResourceQualifierName::Custom()
    {
        return hstring(L"Custom");
    }
    hstring KnownResourceQualifierName::DeviceFamily()
    {
        return hstring(L"DeviceFamily");
    }
    hstring KnownResourceQualifierName::HomeRegion()
    {
        return hstring(L"HomeRegion");
    }
    hstring KnownResourceQualifierName::Language()
    {
        return hstring(L"Language");
    }
    hstring KnownResourceQualifierName::LayoutDirection()
    {
        return hstring(L"LayoutDirection");
    }
    hstring KnownResourceQualifierName::Scale()
    {
        return hstring(L"Scale");
    }
    hstring KnownResourceQualifierName::TargetSize()
    {
        return hstring(L"TargetSize");
    }
    hstring KnownResourceQualifierName::Theme()
    {
        return hstring(L"Theme");
    }
}
