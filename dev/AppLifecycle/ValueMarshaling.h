// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    static LPCWSTR c_launchSchemeName{ L"ms-launch" };
    static LPCWSTR c_encodedLaunchSchemeName{ L"ms-encodedlaunch" };
    static LPCWSTR c_contractIdKeyName{ L"ContractId" };

    // Marker interface to denote the event arg object can be marshaled using values
    // by the internal marshaling mechanism.  Using this interface requires explicit
    // support be added to the marshaling code to have intimate knowledge of the given
    // object.
    MIDL_INTERFACE("1E875DD8-3E09-465D-8684-E76EF58145C5") IInternalValueMarshalable : IInspectable
    {
        virtual winrt::Windows::Foundation::Uri Serialize() PURE;
    };

    inline std::wstring GenerateEncodedLaunchUri(std::wstring const& appUserModelId, std::wstring const& contractId)
    {
        winrt::Windows::Foundation::Uri uri{ wil::str_printf<std::wstring>(L"%s://%s?%s=%s",
            c_encodedLaunchSchemeName, appUserModelId.c_str(), c_contractIdKeyName, contractId.c_str()).c_str() };
        return uri.AbsoluteUri().c_str();
    }
}

