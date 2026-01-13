
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif /*COM_NO_WINDOWS_H*/
#ifndef __microsoft2Eui2Ecomposition2Ediagnostics_h__
#define __microsoft2Eui2Ecomposition2Ediagnostics_h__
#ifndef __microsoft2Eui2Ecomposition2Ediagnostics_p_h__
#define __microsoft2Eui2Ecomposition2Ediagnostics_p_h__


#pragma once

// Ensure that the setting of the /ns_prefix command line switch is consistent for all headers.
// If you get an error from the compiler indicating "warning C4005: 'CHECK_NS_PREFIX_STATE': macro redefinition", this
// indicates that you have included two different headers with different settings for the /ns_prefix MIDL command line switch
#if !defined(DISABLE_NS_PREFIX_CHECKS)
#define CHECK_NS_PREFIX_STATE "always"
#endif // !defined(DISABLE_NS_PREFIX_CHECKS)


#pragma push_macro("MIDL_CONST_ID")
#undef MIDL_CONST_ID
#define MIDL_CONST_ID const __declspec(selectany)


//  API Contract Inclusion Definitions
#if !defined(SPECIFIC_API_CONTRACT_DEFINITIONS)
#if !defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)
#define MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION 0x10008
#endif // defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.Foundation.h"
#include "Microsoft.UI.Composition.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    interface ICompositionDebugHeatMaps;
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps ABI::Microsoft::UI::Composition::Diagnostics::ICompositionDebugHeatMaps

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    interface ICompositionDebugSettings;
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings ABI::Microsoft::UI::Composition::Diagnostics::ICompositionDebugSettings

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    interface ICompositionDebugSettingsStatics;
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics ABI::Microsoft::UI::Composition::Diagnostics::ICompositionDebugSettingsStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class Compositor;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositor;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositor ABI::Microsoft::UI::Composition::ICompositor

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class Visual;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IVisual;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIVisual ABI::Microsoft::UI::Composition::IVisual

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    typedef enum CompositionDebugOverdrawContentKinds : unsigned int CompositionDebugOverdrawContentKinds;
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    class CompositionDebugHeatMaps;
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    class CompositionDebugSettings;
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Composition.Diagnostics.CompositionDebugOverdrawContentKinds
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    enum CompositionDebugOverdrawContentKinds : unsigned int
                    {
                        CompositionDebugOverdrawContentKinds_None = 0,
                        CompositionDebugOverdrawContentKinds_OffscreenRendered = 0x1,
                        CompositionDebugOverdrawContentKinds_Colors = 0x2,
                        CompositionDebugOverdrawContentKinds_Effects = 0x4,
                        CompositionDebugOverdrawContentKinds_Shadows = 0x8,
                        CompositionDebugOverdrawContentKinds_Lights = 0x10,
                        CompositionDebugOverdrawContentKinds_Surfaces = 0x20,
                        CompositionDebugOverdrawContentKinds_SwapChains = 0x40,
                        CompositionDebugOverdrawContentKinds_All = 0xffffffff,
                    };

                    DEFINE_ENUM_FLAG_OPERATORS(CompositionDebugOverdrawContentKinds)
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Diagnostics.ICompositionDebugHeatMaps
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Diagnostics.CompositionDebugHeatMaps
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Diagnostics_ICompositionDebugHeatMaps[] = L"Microsoft.UI.Composition.Diagnostics.ICompositionDebugHeatMaps";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    MIDL_INTERFACE("815016b8-f645-5c55-87b5-fe2167282b6f")
                    ICompositionDebugHeatMaps : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Hide(
                            ABI::Microsoft::UI::Composition::IVisual* subtree
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ShowMemoryUsage(
                            ABI::Microsoft::UI::Composition::IVisual* subtree
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ShowOverdraw(
                            ABI::Microsoft::UI::Composition::IVisual* subtree,
                            ABI::Microsoft::UI::Composition::Diagnostics::CompositionDebugOverdrawContentKinds contentKinds
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ShowRedraw(
                            ABI::Microsoft::UI::Composition::IVisual* subtree
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositionDebugHeatMaps = _uuidof(ICompositionDebugHeatMaps);
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettings
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Diagnostics_ICompositionDebugSettings[] = L"Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettings";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    MIDL_INTERFACE("f4c0c0f6-7f5f-5014-a0d6-c8c7eeecace6")
                    ICompositionDebugSettings : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_HeatMaps(
                            ABI::Microsoft::UI::Composition::Diagnostics::ICompositionDebugHeatMaps** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositionDebugSettings = _uuidof(ICompositionDebugSettings);
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettingsStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Diagnostics_ICompositionDebugSettingsStatics[] = L"Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettingsStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Diagnostics {
                    MIDL_INTERFACE("b56f8aab-2b8c-51aa-b974-10e5c517f50e")
                    ICompositionDebugSettingsStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE TryGetSettings(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Diagnostics::ICompositionDebugSettings** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositionDebugSettingsStatics = _uuidof(ICompositionDebugSettingsStatics);
                } /* Diagnostics */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Diagnostics.CompositionDebugHeatMaps
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Diagnostics.ICompositionDebugHeatMaps ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugHeatMaps_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugHeatMaps_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Diagnostics_CompositionDebugHeatMaps[] = L"Microsoft.UI.Composition.Diagnostics.CompositionDebugHeatMaps";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettingsStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettings ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugSettings_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugSettings_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Diagnostics_CompositionDebugSettings[] = L"Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositor __x_ABI_CMicrosoft_CUI_CComposition_CICompositor;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIVisual __x_ABI_CMicrosoft_CUI_CComposition_CIVisual;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CCompositionDebugOverdrawContentKinds __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CCompositionDebugOverdrawContentKinds;

/*
 *
 * Struct Microsoft.UI.Composition.Diagnostics.CompositionDebugOverdrawContentKinds
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CCompositionDebugOverdrawContentKinds
{
    CompositionDebugOverdrawContentKinds_None = 0,
    CompositionDebugOverdrawContentKinds_OffscreenRendered = 0x1,
    CompositionDebugOverdrawContentKinds_Colors = 0x2,
    CompositionDebugOverdrawContentKinds_Effects = 0x4,
    CompositionDebugOverdrawContentKinds_Shadows = 0x8,
    CompositionDebugOverdrawContentKinds_Lights = 0x10,
    CompositionDebugOverdrawContentKinds_Surfaces = 0x20,
    CompositionDebugOverdrawContentKinds_SwapChains = 0x40,
    CompositionDebugOverdrawContentKinds_All = 0xffffffff,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Diagnostics.ICompositionDebugHeatMaps
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Diagnostics.CompositionDebugHeatMaps
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Diagnostics_ICompositionDebugHeatMaps[] = L"Microsoft.UI.Composition.Diagnostics.ICompositionDebugHeatMaps";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMapsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Hide)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* subtree);
    HRESULT (STDMETHODCALLTYPE* ShowMemoryUsage)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* subtree);
    HRESULT (STDMETHODCALLTYPE* ShowOverdraw)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* subtree,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CCompositionDebugOverdrawContentKinds contentKinds);
    HRESULT (STDMETHODCALLTYPE* ShowRedraw)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* subtree);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMapsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMapsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_Hide(This, subtree) \
    ((This)->lpVtbl->Hide(This, subtree))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_ShowMemoryUsage(This, subtree) \
    ((This)->lpVtbl->ShowMemoryUsage(This, subtree))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_ShowOverdraw(This, subtree, contentKinds) \
    ((This)->lpVtbl->ShowOverdraw(This, subtree, contentKinds))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_ShowRedraw(This, subtree) \
    ((This)->lpVtbl->ShowRedraw(This, subtree))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettings
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Diagnostics_ICompositionDebugSettings[] = L"Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettings";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_HeatMaps)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugHeatMaps** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_get_HeatMaps(This, value) \
    ((This)->lpVtbl->get_HeatMaps(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettingsStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Diagnostics_ICompositionDebugSettingsStatics[] = L"Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettingsStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* TryGetSettings)(__x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettings** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_TryGetSettings(This, compositor, result) \
    ((This)->lpVtbl->TryGetSettings(This, compositor, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CDiagnostics_CICompositionDebugSettingsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Diagnostics.CompositionDebugHeatMaps
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Diagnostics.ICompositionDebugHeatMaps ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugHeatMaps_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugHeatMaps_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Diagnostics_CompositionDebugHeatMaps[] = L"Microsoft.UI.Composition.Diagnostics.CompositionDebugHeatMaps";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettingsStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Diagnostics.ICompositionDebugSettings ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugSettings_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Diagnostics_CompositionDebugSettings_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Diagnostics_CompositionDebugSettings[] = L"Microsoft.UI.Composition.Diagnostics.CompositionDebugSettings";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Ecomposition2Ediagnostics_p_h__

#endif // __microsoft2Eui2Ecomposition2Ediagnostics_h__
