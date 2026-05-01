
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
#ifndef __microsoft2Eui2Examl2Emedia2Emedia3d_h__
#define __microsoft2Eui2Examl2Emedia2Emedia3d_h__
#ifndef __microsoft2Eui2Examl2Emedia2Emedia3d_p_h__
#define __microsoft2Eui2Examl2Emedia2Emedia3d_p_h__


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
#if !defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)
#define MICROSOFT_UI_XAML_WINUICONTRACT_VERSION 0xa0000
#endif // defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)

#if !defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)
#define MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION 0xa0000
#endif // defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.UI.Xaml.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface ICompositeTransform3D;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D ABI::Microsoft::UI::Xaml::Media::Media3D::ICompositeTransform3D

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface ICompositeTransform3DStatics;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics ABI::Microsoft::UI::Xaml::Media::Media3D::ICompositeTransform3DStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface IMatrix3DHelper;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper ABI::Microsoft::UI::Xaml::Media::Media3D::IMatrix3DHelper

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface IMatrix3DHelperStatics;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics ABI::Microsoft::UI::Xaml::Media::Media3D::IMatrix3DHelperStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface IPerspectiveTransform3D;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D ABI::Microsoft::UI::Xaml::Media::Media3D::IPerspectiveTransform3D

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface IPerspectiveTransform3DStatics;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics ABI::Microsoft::UI::Xaml::Media::Media3D::IPerspectiveTransform3DStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface ITransform3D;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D ABI::Microsoft::UI::Xaml::Media::Media3D::ITransform3D

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        interface ITransform3DFactory;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory ABI::Microsoft::UI::Xaml::Media::Media3D::ITransform3DFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class DependencyProperty;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IDependencyProperty;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty ABI::Microsoft::UI::Xaml::IDependencyProperty

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        typedef struct Matrix3D Matrix3D;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        class Transform3D;
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Media.Media3D.Matrix3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        struct Matrix3D
                        {
                            DOUBLE M11;
                            DOUBLE M12;
                            DOUBLE M13;
                            DOUBLE M14;
                            DOUBLE M21;
                            DOUBLE M22;
                            DOUBLE M23;
                            DOUBLE M24;
                            DOUBLE M31;
                            DOUBLE M32;
                            DOUBLE M33;
                            DOUBLE M34;
                            DOUBLE OffsetX;
                            DOUBLE OffsetY;
                            DOUBLE OffsetZ;
                            DOUBLE M44;
                        };
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ICompositeTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3D";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("cbaf163f-c254-5dcf-8ae4-40e21ce1b4ca")
                        ICompositeTransform3D : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_CenterX(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_CenterX(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CenterY(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_CenterY(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CenterZ(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_CenterZ(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RotationX(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_RotationX(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RotationY(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_RotationY(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RotationZ(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_RotationZ(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ScaleX(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_ScaleX(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ScaleY(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_ScaleY(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ScaleZ(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_ScaleZ(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TranslateX(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_TranslateX(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TranslateY(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_TranslateY(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TranslateZ(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_TranslateZ(
                                DOUBLE value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ICompositeTransform3D = _uuidof(ICompositeTransform3D);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3DStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ICompositeTransform3DStatics[] = L"Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3DStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("b64d4181-6988-5d46-858a-224db7089dc4")
                        ICompositeTransform3DStatics : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_CenterXProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CenterYProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CenterZProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RotationXProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RotationYProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RotationZProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ScaleXProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ScaleYProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ScaleZProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TranslateXProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TranslateYProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TranslateZProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ICompositeTransform3DStatics = _uuidof(ICompositeTransform3DStatics);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IMatrix3DHelper[] = L"Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelper";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("d2909be1-9c28-5b38-b63c-88e838644533")
                        IMatrix3DHelper : public IInspectable
                        {
                        public:
                        };

                        MIDL_CONST_ID IID& IID_IMatrix3DHelper = _uuidof(IMatrix3DHelper);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IMatrix3DHelperStatics[] = L"Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("930e447b-265c-5ded-9e64-57b8933c55c3")
                        IMatrix3DHelperStatics : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_Identity(
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Multiply(
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D matrix1,
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D matrix2,
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE FromElements(
                                DOUBLE m11,
                                DOUBLE m12,
                                DOUBLE m13,
                                DOUBLE m14,
                                DOUBLE m21,
                                DOUBLE m22,
                                DOUBLE m23,
                                DOUBLE m24,
                                DOUBLE m31,
                                DOUBLE m32,
                                DOUBLE m33,
                                DOUBLE m34,
                                DOUBLE offsetX,
                                DOUBLE offsetY,
                                DOUBLE offsetZ,
                                DOUBLE m44,
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetHasInverse(
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D target,
                                boolean* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetIsIdentity(
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D target,
                                boolean* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Invert(
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D target,
                                ABI::Microsoft::UI::Xaml::Media::Media3D::Matrix3D* result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IMatrix3DHelperStatics = _uuidof(IMatrix3DHelperStatics);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IPerspectiveTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3D";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("4006cc46-684e-54ea-a421-dae5b0556b85")
                        IPerspectiveTransform3D : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_Depth(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_Depth(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_OffsetX(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_OffsetX(
                                DOUBLE value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_OffsetY(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_OffsetY(
                                DOUBLE value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IPerspectiveTransform3D = _uuidof(IPerspectiveTransform3D);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3DStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IPerspectiveTransform3DStatics[] = L"Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3DStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("3b16aa8d-0ee2-5d46-a723-dc8e5c1c0b19")
                        IPerspectiveTransform3DStatics : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_DepthProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_OffsetXProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_OffsetYProperty(
                                ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IPerspectiveTransform3DStatics = _uuidof(IPerspectiveTransform3DStatics);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ITransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Transform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ITransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.ITransform3D";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("afea4941-2e49-533c-9f8f-2c126ef9893a")
                        ITransform3D : public IInspectable
                        {
                        public:
                        };

                        MIDL_CONST_ID IID& IID_ITransform3D = _uuidof(ITransform3D);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ITransform3DFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Transform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ITransform3DFactory[] = L"Microsoft.UI.Xaml.Media.Media3D.ITransform3DFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Media3D {
                        MIDL_INTERFACE("9bcce0a1-10ac-5319-bdf1-548d2e5ae504")
                        ITransform3DFactory : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                                IInspectable* baseInterface,
                                IInspectable** innerInterface,
                                ABI::Microsoft::UI::Xaml::Media::Media3D::ITransform3D** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITransform3DFactory = _uuidof(ITransform3DFactory);
                    } /* Media3D */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3DStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3D ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_CompositeTransform3D_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_CompositeTransform3D_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_CompositeTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Matrix3DHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Matrix3DHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_Matrix3DHelper[] = L"Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3DStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3D ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_PerspectiveTransform3D_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_PerspectiveTransform3D_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_PerspectiveTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.Transform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.ITransform3D ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Transform3D_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Transform3D_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_Transform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.Transform3D";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D;

/*
 *
 * Struct Microsoft.UI.Xaml.Media.Media3D.Matrix3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D
{
    DOUBLE M11;
    DOUBLE M12;
    DOUBLE M13;
    DOUBLE M14;
    DOUBLE M21;
    DOUBLE M22;
    DOUBLE M23;
    DOUBLE M24;
    DOUBLE M31;
    DOUBLE M32;
    DOUBLE M33;
    DOUBLE M34;
    DOUBLE OffsetX;
    DOUBLE OffsetY;
    DOUBLE OffsetZ;
    DOUBLE M44;
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ICompositeTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3D";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CenterX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_CenterX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_CenterY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_CenterY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_CenterZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_CenterZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_RotationX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_RotationX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_RotationY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_RotationY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_RotationZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_RotationZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_TranslateX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_TranslateX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_TranslateY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_TranslateY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_TranslateZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_TranslateZ)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_CenterX(This, value) \
    ((This)->lpVtbl->get_CenterX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_CenterX(This, value) \
    ((This)->lpVtbl->put_CenterX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_CenterY(This, value) \
    ((This)->lpVtbl->get_CenterY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_CenterY(This, value) \
    ((This)->lpVtbl->put_CenterY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_CenterZ(This, value) \
    ((This)->lpVtbl->get_CenterZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_CenterZ(This, value) \
    ((This)->lpVtbl->put_CenterZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_RotationX(This, value) \
    ((This)->lpVtbl->get_RotationX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_RotationX(This, value) \
    ((This)->lpVtbl->put_RotationX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_RotationY(This, value) \
    ((This)->lpVtbl->get_RotationY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_RotationY(This, value) \
    ((This)->lpVtbl->put_RotationY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_RotationZ(This, value) \
    ((This)->lpVtbl->get_RotationZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_RotationZ(This, value) \
    ((This)->lpVtbl->put_RotationZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_ScaleX(This, value) \
    ((This)->lpVtbl->get_ScaleX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_ScaleX(This, value) \
    ((This)->lpVtbl->put_ScaleX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_ScaleY(This, value) \
    ((This)->lpVtbl->get_ScaleY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_ScaleY(This, value) \
    ((This)->lpVtbl->put_ScaleY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_ScaleZ(This, value) \
    ((This)->lpVtbl->get_ScaleZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_ScaleZ(This, value) \
    ((This)->lpVtbl->put_ScaleZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_TranslateX(This, value) \
    ((This)->lpVtbl->get_TranslateX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_TranslateX(This, value) \
    ((This)->lpVtbl->put_TranslateX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_TranslateY(This, value) \
    ((This)->lpVtbl->get_TranslateY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_TranslateY(This, value) \
    ((This)->lpVtbl->put_TranslateY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_get_TranslateZ(This, value) \
    ((This)->lpVtbl->get_TranslateZ(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_put_TranslateZ(This, value) \
    ((This)->lpVtbl->put_TranslateZ(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3D_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3DStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ICompositeTransform3DStatics[] = L"Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3DStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CenterXProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_CenterYProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_CenterZProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_RotationXProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_RotationYProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_RotationZProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleXProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleYProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleZProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_TranslateXProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_TranslateYProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_TranslateZProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_CenterXProperty(This, value) \
    ((This)->lpVtbl->get_CenterXProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_CenterYProperty(This, value) \
    ((This)->lpVtbl->get_CenterYProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_CenterZProperty(This, value) \
    ((This)->lpVtbl->get_CenterZProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_RotationXProperty(This, value) \
    ((This)->lpVtbl->get_RotationXProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_RotationYProperty(This, value) \
    ((This)->lpVtbl->get_RotationYProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_RotationZProperty(This, value) \
    ((This)->lpVtbl->get_RotationZProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_ScaleXProperty(This, value) \
    ((This)->lpVtbl->get_ScaleXProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_ScaleYProperty(This, value) \
    ((This)->lpVtbl->get_ScaleYProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_ScaleZProperty(This, value) \
    ((This)->lpVtbl->get_ScaleZProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_TranslateXProperty(This, value) \
    ((This)->lpVtbl->get_TranslateXProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_TranslateYProperty(This, value) \
    ((This)->lpVtbl->get_TranslateYProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_get_TranslateZProperty(This, value) \
    ((This)->lpVtbl->get_TranslateZProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CICompositeTransform3DStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IMatrix3DHelper[] = L"Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelper";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IMatrix3DHelperStatics[] = L"Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Identity)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D* value);
    HRESULT (STDMETHODCALLTYPE* Multiply)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D matrix1,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D matrix2,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D* result);
    HRESULT (STDMETHODCALLTYPE* FromElements)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        DOUBLE m11,
        DOUBLE m12,
        DOUBLE m13,
        DOUBLE m14,
        DOUBLE m21,
        DOUBLE m22,
        DOUBLE m23,
        DOUBLE m24,
        DOUBLE m31,
        DOUBLE m32,
        DOUBLE m33,
        DOUBLE m34,
        DOUBLE offsetX,
        DOUBLE offsetY,
        DOUBLE offsetZ,
        DOUBLE m44,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D* result);
    HRESULT (STDMETHODCALLTYPE* GetHasInverse)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D target,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetIsIdentity)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D target,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Invert)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D target,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CMatrix3D* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_get_Identity(This, value) \
    ((This)->lpVtbl->get_Identity(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_Multiply(This, matrix1, matrix2, result) \
    ((This)->lpVtbl->Multiply(This, matrix1, matrix2, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_FromElements(This, m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, offsetX, offsetY, offsetZ, m44, result) \
    ((This)->lpVtbl->FromElements(This, m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, offsetX, offsetY, offsetZ, m44, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_GetHasInverse(This, target, result) \
    ((This)->lpVtbl->GetHasInverse(This, target, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_GetIsIdentity(This, target, result) \
    ((This)->lpVtbl->GetIsIdentity(This, target, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_Invert(This, target, result) \
    ((This)->lpVtbl->Invert(This, target, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IPerspectiveTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3D";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Depth)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_Depth)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_OffsetX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_OffsetX)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_OffsetY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_OffsetY)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_get_Depth(This, value) \
    ((This)->lpVtbl->get_Depth(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_put_Depth(This, value) \
    ((This)->lpVtbl->put_Depth(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_get_OffsetX(This, value) \
    ((This)->lpVtbl->get_OffsetX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_put_OffsetX(This, value) \
    ((This)->lpVtbl->put_OffsetX(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_get_OffsetY(This, value) \
    ((This)->lpVtbl->get_OffsetY(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_put_OffsetY(This, value) \
    ((This)->lpVtbl->put_OffsetY(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3D_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3DStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_IPerspectiveTransform3DStatics[] = L"Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3DStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DepthProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_OffsetXProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_OffsetYProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_get_DepthProperty(This, value) \
    ((This)->lpVtbl->get_DepthProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_get_OffsetXProperty(This, value) \
    ((This)->lpVtbl->get_OffsetXProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_get_OffsetYProperty(This, value) \
    ((This)->lpVtbl->get_OffsetYProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CIPerspectiveTransform3DStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ITransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Transform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ITransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.ITransform3D";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Media.Media3D.ITransform3DFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Media.Media3D.Transform3D
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Media_Media3D_ITransform3DFactory[] = L"Microsoft.UI.Xaml.Media.Media3D.ITransform3DFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3D** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CMedia3D_CITransform3DFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3DStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.ICompositeTransform3D ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_CompositeTransform3D_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_CompositeTransform3D_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_CompositeTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.CompositeTransform3D";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.IMatrix3DHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Matrix3DHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Matrix3DHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_Matrix3DHelper[] = L"Microsoft.UI.Xaml.Media.Media3D.Matrix3DHelper";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3DStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.IPerspectiveTransform3D ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_PerspectiveTransform3D_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_PerspectiveTransform3D_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_PerspectiveTransform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.PerspectiveTransform3D";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Media.Media3D.Transform3D
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Media.Media3D.ITransform3D ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Transform3D_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Media_Media3D_Transform3D_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Media_Media3D_Transform3D[] = L"Microsoft.UI.Xaml.Media.Media3D.Transform3D";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Emedia2Emedia3d_p_h__

#endif // __microsoft2Eui2Examl2Emedia2Emedia3d_h__
