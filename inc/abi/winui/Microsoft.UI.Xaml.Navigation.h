
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
#ifndef __microsoft2Eui2Examl2Enavigation_h__
#define __microsoft2Eui2Examl2Enavigation_h__
#ifndef __microsoft2Eui2Examl2Enavigation_p_h__
#define __microsoft2Eui2Examl2Enavigation_p_h__


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
#include "Microsoft.UI.Xaml.h"
#include "Microsoft.UI.Xaml.Media.Animation.h"
#include "Windows.UI.Xaml.Interop.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigatedEventHandler;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler ABI::Microsoft::UI::Xaml::Navigation::INavigatedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigatingCancelEventHandler;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler ABI::Microsoft::UI::Xaml::Navigation::INavigatingCancelEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigationFailedEventHandler;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler ABI::Microsoft::UI::Xaml::Navigation::INavigationFailedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigationStoppedEventHandler;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler ABI::Microsoft::UI::Xaml::Navigation::INavigationStoppedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface IFrameNavigationOptions;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions ABI::Microsoft::UI::Xaml::Navigation::IFrameNavigationOptions

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface IFrameNavigationOptionsFactory;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory ABI::Microsoft::UI::Xaml::Navigation::IFrameNavigationOptionsFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigatingCancelEventArgs;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs ABI::Microsoft::UI::Xaml::Navigation::INavigatingCancelEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigationEventArgs;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs ABI::Microsoft::UI::Xaml::Navigation::INavigationEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface INavigationFailedEventArgs;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs ABI::Microsoft::UI::Xaml::Navigation::INavigationFailedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface IPageStackEntry;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry ABI::Microsoft::UI::Xaml::Navigation::IPageStackEntry

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface IPageStackEntryFactory;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory ABI::Microsoft::UI::Xaml::Navigation::IPageStackEntryFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    interface IPageStackEntryStatics;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics ABI::Microsoft::UI::Xaml::Navigation::IPageStackEntryStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_FWD_DEFINED__

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
                    namespace Animation {
                        class NavigationTransitionInfo;
                    } /* Animation */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    namespace Animation {
                        interface INavigationTransitionInfo;
                    } /* Animation */
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Foundation {
            class Uri;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IUriRuntimeClass;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIUriRuntimeClass ABI::Windows::Foundation::IUriRuntimeClass

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Xaml {
                namespace Interop {
                    typedef struct TypeName TypeName;
                } /* Interop */
            } /* Xaml */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    typedef enum NavigationMode : int NavigationMode;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    class FrameNavigationOptions;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    class NavigatingCancelEventArgs;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    class NavigationEventArgs;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    class NavigationFailedEventArgs;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    class PageStackEntry;
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Navigation.NavigationCacheMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    enum NavigationCacheMode : int
                    {
                        NavigationCacheMode_Disabled = 0,
                        NavigationCacheMode_Required = 1,
                        NavigationCacheMode_Enabled = 2,
                    };
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Navigation.NavigationMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    enum NavigationMode : int
                    {
                        NavigationMode_New = 0,
                        NavigationMode_Back = 1,
                        NavigationMode_Forward = 2,
                        NavigationMode_Refresh = 3,
                    };
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigatedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("8631b517-6d8e-58ee-82fe-d4034d1bd7c1")
                    INavigatedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Navigation::INavigationEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigatedEventHandler = _uuidof(INavigatedEventHandler);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigatingCancelEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("fcae1401-ec94-565f-9f48-7c4b6272b3b1")
                    INavigatingCancelEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Navigation::INavigatingCancelEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigatingCancelEventHandler = _uuidof(INavigatingCancelEventHandler);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigationFailedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("97ca2b56-d6eb-5fd2-a675-a339640eedba")
                    INavigationFailedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Navigation::INavigationFailedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigationFailedEventHandler = _uuidof(INavigationFailedEventHandler);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigationStoppedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("b9e796a6-7ffe-5a63-aef4-cbc331663b66")
                    INavigationStoppedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Navigation::INavigationEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigationStoppedEventHandler = _uuidof(INavigationStoppedEventHandler);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IFrameNavigationOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.FrameNavigationOptions
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IFrameNavigationOptions[] = L"Microsoft.UI.Xaml.Navigation.IFrameNavigationOptions";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("390de593-14cf-5312-af99-6cd8d59ec5d5")
                    IFrameNavigationOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsNavigationStackEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsNavigationStackEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TransitionInfoOverride(
                            ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TransitionInfoOverride(
                            ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFrameNavigationOptions = _uuidof(IFrameNavigationOptions);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IFrameNavigationOptionsFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.FrameNavigationOptions
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IFrameNavigationOptionsFactory[] = L"Microsoft.UI.Xaml.Navigation.IFrameNavigationOptionsFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("ddf3f748-7127-5cee-9f79-ac281a234632")
                    IFrameNavigationOptionsFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Navigation::IFrameNavigationOptions** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFrameNavigationOptionsFactory = _uuidof(IFrameNavigationOptionsFactory);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.INavigatingCancelEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.NavigatingCancelEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_INavigatingCancelEventArgs[] = L"Microsoft.UI.Xaml.Navigation.INavigatingCancelEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("172fde12-e06f-5df6-930e-5facf7b3fbe7")
                    INavigatingCancelEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Cancel(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Cancel(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NavigationMode(
                            ABI::Microsoft::UI::Xaml::Navigation::NavigationMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SourcePageType(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Parameter(
                            IInspectable** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NavigationTransitionInfo(
                            ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigatingCancelEventArgs = _uuidof(INavigatingCancelEventArgs);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.INavigationEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.NavigationEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_INavigationEventArgs[] = L"Microsoft.UI.Xaml.Navigation.INavigationEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("876b70b4-2923-5785-9cea-2e44aa0761bd")
                    INavigationEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Content(
                            IInspectable** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Parameter(
                            IInspectable** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NavigationTransitionInfo(
                            ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SourcePageType(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NavigationMode(
                            ABI::Microsoft::UI::Xaml::Navigation::NavigationMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Uri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Uri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigationEventArgs = _uuidof(INavigationEventArgs);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.INavigationFailedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.NavigationFailedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_INavigationFailedEventArgs[] = L"Microsoft.UI.Xaml.Navigation.INavigationFailedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("f808f9a0-130c-5974-87f8-4433271a35a9")
                    INavigationFailedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Exception(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SourcePageType(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INavigationFailedEventArgs = _uuidof(INavigationFailedEventArgs);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IPageStackEntry
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IPageStackEntry[] = L"Microsoft.UI.Xaml.Navigation.IPageStackEntry";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("d591f56e-4262-5c91-9d79-29165cd82100")
                    IPageStackEntry : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_SourcePageType(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Parameter(
                            IInspectable** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NavigationTransitionInfo(
                            ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPageStackEntry = _uuidof(IPageStackEntry);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IPageStackEntryFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IPageStackEntryFactory[] = L"Microsoft.UI.Xaml.Navigation.IPageStackEntryFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("7e5a9469-6108-5e92-a499-5ee9f065a68a")
                    IPageStackEntryFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Windows::UI::Xaml::Interop::TypeName sourcePageType,
                            IInspectable* parameter,
                            ABI::Microsoft::UI::Xaml::Media::Animation::INavigationTransitionInfo* navigationTransitionInfo,
                            ABI::Microsoft::UI::Xaml::Navigation::IPageStackEntry** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPageStackEntryFactory = _uuidof(IPageStackEntryFactory);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IPageStackEntryStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IPageStackEntryStatics[] = L"Microsoft.UI.Xaml.Navigation.IPageStackEntryStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Navigation {
                    MIDL_INTERFACE("2f1d4cb7-923b-59bb-bfc4-750933f28385")
                    IPageStackEntryStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_SourcePageTypeProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPageStackEntryStatics = _uuidof(IPageStackEntryStatics);
                } /* Navigation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.FrameNavigationOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.IFrameNavigationOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_FrameNavigationOptions_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_FrameNavigationOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_FrameNavigationOptions[] = L"Microsoft.UI.Xaml.Navigation.FrameNavigationOptions";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.NavigatingCancelEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.INavigatingCancelEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigatingCancelEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigatingCancelEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_NavigatingCancelEventArgs[] = L"Microsoft.UI.Xaml.Navigation.NavigatingCancelEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.NavigationEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.INavigationEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_NavigationEventArgs[] = L"Microsoft.UI.Xaml.Navigation.NavigationEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.NavigationFailedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.INavigationFailedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationFailedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationFailedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_NavigationFailedEventArgs[] = L"Microsoft.UI.Xaml.Navigation.NavigationFailedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Navigation.IPageStackEntryFactory interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Navigation.IPageStackEntryStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.IPageStackEntry ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_PageStackEntry_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_PageStackEntry_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_PageStackEntry[] = L"Microsoft.UI.Xaml.Navigation.PageStackEntry";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CNavigationMode __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CNavigationMode;

/*
 *
 * Struct Microsoft.UI.Xaml.Navigation.NavigationCacheMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CNavigationCacheMode
{
    NavigationCacheMode_Disabled = 0,
    NavigationCacheMode_Required = 1,
    NavigationCacheMode_Enabled = 2,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Navigation.NavigationMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CNavigationMode
{
    NavigationMode_New = 0,
    NavigationMode_Back = 1,
    NavigationMode_Forward = 2,
    NavigationMode_Refresh = 3,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigatedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigatingCancelEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigationFailedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Navigation.NavigationStoppedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IFrameNavigationOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.FrameNavigationOptions
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IFrameNavigationOptions[] = L"Microsoft.UI.Xaml.Navigation.IFrameNavigationOptions";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsNavigationStackEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsNavigationStackEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_TransitionInfoOverride)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo** value);
    HRESULT (STDMETHODCALLTYPE* put_TransitionInfoOverride)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_get_IsNavigationStackEnabled(This, value) \
    ((This)->lpVtbl->get_IsNavigationStackEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_put_IsNavigationStackEnabled(This, value) \
    ((This)->lpVtbl->put_IsNavigationStackEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_get_TransitionInfoOverride(This, value) \
    ((This)->lpVtbl->get_TransitionInfoOverride(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_put_TransitionInfoOverride(This, value) \
    ((This)->lpVtbl->put_TransitionInfoOverride(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IFrameNavigationOptionsFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.FrameNavigationOptions
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IFrameNavigationOptionsFactory[] = L"Microsoft.UI.Xaml.Navigation.IFrameNavigationOptionsFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptions** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIFrameNavigationOptionsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.INavigatingCancelEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.NavigatingCancelEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_INavigatingCancelEventArgs[] = L"Microsoft.UI.Xaml.Navigation.INavigatingCancelEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_NavigationMode)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CNavigationMode* value);
    HRESULT (STDMETHODCALLTYPE* get_SourcePageType)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);
    HRESULT (STDMETHODCALLTYPE* get_Parameter)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_NavigationTransitionInfo)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_get_Cancel(This, value) \
    ((This)->lpVtbl->get_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_put_Cancel(This, value) \
    ((This)->lpVtbl->put_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_get_NavigationMode(This, value) \
    ((This)->lpVtbl->get_NavigationMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_get_SourcePageType(This, value) \
    ((This)->lpVtbl->get_SourcePageType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_get_Parameter(This, value) \
    ((This)->lpVtbl->get_Parameter(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_get_NavigationTransitionInfo(This, value) \
    ((This)->lpVtbl->get_NavigationTransitionInfo(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.INavigationEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.NavigationEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_INavigationEventArgs[] = L"Microsoft.UI.Xaml.Navigation.INavigationEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_Parameter)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_NavigationTransitionInfo)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo** value);
    HRESULT (STDMETHODCALLTYPE* get_SourcePageType)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);
    HRESULT (STDMETHODCALLTYPE* get_NavigationMode)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CNavigationMode* value);
    HRESULT (STDMETHODCALLTYPE* get_Uri)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_Uri)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_get_Parameter(This, value) \
    ((This)->lpVtbl->get_Parameter(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_get_NavigationTransitionInfo(This, value) \
    ((This)->lpVtbl->get_NavigationTransitionInfo(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_get_SourcePageType(This, value) \
    ((This)->lpVtbl->get_SourcePageType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_get_NavigationMode(This, value) \
    ((This)->lpVtbl->get_NavigationMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_get_Uri(This, value) \
    ((This)->lpVtbl->get_Uri(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_put_Uri(This, value) \
    ((This)->lpVtbl->put_Uri(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.INavigationFailedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.NavigationFailedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_INavigationFailedEventArgs[] = L"Microsoft.UI.Xaml.Navigation.INavigationFailedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Exception)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_SourcePageType)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_get_Exception(This, value) \
    ((This)->lpVtbl->get_Exception(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_get_SourcePageType(This, value) \
    ((This)->lpVtbl->get_SourcePageType(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IPageStackEntry
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IPageStackEntry[] = L"Microsoft.UI.Xaml.Navigation.IPageStackEntry";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SourcePageType)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);
    HRESULT (STDMETHODCALLTYPE* get_Parameter)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_NavigationTransitionInfo)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_get_SourcePageType(This, value) \
    ((This)->lpVtbl->get_SourcePageType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_get_Parameter(This, value) \
    ((This)->lpVtbl->get_Parameter(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_get_NavigationTransitionInfo(This, value) \
    ((This)->lpVtbl->get_NavigationTransitionInfo(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IPageStackEntryFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IPageStackEntryFactory[] = L"Microsoft.UI.Xaml.Navigation.IPageStackEntryFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName sourcePageType,
        IInspectable* parameter,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CAnimation_CINavigationTransitionInfo* navigationTransitionInfo,
        __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntry** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_CreateInstance(This, sourcePageType, parameter, navigationTransitionInfo, value) \
    ((This)->lpVtbl->CreateInstance(This, sourcePageType, parameter, navigationTransitionInfo, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Navigation.IPageStackEntryStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Navigation_IPageStackEntryStatics[] = L"Microsoft.UI.Xaml.Navigation.IPageStackEntryStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SourcePageTypeProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_get_SourcePageTypeProperty(This, value) \
    ((This)->lpVtbl->get_SourcePageTypeProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.FrameNavigationOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.IFrameNavigationOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_FrameNavigationOptions_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_FrameNavigationOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_FrameNavigationOptions[] = L"Microsoft.UI.Xaml.Navigation.FrameNavigationOptions";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.NavigatingCancelEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.INavigatingCancelEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigatingCancelEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigatingCancelEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_NavigatingCancelEventArgs[] = L"Microsoft.UI.Xaml.Navigation.NavigatingCancelEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.NavigationEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.INavigationEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_NavigationEventArgs[] = L"Microsoft.UI.Xaml.Navigation.NavigationEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.NavigationFailedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.INavigationFailedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationFailedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_NavigationFailedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_NavigationFailedEventArgs[] = L"Microsoft.UI.Xaml.Navigation.NavigationFailedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Navigation.PageStackEntry
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Navigation.IPageStackEntryFactory interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Navigation.IPageStackEntryStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Navigation.IPageStackEntry ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_PageStackEntry_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Navigation_PageStackEntry_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Navigation_PageStackEntry[] = L"Microsoft.UI.Xaml.Navigation.PageStackEntry";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Enavigation_p_h__

#endif // __microsoft2Eui2Examl2Enavigation_h__
