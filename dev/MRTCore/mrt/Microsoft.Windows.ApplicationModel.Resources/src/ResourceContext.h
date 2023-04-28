// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ResourceContext.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ResourceContext : ResourceContextT<ResourceContext>
{
    ResourceContext() = delete;
    ResourceContext(MrmContextHandle resourceContext) : m_resourceContext(resourceContext) {}
    ~ResourceContext();

    winrt::Windows::Foundation::Collections::IMap<hstring, hstring> QualifierValues();

    void Apply();
    MrmContextHandle GetContextHandle();

private:
    bool IsInitialized();
    void InitializeQualifierNames();
    void InitializeQualifierValueMap();
    hstring GetLangugageContext();

    slim_mutex m_lock;
    MrmContextHandle m_resourceContext = nullptr;
    com_array<hstring> m_qualifierNames;
    winrt::Windows::Foundation::Collections::IMap<hstring, hstring> m_qualifierValueMap = nullptr;
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
