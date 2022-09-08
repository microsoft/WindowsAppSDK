// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ResourceNotFoundEventArgs.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ResourceNotFoundEventArgs : ResourceNotFoundEventArgsT<ResourceNotFoundEventArgs>
{
    ResourceNotFoundEventArgs() = delete;
    ResourceNotFoundEventArgs(Microsoft::Windows::ApplicationModel::Resources::ResourceContext context, hstring name) :
        m_resourceContext(context), m_resourceName(name)
    {}

    Microsoft::Windows::ApplicationModel::Resources::ResourceContext Context();
    hstring Name();
    void SetResolvedCandidate(Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate const& candidate);

    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate GetResolvedCandidate() { return m_candidate; }

private:
    Microsoft::Windows::ApplicationModel::Resources::ResourceContext m_resourceContext = nullptr;
    hstring m_resourceName;
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate m_candidate = nullptr;
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
