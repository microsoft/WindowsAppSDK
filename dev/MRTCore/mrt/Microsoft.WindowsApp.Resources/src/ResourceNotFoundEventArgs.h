// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ResourceNotFoundEventArgs.g.h"

namespace winrt::Microsoft::WindowsApp::Resources::implementation
{

struct ResourceNotFoundEventArgs : ResourceNotFoundEventArgsT<ResourceNotFoundEventArgs>
{
    ResourceNotFoundEventArgs() = delete;
    ResourceNotFoundEventArgs(Microsoft::WindowsApp::Resources::ResourceContext context, hstring name) :
        m_resourceContext(context), m_resourceName(name)
    {}

    Microsoft::WindowsApp::Resources::ResourceContext Context();
    hstring Name();
    void SetResolvedCandidate(Microsoft::WindowsApp::Resources::ResourceCandidate const& candidate);

    Microsoft::WindowsApp::Resources::ResourceCandidate GetResolvedCandidate() { return m_candidate; }

private:
    Microsoft::WindowsApp::Resources::ResourceContext m_resourceContext = nullptr;
    hstring m_resourceName;
    Microsoft::WindowsApp::Resources::ResourceCandidate m_candidate = nullptr;
};

} // namespace winrt::Microsoft::WindowsApp::Resources::implementation
