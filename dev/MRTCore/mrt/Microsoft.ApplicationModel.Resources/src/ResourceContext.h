// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ResourceContext.g.h"

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{

struct ResourceContext : ResourceContextT<ResourceContext>
{
    ResourceContext() = delete;
    ResourceContext(MrmContextHandle resourceContext) : m_resourceContext(resourceContext) {}
    ~ResourceContext() { MrmDestroyResourceContext(m_resourceContext); }

    Windows::Foundation::Collections::IMap<hstring, hstring> QualifierValues();

    void Apply();
    MrmContextHandle GetContextHandle() { return m_resourceContext; }

private:
    void InitializeQualifierNames();
    void InitializeQualifierValueMap();
    hstring GetLangugageContext();

    MrmContextHandle m_resourceContext = nullptr;
    com_array<hstring> m_qualifierNames;
    Windows::Foundation::Collections::IMap<hstring, hstring> m_qualifierValueMap = nullptr;
};

} // namespace winrt::Microsoft::ApplicationModel::Resources::implementation
