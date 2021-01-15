// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/Windows.Foundation.h>
#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::ApplicationModel::Activation;

    class ProtocolActivatedEventArgs : public winrt::implements<ProtocolActivatedEventArgs, 
        ActivatedEventArgsBase, IProtocolActivatedEventArgs>
    {
    public:
        ProtocolActivatedEventArgs(const std::wstring& uri) : m_uri(winrt::Windows::Foundation::Uri(uri))
        {
            m_kind = ActivationKind::Protocol;
        }

        static IActivatedEventArgs CreateFromProtocol(IProtocolActivatedEventArgs const& protocolArgs)
        {
            return protocolArgs;
        }

        // IProtocolActivatedEventArgs
        winrt::Windows::Foundation::Uri Uri()
        {
            return m_uri;
        }

    private:
        winrt::Windows::Foundation::Uri m_uri{nullptr};
    };
}
