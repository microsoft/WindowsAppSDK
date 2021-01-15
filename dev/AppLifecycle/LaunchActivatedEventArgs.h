// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    class LaunchActivatedEventArgs : public winrt::implements<LaunchActivatedEventArgs,
        ActivatedEventArgsBase, ILaunchActivatedEventArgs>
    {
    public:
        LaunchActivatedEventArgs(const std::wstring& args) : m_args(args)
        {
            m_kind = ActivationKind::Launch;
        }

        static IActivatedEventArgs CreateFromProtocol(IProtocolActivatedEventArgs const& protocolArgs)
        {
            auto query = protocolArgs.Uri().QueryParsed();
            auto args = query.GetFirstValueByName(L"Arguments").c_str();
            return make<LaunchActivatedEventArgs>(args);
        }

        // ILaunchActivatedEventArgs
        winrt::hstring Arguments()
        {
            return m_args.c_str();
        }

        winrt::hstring TileId()
        {
            // This implementation is only used for Win32 which don't support secondary tiles.
            return L"";
        }

    private:
        std::wstring m_args;
    };
}
