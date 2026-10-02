// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ResourceCandidate.h"
#include "ResourceCandidate.g.cpp"
#include "ResourceContext.h"

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
        return com_array<uint8_t>(m_blobData.begin(), m_blobData.end());
    }
    throw_hresult(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
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
