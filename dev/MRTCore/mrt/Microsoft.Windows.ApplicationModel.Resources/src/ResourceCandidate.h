// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ResourceCandidate.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ResourceCandidate : ResourceCandidateT<ResourceCandidate>
{
    ResourceCandidate() = delete;
    ResourceCandidate(ResourceCandidateKind kind, hstring data);
    ResourceCandidate(array_view<uint8_t const> data);
    ResourceCandidate(MrmManagerHandle manager, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, ResourceCandidateKind kind, hstring data);
    ResourceCandidate(MrmManagerHandle manager, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, array_view<uint8_t const> data);

    hstring ValueAsString();
    com_array<uint8_t> ValueAsBytes();
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidateKind Kind();
    winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> QualifierValues();

    void SetQualifierValuesFromContext(Microsoft::Windows::ApplicationModel::Resources::ResourceContext context);

private:
    hstring m_stringData;
    com_array<uint8_t> m_blobData;
    ResourceCandidateKind m_kind = ResourceCandidateKind::Unknown;
    winrt::Windows::Foundation::Collections::IMap<hstring, hstring> m_qualifierValueMap = nullptr;

    // Information required to refetch the candidate for candidate qualifier values
    MrmManagerHandle m_resourceManagerHandle = nullptr;
    Microsoft::Windows::ApplicationModel::Resources::ResourceContext m_resourceContext = nullptr;
    MrmMapHandle m_resourceMapHandle = nullptr;
    uint32_t m_resourceIndex = static_cast<uint32_t>(-1);
    hstring m_resourceId;
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
{

struct ResourceCandidate : ResourceCandidateT<ResourceCandidate, implementation::ResourceCandidate>
{};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
