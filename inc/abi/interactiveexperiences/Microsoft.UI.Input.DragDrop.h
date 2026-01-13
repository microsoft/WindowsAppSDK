
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
#ifndef __microsoft2Eui2Einput2Edragdrop_h__
#define __microsoft2Eui2Einput2Edragdrop_h__
#ifndef __microsoft2Eui2Einput2Edragdrop_p_h__
#define __microsoft2Eui2Einput2Edragdrop_p_h__


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

#if !defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)
#define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
#endif // defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)
#define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
#endif // defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.Foundation.h"
#include "Microsoft.UI.Content.h"
#include "Microsoft.UI.Input.h"
#include "Windows.ApplicationModel.DataTransfer.h"
#include "Windows.Graphics.Imaging.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDragDropManager;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager ABI::Microsoft::UI::Input::DragDrop::IDragDropManager

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDragDropManagerStatics;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics ABI::Microsoft::UI::Input::DragDrop::IDragDropManagerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDragInfo;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo ABI::Microsoft::UI::Input::DragDrop::IDragInfo

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDragOperation;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation ABI::Microsoft::UI::Input::DragDrop::IDragOperation

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDragUIOverride;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride ABI::Microsoft::UI::Input::DragDrop::IDragUIOverride

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDropOperationTarget;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget ABI::Microsoft::UI::Input::DragDrop::IDropOperationTarget

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    interface IDropOperationTargetRequestedEventArgs;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs ABI::Microsoft::UI::Input::DragDrop::IDropOperationTargetRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace DataTransfer {
                typedef enum DataPackageOperation : unsigned int DataPackageOperation;
            } /* DataTransfer */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_USE
#define DEF___FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("8b98aea9-64f0-5672-b30e-dfd9c2e4f6fe"))
IAsyncOperation<enum ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation> : IAsyncOperation_impl<enum ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Windows.ApplicationModel.DataTransfer.DataPackageOperation>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<enum ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation> __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_t;
#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation ABI::Windows::Foundation::__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("add21d46-17df-5a43-a685-3262fce84643"))
IAsyncOperationCompletedHandler<enum ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation> : IAsyncOperationCompletedHandler_impl<enum ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.ApplicationModel.DataTransfer.DataPackageOperation>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<enum ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation> __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_t;
#define __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    class DragDropManager;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    class DropOperationTargetRequestedEventArgs;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("0c4ab140-bf34-57d9-8136-169a83c0dcdb"))
ITypedEventHandler<ABI::Microsoft::UI::Input::DragDrop::DragDropManager*, ABI::Microsoft::UI::Input::DragDrop::DropOperationTargetRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Input::DragDrop::DragDropManager*, ABI::Microsoft::UI::Input::DragDrop::IDragDropManager*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Input::DragDrop::DropOperationTargetRequestedEventArgs*, ABI::Microsoft::UI::Input::DragDrop::IDropOperationTargetRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Input.DragDrop.DragDropManager, Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Input::DragDrop::DragDropManager*, ABI::Microsoft::UI::Input::DragDrop::DropOperationTargetRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentIsland;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIsland;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland ABI::Microsoft::UI::Content::IContentIsland

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                class PointerPoint;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                interface IPointerPoint;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint ABI::Microsoft::UI::Input::IPointerPoint

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace DataTransfer {
                class DataPackage;
            } /* DataTransfer */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace DataTransfer {
                interface IDataPackage;
            } /* DataTransfer */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage ABI::Windows::ApplicationModel::DataTransfer::IDataPackage

#endif // ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace DataTransfer {
                class DataPackageView;
            } /* DataTransfer */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace DataTransfer {
                interface IDataPackageView;
            } /* DataTransfer */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView ABI::Windows::ApplicationModel::DataTransfer::IDataPackageView

#endif // ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IAsyncAction;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIAsyncAction ABI::Windows::Foundation::IAsyncAction

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IClosable;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIClosable ABI::Windows::Foundation::IClosable

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Point Point;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Graphics {
            namespace Imaging {
                class SoftwareBitmap;
            } /* Imaging */
        } /* Graphics */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Graphics {
            namespace Imaging {
                interface ISoftwareBitmap;
            } /* Imaging */
        } /* Graphics */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap ABI::Windows::Graphics::Imaging::ISoftwareBitmap

