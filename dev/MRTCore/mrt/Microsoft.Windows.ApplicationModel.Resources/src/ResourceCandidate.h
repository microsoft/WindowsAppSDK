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

    // Adopting constructors: take ownership of a loader-provided embedded resource buffer (freed via
    // MrmFreeResource) instead of copying it. This avoids duplicating memory that already lives in a
    // heap copy owned by the MRT Core loader (see ADO #61159271).
    ResourceCandidate(embedded_resoure_ptr&& data, uint32_t size);
    ResourceCandidate(MrmManagerHandle manager, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, embedded_resoure_ptr&& data, uint32_t size);

    hstring ValueAsString();
    com_array<uint8_t> ValueAsBytes();
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidateKind Kind();
    winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> QualifierValues();

    void SetQualifierValuesFromContext(Microsoft::Windows::ApplicationModel::Resources::ResourceContext context);

private:
    // Returns a read-only view over the embedded bytes, regardless of whether they are owned as an
    // adopted loader buffer (m_loadedBlob) or a caller-copied array (m_blobData).
    winrt::array_view<uint8_t const> EmbeddedBytes() const noexcept;

    hstring m_stringData;
    com_array<uint8_t> m_blobData;
    embedded_resoure_ptr m_loadedBlob{nullptr};
    uint32_t m_loadedBlobSize = 0;
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
