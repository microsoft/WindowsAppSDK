
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
#ifndef __microsoft2Ewindows2Emedia2Ecapture_h__
#define __microsoft2Ewindows2Emedia2Ecapture_h__
#ifndef __microsoft2Ewindows2Emedia2Ecapture_p_h__
#define __microsoft2Ewindows2Emedia2Ecapture_p_h__


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
#if !defined(MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION)
#define MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION)

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
#include "Windows.Storage.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    interface ICameraCaptureUI;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUI

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    interface ICameraCaptureUIFactory;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUIFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    interface ICameraCaptureUIPhotoCaptureSettings;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUIPhotoCaptureSettings

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    interface ICameraCaptureUIVideoCaptureSettings;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUIVideoCaptureSettings

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Windows {
        namespace Storage {
            class StorageFile;
        } /* Storage */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CStorage_CIStorageFile_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CIStorageFile_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            interface IStorageFile;
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CIStorageFile ABI::Windows::Storage::IStorageFile

#endif // ____x_ABI_CWindows_CStorage_CIStorageFile_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Windows__CStorage__CStorageFile_USE
#define DEF___FIAsyncOperation_1_Windows__CStorage__CStorageFile_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("5e52f8ce-aced-5a42-95b4-f674dd84885e"))
IAsyncOperation<ABI::Windows::Storage::StorageFile*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Storage::StorageFile*, ABI::Windows::Storage::IStorageFile*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Windows.Storage.StorageFile>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Windows::Storage::StorageFile*> __FIAsyncOperation_1_Windows__CStorage__CStorageFile_t;
#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile ABI::Windows::Foundation::__FIAsyncOperation_1_Windows__CStorage__CStorageFile_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Windows__CStorage__CStorageFile_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("e521c894-2c26-5946-9e61-2b5e188d01ed"))
IAsyncOperationCompletedHandler<ABI::Windows::Storage::StorageFile*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Storage::StorageFile*, ABI::Windows::Storage::IStorageFile*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.Storage.StorageFile>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Windows::Storage::StorageFile*> __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_t;
#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Size Size;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    typedef enum CameraCaptureUIMaxPhotoResolution : int CameraCaptureUIMaxPhotoResolution;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    typedef enum CameraCaptureUIMaxVideoResolution : int CameraCaptureUIMaxVideoResolution;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    typedef enum CameraCaptureUIMode : int CameraCaptureUIMode;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    typedef enum CameraCaptureUIPhotoFormat : int CameraCaptureUIPhotoFormat;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    typedef enum CameraCaptureUIVideoFormat : int CameraCaptureUIVideoFormat;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    class CameraCaptureUI;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    class CameraCaptureUIPhotoCaptureSettings;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    class CameraCaptureUIVideoCaptureSettings;
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIMaxPhotoResolution
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    enum CameraCaptureUIMaxPhotoResolution : int
                    {
                        CameraCaptureUIMaxPhotoResolution_HighestAvailable = 0,
                        CameraCaptureUIMaxPhotoResolution_VerySmallQvga = 1,
                        CameraCaptureUIMaxPhotoResolution_SmallVga = 2,
                        CameraCaptureUIMaxPhotoResolution_MediumXga = 3,
                        CameraCaptureUIMaxPhotoResolution_Large3M = 4,
                        CameraCaptureUIMaxPhotoResolution_VeryLarge5M = 5,
                    };
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIMaxVideoResolution
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    enum CameraCaptureUIMaxVideoResolution : int
                    {
                        CameraCaptureUIMaxVideoResolution_HighestAvailable = 0,
                        CameraCaptureUIMaxVideoResolution_LowDefinition = 1,
                        CameraCaptureUIMaxVideoResolution_StandardDefinition = 2,
                        CameraCaptureUIMaxVideoResolution_HighDefinition = 3,
                    };
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIMode
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    enum CameraCaptureUIMode : int
                    {
                        CameraCaptureUIMode_PhotoOrVideo = 0,
                        CameraCaptureUIMode_Photo = 1,
                        CameraCaptureUIMode_Video = 2,
                    };
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoFormat
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    enum CameraCaptureUIPhotoFormat : int
                    {
                        CameraCaptureUIPhotoFormat_Jpeg = 0,
                        CameraCaptureUIPhotoFormat_Png = 1,
                        CameraCaptureUIPhotoFormat_JpegXR = 2,
                    };
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIVideoFormat
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    enum CameraCaptureUIVideoFormat : int
                    {
                        CameraCaptureUIVideoFormat_Mp4 = 0,
                        CameraCaptureUIVideoFormat_Wmv = 1,
                    };
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUI
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUI
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUI[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUI";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    MIDL_INTERFACE("c001d024-c617-5742-9ae1-8fd31be07f6c")
                    ICameraCaptureUI : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PhotoSettings(
                            ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUIPhotoCaptureSettings** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_VideoSettings(
                            ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUIVideoCaptureSettings** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CaptureFileAsync(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIMode mode,
                            __FIAsyncOperation_1_Windows__CStorage__CStorageFile** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICameraCaptureUI = _uuidof(ICameraCaptureUI);
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUIFactory
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUI
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUIFactory[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUIFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    MIDL_INTERFACE("2b49623d-5f22-5fee-991f-14f24592a3c2")
                    ICameraCaptureUIFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::UI::WindowId windowId,
                            ABI::Microsoft::Windows::Media::Capture::ICameraCaptureUI** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICameraCaptureUIFactory = _uuidof(ICameraCaptureUIFactory);
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUIPhotoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    MIDL_INTERFACE("19fe2155-d018-53fc-bbdc-5781a94687a0")
                    ICameraCaptureUIPhotoCaptureSettings : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AllowCropping(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowCropping(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CroppedAspectRatio(
                            ABI::Windows::Foundation::Size* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CroppedAspectRatio(
                            ABI::Windows::Foundation::Size value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CroppedSizeInPixels(
                            ABI::Windows::Foundation::Size* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CroppedSizeInPixels(
                            ABI::Windows::Foundation::Size value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Format(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Format(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoFormat value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxResolution(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxResolution(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICameraCaptureUIPhotoCaptureSettings = _uuidof(ICameraCaptureUIPhotoCaptureSettings);
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUIVideoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Media {
                namespace Capture {
                    MIDL_INTERFACE("47dd74f6-83b7-5123-bbdf-d757201d1ee8")
                    ICameraCaptureUIVideoCaptureSettings : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AllowTrimming(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowTrimming(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Format(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Format(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoFormat value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxDurationInSeconds(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxDurationInSeconds(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxResolution(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxResolution(
                            ABI::Microsoft::Windows::Media::Capture::CameraCaptureUIMaxVideoResolution value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICameraCaptureUIVideoCaptureSettings = _uuidof(ICameraCaptureUIVideoCaptureSettings);
                } /* Capture */
            } /* Media */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Media.Capture.CameraCaptureUI
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Media.Capture.ICameraCaptureUIFactory interface starting with version 1.0 of the Microsoft.Windows.Media.Capture.CameraCaptureUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Media.Capture.ICameraCaptureUI ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUI_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUI_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Media_Capture_CameraCaptureUI[] = L"Microsoft.Windows.Media.Capture.CameraCaptureUI";
#endif
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Media.Capture.CameraCaptureUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings";
#endif
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Media.Capture.CameraCaptureUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings";
#endif
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI;

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings;

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings;

#endif // ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CWindows_CStorage_CIStorageFile_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CIStorageFile_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CIStorageFile __x_ABI_CWindows_CStorage_CIStorageFile;

#endif // ____x_ABI_CWindows_CStorage_CIStorageFile_FWD_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Windows__CStorage__CStorageFile __FIAsyncOperation_1_Windows__CStorage__CStorageFile;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Windows__CStorage__CStorageFile;

typedef struct __FIAsyncOperation_1_Windows__CStorage__CStorageFileVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Windows__CStorage__CStorageFile* This,
        __x_ABI_CWindows_CStorage_CIStorageFile** result);

    END_INTERFACE
} __FIAsyncOperation_1_Windows__CStorage__CStorageFileVtbl;

interface __FIAsyncOperation_1_Windows__CStorage__CStorageFile
{
    CONST_VTBL struct __FIAsyncOperation_1_Windows__CStorage__CStorageFileVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Windows__CStorage__CStorageFile_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile;

typedef struct __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFileVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile* This,
        __FIAsyncOperation_1_Windows__CStorage__CStorageFile* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFileVtbl;

interface __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFileVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

typedef struct __x_ABI_CWindows_CFoundation_CSize __x_ABI_CWindows_CFoundation_CSize;

typedef enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxPhotoResolution __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxPhotoResolution;

typedef enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxVideoResolution __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxVideoResolution;

typedef enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMode __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMode;

typedef enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIPhotoFormat __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIPhotoFormat;

typedef enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIVideoFormat __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIVideoFormat;

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIMaxPhotoResolution
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxPhotoResolution
{
    CameraCaptureUIMaxPhotoResolution_HighestAvailable = 0,
    CameraCaptureUIMaxPhotoResolution_VerySmallQvga = 1,
    CameraCaptureUIMaxPhotoResolution_SmallVga = 2,
    CameraCaptureUIMaxPhotoResolution_MediumXga = 3,
    CameraCaptureUIMaxPhotoResolution_Large3M = 4,
    CameraCaptureUIMaxPhotoResolution_VeryLarge5M = 5,
};
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIMaxVideoResolution
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxVideoResolution
{
    CameraCaptureUIMaxVideoResolution_HighestAvailable = 0,
    CameraCaptureUIMaxVideoResolution_LowDefinition = 1,
    CameraCaptureUIMaxVideoResolution_StandardDefinition = 2,
    CameraCaptureUIMaxVideoResolution_HighDefinition = 3,
};
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIMode
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMode
{
    CameraCaptureUIMode_PhotoOrVideo = 0,
    CameraCaptureUIMode_Photo = 1,
    CameraCaptureUIMode_Video = 2,
};
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoFormat
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIPhotoFormat
{
    CameraCaptureUIPhotoFormat_Jpeg = 0,
    CameraCaptureUIPhotoFormat_Png = 1,
    CameraCaptureUIPhotoFormat_JpegXR = 2,
};
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Media.Capture.CameraCaptureUIVideoFormat
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIVideoFormat
{
    CameraCaptureUIVideoFormat_Mp4 = 0,
    CameraCaptureUIVideoFormat_Wmv = 1,
};
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUI
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUI
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUI[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUI";
typedef struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PhotoSettings)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings** value);
    HRESULT (STDMETHODCALLTYPE* get_VideoSettings)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings** value);
    HRESULT (STDMETHODCALLTYPE* CaptureFileAsync)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMode mode,
        __FIAsyncOperation_1_Windows__CStorage__CStorageFile** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVtbl;

interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_get_PhotoSettings(This, value) \
    ((This)->lpVtbl->get_PhotoSettings(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_get_VideoSettings(This, value) \
    ((This)->lpVtbl->get_VideoSettings(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_CaptureFileAsync(This, mode, operation) \
    ((This)->lpVtbl->CaptureFileAsync(This, mode, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUIFactory
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUI
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUIFactory[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUIFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUI** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_CreateInstance(This, windowId, value) \
    ((This)->lpVtbl->CreateInstance(This, windowId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUIPhotoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings";
typedef struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettingsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AllowCropping)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowCropping)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_CroppedAspectRatio)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        struct __x_ABI_CWindows_CFoundation_CSize* value);
    HRESULT (STDMETHODCALLTYPE* put_CroppedAspectRatio)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        struct __x_ABI_CWindows_CFoundation_CSize value);
    HRESULT (STDMETHODCALLTYPE* get_CroppedSizeInPixels)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        struct __x_ABI_CWindows_CFoundation_CSize* value);
    HRESULT (STDMETHODCALLTYPE* put_CroppedSizeInPixels)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        struct __x_ABI_CWindows_CFoundation_CSize value);
    HRESULT (STDMETHODCALLTYPE* get_Format)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIPhotoFormat* value);
    HRESULT (STDMETHODCALLTYPE* put_Format)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIPhotoFormat value);
    HRESULT (STDMETHODCALLTYPE* get_MaxResolution)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxPhotoResolution* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxResolution)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxPhotoResolution value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettingsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettingsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_get_AllowCropping(This, value) \
    ((This)->lpVtbl->get_AllowCropping(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_put_AllowCropping(This, value) \
    ((This)->lpVtbl->put_AllowCropping(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_get_CroppedAspectRatio(This, value) \
    ((This)->lpVtbl->get_CroppedAspectRatio(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_put_CroppedAspectRatio(This, value) \
    ((This)->lpVtbl->put_CroppedAspectRatio(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_get_CroppedSizeInPixels(This, value) \
    ((This)->lpVtbl->get_CroppedSizeInPixels(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_put_CroppedSizeInPixels(This, value) \
    ((This)->lpVtbl->put_CroppedSizeInPixels(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_get_Format(This, value) \
    ((This)->lpVtbl->get_Format(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_put_Format(This, value) \
    ((This)->lpVtbl->put_Format(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_get_MaxResolution(This, value) \
    ((This)->lpVtbl->get_MaxResolution(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_put_MaxResolution(This, value) \
    ((This)->lpVtbl->put_MaxResolution(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Media_Capture_ICameraCaptureUIVideoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings";
typedef struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettingsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AllowTrimming)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowTrimming)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_Format)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIVideoFormat* value);
    HRESULT (STDMETHODCALLTYPE* put_Format)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIVideoFormat value);
    HRESULT (STDMETHODCALLTYPE* get_MaxDurationInSeconds)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxDurationInSeconds)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_MaxResolution)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxVideoResolution* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxResolution)(__x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings* This,
        enum __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CCameraCaptureUIMaxVideoResolution value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettingsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettingsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_get_AllowTrimming(This, value) \
    ((This)->lpVtbl->get_AllowTrimming(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_put_AllowTrimming(This, value) \
    ((This)->lpVtbl->put_AllowTrimming(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_get_Format(This, value) \
    ((This)->lpVtbl->get_Format(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_put_Format(This, value) \
    ((This)->lpVtbl->put_Format(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_get_MaxDurationInSeconds(This, value) \
    ((This)->lpVtbl->get_MaxDurationInSeconds(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_put_MaxDurationInSeconds(This, value) \
    ((This)->lpVtbl->put_MaxDurationInSeconds(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_get_MaxResolution(This, value) \
    ((This)->lpVtbl->get_MaxResolution(This, value))

#define __x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_put_MaxResolution(This, value) \
    ((This)->lpVtbl->put_MaxResolution(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Media.Capture.CameraCaptureUI
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Media.Capture.ICameraCaptureUIFactory interface starting with version 1.0 of the Microsoft.Windows.Media.Capture.CameraCaptureUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Media.Capture.ICameraCaptureUI ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUI_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUI_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Media_Capture_CameraCaptureUI[] = L"Microsoft.Windows.Media.Capture.CameraCaptureUI";
#endif
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Media.Capture.CameraCaptureUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings";
#endif
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings
 *
 * Introduced to Microsoft.Windows.Media.Capture.CameraCaptureUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Media.Capture.CameraCaptureUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings[] = L"Microsoft.Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings";
#endif
#endif // MICROSOFT_WINDOWS_MEDIA_CAPTURE_CAMERACAPTUREUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Emedia2Ecapture_p_h__

#endif // __microsoft2Ewindows2Emedia2Ecapture_h__