#endif // ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    typedef enum DragDropModifiers : unsigned int DragDropModifiers;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    typedef enum DragUIContentMode : int DragUIContentMode;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    class DragInfo;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    class DragUIOverride;
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Input.DragDrop.DragDropModifiers
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    enum DragDropModifiers : unsigned int
                    {
                        DragDropModifiers_None = 0,
                        DragDropModifiers_Shift = 0x1,
                        DragDropModifiers_Control = 0x2,
                        DragDropModifiers_Alt = 0x4,
                        DragDropModifiers_LeftButton = 0x8,
                        DragDropModifiers_MiddleButton = 0x10,
                        DragDropModifiers_RightButton = 0x20,
                    };

                    DEFINE_ENUM_FLAG_OPERATORS(DragDropModifiers)
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Input.DragDrop.DragUIContentMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    enum DragUIContentMode : int
                    {
                        DragUIContentMode_Auto = 0,
                        DragUIContentMode_Deferred = 1,
                    };
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragDropManager
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragDropManager
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragDropManager[] = L"Microsoft.UI.Input.DragDrop.IDragDropManager";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("4fea9efc-b073-5fbe-9c95-a4113ef6393f")
                    IDragDropManager : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AreConcurrentOperationsEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AreConcurrentOperationsEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_TargetRequested(
                            __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_TargetRequested(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDragDropManager = _uuidof(IDragDropManager);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragDropManagerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragDropManager
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragDropManagerStatics[] = L"Microsoft.UI.Input.DragDrop.IDragDropManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("5587c863-57d7-5d0f-8ea9-e5dcf06a0f83")
                    IDragDropManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetForIsland(
                            ABI::Microsoft::UI::Content::IContentIsland* content,
                            ABI::Microsoft::UI::Input::DragDrop::IDragDropManager** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDragDropManagerStatics = _uuidof(IDragDropManagerStatics);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragInfo
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragInfo[] = L"Microsoft.UI.Input.DragDrop.IDragInfo";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("7507d891-62a8-5a79-a880-ac7353d001ec")
                    IDragInfo : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AllowedOperations(
                            ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Data(
                            ABI::Windows::ApplicationModel::DataTransfer::IDataPackageView** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Modifiers(
                            ABI::Microsoft::UI::Input::DragDrop::DragDropModifiers* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Point* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDragInfo = _uuidof(IDragInfo);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragOperation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragOperation
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragOperation[] = L"Microsoft.UI.Input.DragDrop.IDragOperation";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("ef122288-7984-53d3-8488-133dcd3de793")
                    IDragOperation : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AllowedOperations(
                            ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowedOperations(
                            ABI::Windows::ApplicationModel::DataTransfer::DataPackageOperation value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Data(
                            ABI::Windows::ApplicationModel::DataTransfer::IDataPackage** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DragUIContentMode(
                            ABI::Microsoft::UI::Input::DragDrop::DragUIContentMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DragUIContentMode(
                            ABI::Microsoft::UI::Input::DragDrop::DragUIContentMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetDragUIContentFromSoftwareBitmap(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* bitmap
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetDragUIContentFromSoftwareBitmap2(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* bitmap,
                            ABI::Windows::Foundation::Point anchorPoint
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StartAsync(
                            ABI::Microsoft::UI::Input::DragDrop::IDragDropManager* initialTarget,
                            ABI::Microsoft::UI::Input::IPointerPoint* initialPointerPoint,
                            __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDragOperation = _uuidof(IDragOperation);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragUIOverride
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragUIOverride
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragUIOverride[] = L"Microsoft.UI.Input.DragDrop.IDragUIOverride";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("8432fbac-a17f-5a95-8f56-fb432280b54d")
                    IDragUIOverride : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Caption(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Caption(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsCaptionVisible(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsCaptionVisible(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsContentVisible(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsContentVisible(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsGlyphVisible(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsGlyphVisible(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Clear(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetContentFromSoftwareBitmap(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* bitmap
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetContentFromSoftwareBitmap2(
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* bitmap,
                            ABI::Windows::Foundation::Point anchorPoint
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDragUIOverride = _uuidof(IDragUIOverride);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDropOperationTarget
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDropOperationTarget[] = L"Microsoft.UI.Input.DragDrop.IDropOperationTarget";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("1c2707d9-0065-53c7-bbfb-50850378caf3")
                    IDropOperationTarget : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE DropAsync(
                            ABI::Microsoft::UI::Input::DragDrop::IDragInfo* dragInfo,
                            __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnterAsync(
                            ABI::Microsoft::UI::Input::DragDrop::IDragInfo* dragInfo,
                            ABI::Microsoft::UI::Input::DragDrop::IDragUIOverride* dragUIOverride,
                            __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE LeaveAsync(
                            ABI::Microsoft::UI::Input::DragDrop::IDragInfo* dragInfo,
                            ABI::Windows::Foundation::IAsyncAction** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE OverAsync(
                            ABI::Microsoft::UI::Input::DragDrop::IDragInfo* dragInfo,
                            ABI::Microsoft::UI::Input::DragDrop::IDragUIOverride* dragUIOverride,
                            __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDropOperationTarget = _uuidof(IDropOperationTarget);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDropOperationTargetRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDropOperationTargetRequestedEventArgs[] = L"Microsoft.UI.Input.DragDrop.IDropOperationTargetRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace DragDrop {
                    MIDL_INTERFACE("f61c5b62-720e-59ff-ad0b-e77fc5b8a4a3")
                    IDropOperationTargetRequestedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SetTarget(
                            ABI::Microsoft::UI::Input::DragDrop::IDropOperationTarget* target
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDropOperationTargetRequestedEventArgs = _uuidof(IDropOperationTargetRequestedEventArgs);
                } /* DragDrop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragDropManager
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Input.DragDrop.IDragDropManagerStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragDropManager ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragDropManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragDropManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragDropManager[] = L"Microsoft.UI.Input.DragDrop.DragDropManager";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragInfo ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragInfo_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragInfo[] = L"Microsoft.UI.Input.DragDrop.DragInfo";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragOperation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragOperation ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragOperation_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragOperation_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragOperation[] = L"Microsoft.UI.Input.DragDrop.DragOperation";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragUIOverride
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragUIOverride ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragUIOverride_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragUIOverride_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragUIOverride[] = L"Microsoft.UI.Input.DragDrop.DragUIOverride";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDropOperationTargetRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DropOperationTargetRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DropOperationTargetRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DropOperationTargetRequestedEventArgs[] = L"Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CWindows_CApplicationModel_CDataTransfer_CDataPackageOperation __x_ABI_CWindows_CApplicationModel_CDataTransfer_CDataPackageOperation;

typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation;

typedef struct __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        enum __x_ABI_CWindows_CApplicationModel_CDataTransfer_CDataPackageOperation* result);

    END_INTERFACE
} __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperationVtbl;

interface __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation
{
    CONST_VTBL struct __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation;

typedef struct __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* This,
        __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperationVtbl;

interface __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* sender,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage;

#endif // ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView;

#endif // ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIAsyncAction __x_ABI_CWindows_CFoundation_CIAsyncAction;

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

#ifndef ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap;

#endif // ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragDropModifiers __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragDropModifiers;

typedef enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragUIContentMode __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragUIContentMode;

/*
 *
 * Struct Microsoft.UI.Input.DragDrop.DragDropModifiers
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragDropModifiers
{
    DragDropModifiers_None = 0,
    DragDropModifiers_Shift = 0x1,
    DragDropModifiers_Control = 0x2,
    DragDropModifiers_Alt = 0x4,
    DragDropModifiers_LeftButton = 0x8,
    DragDropModifiers_MiddleButton = 0x10,
    DragDropModifiers_RightButton = 0x20,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Input.DragDrop.DragUIContentMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragUIContentMode
{
    DragUIContentMode_Auto = 0,
    DragUIContentMode_Deferred = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragDropManager
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragDropManager
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragDropManager[] = L"Microsoft.UI.Input.DragDrop.IDragDropManager";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AreConcurrentOperationsEnabled)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AreConcurrentOperationsEnabled)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* add_TargetRequested)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        __FITypedEventHandler_2_Microsoft__CUI__CInput__CDragDrop__CDragDropManager_Microsoft__CUI__CInput__CDragDrop__CDropOperationTargetRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_TargetRequested)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_get_AreConcurrentOperationsEnabled(This, value) \
    ((This)->lpVtbl->get_AreConcurrentOperationsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_put_AreConcurrentOperationsEnabled(This, value) \
    ((This)->lpVtbl->put_AreConcurrentOperationsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_add_TargetRequested(This, handler, token) \
    ((This)->lpVtbl->add_TargetRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_remove_TargetRequested(This, token) \
    ((This)->lpVtbl->remove_TargetRequested(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragDropManagerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragDropManager
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragDropManagerStatics[] = L"Microsoft.UI.Input.DragDrop.IDragDropManagerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetForIsland)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* content,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_GetForIsland(This, content, result) \
    ((This)->lpVtbl->GetForIsland(This, content, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragInfo
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragInfo[] = L"Microsoft.UI.Input.DragDrop.IDragInfo";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfoVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AllowedOperations)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        enum __x_ABI_CWindows_CApplicationModel_CDataTransfer_CDataPackageOperation* value);
    HRESULT (STDMETHODCALLTYPE* get_Data)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView** value);
    HRESULT (STDMETHODCALLTYPE* get_Modifiers)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragDropModifiers* value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfoVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfoVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_get_AllowedOperations(This, value) \
    ((This)->lpVtbl->get_AllowedOperations(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_get_Data(This, value) \
    ((This)->lpVtbl->get_Data(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_get_Modifiers(This, value) \
    ((This)->lpVtbl->get_Modifiers(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragOperation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragOperation
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragOperation[] = L"Microsoft.UI.Input.DragDrop.IDragOperation";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AllowedOperations)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        enum __x_ABI_CWindows_CApplicationModel_CDataTransfer_CDataPackageOperation* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowedOperations)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        enum __x_ABI_CWindows_CApplicationModel_CDataTransfer_CDataPackageOperation value);
    HRESULT (STDMETHODCALLTYPE* get_Data)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        __x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage** value);
    HRESULT (STDMETHODCALLTYPE* get_DragUIContentMode)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragUIContentMode* value);
    HRESULT (STDMETHODCALLTYPE* put_DragUIContentMode)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CDragUIContentMode value);
    HRESULT (STDMETHODCALLTYPE* SetDragUIContentFromSoftwareBitmap)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* bitmap);
    HRESULT (STDMETHODCALLTYPE* SetDragUIContentFromSoftwareBitmap2)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* bitmap,
        struct __x_ABI_CWindows_CFoundation_CPoint anchorPoint);
    HRESULT (STDMETHODCALLTYPE* StartAsync)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragDropManager* initialTarget,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* initialPointerPoint,
        __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperationVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_get_AllowedOperations(This, value) \
    ((This)->lpVtbl->get_AllowedOperations(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_put_AllowedOperations(This, value) \
    ((This)->lpVtbl->put_AllowedOperations(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_get_Data(This, value) \
    ((This)->lpVtbl->get_Data(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_get_DragUIContentMode(This, value) \
    ((This)->lpVtbl->get_DragUIContentMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_put_DragUIContentMode(This, value) \
    ((This)->lpVtbl->put_DragUIContentMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_SetDragUIContentFromSoftwareBitmap(This, bitmap) \
    ((This)->lpVtbl->SetDragUIContentFromSoftwareBitmap(This, bitmap))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_SetDragUIContentFromSoftwareBitmap2(This, bitmap, anchorPoint) \
    ((This)->lpVtbl->SetDragUIContentFromSoftwareBitmap2(This, bitmap, anchorPoint))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_StartAsync(This, initialTarget, initialPointerPoint, operation) \
    ((This)->lpVtbl->StartAsync(This, initialTarget, initialPointerPoint, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragOperation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDragUIOverride
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DragUIOverride
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDragUIOverride[] = L"Microsoft.UI.Input.DragDrop.IDragUIOverride";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverrideVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Caption)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Caption)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_IsCaptionVisible)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsCaptionVisible)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsContentVisible)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsContentVisible)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsGlyphVisible)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsGlyphVisible)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* Clear)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This);
    HRESULT (STDMETHODCALLTYPE* SetContentFromSoftwareBitmap)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* bitmap);
    HRESULT (STDMETHODCALLTYPE* SetContentFromSoftwareBitmap2)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* This,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* bitmap,
        struct __x_ABI_CWindows_CFoundation_CPoint anchorPoint);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverrideVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverrideVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_get_Caption(This, value) \
    ((This)->lpVtbl->get_Caption(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_put_Caption(This, value) \
    ((This)->lpVtbl->put_Caption(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_get_IsCaptionVisible(This, value) \
    ((This)->lpVtbl->get_IsCaptionVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_put_IsCaptionVisible(This, value) \
    ((This)->lpVtbl->put_IsCaptionVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_get_IsContentVisible(This, value) \
    ((This)->lpVtbl->get_IsContentVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_put_IsContentVisible(This, value) \
    ((This)->lpVtbl->put_IsContentVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_get_IsGlyphVisible(This, value) \
    ((This)->lpVtbl->get_IsGlyphVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_put_IsGlyphVisible(This, value) \
    ((This)->lpVtbl->put_IsGlyphVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_SetContentFromSoftwareBitmap(This, bitmap) \
    ((This)->lpVtbl->SetContentFromSoftwareBitmap(This, bitmap))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_SetContentFromSoftwareBitmap2(This, bitmap, anchorPoint) \
    ((This)->lpVtbl->SetContentFromSoftwareBitmap2(This, bitmap, anchorPoint))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDropOperationTarget
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDropOperationTarget[] = L"Microsoft.UI.Input.DragDrop.IDropOperationTarget";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* DropAsync)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* dragInfo,
        __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation);
    HRESULT (STDMETHODCALLTYPE* EnterAsync)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* dragInfo,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* dragUIOverride,
        __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation);
    HRESULT (STDMETHODCALLTYPE* LeaveAsync)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* dragInfo,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* OverAsync)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragInfo* dragInfo,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDragUIOverride* dragUIOverride,
        __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackageOperation** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_DropAsync(This, dragInfo, operation) \
    ((This)->lpVtbl->DropAsync(This, dragInfo, operation))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_EnterAsync(This, dragInfo, dragUIOverride, operation) \
    ((This)->lpVtbl->EnterAsync(This, dragInfo, dragUIOverride, operation))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_LeaveAsync(This, dragInfo, operation) \
    ((This)->lpVtbl->LeaveAsync(This, dragInfo, operation))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_OverAsync(This, dragInfo, dragUIOverride, operation) \
    ((This)->lpVtbl->OverAsync(This, dragInfo, dragUIOverride, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Input.DragDrop.IDropOperationTargetRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_DragDrop_IDropOperationTargetRequestedEventArgs[] = L"Microsoft.UI.Input.DragDrop.IDropOperationTargetRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SetTarget)(__x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTarget* target);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_SetTarget(This, target) \
    ((This)->lpVtbl->SetTarget(This, target))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CDragDrop_CIDropOperationTargetRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragDropManager
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Input.DragDrop.IDragDropManagerStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragDropManager ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragDropManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragDropManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragDropManager[] = L"Microsoft.UI.Input.DragDrop.DragDropManager";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragInfo ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragInfo_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragInfo[] = L"Microsoft.UI.Input.DragDrop.DragInfo";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragOperation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragOperation ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragOperation_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragOperation_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragOperation[] = L"Microsoft.UI.Input.DragDrop.DragOperation";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DragUIOverride
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDragUIOverride ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragUIOverride_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DragUIOverride_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DragUIOverride[] = L"Microsoft.UI.Input.DragDrop.DragUIOverride";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Input.DragDrop.IDropOperationTargetRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DropOperationTargetRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_DragDrop_DropOperationTargetRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_DragDrop_DropOperationTargetRequestedEventArgs[] = L"Microsoft.UI.Input.DragDrop.DropOperationTargetRequestedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Einput2Edragdrop_p_h__

#endif // __microsoft2Eui2Einput2Edragdrop_h__
