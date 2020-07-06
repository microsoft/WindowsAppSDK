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
            std::call_once(m_initOnce, InitInner);
        }

        static hstring AppIdentity()
        {
            Initialize();
            return { m_fullName.data(), m_fullNameLen };
        }

        static bool IsAppContainer()
        {
            static bool isAppContainer = wil::get_token_is_app_container();
            return isAppContainer;
        }

        static bool HasIdentity()
        {
            Initialize();
            return m_fullNameLen > 0;
        }

        static void InitInner()
        {
            // Initially, our only option is to get the package identity from this process
            UINT32 nameBufferLen = m_fullName.size();
            if (::GetCurrentPackageFullName(&nameBufferLen, m_fullName.data()) == ERROR_SUCCESS)
            {
                m_fullNameLen = nameBufferLen;
            }
        }

        static inline std::once_flag m_initOnce;
        static inline std::array<wchar_t, PACKAGE_FULL_NAME_MAX_LENGTH> m_fullName;
        static inline UINT32 m_fullNameLen = 0;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct Common : CommonT<Common, implementation::Common>
    {
    };
}
