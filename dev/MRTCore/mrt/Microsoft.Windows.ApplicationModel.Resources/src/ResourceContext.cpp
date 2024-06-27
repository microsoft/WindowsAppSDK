// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ResourceContext.h"
#include "ResourceContext.g.cpp"
#include "winrt/Windows.Globalization.h"

const wchar_t c_languageQualifierName[] = L"Language";

#include "ApplicationLanguages.h"

using namespace winrt::Microsoft::Windows::Globalization;

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
void ResourceContext::InitializeQualifierNames()
{
    // m_resourceContext can be null when resource is not in a PRI file.
    if (m_resourceContext != nullptr)
    {
        UINT size;
        PWSTR* names;
        winrt::check_hresult(MrmGetAllQualifierNames(m_resourceContext, &size, &names));

        m_qualifierNames = winrt::com_array<hstring>(size);

        PWSTR* eachName = names;
        for (UINT i = 0; i < size; i++)
        {
            m_qualifierNames[i] = hstring(*eachName);
            MrmFreeResource(*eachName);
            eachName++;
        }
        MrmFreeResource(names);
    }
    else
    {
        // We always have Language.
        m_qualifierNames = winrt::com_array<hstring>(1);
        m_qualifierNames[0] = c_languageQualifierName;
    }
}

void ResourceContext::InitializeQualifierValueMap()
{
    std::call_once(m_areQualifierNamesAndValueMapInitialized, [this] {
        InitializeQualifierNames();

        m_qualifierValueMap = single_threaded_map<hstring, hstring>();

        if (m_resourceContext != nullptr)
        {
            for (uint32_t i = 0; i < m_qualifierNames.size(); i++)
            {
                // Override the default behavior
                if (m_qualifierNames[i] == c_languageQualifierName)
                {
                    auto languages = GetLangugageContext();
                    if (!languages.empty())
                    {
                        m_qualifierValueMap.Insert(m_qualifierNames[i], languages);
                        continue;
                    }
                }

                wchar_t* value;
                winrt::check_hresult(MrmGetQualifier(m_resourceContext, m_qualifierNames[i].c_str(), &value));
                string_resoure_ptr stringValue(value);
                m_qualifierValueMap.Insert(m_qualifierNames[i], stringValue.get());
            }
        }
        else
        {
            m_qualifierValueMap.Insert(c_languageQualifierName, GetLangugageContext());
        }
    });
}

winrt::Windows::Foundation::Collections::IMap<hstring, hstring> ResourceContext::QualifierValues()
{
    InitializeQualifierValueMap();

    return m_qualifierValueMap;
}

void ResourceContext::Apply()
{
    if (m_resourceContext == nullptr)
    {
        // Resource not handled by MRT. Nothing to apply.
        return;
    }

    InitializeQualifierValueMap();

    for (auto const& eachValue : m_qualifierValueMap)
    {
        if (!eachValue.Value().empty())
        {
            winrt::check_hresult(MrmSetQualifier(m_resourceContext, eachValue.Key().c_str(), eachValue.Value().c_str()));
        }
    }
    if (!ApplicationLanguages::PrimaryLanguageOverride().empty())
    {
        winrt::check_hresult(MrmSetQualifier(m_resourceContext, c_languageQualifierName, ApplicationLanguages::PrimaryLanguageOverride().c_str()));
    }
}

hstring ResourceContext::GetLangugageContext()
{
    hstring context;
    try
    {
        // Use Application Languages
        auto languages = winrt::Windows::Globalization::ApplicationLanguages::Languages();

        for (auto const& lang : languages)
        {
            context = context + lang + L";";
        }
    }
    catch (...)
    {
        return hstring();
    }

    return context;
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
