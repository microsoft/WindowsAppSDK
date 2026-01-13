
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
#ifndef __microsoft2Ewindows2Estorage2Epickers_h__
#define __microsoft2Ewindows2Estorage2Epickers_h__
#ifndef __microsoft2Ewindows2Estorage2Epickers_p_h__
#define __microsoft2Ewindows2Estorage2Epickers_p_h__


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
#if !defined(MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION 0x10008
#endif // defined(MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION)

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
#include "Microsoft.UI.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IFileOpenPicker;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker ABI::Microsoft::Windows::Storage::Pickers::IFileOpenPicker

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IFileOpenPickerFactory;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory ABI::Microsoft::Windows::Storage::Pickers::IFileOpenPickerFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IFileSavePicker;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker ABI::Microsoft::Windows::Storage::Pickers::IFileSavePicker

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IFileSavePickerFactory;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory ABI::Microsoft::Windows::Storage::Pickers::IFileSavePickerFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IFolderPicker;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker ABI::Microsoft::Windows::Storage::Pickers::IFolderPicker

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IFolderPickerFactory;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory ABI::Microsoft::Windows::Storage::Pickers::IFolderPickerFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IPickFileResult;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult ABI::Microsoft::Windows::Storage::Pickers::IPickFileResult

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    interface IPickFolderResult;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult ABI::Microsoft::Windows::Storage::Pickers::IPickFolderResult

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    class PickFileResult;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("98316bd9-5a80-5c8a-8f99-2efbe1e70233"))
IAsyncOperation<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFileResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.Storage.Pickers.PickFileResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("4689da0a-d31d-5be4-8722-bfdb60893026"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFileResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.Storage.Pickers.PickFileResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    class PickFolderResult;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f5ef0362-d68a-5d05-a166-fe608b68c278"))
IAsyncOperation<ABI::Microsoft::Windows::Storage::Pickers::PickFolderResult*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFolderResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFolderResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.Storage.Pickers.PickFolderResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Windows::Storage::Pickers::PickFolderResult*> __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a429a329-573b-52b9-883f-3ccfb310f143"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::Storage::Pickers::PickFolderResult*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFolderResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFolderResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.Storage.Pickers.PickFolderResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Windows::Storage::Pickers::PickFolderResult*> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b07e34ef-ae42-5dea-b3d3-4c252990ab31"))
IIterator<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFileResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Storage.Pickers.PickFileResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ff8b2322-ce6d-5136-b5f0-4034dfe09c4b"))
IIterable<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFileResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Storage.Pickers.PickFileResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("76506627-d304-5763-86c2-d7fd3f17152b"))
IVectorView<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*, ABI::Microsoft::Windows::Storage::Pickers::IPickFileResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Storage.Pickers.PickFileResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Storage::Pickers::PickFileResult*> __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f8cde12a-675a-5291-b048-586c2625ae3e"))
IAsyncOperation<__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult*> : IAsyncOperation_impl<__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Storage.Pickers.PickFileResult>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult*> __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#ifndef DEF___FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f1a085fd-b82d-5f07-81f6-28abefd1c84c"))
IAsyncOperationCompletedHandler<__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult*> : IAsyncOperationCompletedHandler_impl<__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Storage.Pickers.PickFileResult>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult*> __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t;
#define __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008


#ifndef DEF___FIIterator_1_HSTRING_USE
#define DEF___FIIterator_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8c304ebb-6615-50a4-8829-879ecd443236"))
IIterator<HSTRING> : IIterator_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<HSTRING> __FIIterator_1_HSTRING_t;
#define __FIIterator_1_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_HSTRING_USE */



#ifndef DEF___FIIterable_1_HSTRING_USE
#define DEF___FIIterable_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e2fcc7c1-3bfc-5a0b-b2b0-72e769d1cb7e"))
IIterable<HSTRING> : IIterable_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<HSTRING> __FIIterable_1_HSTRING_t;
#define __FIIterable_1_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_HSTRING_USE */



#ifndef DEF___FIVectorView_1_HSTRING_USE
#define DEF___FIVectorView_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("2f13c006-a03a-5f69-b090-75a43e33423e"))
IVectorView<HSTRING> : IVectorView_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<HSTRING> __FIVectorView_1_HSTRING_t;
#define __FIVectorView_1_HSTRING ABI::Windows::Foundation::Collections::__FIVectorView_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_HSTRING_USE */



