// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    static PCWSTR c_launchSchemeName{ L"ms-launch" };
    static PCWSTR c_encodedLaunchSchemeName{ L"ms-encodedlaunch" };
    static PCWSTR c_contractIdKeyName{ L"ContractId" };

    // This interface used for the internal value marshaling mechanism.  Implementing this interface means
    // that both Serialize and Deserialize be implemented.  Deserialize is a static and can't be expressed
    // here.  Deserialize is required also by the encoded launch mechanism, and is how ActivatedEventArgs
    // are created regardless of marshaling.  The below method is only used for marshaling.
    MIDL_INTERFACE("1E875DD8-3E09-465D-8684-E76EF58145C5") IInternalValueMarshalable : IInspectable
    {
        virtual winrt::Windows::Foundation::Uri Serialize() PURE;
    };

    inline std::wstring GenerateEncodedLaunchUri(std::wstring const& appUserModelId, std::wstring const& contractId)
    {
        // Example: ms-encodedlaunch:App/?ContractId=Windows.File&Verb=open&File=%1
        winrt::Windows::Foundation::Uri uri{ wil::str_printf<std::wstring>(L"%s:%s?%s=%s",
            c_encodedLaunchSchemeName, appUserModelId.c_str(), c_contractIdKeyName, contractId.c_str()).c_str() };
        return uri.AbsoluteUri().c_str();
    }
}

