// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Globalization.ApplicationLanguages.g.h"

namespace winrt::Microsoft::Windows::Globalization::implementation
{
    struct ApplicationLanguages
    {
        ApplicationLanguages() = delete;

        static winrt::Windows::Foundation::Collections::IVectorView<hstring> Languages();
        static winrt::Windows::Foundation::Collections::IVectorView<hstring> ManifestLanguages();
        static hstring PrimaryLanguageOverride();
        static void PrimaryLanguageOverride(hstring const& language);

    private:
        static hstring m_language;
        static wil::srwlock m_lock;
    };
} // namespace winrt::Microsoft::Windows::Globalization::implementation

namespace winrt::Microsoft::Windows::Globalization::factory_implementation
{
    struct ApplicationLanguages : ApplicationLanguagesT<ApplicationLanguages, implementation::ApplicationLanguages>
    {
    };
} // namespace winrt::Microsoft::Windows::Globalization::factory_implementation
