// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ApplicationLanguages.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ApplicationLanguages
{
    ApplicationLanguages() = delete;

    static void PrimaryLanguageOverride(hstring language);
    static hstring PrimaryLanguageOverride();

private:
    static hstring m_language;
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
{
    struct ApplicationLanguages : ApplicationLanguagesT<ApplicationLanguages, implementation::ApplicationLanguages>
    {
    };
}
// namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
