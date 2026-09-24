// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ApplicationLanguages.h"
#include "Microsoft.Windows.Globalization.ApplicationLanguages.g.cpp"

#include <bcp47mrm.h>
#include <winrt/Windows.Globalization.h>

#include <AppModel.Identity.h>

namespace winrt::Microsoft::Windows::Globalization::implementation
{
hstring ApplicationLanguages::m_language;
wil::srwlock ApplicationLanguages::m_lock;

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
    if (AppModel::Identity::IsPackagedProcess())
    {
        try
        {
            hstring const language = winrt::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride();
            auto criticalSection {m_lock.lock_exclusive()};
            m_language = language;
            return language;
        }
        catch (...)
        {
            auto hr {wil::ResultFromCaughtException()};
            THROW_HR_MSG(hr, "Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride(get) failed for packaged process");
        }
    }

    auto criticalSection {m_lock.lock_shared()};
    return m_language;
}

void ApplicationLanguages::PrimaryLanguageOverride(hstring const& language)
{
    if (!language.empty())
    {
        bool isValidLanguageTag = IsWellFormedTag(language.c_str());
        THROW_HR_IF_MSG(E_INVALIDARG, !isValidLanguageTag, "The parameter is incorrect");
    }

    if (AppModel::Identity::IsPackagedProcess())
    {
        try
        {
            winrt::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride(language);
        }
        catch (...)
        {
            auto hr {wil::ResultFromCaughtException()};
            THROW_HR_MSG(
                hr,
                "Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride(set) failed for packaged process. language=%ls",
                language.c_str());
        }
    }

    auto criticalSection {m_lock.lock_exclusive()};
    m_language = language;
}
} // namespace winrt::Microsoft::Windows::Globalization::implementation
