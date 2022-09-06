// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSOFT_FOUNDATION_STRING_H
#define __MICROSOFT_FOUNDATION_STRING_H

namespace Microsoft::Foundation::String
{
    /// Return true if the string is nullptr or an empty string ("").
    inline bool IsNullOrEmpty(_In_ PCSTR string)
    {
        return !string || (*string == '\0');
    }

    /// Return true if the string is nullptr or an empty string ("").
    inline bool IsNullOrEmpty(_In_ PCWSTR string)
    {
        return !string || (*string == L'\0');
    }
}

#endif // __MICROSOFT_FOUNDATION_STRING_H
