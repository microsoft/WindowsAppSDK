// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <Common.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct Common
    {
        Common() = default;

        static void Initialize()
        {
        }

        static hstring AppIdentity()
        {
            static winrt::hstring fullName = GetFullIdentityString();
            return fullName;
        }

        static bool IsAppContainer()
        {
            static bool isAppContainer = wil::get_token_is_app_container();
            return isAppContainer;
        }

        static bool HasIdentity()
        {
            return !AppIdentity().empty();
        }

        static winrt::hstring GetFullIdentityString()
        {
            winrt::hstring identityString;
            WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH];
            UINT32 idNameBufferLen = ARRAYSIZE(idNameBuffer);
            if (::GetCurrentPackageFullName(&idNameBufferLen, idNameBuffer) == ERROR_SUCCESS)
            {
                identityString = idNameBuffer;
            }

            return identityString;            
        }
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct Common : CommonT<Common, implementation::Common>
    {
    };
}
