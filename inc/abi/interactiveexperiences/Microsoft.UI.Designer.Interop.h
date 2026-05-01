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

namespace $DUAL_NAMESPACE$ {
namespace UI {
namespace Designer {
#define INTERFACE IDesignerOutputHostInterop 

DUAL_INTEROP_INTERFACE(IDesignerOutputHostInterop, IUnknown, "F2BBCDB3-100E-40AB-9D29-63FC85C315B3" , "D1A4FBE7-7E30-4F56-AC9E-9A1C2E5D8F23")
{
    IFACEMETHOD(GetDesignerOutputHandle)(
        _Out_ HANDLE* designerOutputHandle
        ) PURE;
};

} // namespace Designer
} // namespace UI
} // namespace $DUAL_NAMESPACE$

#ifndef BUILD_WINDOWS
} // namespace ABI
#endif
