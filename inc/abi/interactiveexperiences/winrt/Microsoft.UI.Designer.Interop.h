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
namespace Designer {

#define INTERFACE IDesignerOutputHostInterop 

DECLARE_INTERFACE_IID_(IDesignerOutputHostInterop, IUnknown, "F2BBCDB3-100E-40AB-9D29-63FC85C315B3")
{
    IFACEMETHOD(GetDesignerOutputHandle)(
        _Out_ HANDLE* designerOutputHandle
        ) PURE;
};

} // namespace Designer
} // namespace UI
} // namespace Microsoft
} // namespace winrt 