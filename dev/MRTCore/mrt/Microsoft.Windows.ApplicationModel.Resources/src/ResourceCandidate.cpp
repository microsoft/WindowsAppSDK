// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ResourceCandidate.h"
#include "ResourceCandidate.g.cpp"
#include "ResourceContext.h"

#include <MemoryBuffer.h> // for ::Windows::Foundation::IMemoryBufferByteAccess

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
ResourceCandidate::ResourceCandidate(ResourceCandidateKind kind, hstring data) : m_stringData(std::move(data)), m_kind(kind)
{
    if ((kind != ResourceCandidateKind::String) && (kind != ResourceCandidateKind::FilePath))
    {
        throw_hresult(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
    }
}

ResourceCandidate::ResourceCandidate(array_view<uint8_t const> data)
{
    m_blobData = winrt::com_array<uint8_t>(data.begin(), data.end());
    m_kind = ResourceCandidateKind::EmbeddedData;
}

ResourceCandidate::ResourceCandidate(MrmManagerHandle manager, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, ResourceCandidateKind kind, hstring data)
    : m_resourceManagerHandle(manager), m_resourceContext(context), m_resourceMapHandle(map), m_resourceIndex(index), m_resourceId(id), m_stringData(std::move(data)), m_kind(kind)
{
    if ((kind != ResourceCandidateKind::String) && (kind != ResourceCandidateKind::FilePath))
    {
        throw_hresult(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
    }
}

ResourceCandidate::ResourceCandidate(MrmManagerHandle manager, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, array_view<uint8_t const> data)
    : m_resourceManagerHandle(manager), m_resourceContext(context), m_resourceMapHandle(map), m_resourceIndex(index), m_resourceId(id)
{
    m_blobData = winrt::com_array<uint8_t>(data.begin(), data.end());
    m_kind = ResourceCandidateKind::EmbeddedData;
}

ResourceCandidate::ResourceCandidate(MrmManagerHandle manager, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, embedded_resoure_ptr&& data, uint32_t size)
    : m_resourceManagerHandle(manager), m_resourceContext(context), m_resourceMapHandle(map), m_resourceIndex(index), m_resourceId(id), m_loadedBlob(std::move(data)), m_loadedBlobSize(size), m_kind(ResourceCandidateKind::EmbeddedData)
{
}

ResourceCandidate::ResourceCandidate(Microsoft::Windows::ApplicationModel::Resources::ResourceManager manager, MrmManagerHandle managerHandle, Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, MrmMapHandle map, uint32_t index, const hstring& id, array_view<uint8_t const> data)
    : m_blobView(data.data()), m_blobViewSize(static_cast<uint32_t>(data.size())), m_kind(ResourceCandidateKind::EmbeddedData),
      m_resourceManager(manager), m_resourceManagerHandle(managerHandle), m_resourceContext(context), m_resourceMapHandle(map), m_resourceIndex(index), m_resourceId(id)
{
}

winrt::array_view<uint8_t const> ResourceCandidate::EmbeddedBytes() const noexcept
{
    if (m_blobView != nullptr)
    {
        return {m_blobView, m_blobView + m_blobViewSize};
    }
    if (m_loadedBlob != nullptr)
    {
        auto const first = static_cast<uint8_t const*>(m_loadedBlob.get());
        return {first, first + m_loadedBlobSize};
    }
    return {m_blobData.begin(), m_blobData.end()};
}

hstring ResourceCandidate::ValueAsString()
{
    if (m_kind == ResourceCandidateKind::String || m_kind == ResourceCandidateKind::FilePath)
    {
        return m_stringData;
    }
    throw_hresult(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
}

com_array<uint8_t> ResourceCandidate::ValueAsBytes()
{
    if (m_kind == ResourceCandidateKind::EmbeddedData)
    {
        auto const bytes = EmbeddedBytes();
        return com_array<uint8_t>(bytes.begin(), bytes.end());
    }
    throw_hresult(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
}

namespace
{
    using winrt::Windows::Foundation::IInspectable;
    using winrt::Windows::Foundation::IMemoryBuffer;
    using winrt::Windows::Foundation::IMemoryBufferReference;
    using winrt::Windows::Foundation::TypedEventHandler;

    // Non-owning, read-only reference into a ResourceCandidate's embedded bytes. Holds the candidate
    // strongly so the backing memory (heap-owned or the memory-mapped PRI pinned transitively by the
    // candidate's ResourceManager) stays valid for as long as this reference is open.
    struct ResourceMemoryBufferReference : winrt::implements<ResourceMemoryBufferReference,
        IMemoryBufferReference, winrt::Windows::Foundation::IClosable, ::Windows::Foundation::IMemoryBufferByteAccess>
    {
        explicit ResourceMemoryBufferReference(winrt::com_ptr<ResourceCandidate> owner) noexcept
            : m_owner(std::move(owner))
        {
        }

        uint32_t Capacity() const noexcept
        {
            return m_owner ? static_cast<uint32_t>(m_owner->EmbeddedBytes().size()) : 0;
        }

        winrt::event_token Closed(TypedEventHandler<IMemoryBufferReference, IInspectable> const& handler)
        {
            return m_closed.add(handler);
        }

        void Closed(winrt::event_token const& token) noexcept { m_closed.remove(token); }

        void Close()
        {
            if (m_owner)
            {
                m_owner = nullptr;
                m_closed(*this, nullptr);
            }
        }

        HRESULT __stdcall GetBuffer(uint8_t** value, uint32_t* capacity) noexcept override
        {
            if ((value == nullptr) || (capacity == nullptr))
            {
                return E_POINTER;
            }
            if (!m_owner)
            {
                *value = nullptr;
                *capacity = 0;
                return RO_E_CLOSED;
            }
            auto const view = m_owner->EmbeddedBytes();
            *value = const_cast<uint8_t*>(view.data());
            *capacity = static_cast<uint32_t>(view.size());
            return S_OK;
        }

    private:
        winrt::com_ptr<ResourceCandidate> m_owner;
        winrt::event<TypedEventHandler<IMemoryBufferReference, IInspectable>> m_closed;
    };

    // Read-only IMemoryBuffer that projects a ResourceCandidate's embedded bytes with no copy. Each
    // CreateReference() hands out a reference sharing the same pinned candidate.
    struct ResourceMemoryBuffer : winrt::implements<ResourceMemoryBuffer,
        IMemoryBuffer, winrt::Windows::Foundation::IClosable>
    {
        explicit ResourceMemoryBuffer(winrt::com_ptr<ResourceCandidate> owner) noexcept
            : m_owner(std::move(owner))
        {
        }

        IMemoryBufferReference CreateReference()
        {
            if (!m_owner)
            {
                throw winrt::hresult_error(RO_E_CLOSED);
            }
            return winrt::make<ResourceMemoryBufferReference>(m_owner);
        }

        void Close() noexcept { m_owner = nullptr; }

    private:
        winrt::com_ptr<ResourceCandidate> m_owner;
    };
}

winrt::Windows::Foundation::IMemoryBuffer ResourceCandidate::ValueAsMemoryBuffer()
{
    if (m_kind != ResourceCandidateKind::EmbeddedData)
    {
        throw_hresult(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
    }
    return winrt::make<ResourceMemoryBuffer>(get_strong());
}

Microsoft::Windows::ApplicationModel::Resources::ResourceCandidateKind ResourceCandidate::Kind() { return m_kind; }

winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> ResourceCandidate::QualifierValues()
{
    if (m_qualifierValueMap == nullptr)
    {
        MrmType resourceType;
        wchar_t* resourceString = nullptr;
        wchar_t* resourceName = nullptr;
        MrmResourceData resourceData{};
        UINT32 qualifierCount;
        PWSTR* qualifierNames = nullptr;
        PWSTR* qualifierValues = nullptr;

        if (m_resourceIndex == static_cast<uint32_t>(-1))
        {
            winrt::check_hresult(MrmLoadStringOrEmbeddedResourceWithQualifierValues(
                m_resourceManagerHandle,
                m_resourceContext.as<Resources::implementation::ResourceContext>()->GetContextHandle(),
                m_resourceMapHandle,
                m_resourceId.c_str(),
                &resourceType,
                &resourceString,
                &resourceData,
                &qualifierCount, 
                &qualifierNames, 
                &qualifierValues));
        }
        else
        {
            winrt::check_hresult(MrmLoadStringOrEmbeddedResourceByIndexWithQualifierValues(
                m_resourceManagerHandle,
                m_resourceContext.as<Resources::implementation::ResourceContext>()->GetContextHandle(),
                m_resourceMapHandle,
                m_resourceIndex,
                &resourceType,
                &resourceName,
                &resourceString,
                &resourceData,
                &qualifierCount,
                &qualifierNames,
                &qualifierValues));
        }

        m_qualifierValueMap = single_threaded_map<hstring, hstring>();
        for (uint32_t i = 0; i < qualifierCount; i++)
        {
            m_qualifierValueMap.Insert(qualifierNames[i], qualifierValues[i]);
        }

        string_resoure_ptr resourceNameContainter(resourceName);
        string_resoure_ptr resourceStringContainer(resourceString);
        embedded_resoure_ptr resourceDataContainer(resourceData.data);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierNames);
        MrmFreeQualifierNamesOrValues(qualifierCount, qualifierValues);
    }

    return m_qualifierValueMap.GetView();
}

void ResourceCandidate::SetQualifierValuesFromContext(Microsoft::Windows::ApplicationModel::Resources::ResourceContext context)
{
    winrt::Windows::Foundation::Collections::IMap<hstring, hstring> qualifierValues = context.QualifierValues();
    m_qualifierValueMap = single_threaded_map<hstring, hstring>();
    for (auto const& value : qualifierValues)
    {
        m_qualifierValueMap.Insert(value.Key(), value.Value());
    }
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
