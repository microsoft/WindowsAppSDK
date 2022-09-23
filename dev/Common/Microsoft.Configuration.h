// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __MICROSOFT_CONFIGURATION_H
#define __MICROSOFT_CONFIGURATION_H

namespace Microsoft::Configuration
{
inline bool IsOptionEnabled(PCWSTR name)
{
    WCHAR value[1 + 1]{};
    if (::GetEnvironmentVariableW(name, value, ARRAYSIZE(value)) == 1)
    {
        if (*value == L'0')
        {
            return false;
        }
        else if (*value == L'1')
        {
            return true;
        }
    }
    return false;
}
}

#endif // __MICROSOFT_CONFIGURATION_H
