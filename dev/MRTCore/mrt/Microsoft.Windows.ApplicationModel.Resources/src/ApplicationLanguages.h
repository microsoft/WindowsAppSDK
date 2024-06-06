// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ApplicationLanguages.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
    struct ApplicationLanguages
    {
        ApplicationLanguages() = delete;

        static hstring PrimaryLanguageOverride();
        static void PrimaryLanguageOverride(hstring const& language);

    private:
        static hstring m_language;
    };
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
{
    struct ApplicationLanguages : ApplicationLanguagesT<ApplicationLanguages, implementation::ApplicationLanguages>
    {
    };
} // winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
