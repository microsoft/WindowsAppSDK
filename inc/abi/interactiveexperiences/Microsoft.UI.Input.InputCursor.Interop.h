//---------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <sdkddkver.h>

#ifndef BUILD_WINDOWS
namespace ABI {
#endif
namespace Microsoft{
namespace UI {
namespace Input {

// Ever wondered what all of the macros do for these manual COM-style interface definitions? I 
// know I did! And Raymond Chen has the answers: https://devblogs.microsoft.com/oldnewthing/20041005-00/?p=37653
// 
// Since we don't support C code calling these interfaces, we've opted to forego a few of the usual
// requirements. Specifically, we don't use "#undef INTERFACE / #define INTERFACE", we don't use the
// BEGIN and END macros, we don't use the THIS or THIS_ macros, and we don't repeat the base class 
// members.

DECLARE_INTERFACE_IID_(IInputCursorStaticsInterop, IInspectable, "ac6f5065-90c4-46ce-beb7-05e138e54117")
{
    IFACEMETHOD(CreateFromHCursor)(
        _In_ HCURSOR cursor,
        _Out_ IInputCursor * *result
    ) PURE;
};

} // namepsace Input
} // namespace UI
} // namespace Microsoft

#ifndef BUILD_WINDOWS
} // namespace ABI
#endif