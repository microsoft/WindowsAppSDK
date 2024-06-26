// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ApplicationLanguages.h"
#include "ApplicationLanguages.g.cpp"

#include <winrt/Windows.Globalization.h>

#include <AppModel.Identity.h>

#include "Helper.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
    hstring ApplicationLanguages::m_language;

    winrt::Windows::Foundation::Collections::IVectorView<hstring> ApplicationLanguages::Languages()
    {
        return winrt::Windows::Globalization::ApplicationLanguages::Languages();
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> ApplicationLanguages::ManifestLanguages()
    {
        if (AppModel::Identity::IsPackagedProcess())
        {
            return winrt::Windows::Globalization::ApplicationLanguages::ManifestLanguages();
        }
        else
        {
            return {};
        }
    }

    hstring ApplicationLanguages::PrimaryLanguageOverride()
    {
        static wil::srwlock lock;

        auto criticalSection{ lock.lock_shared() };
        return m_language;
    }

    void ApplicationLanguages::PrimaryLanguageOverride(hstring const& language)
    {
        bool isValidLanguageTag = IsWellFormedLanguageTag(language.c_str());

        THROW_HR_IF_MSG(E_INVALIDARG, isValidLanguageTag, "The parameter is incorrect");

        static wil::srwlock lock;

        auto criticalSection {lock.lock_exclusive()};
        m_language = language;

        if (AppModel::Identity::IsPackagedProcess())
        {
            winrt::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride(language);
        }
    }
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
