//---------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <sdkddkver.h>

namespace winrt {
namespace Microsoft {
namespace UI {
namespace Input {

#undef INTERFACE
#define INTERFACE IInputCursorStaticsInterop

DECLARE_INTERFACE_IID_(IInputCursorStaticsInterop, IInspectable, "ac6f5065-90c4-46ce-beb7-05e138e54117")
{
    IFACEMETHOD(CreateFromHCursor)(
        _In_ HCURSOR cursor,
        _Out_ IInputCursor * *result
    ) PURE;
};

} // namespace Input
} // namespace UI
} // namespace Microsoft
} // namespace winrt