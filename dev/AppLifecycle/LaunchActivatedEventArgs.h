// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include "ActivatedEventArgsBase.h"
#include "ValueMarshaling.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    constexpr PCWSTR c_launchContractId = L"Windows.Launch";

    class LaunchActivatedEventArgs : public winrt::implements<LaunchActivatedEventArgs, ILaunchActivatedEventArgs,
        ActivatedEventArgsBase, IInternalValueMarshalable>
    {
    public:
        LaunchActivatedEventArgs(const winrt::hstring args) : m_args(args)
        {
            m_kind = ActivationKind::Launch;
        }

        static winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const& uri)
        {
            auto query = uri.QueryParsed();
            auto args = query.GetFirstValueByName(L"Arguments");
            return make<LaunchActivatedEventArgs>(args);
        }

        // IInternalValueMarshalable
        winrt::Windows::Foundation::Uri Serialize()
        {
            auto uri = GenerateEncodedLaunchUri(L"App", c_launchContractId) + L"&Arguments=" + winrt::Windows::Foundation::Uri::EscapeComponent(m_args.c_str());
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
        winrt::hstring m_args;
    };
}
