// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ApplicationLanguages.h"
#include "ApplicationLanguages.g.cpp"

#include <winrt/Windows.Globalization.h>

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
    hstring ApplicationLanguages::m_language;

    winrt::Windows::Foundation::Collections::IVectorView<hstring> ApplicationLanguages::Languages()
    {
        return winrt::Windows::Globalization::ApplicationLanguages::Languages();
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> ApplicationLanguages::ManifestLanguages()
    {
        return winrt::Windows::Globalization::ApplicationLanguages::ManifestLanguages();
    }

    hstring ApplicationLanguages::PrimaryLanguageOverride()
    {
        return m_language;
    }

    void ApplicationLanguages::PrimaryLanguageOverride(hstring const& language)
    {
        m_language = language;
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> ApplicationLanguages::GetLanguagesForUser(winrt::Windows::System::User const& user)
    {
        return winrt::Windows::Globalization::ApplicationLanguages::GetLanguagesForUser(user);
    }

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
