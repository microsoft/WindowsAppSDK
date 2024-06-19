// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ApplicationLanguages.h"
#include "ApplicationLanguages.g.cpp"

#include <winrt/Windows.Globalization.h>

#include <AppModel.Identity.h>

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
        static wil::srwlock lock;

        auto criticalSection{ lock.lock_shared() };
        return m_language;
    }

    void ApplicationLanguages::PrimaryLanguageOverride(hstring const& language)
    {
        if (AppModel::Identity::IsPackagedProcess())
        {
            winrt::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride(language);
        }
        else
        {
            static wil::srwlock lock;

            auto criticalSection{ lock.lock_exclusive() };
            m_language = language;
        }
    }
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
