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


// Ever wondered what all of the macros do for these manual COM-style interface definitions? I 
// know I did! And Raymond Chen has the answers: https://devblogs.microsoft.com/oldnewthing/20041005-00/?p=37653
// 
// Since we don't support C code calling these interfaces, we've opted to forego a few of the usual
// requirements. Specifically, we don't use "#undef INTERFACE / #define INTERFACE", we don't use the
// BEGIN and END macros, we don't use the THIS or THIS_ macros, and we don't repeat the base class 
// members.

interface IInputPreTranslateKeyboardSourceHandler;

DECLARE_INTERFACE_IID_(IInputPreTranslateKeyboardSourceInterop, IUnknown, "C3244A48-DCB4-416C-901A-FFC5E50C2FFA")
{    
    IFACEMETHOD(SetPreTranslateHandler)(
        _In_ IInputPreTranslateKeyboardSourceHandler* handler
        ) PURE;
};


DECLARE_INTERFACE_IID_(IInputPreTranslateKeyboardSourceHandler, IUnknown, "9A4B69AA-E3BE-4590-95F5-3AAA7B12B260")
{
    // "keyboardModifiers" are flags that can hold a combination of the following values:
    //
    //  FVIRTKEY                0x0001      Message is WM_(SYS)KEYDOWN or WM_(SYS)KEYUP.
    //  FSHIFT                  0x0004      VK_SHIFT is pressed.
    //  FCONTROL                0x0008      VK_CONTROL is pressed (or VK_RCONTROL when the AltGr key is present and pressed).
    //  FALT                    0x0010      VK_MENU is pressed (or VK_LMENU when the AltGr key is present and pressed).

    IFACEMETHOD(OnDirectMessage)(
        _In_ IInputPreTranslateKeyboardSourceInterop* source,
        _In_ const MSG* msg,
        _In_ UINT keyboardModifiers,
        _Inout_ bool* handled
        ) PURE;

    IFACEMETHOD(OnTreeMessage)(
        _In_ IInputPreTranslateKeyboardSourceInterop* source,
        _In_ const MSG* msg,
        _In_ UINT keyboardModifiers,
        _Inout_ bool* handled
        ) PURE;
};


} // namespace Input
} // namespace UI
} // namespace Microsoft
} // namespace winrt