#ifndef DEF___FIVector_1_HSTRING_USE
#define DEF___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("98b9acc1-4b56-532e-ac73-03d5291cca90"))
IVector<HSTRING> : IVector_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<HSTRING> __FIVector_1_HSTRING_t;
#define __FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_HSTRING_USE */



#ifndef DEF___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE
#define DEF___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("174f26c7-79ea-5f7c-bd70-ac4457f2cac8"))
IKeyValuePair<HSTRING, __FIVector_1_HSTRING*> : IKeyValuePair_impl<HSTRING, __FIVector_1_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Foundation.Collections.IVector`1<String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, __FIVector_1_HSTRING*> __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_t;
#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE */



#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("a11824c9-e458-502a-afd8-ce3ce0abd6fe"))
IIterator<__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING*> : IIterator_impl<__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Foundation.Collections.IVector`1<String>>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING*> __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE */



#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4fed2669-d0d3-59f6-91d9-95902d728d6a"))
IIterable<__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING*> : IIterable_impl<__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Foundation.Collections.IVector`1<String>>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING*> __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_USE */



#ifndef DEF___FIMapView_2_HSTRING___FIVector_1_HSTRING_USE
#define DEF___FIMapView_2_HSTRING___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("153f9c9c-d22a-5c9e-9c74-8b85c908b000"))
IMapView<HSTRING, __FIVector_1_HSTRING*> : IMapView_impl<HSTRING, __FIVector_1_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, Windows.Foundation.Collections.IVector`1<String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, __FIVector_1_HSTRING*> __FIMapView_2_HSTRING___FIVector_1_HSTRING_t;
#define __FIMapView_2_HSTRING___FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING___FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING___FIVector_1_HSTRING_USE */



#ifndef DEF___FIMap_2_HSTRING___FIVector_1_HSTRING_USE
#define DEF___FIMap_2_HSTRING___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e475ca9d-6afb-5992-993e-53e6ef7a9ecd"))
IMap<HSTRING, __FIVector_1_HSTRING*> : IMap_impl<HSTRING, __FIVector_1_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMap`2<String, Windows.Foundation.Collections.IVector`1<String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMap<HSTRING, __FIVector_1_HSTRING*> __FIMap_2_HSTRING___FIVector_1_HSTRING_t;
#define __FIMap_2_HSTRING___FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIMap_2_HSTRING___FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMap_2_HSTRING___FIVector_1_HSTRING_USE */


namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    typedef enum PickerLocationId : int PickerLocationId;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    typedef enum PickerViewMode : int PickerViewMode;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    class FileOpenPicker;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    class FileSavePicker;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    class FolderPicker;
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Storage.Pickers.PickerLocationId
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    enum PickerLocationId : int
                    {
                        PickerLocationId_DocumentsLibrary = 0,
                        PickerLocationId_ComputerFolder = 1,
                        PickerLocationId_Desktop = 2,
                        PickerLocationId_Downloads = 3,
                        PickerLocationId_MusicLibrary = 5,
                        PickerLocationId_PicturesLibrary = 6,
                        PickerLocationId_VideosLibrary = 7,
                        PickerLocationId_Objects3D = 8,
                        PickerLocationId_Unspecified = 9,
                    };
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Struct Microsoft.Windows.Storage.Pickers.PickerViewMode
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    enum PickerViewMode : int
                    {
                        PickerViewMode_List = 0,
                        PickerViewMode_Thumbnail = 1,
                    };
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileOpenPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileOpenPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileOpenPicker[] = L"Microsoft.Windows.Storage.Pickers.IFileOpenPicker";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("9d00f175-c783-51bd-8c93-fb63695d3abc")
                    IFileOpenPicker : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ViewMode(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerViewMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ViewMode(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerViewMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SuggestedStartLocation(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerLocationId* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuggestedStartLocation(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerLocationId value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CommitButtonText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CommitButtonText(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FileTypeFilter(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE PickSingleFileAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE PickMultipleFilesAsync(
                            __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFileOpenPicker = _uuidof(IFileOpenPicker);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileOpenPickerFactory
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileOpenPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileOpenPickerFactory[] = L"Microsoft.Windows.Storage.Pickers.IFileOpenPickerFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("315e86d7-d7a2-5d81-b379-7af78207b1af")
                    IFileOpenPickerFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::UI::WindowId windowId,
                            ABI::Microsoft::Windows::Storage::Pickers::IFileOpenPicker** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFileOpenPickerFactory = _uuidof(IFileOpenPickerFactory);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileSavePicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileSavePicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileSavePicker[] = L"Microsoft.Windows.Storage.Pickers.IFileSavePicker";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("79f1f4df-741b-59b2-aa06-fe9ac817b7dd")
                    IFileSavePicker : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_SuggestedStartLocation(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerLocationId* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuggestedStartLocation(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerLocationId value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CommitButtonText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CommitButtonText(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FileTypeChoices(
                            __FIMap_2_HSTRING___FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DefaultFileExtension(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DefaultFileExtension(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SuggestedFileName(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuggestedFileName(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SuggestedFolder(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuggestedFolder(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE PickSaveFileAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFileSavePicker = _uuidof(IFileSavePicker);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileSavePickerFactory
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileSavePicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileSavePickerFactory[] = L"Microsoft.Windows.Storage.Pickers.IFileSavePickerFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("2e256696-30b6-5a05-a8f5-c752db6dd268")
                    IFileSavePickerFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::UI::WindowId windowId,
                            ABI::Microsoft::Windows::Storage::Pickers::IFileSavePicker** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFileSavePickerFactory = _uuidof(IFileSavePickerFactory);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFolderPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FolderPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFolderPicker[] = L"Microsoft.Windows.Storage.Pickers.IFolderPicker";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("3ef0d1ca-97c6-5873-8ea2-02c450174290")
                    IFolderPicker : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ViewMode(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerViewMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ViewMode(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerViewMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SuggestedStartLocation(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerLocationId* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuggestedStartLocation(
                            ABI::Microsoft::Windows::Storage::Pickers::PickerLocationId value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CommitButtonText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CommitButtonText(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE PickSingleFolderAsync(
                            __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFolderPicker = _uuidof(IFolderPicker);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFolderPickerFactory
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FolderPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFolderPickerFactory[] = L"Microsoft.Windows.Storage.Pickers.IFolderPickerFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("e1550d89-b389-5886-8395-022b1588d6a8")
                    IFolderPickerFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::UI::WindowId windowId,
                            ABI::Microsoft::Windows::Storage::Pickers::IFolderPicker** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFolderPickerFactory = _uuidof(IFolderPickerFactory);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IPickFileResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.PickFileResult
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IPickFileResult[] = L"Microsoft.Windows.Storage.Pickers.IPickFileResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("e6f2e3d6-7bb0-5d81-9e7d-6fd35a1f25ab")
                    IPickFileResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Path(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPickFileResult = _uuidof(IPickFileResult);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IPickFolderResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.PickFolderResult
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IPickFolderResult[] = L"Microsoft.Windows.Storage.Pickers.IPickFolderResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                namespace Pickers {
                    MIDL_INTERFACE("6f7fd316-fe29-59d1-9343-c49cf5cde680")
                    IPickFolderResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Path(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPickFolderResult = _uuidof(IPickFolderResult);
                } /* Pickers */
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.FileOpenPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Storage.Pickers.IFileOpenPickerFactory interface starting with version 1.8 of the Microsoft.Windows.Storage.Pickers.StoragePickersContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IFileOpenPicker ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileOpenPicker_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileOpenPicker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_FileOpenPicker[] = L"Microsoft.Windows.Storage.Pickers.FileOpenPicker";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.FileSavePicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Storage.Pickers.IFileSavePickerFactory interface starting with version 1.8 of the Microsoft.Windows.Storage.Pickers.StoragePickersContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IFileSavePicker ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileSavePicker_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileSavePicker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_FileSavePicker[] = L"Microsoft.Windows.Storage.Pickers.FileSavePicker";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.FolderPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Storage.Pickers.IFolderPickerFactory interface starting with version 1.8 of the Microsoft.Windows.Storage.Pickers.StoragePickersContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IFolderPicker ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FolderPicker_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FolderPicker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_FolderPicker[] = L"Microsoft.Windows.Storage.Pickers.FolderPicker";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.PickFileResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IPickFileResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFileResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFileResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_PickFileResult[] = L"Microsoft.Windows.Storage.Pickers.PickFileResult";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.PickFolderResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IPickFolderResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFolderResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFolderResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_PickFolderResult[] = L"Microsoft.Windows.Storage.Pickers.PickFolderResult";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult;

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResultVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResultVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIIterator_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

typedef interface __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** result);

    END_INTERFACE
} __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult;

typedef struct __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* This,
        __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl;

interface __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#if !defined(____FIIterator_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1_HSTRING __FIIterator_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_HSTRING;

typedef struct __FIIterator_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_HSTRING* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_HSTRING* This,
        UINT32 itemsLength,
        HSTRING* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_HSTRINGVtbl;

interface __FIIterator_1_HSTRING
{
    CONST_VTBL struct __FIIterator_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterable_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1_HSTRING __FIIterable_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_HSTRING;

typedef struct __FIIterable_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_HSTRING* This,
        __FIIterator_1_HSTRING** result);

    END_INTERFACE
} __FIIterable_1_HSTRINGVtbl;

interface __FIIterable_1_HSTRING
{
    CONST_VTBL struct __FIIterable_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIVectorView_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIVectorView_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_HSTRING __FIVectorView_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_HSTRING;

typedef struct __FIVectorView_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_HSTRING* This,
        UINT32 index,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_HSTRING* This,
        HSTRING value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_HSTRING* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        HSTRING* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_HSTRINGVtbl;

interface __FIVectorView_1_HSTRING
{
    CONST_VTBL struct __FIVectorView_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_HSTRING_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_HSTRING_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_HSTRING_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIVector_1_HSTRING __FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_HSTRING;

typedef struct __FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_HSTRING* This,
        UINT32 index,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_HSTRING* This,
        __FIVectorView_1_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_HSTRING* This,
        HSTRING value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_HSTRING* This,
        UINT32 index,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_HSTRING* This,
        UINT32 index,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_HSTRING* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_HSTRING* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_HSTRING* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        HSTRING* items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_HSTRING* This,
        UINT32 itemsLength,
        HSTRING* items);

    END_INTERFACE
} __FIVector_1_HSTRINGVtbl;

interface __FIVector_1_HSTRING
{
    CONST_VTBL struct __FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_HSTRING_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_HSTRING_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_HSTRING_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_HSTRING_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_HSTRING_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_HSTRING_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_HSTRING_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_HSTRING_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_HSTRING_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING;

typedef struct __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        __FIVector_1_HSTRING** result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl;

interface __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING___FIVector_1_HSTRING __FIMapView_2_HSTRING___FIVector_1_HSTRING;

#if !defined(____FIMapView_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING___FIVector_1_HSTRING __FIMapView_2_HSTRING___FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING___FIVector_1_HSTRING;

typedef struct __FIMapView_2_HSTRING___FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING key,
        __FIVector_1_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING___FIVector_1_HSTRING* This,
        __FIMapView_2_HSTRING___FIVector_1_HSTRING** first,
        __FIMapView_2_HSTRING___FIVector_1_HSTRING** second);

    END_INTERFACE
} __FIMapView_2_HSTRING___FIVector_1_HSTRINGVtbl;

interface __FIMapView_2_HSTRING___FIVector_1_HSTRING
{
    CONST_VTBL struct __FIMapView_2_HSTRING___FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING___FIVector_1_HSTRING_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIMap_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIMap_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMap_2_HSTRING___FIVector_1_HSTRING __FIMap_2_HSTRING___FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMap_2_HSTRING___FIVector_1_HSTRING;

typedef struct __FIMap_2_HSTRING___FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING key,
        __FIVector_1_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        __FIMapView_2_HSTRING___FIVector_1_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* Insert)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING key,
        __FIVector_1_HSTRING* value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Remove)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This,
        HSTRING key);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIMap_2_HSTRING___FIVector_1_HSTRING* This);

    END_INTERFACE
} __FIMap_2_HSTRING___FIVector_1_HSTRINGVtbl;

interface __FIMap_2_HSTRING___FIVector_1_HSTRING
{
    CONST_VTBL struct __FIMap_2_HSTRING___FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_Insert(This, key, value, result) \
    ((This)->lpVtbl->Insert(This, key, value, result))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_Remove(This, key) \
    ((This)->lpVtbl->Remove(This, key))

#define __FIMap_2_HSTRING___FIVector_1_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#endif /* COBJMACROS */

#endif // ____FIMap_2_HSTRING___FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

typedef enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId;

typedef enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode;

/*
 *
 * Struct Microsoft.Windows.Storage.Pickers.PickerLocationId
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId
{
    PickerLocationId_DocumentsLibrary = 0,
    PickerLocationId_ComputerFolder = 1,
    PickerLocationId_Desktop = 2,
    PickerLocationId_Downloads = 3,
    PickerLocationId_MusicLibrary = 5,
    PickerLocationId_PicturesLibrary = 6,
    PickerLocationId_VideosLibrary = 7,
    PickerLocationId_Objects3D = 8,
    PickerLocationId_Unspecified = 9,
};
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Struct Microsoft.Windows.Storage.Pickers.PickerViewMode
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode
{
    PickerViewMode_List = 0,
    PickerViewMode_Thumbnail = 1,
};
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileOpenPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileOpenPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileOpenPicker[] = L"Microsoft.Windows.Storage.Pickers.IFileOpenPicker";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ViewMode)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ViewMode)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode value);
    HRESULT (STDMETHODCALLTYPE* get_SuggestedStartLocation)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId* value);
    HRESULT (STDMETHODCALLTYPE* put_SuggestedStartLocation)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId value);
    HRESULT (STDMETHODCALLTYPE* get_CommitButtonText)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CommitButtonText)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_FileTypeFilter)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        __FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* PickSingleFileAsync)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** operation);
    HRESULT (STDMETHODCALLTYPE* PickMultipleFilesAsync)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker* This,
        __FIAsyncOperation_1___FIVectorView_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_get_ViewMode(This, value) \
    ((This)->lpVtbl->get_ViewMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_put_ViewMode(This, value) \
    ((This)->lpVtbl->put_ViewMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_get_SuggestedStartLocation(This, value) \
    ((This)->lpVtbl->get_SuggestedStartLocation(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_put_SuggestedStartLocation(This, value) \
    ((This)->lpVtbl->put_SuggestedStartLocation(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_get_CommitButtonText(This, value) \
    ((This)->lpVtbl->get_CommitButtonText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_put_CommitButtonText(This, value) \
    ((This)->lpVtbl->put_CommitButtonText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_get_FileTypeFilter(This, value) \
    ((This)->lpVtbl->get_FileTypeFilter(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_PickSingleFileAsync(This, operation) \
    ((This)->lpVtbl->PickSingleFileAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_PickMultipleFilesAsync(This, operation) \
    ((This)->lpVtbl->PickMultipleFilesAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileOpenPickerFactory
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileOpenPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileOpenPickerFactory[] = L"Microsoft.Windows.Storage.Pickers.IFileOpenPickerFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPicker** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_CreateInstance(This, windowId, value) \
    ((This)->lpVtbl->CreateInstance(This, windowId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileOpenPickerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileSavePicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileSavePicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileSavePicker[] = L"Microsoft.Windows.Storage.Pickers.IFileSavePicker";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SuggestedStartLocation)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId* value);
    HRESULT (STDMETHODCALLTYPE* put_SuggestedStartLocation)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId value);
    HRESULT (STDMETHODCALLTYPE* get_CommitButtonText)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CommitButtonText)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_FileTypeChoices)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        __FIMap_2_HSTRING___FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_DefaultFileExtension)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_DefaultFileExtension)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_SuggestedFileName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_SuggestedFileName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_SuggestedFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_SuggestedFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* PickSaveFileAsync)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFileResult** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_get_SuggestedStartLocation(This, value) \
    ((This)->lpVtbl->get_SuggestedStartLocation(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_put_SuggestedStartLocation(This, value) \
    ((This)->lpVtbl->put_SuggestedStartLocation(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_get_CommitButtonText(This, value) \
    ((This)->lpVtbl->get_CommitButtonText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_put_CommitButtonText(This, value) \
    ((This)->lpVtbl->put_CommitButtonText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_get_FileTypeChoices(This, value) \
    ((This)->lpVtbl->get_FileTypeChoices(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_get_DefaultFileExtension(This, value) \
    ((This)->lpVtbl->get_DefaultFileExtension(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_put_DefaultFileExtension(This, value) \
    ((This)->lpVtbl->put_DefaultFileExtension(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_get_SuggestedFileName(This, value) \
    ((This)->lpVtbl->get_SuggestedFileName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_put_SuggestedFileName(This, value) \
    ((This)->lpVtbl->put_SuggestedFileName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_get_SuggestedFolder(This, value) \
    ((This)->lpVtbl->get_SuggestedFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_put_SuggestedFolder(This, value) \
    ((This)->lpVtbl->put_SuggestedFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_PickSaveFileAsync(This, operation) \
    ((This)->lpVtbl->PickSaveFileAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFileSavePickerFactory
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FileSavePicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFileSavePickerFactory[] = L"Microsoft.Windows.Storage.Pickers.IFileSavePickerFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePicker** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_CreateInstance(This, windowId, value) \
    ((This)->lpVtbl->CreateInstance(This, windowId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFileSavePickerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFolderPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FolderPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFolderPicker[] = L"Microsoft.Windows.Storage.Pickers.IFolderPicker";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ViewMode)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ViewMode)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerViewMode value);
    HRESULT (STDMETHODCALLTYPE* get_SuggestedStartLocation)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId* value);
    HRESULT (STDMETHODCALLTYPE* put_SuggestedStartLocation)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CPickerLocationId value);
    HRESULT (STDMETHODCALLTYPE* get_CommitButtonText)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CommitButtonText)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* PickSingleFolderAsync)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CStorage__CPickers__CPickFolderResult** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_get_ViewMode(This, value) \
    ((This)->lpVtbl->get_ViewMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_put_ViewMode(This, value) \
    ((This)->lpVtbl->put_ViewMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_get_SuggestedStartLocation(This, value) \
    ((This)->lpVtbl->get_SuggestedStartLocation(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_put_SuggestedStartLocation(This, value) \
    ((This)->lpVtbl->put_SuggestedStartLocation(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_get_CommitButtonText(This, value) \
    ((This)->lpVtbl->get_CommitButtonText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_put_CommitButtonText(This, value) \
    ((This)->lpVtbl->put_CommitButtonText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_PickSingleFolderAsync(This, operation) \
    ((This)->lpVtbl->PickSingleFolderAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IFolderPickerFactory
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.FolderPicker
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IFolderPickerFactory[] = L"Microsoft.Windows.Storage.Pickers.IFolderPickerFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPicker** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_CreateInstance(This, windowId, value) \
    ((This)->lpVtbl->CreateInstance(This, windowId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIFolderPickerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IPickFileResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.PickFileResult
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IPickFileResult[] = L"Microsoft.Windows.Storage.Pickers.IPickFileResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Path)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_get_Path(This, value) \
    ((This)->lpVtbl->get_Path(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFileResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Interface Microsoft.Windows.Storage.Pickers.IPickFolderResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.Pickers.PickFolderResult
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_Pickers_IPickFolderResult[] = L"Microsoft.Windows.Storage.Pickers.IPickFolderResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Path)(__x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_get_Path(This, value) \
    ((This)->lpVtbl->get_Path(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CPickers_CIPickFolderResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.FileOpenPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Storage.Pickers.IFileOpenPickerFactory interface starting with version 1.8 of the Microsoft.Windows.Storage.Pickers.StoragePickersContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IFileOpenPicker ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileOpenPicker_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileOpenPicker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_FileOpenPicker[] = L"Microsoft.Windows.Storage.Pickers.FileOpenPicker";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.FileSavePicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Storage.Pickers.IFileSavePickerFactory interface starting with version 1.8 of the Microsoft.Windows.Storage.Pickers.StoragePickersContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IFileSavePicker ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileSavePicker_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FileSavePicker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_FileSavePicker[] = L"Microsoft.Windows.Storage.Pickers.FileSavePicker";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.FolderPicker
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Storage.Pickers.IFolderPickerFactory interface starting with version 1.8 of the Microsoft.Windows.Storage.Pickers.StoragePickersContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IFolderPicker ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FolderPicker_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_FolderPicker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_FolderPicker[] = L"Microsoft.Windows.Storage.Pickers.FolderPicker";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.PickFileResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IPickFileResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFileResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFileResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_PickFileResult[] = L"Microsoft.Windows.Storage.Pickers.PickFileResult";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

/*
 *
 * Class Microsoft.Windows.Storage.Pickers.PickFolderResult
 *
 * Introduced to Microsoft.Windows.Storage.Pickers.StoragePickersContract in version 1.8
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.Pickers.IPickFolderResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFolderResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_Pickers_PickFolderResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_Pickers_PickFolderResult[] = L"Microsoft.Windows.Storage.Pickers.PickFolderResult";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_PICKERS_STORAGEPICKERSCONTRACT_VERSION >= 0x10008

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Estorage2Epickers_p_h__

#endif // __microsoft2Ewindows2Estorage2Epickers_h__
