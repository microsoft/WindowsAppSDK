// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Helper.h"
#include "ResourceMap.h"
#include "ResourceMap.g.cpp"
#include "ResourceCandidate.h"
#include "ResourceContext.h"
#include "ResourceManager.h"

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
uint32_t ResourceMap::ResourceCount()
{
    if (m_resourceManagerHandle == nullptr)
    {
        return 0;
    }

    if (m_resourceCount == static_cast<uint32_t>(-1))
    {
        winrt::check_hresult(MrmGetResourceCount(m_resourceManagerHandle, m_resourceMapHandle, &m_resourceCount));
    }

    return m_resourceCount;
}

Resources::ResourceMap ResourceMap::GetSubtreeImpl(hstring const& reference, bool treatNotFoundAsOk)
{
    MrmMapHandle subtree = nullptr;
    if (m_resourceManagerHandle != nullptr)
    {
        HRESULT hr = MrmGetChildResourceMap(m_resourceManagerHandle, m_resourceMapHandle, reference.c_str(), &subtree);
        if (treatNotFoundAsOk && IsResourceNotFound(hr))
        {
            return nullptr;
        }
        winrt::check_hresult(hr);
    }

    return winrt::make<ResourceMap>(m_resourceManager, m_resourceManagerHandle, subtree);
}

Resources::ResourceMap ResourceMap::GetSubtree(hstring const& reference)
{
    return GetSubtreeImpl(reference, false);
}

Resources::ResourceMap ResourceMap::TryGetSubtree(hstring const& reference)
{
    return GetSubtreeImpl(reference, true);
}

