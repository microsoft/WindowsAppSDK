// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    class LaunchActivatedEventArgs : public winrt::implements<LaunchActivatedEventArgs, ActivatedEventArgsBase, ILaunchActivatedEventArgs>
    {
    public:
        LaunchActivatedEventArgs(const std::wstring& args, const std::wstring& tileId)
        {
            m_kind = ActivationKind::Launch;
            m_args = args;
            m_tileId = tileId;
        }

        // ILaunchActivatedEventArgs
        winrt::hstring Arguments()
        {
            return m_args.c_str();
        }

        winrt::hstring TileId()
        {
            return m_tileId.c_str();
        }

    private:
        std::wstring m_args;
        std::wstring m_tileId;
    };
}
