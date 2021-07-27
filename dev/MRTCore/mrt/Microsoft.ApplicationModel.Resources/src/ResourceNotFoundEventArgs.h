// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ResourceNotFoundEventArgs.g.h"

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{

struct ResourceNotFoundEventArgs : ResourceNotFoundEventArgsT<ResourceNotFoundEventArgs>
{
    ResourceNotFoundEventArgs() = delete;
    ResourceNotFoundEventArgs(Microsoft::ApplicationModel::Resources::ResourceContext context, hstring name) :
        m_resourceContext(context), m_resourceName(name)
    {}

    Microsoft::ApplicationModel::Resources::ResourceContext Context();
    hstring Name();
    void SetResolvedCandidate(Microsoft::ApplicationModel::Resources::ResourceCandidate const& candidate);

    Microsoft::ApplicationModel::Resources::ResourceCandidate GetResolvedCandidate() { return m_candidate; }

private:
    Microsoft::ApplicationModel::Resources::ResourceContext m_resourceContext = nullptr;
    hstring m_resourceName;
    Microsoft::ApplicationModel::Resources::ResourceCandidate m_candidate = nullptr;
};

} // namespace winrt::Microsoft::ApplicationModel::Resources::implementation
