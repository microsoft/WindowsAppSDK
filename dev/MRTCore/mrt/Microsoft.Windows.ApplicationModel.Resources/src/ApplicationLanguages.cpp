// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ApplicationLanguages.h"
#include "ApplicationLanguages.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
    hstring ApplicationLanguages::m_language;

    void ApplicationLanguages::PrimaryLanguageOverride(hstring language)
    {
        m_language = language;
    }

    hstring ApplicationLanguages::PrimaryLanguageOverride()
    {
        return m_language;
    }

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