Resources::ResourceCandidate ResourceMap::GetValueImpl(const Resources::ResourceContext* context, hstring const& resource, bool treatNotFoundAsOk)
{
    // Always use a context as we override the languages.
    Resources::ResourceContext resourceContext = (context != nullptr) ? *context : m_resourceManager.CreateResourceContext();

    if (m_resourceManagerHandle == nullptr)
    {
        // Resource is not managed by MRT. Handle with event handler
        Resources::ResourceCandidate candidate = m_resourceManager.as<ResourceManager>()->HandleResourceNotFound(resourceContext, resource);
        if (candidate != nullptr)
        {
            return candidate;
        }

        if (treatNotFoundAsOk)
        {
            return nullptr;
        }
        winrt::throw_hresult(HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    }

    resourceContext.as<Resources::implementation::ResourceContext>()->Apply();

    MrmType resourceType;
    wchar_t* resourceString;
    MrmResourceData resourceData {};

    HRESULT hr = MrmLoadStringOrEmbeddedResource(
        m_resourceManagerHandle,
        resourceContext.as<Resources::implementation::ResourceContext>()->GetContextHandle(),
        m_resourceMapHandle,
        resource.c_str(),
        &resourceType,
        &resourceString,
        &resourceData);
    if (IsResourceNotFound(hr))
    {
        Resources::ResourceCandidate candidate = m_resourceManager.as<ResourceManager>()->HandleResourceNotFound(resourceContext, resource);
        if (candidate != nullptr)
        {
            return candidate;
        }

        if (treatNotFoundAsOk)
        {
            return nullptr;
        }
    }
    winrt::check_hresult(hr);

    switch (resourceType)
    {
    case MrmType_Embedded:
    {
        embedded_resoure_ptr resourceContainer(resourceData.data);
        return winrt::make<ResourceCandidate>(
            m_resourceManagerHandle,
            resourceContext,
            m_resourceMapHandle,
            static_cast<uint32_t>(-1),
            resource,
            winrt::array_view<uint8_t>(reinterpret_cast<byte*>(resourceContainer.get()), reinterpret_cast<byte*>(resourceContainer.get()) + resourceData.size));
    }
    case MrmType_String:
    {
        string_resoure_ptr resourceContainer(resourceString);
        return winrt::make<ResourceCandidate>(
            m_resourceManagerHandle,
            resourceContext,
            m_resourceMapHandle,
            static_cast<uint32_t>(-1),
            resource,
            ResourceCandidateKind::String, 
            winrt::to_hstring(resourceContainer.get()));
    }
    case MrmType_Path:
    {
        string_resoure_ptr resourceContainer(resourceString);
        return winrt::make<ResourceCandidate>(
            m_resourceManagerHandle,
            resourceContext,
            m_resourceMapHandle,
            static_cast<uint32_t>(-1),
            resource,
            ResourceCandidateKind::FilePath, 
            winrt::to_hstring(resourceContainer.get()));
    }
    }
    // Should never happen.
    winrt::throw_hresult(E_UNEXPECTED);
}

Resources::ResourceCandidate ResourceMap::GetValue(hstring const& resource)
{
    return GetValueImpl(nullptr, resource, false);
}

Resources::ResourceCandidate ResourceMap::GetValue(hstring const& resource, Resources::ResourceContext const& context)
{
    return GetValueImpl(&context, resource, false);
}

Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate ResourceMap::TryGetValue(hstring const& resource)
{
    return GetValueImpl(nullptr, resource, true);
}

Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate ResourceMap::TryGetValue(hstring const& resource, Microsoft::Windows::ApplicationModel::Resources::ResourceContext const& context)
{
    return GetValueImpl(&context, resource, true);
}

IKeyValuePair<hstring, Resources::ResourceCandidate> ResourceMap::GetValueByIndexImpl(
    const Resources::ResourceContext* context,
    uint32_t index)
{
    // Always use a context as we override the languages.
    Microsoft::Windows::ApplicationModel::Resources::ResourceContext resourceContext =
        (context != nullptr) ? *context : m_resourceManager.CreateResourceContext();

    resourceContext.as<Resources::implementation::ResourceContext>()->Apply();

    MrmType resourceType;
    wchar_t* resourceName;
    wchar_t* resourceString;
    MrmResourceData resourceData {};

    winrt::check_hresult(MrmLoadStringOrEmbeddedResourceByIndex(
        m_resourceManagerHandle,
        resourceContext.as<Resources::implementation::ResourceContext>()->GetContextHandle(),
        m_resourceMapHandle,
        index,
        &resourceType,
        &resourceName,
        &resourceString,
        &resourceData));

    string_resoure_ptr resourceNameContainter(resourceName);

    switch (resourceType)
    {
    case MrmType_Embedded:
    {
        embedded_resoure_ptr resourceContainer(resourceData.data);
        Resources::ResourceCandidate candidate = winrt::make<ResourceCandidate>(
            m_resourceManagerHandle,
            resourceContext,
            m_resourceMapHandle,
            index,
            hstring(),
            winrt::array_view<uint8_t>(reinterpret_cast<byte*>(resourceContainer.get()), reinterpret_cast<byte*>(resourceContainer.get()) + resourceData.size));

        return winrt::make<winrt::impl::key_value_pair<IKeyValuePair<hstring, Resources::ResourceCandidate>>>(resourceName, candidate);
    }
    case MrmType_String:
    {
        string_resoure_ptr resourceContainer(resourceString);
        Resources::ResourceCandidate candidate =
            winrt::make<ResourceCandidate>(
                m_resourceManagerHandle,
                resourceContext,
                m_resourceMapHandle,
                index,
                hstring(),
                ResourceCandidateKind::String, 
                winrt::to_hstring(resourceContainer.get()));

        return winrt::make<winrt::impl::key_value_pair<IKeyValuePair<hstring, Resources::ResourceCandidate>>>(resourceName, candidate);
    }
    case MrmType_Path:
    {
        string_resoure_ptr resourceContainer(resourceString);
        Resources::ResourceCandidate candidate =
            winrt::make<ResourceCandidate>(
                m_resourceManagerHandle,
                resourceContext,
                m_resourceMapHandle,
                index,
                hstring(),
                ResourceCandidateKind::FilePath, 
                winrt::to_hstring(resourceContainer.get()));

        return winrt::make<winrt::impl::key_value_pair<
            winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate>>>(
            resourceName, candidate);
    }
    }
    // Should never happen.
    winrt::throw_hresult(E_UNEXPECTED);
}

IKeyValuePair<hstring, Resources::ResourceCandidate> ResourceMap::GetValueByIndex(uint32_t index)
{
    return GetValueByIndexImpl(nullptr, index);
}

IKeyValuePair<hstring, Resources::ResourceCandidate> ResourceMap::GetValueByIndex(uint32_t index, Resources::ResourceContext const& context)
{
    return GetValueByIndexImpl(&context, index);
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
