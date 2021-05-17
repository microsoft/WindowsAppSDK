// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "ActivatedEventArgsBase.h"
#include "ValueMarshaling.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    static PCWSTR c_launchContractId = L"Windows.Launch";

    class LaunchActivatedEventArgs : public winrt::implements<LaunchActivatedEventArgs,
        ActivatedEventArgsBase, ILaunchActivatedEventArgs, IInternalValueMarshalable>
    {
    public:
        LaunchActivatedEventArgs(const std::wstring& args) : m_args(args)
        {
            m_kind = ActivationKind::Launch;
        }

        static winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const& uri)
        {
            auto query = uri.QueryParsed();
            auto args = query.GetFirstValueByName(L"Arguments").c_str();
            return make<LaunchActivatedEventArgs>(args);
        }

        // IInternalValueMarshalable
        winrt::Windows::Foundation::Uri Serialize()
        {
            auto uri = GenerateEncodedLaunchUri(L"App", c_launchContractId) + L"&Arguments=" + m_args;
            return winrt::Windows::Foundation::Uri(uri);
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
