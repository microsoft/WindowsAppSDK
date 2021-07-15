// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ResourceMap.g.h"
using namespace winrt::Microsoft::WindowsApp::Resources;

namespace winrt::Microsoft::WindowsApp::Resources::implementation
{

struct ResourceMap : ResourceMapT<ResourceMap>
{
    ResourceMap() = delete;
    ResourceMap(
        Microsoft::WindowsApp::Resources::ResourceManager resourceManager,
        MrmManagerHandle resourceManagerHandle,
        MrmMapHandle resourceMapHandle) :
        m_resourceManager(resourceManager), m_resourceManagerHandle(resourceManagerHandle), m_resourceMapHandle(resourceMapHandle)
    {}

    ~ResourceMap() {} // The resource manager owns all the resource maps so nothing to destroy;

    uint32_t ResourceCount();

    Microsoft::WindowsApp::Resources::ResourceMap GetSubtree(hstring const& reference);
    Microsoft::WindowsApp::Resources::ResourceCandidate GetValue(hstring const& resource);

    Microsoft::WindowsApp::Resources::ResourceCandidate GetValue(
        hstring const& resource,
        Microsoft::WindowsApp::Resources::ResourceContext const& context);

    Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::WindowsApp::Resources::ResourceCandidate> GetValueByIndex(
        uint32_t index);

    Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::WindowsApp::Resources::ResourceCandidate> GetValueByIndex(
        uint32_t index,
        Microsoft::WindowsApp::Resources::ResourceContext const& context);

    Microsoft::WindowsApp::Resources::ResourceCandidate TryGetValue(hstring const& resource);
    Microsoft::WindowsApp::Resources::ResourceCandidate TryGetValue(hstring const& resource, Microsoft::WindowsApp::Resources::ResourceContext const& context);

private:
    Microsoft::WindowsApp::Resources::ResourceCandidate GetValueImpl(
        const Microsoft::WindowsApp::Resources::ResourceContext* context,
        hstring const& resource,
        bool treatNotFoundAsOk);

    Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::WindowsApp::Resources::ResourceCandidate> GetValueByIndexImpl(
        const Microsoft::WindowsApp::Resources::ResourceContext* context,
        uint32_t index);

    Microsoft::WindowsApp::Resources::ResourceManager m_resourceManager = nullptr;
    MrmManagerHandle m_resourceManagerHandle = nullptr;
    MrmMapHandle m_resourceMapHandle = nullptr;
    uint32_t m_resourceCount = static_cast<uint32_t>(-1);
};

} // namespace winrt::Microsoft::WindowsApp::Resources::implementation
