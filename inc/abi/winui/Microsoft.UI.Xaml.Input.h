
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
#ifndef __microsoft2Eui2Examl2Einput_h__
#define __microsoft2Eui2Examl2Einput_h__
#ifndef __microsoft2Eui2Examl2Einput_p_h__
#define __microsoft2Eui2Examl2Einput_p_h__


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

#if !defined(WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION)
#define WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION 0x70000
#endif // defined(WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.UI.Input.h"
#include "Microsoft.UI.Xaml.h"
#include "Microsoft.UI.Xaml.Controls.h"
#include "Windows.System.h"
#include "Windows.UI.Core.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IDoubleTappedEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler ABI::Microsoft::UI::Xaml::Input::IDoubleTappedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IHoldingEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler ABI::Microsoft::UI::Xaml::Input::IHoldingEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IKeyEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler ABI::Microsoft::UI::Xaml::Input::IKeyEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationCompletedEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler ABI::Microsoft::UI::Xaml::Input::IManipulationCompletedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationDeltaEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler ABI::Microsoft::UI::Xaml::Input::IManipulationDeltaEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationInertiaStartingEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler ABI::Microsoft::UI::Xaml::Input::IManipulationInertiaStartingEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationStartedEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler ABI::Microsoft::UI::Xaml::Input::IManipulationStartedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationStartingEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler ABI::Microsoft::UI::Xaml::Input::IManipulationStartingEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IPointerEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler ABI::Microsoft::UI::Xaml::Input::IPointerEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IRightTappedEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler ABI::Microsoft::UI::Xaml::Input::IRightTappedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface ITappedEventHandler;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler ABI::Microsoft::UI::Xaml::Input::ITappedEventHandler

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyDisplayDismissedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs ABI::Microsoft::UI::Xaml::Input::IAccessKeyDisplayDismissedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyDisplayRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs ABI::Microsoft::UI::Xaml::Input::IAccessKeyDisplayRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyInvokedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs ABI::Microsoft::UI::Xaml::Input::IAccessKeyInvokedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyManager;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager ABI::Microsoft::UI::Xaml::Input::IAccessKeyManager

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyManagerStatics;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics ABI::Microsoft::UI::Xaml::Input::IAccessKeyManagerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IAccessKeyManagerStatics2;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2 ABI::Microsoft::UI::Xaml::Input::IAccessKeyManagerStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface ICanExecuteRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs ABI::Microsoft::UI::Xaml::Input::ICanExecuteRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface ICharacterReceivedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::ICharacterReceivedRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface ICommand;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand ABI::Microsoft::UI::Xaml::Input::ICommand

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IContextRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs ABI::Microsoft::UI::Xaml::Input::IContextRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IDoubleTappedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IDoubleTappedRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IExecuteRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs ABI::Microsoft::UI::Xaml::Input::IExecuteRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IFindNextElementOptions;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions ABI::Microsoft::UI::Xaml::Input::IFindNextElementOptions

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IFocusManager;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager ABI::Microsoft::UI::Xaml::Input::IFocusManager

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IFocusManagerGotFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs ABI::Microsoft::UI::Xaml::Input::IFocusManagerGotFocusEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IFocusManagerLostFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs ABI::Microsoft::UI::Xaml::Input::IFocusManagerLostFocusEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IFocusManagerStatics;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics ABI::Microsoft::UI::Xaml::Input::IFocusManagerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IFocusMovementResult;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult ABI::Microsoft::UI::Xaml::Input::IFocusMovementResult

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IGettingFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs ABI::Microsoft::UI::Xaml::Input::IGettingFocusEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IHoldingRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IHoldingRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IInertiaExpansionBehavior;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior ABI::Microsoft::UI::Xaml::Input::IInertiaExpansionBehavior

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IInertiaRotationBehavior;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior ABI::Microsoft::UI::Xaml::Input::IInertiaRotationBehavior

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IInertiaTranslationBehavior;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior ABI::Microsoft::UI::Xaml::Input::IInertiaTranslationBehavior

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IInputScope;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope ABI::Microsoft::UI::Xaml::Input::IInputScope

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IInputScopeName;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName ABI::Microsoft::UI::Xaml::Input::IInputScopeName

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IInputScopeNameFactory;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory ABI::Microsoft::UI::Xaml::Input::IInputScopeNameFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IKeyRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IKeyRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IKeyboardAccelerator;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IKeyboardAcceleratorFactory;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory ABI::Microsoft::UI::Xaml::Input::IKeyboardAcceleratorFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IKeyboardAcceleratorInvokedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs ABI::Microsoft::UI::Xaml::Input::IKeyboardAcceleratorInvokedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IKeyboardAcceleratorStatics;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics ABI::Microsoft::UI::Xaml::Input::IKeyboardAcceleratorStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface ILosingFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs ABI::Microsoft::UI::Xaml::Input::ILosingFocusEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationCompletedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IManipulationCompletedRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationDeltaRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IManipulationDeltaRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationInertiaStartingRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IManipulationInertiaStartingRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationPivot;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot ABI::Microsoft::UI::Xaml::Input::IManipulationPivot

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationPivotFactory;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory ABI::Microsoft::UI::Xaml::Input::IManipulationPivotFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationStartedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IManipulationStartedRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationStartedRoutedEventArgsFactory;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory ABI::Microsoft::UI::Xaml::Input::IManipulationStartedRoutedEventArgsFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IManipulationStartingRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IManipulationStartingRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface INoFocusCandidateFoundEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs ABI::Microsoft::UI::Xaml::Input::INoFocusCandidateFoundEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IPointer;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer ABI::Microsoft::UI::Xaml::Input::IPointer

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IPointerRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IPointerRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IProcessKeyboardAcceleratorEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs ABI::Microsoft::UI::Xaml::Input::IProcessKeyboardAcceleratorEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IRightTappedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::IRightTappedRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IStandardUICommand;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand ABI::Microsoft::UI::Xaml::Input::IStandardUICommand

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IStandardUICommandFactory;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory ABI::Microsoft::UI::Xaml::Input::IStandardUICommandFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IStandardUICommandStatics;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics ABI::Microsoft::UI::Xaml::Input::IStandardUICommandStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface ITappedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs ABI::Microsoft::UI::Xaml::Input::ITappedRoutedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IXamlUICommand;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand ABI::Microsoft::UI::Xaml::Input::IXamlUICommand

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IXamlUICommandFactory;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory ABI::Microsoft::UI::Xaml::Input::IXamlUICommandFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    interface IXamlUICommandStatics;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics ABI::Microsoft::UI::Xaml::Input::IXamlUICommandStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class FocusMovementResult;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_USE
#define DEF___FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("edc8359c-34db-5065-b37e-c8dc44da81c1"))
IAsyncOperation<ABI::Microsoft::UI::Xaml::Input::FocusMovementResult*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::FocusMovementResult*, ABI::Microsoft::UI::Xaml::Input::IFocusMovementResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.UI.Xaml.Input.FocusMovementResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::UI::Xaml::Input::FocusMovementResult*> __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_t;
#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("276fb687-4b2c-535c-9177-ef701fdc052c"))
IAsyncOperationCompletedHandler<ABI::Microsoft::UI::Xaml::Input::FocusMovementResult*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::FocusMovementResult*, ABI::Microsoft::UI::Xaml::Input::IFocusMovementResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.UI.Xaml.Input.FocusMovementResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::UI::Xaml::Input::FocusMovementResult*> __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

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

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_USE
#define DEF___FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5b63939d-11cf-56c4-b0d0-11df9dc487d1"))
IIterator<ABI::Microsoft::UI::Input::PointerPoint*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Input::PointerPoint*, ABI::Microsoft::UI::Input::IPointerPoint*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Input.PointerPoint>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Input::PointerPoint*> __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_t;
#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_USE
#define DEF___FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("645acc33-ffce-5ad3-be2b-c49b9c27c35d"))
IIterable<ABI::Microsoft::UI::Input::PointerPoint*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Input::PointerPoint*, ABI::Microsoft::UI::Input::IPointerPoint*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Input.PointerPoint>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Input::PointerPoint*> __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_t;
#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class InputScopeName;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#define DEF___FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("07f0ed85-97c5-5d09-98a4-7b354c12ae99"))
IIterator<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::InputScopeName*, ABI::Microsoft::UI::Xaml::Input::IInputScopeName*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Xaml.Input.InputScopeName>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t;
#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#define DEF___FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("91489ea1-4d95-55ef-a2e0-7d108c5f5f6b"))
IIterable<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::InputScopeName*, ABI::Microsoft::UI::Xaml::Input::IInputScopeName*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Input.InputScopeName>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t;
#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class KeyboardAccelerator;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#define DEF___FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("6a7cb393-53c9-5481-ba42-90d431243d14"))
IIterator<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Xaml.Input.KeyboardAccelerator>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t;
#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#define DEF___FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("68b2e097-f07e-580f-8bfd-b90a0b2a8835"))
IIterable<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Xaml.Input.KeyboardAccelerator>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t;
#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5fbb224b-8430-5086-ab85-e71dfaa84c90"))
IVectorView<ABI::Microsoft::UI::Input::PointerPoint*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Input::PointerPoint*, ABI::Microsoft::UI::Input::IPointerPoint*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Input.PointerPoint>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::UI::Input::PointerPoint*> __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_t;
#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("183ab292-d2b3-568d-8431-4e3ff18b037e"))
IVectorView<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::InputScopeName*, ABI::Microsoft::UI::Xaml::Input::IInputScopeName*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Xaml.Input.InputScopeName>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t;
#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4d4dfa1a-7153-51f3-8036-6b61de68bca8"))
IVectorView<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Xaml.Input.KeyboardAccelerator>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t;
#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CUI__CInput__CPointerPoint_USE
#define DEF___FIVector_1_Microsoft__CUI__CInput__CPointerPoint_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8220cf33-5d76-5607-bb7d-b7cd07d27f33"))
IVector<ABI::Microsoft::UI::Input::PointerPoint*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Input::PointerPoint*, ABI::Microsoft::UI::Input::IPointerPoint*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.UI.Input.PointerPoint>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::UI::Input::PointerPoint*> __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_t;
#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CUI__CInput__CPointerPoint_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CUI__CInput__CPointerPoint_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#define DEF___FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("fe4c93e9-d6fa-5b96-9c74-de968c79c36e"))
IVector<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::InputScopeName*, ABI::Microsoft::UI::Xaml::Input::IInputScopeName*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Input.InputScopeName>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::UI::Xaml::Input::InputScopeName*> __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t;
#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#define DEF___FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("0db091c3-8538-5d25-937f-db6e003e1f71"))
IVector<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.UI.Xaml.Input.KeyboardAccelerator>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*> __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t;
#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class FocusManagerGotFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_USE
#define DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a1d02c1d-f665-502c-8d06-8f91021ccf98"))
IEventHandler<ABI::Microsoft::UI::Xaml::Input::FocusManagerGotFocusEventArgs*> : IEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::FocusManagerGotFocusEventArgs*, ABI::Microsoft::UI::Xaml::Input::IFocusManagerGotFocusEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<ABI::Microsoft::UI::Xaml::Input::FocusManagerGotFocusEventArgs*> __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_t;
#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs ABI::Windows::Foundation::__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class FocusManagerLostFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_USE
#define DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("5cad2aaf-c531-52bb-85fe-a1815468dbc2"))
IEventHandler<ABI::Microsoft::UI::Xaml::Input::FocusManagerLostFocusEventArgs*> : IEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::FocusManagerLostFocusEventArgs*, ABI::Microsoft::UI::Xaml::Input::IFocusManagerLostFocusEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<ABI::Microsoft::UI::Xaml::Input::FocusManagerLostFocusEventArgs*> __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_t;
#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs ABI::Windows::Foundation::__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class GettingFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_USE
#define DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("19b68d80-e219-5e3f-ac5b-6766fe4188ca"))
IEventHandler<ABI::Microsoft::UI::Xaml::Input::GettingFocusEventArgs*> : IEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::GettingFocusEventArgs*, ABI::Microsoft::UI::Xaml::Input::IGettingFocusEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Microsoft.UI.Xaml.Input.GettingFocusEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<ABI::Microsoft::UI::Xaml::Input::GettingFocusEventArgs*> __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_t;
#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs ABI::Windows::Foundation::__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class LosingFocusEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_USE
#define DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("e209d16e-08e0-545b-a0bc-558035bb8b00"))
IEventHandler<ABI::Microsoft::UI::Xaml::Input::LosingFocusEventArgs*> : IEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::LosingFocusEventArgs*, ABI::Microsoft::UI::Xaml::Input::ILosingFocusEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Microsoft.UI.Xaml.Input.LosingFocusEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<ABI::Microsoft::UI::Xaml::Input::LosingFocusEventArgs*> __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_t;
#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs ABI::Windows::Foundation::__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000


#ifndef DEF___FIEventHandler_1_IInspectable_USE
#define DEF___FIEventHandler_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("c50898f6-c536-5f47-8583-8b2c2438a13b"))
IEventHandler<IInspectable*> : IEventHandler_impl<IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<IInspectable*> __FIEventHandler_1_IInspectable_t;
#define __FIEventHandler_1_IInspectable ABI::Windows::Foundation::__FIEventHandler_1_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_IInspectable_USE */


namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class KeyboardAcceleratorInvokedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("03e5ce6a-5f2d-59d0-b573-0989fe6aead9"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs*, ABI::Microsoft::UI::Xaml::Input::IKeyboardAcceleratorInvokedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Input.KeyboardAccelerator, Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Input::KeyboardAccelerator*, ABI::Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class XamlUICommand;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class CanExecuteRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ebd28ec8-4602-5a98-92cd-b115bf4bd36d"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Input::XamlUICommand*, ABI::Microsoft::UI::Xaml::Input::CanExecuteRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::XamlUICommand*, ABI::Microsoft::UI::Xaml::Input::IXamlUICommand*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::CanExecuteRequestedEventArgs*, ABI::Microsoft::UI::Xaml::Input::ICanExecuteRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Input.XamlUICommand, Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Input::XamlUICommand*, ABI::Microsoft::UI::Xaml::Input::CanExecuteRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ExecuteRequestedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("2ca62a8a-c70a-5152-b3a8-495586d702cf"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Input::XamlUICommand*, ABI::Microsoft::UI::Xaml::Input::ExecuteRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::XamlUICommand*, ABI::Microsoft::UI::Xaml::Input::IXamlUICommand*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Input::ExecuteRequestedEventArgs*, ABI::Microsoft::UI::Xaml::Input::IExecuteRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Input.XamlUICommand, Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Input::XamlUICommand*, ABI::Microsoft::UI::Xaml::Input::ExecuteRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000


#ifndef DEF___FITypedEventHandler_2_IInspectable_IInspectable_USE
#define DEF___FITypedEventHandler_2_IInspectable_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("c7e65ce2-fad5-5e3b-9c58-186ca8c1dd57"))
ITypedEventHandler<IInspectable*, IInspectable*> : ITypedEventHandler_impl<IInspectable*, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Object, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<IInspectable*, IInspectable*> __FITypedEventHandler_2_IInspectable_IInspectable_t;
#define __FITypedEventHandler_2_IInspectable_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_IInspectable_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_IInspectable_IInspectable_USE */


namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                typedef enum HoldingState : int HoldingState;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                typedef struct ManipulationDelta ManipulationDelta;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                typedef struct ManipulationVelocities ManipulationVelocities;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                typedef enum PointerDeviceType : int PointerDeviceType;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Controls {
                    class IconSource;
                } /* Controls */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Controls {
                    interface IIconSource;
                } /* Controls */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource ABI::Microsoft::UI::Xaml::Controls::IIconSource

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class DependencyObject;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IDependencyObject;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject ABI::Microsoft::UI::Xaml::IDependencyObject

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__

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
                typedef enum FocusState : int FocusState;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class UIElement;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IUIElement;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement ABI::Microsoft::UI::Xaml::IUIElement

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class XamlRoot;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IXamlRoot;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot ABI::Microsoft::UI::Xaml::IXamlRoot

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Point Point;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Rect Rect;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace System {
            typedef enum VirtualKey : int VirtualKey;
        } /* System */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace System {
            typedef enum VirtualKeyModifiers : unsigned int VirtualKeyModifiers;
        } /* System */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Core {
                typedef struct CorePhysicalKeyStatus CorePhysicalKeyStatus;
            } /* Core */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum FocusInputDeviceKind : int FocusInputDeviceKind;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum FocusNavigationDirection : int FocusNavigationDirection;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum InputScopeNameValue : int InputScopeNameValue;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum ManipulationModes : unsigned int ManipulationModes;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum StandardUICommandKind : int StandardUICommandKind;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    typedef enum XYFocusNavigationStrategyOverride : int XYFocusNavigationStrategyOverride;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class DoubleTappedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class FindNextElementOptions;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class HoldingRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class InertiaExpansionBehavior;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class InertiaRotationBehavior;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class InertiaTranslationBehavior;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class KeyRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ManipulationCompletedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ManipulationDeltaRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ManipulationInertiaStartingRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ManipulationPivot;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ManipulationStartedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class ManipulationStartingRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class Pointer;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class PointerRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class RightTappedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class StandardUICommand;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    class TappedRoutedEventArgs;
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Input.FocusInputDeviceKind
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum FocusInputDeviceKind : int
                    {
                        FocusInputDeviceKind_None = 0,
                        FocusInputDeviceKind_Mouse = 1,
                        FocusInputDeviceKind_Touch = 2,
                        FocusInputDeviceKind_Pen = 3,
                        FocusInputDeviceKind_Keyboard = 4,
                        FocusInputDeviceKind_GameController = 5,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.FocusNavigationDirection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum FocusNavigationDirection : int
                    {
                        FocusNavigationDirection_Next = 0,
                        FocusNavigationDirection_Previous = 1,
                        FocusNavigationDirection_Up = 2,
                        FocusNavigationDirection_Down = 3,
                        FocusNavigationDirection_Left = 4,
                        FocusNavigationDirection_Right = 5,
                        FocusNavigationDirection_None = 6,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.InputScopeNameValue
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum InputScopeNameValue : int
                    {
                        InputScopeNameValue_Default = 0,
                        InputScopeNameValue_Url = 1,
                        InputScopeNameValue_EmailSmtpAddress = 5,
                        InputScopeNameValue_PersonalFullName = 7,
                        InputScopeNameValue_CurrencyAmountAndSymbol = 20,
                        InputScopeNameValue_CurrencyAmount = 21,
                        InputScopeNameValue_DateMonthNumber = 23,
                        InputScopeNameValue_DateDayNumber = 24,
                        InputScopeNameValue_DateYear = 25,
                        InputScopeNameValue_Digits = 28,
                        InputScopeNameValue_Number = 29,
                        InputScopeNameValue_Password = 31,
                        InputScopeNameValue_TelephoneNumber = 32,
                        InputScopeNameValue_TelephoneCountryCode = 33,
                        InputScopeNameValue_TelephoneAreaCode = 34,
                        InputScopeNameValue_TelephoneLocalNumber = 35,
                        InputScopeNameValue_TimeHour = 37,
                        InputScopeNameValue_TimeMinutesOrSeconds = 38,
                        InputScopeNameValue_NumberFullWidth = 39,
                        InputScopeNameValue_AlphanumericHalfWidth = 40,
                        InputScopeNameValue_AlphanumericFullWidth = 41,
                        InputScopeNameValue_Hiragana = 44,
                        InputScopeNameValue_KatakanaHalfWidth = 45,
                        InputScopeNameValue_KatakanaFullWidth = 46,
                        InputScopeNameValue_Hanja = 47,
                        InputScopeNameValue_HangulHalfWidth = 48,
                        InputScopeNameValue_HangulFullWidth = 49,
                        InputScopeNameValue_Search = 50,
                        InputScopeNameValue_Formula = 51,
                        InputScopeNameValue_SearchIncremental = 52,
                        InputScopeNameValue_ChineseHalfWidth = 53,
                        InputScopeNameValue_ChineseFullWidth = 54,
                        InputScopeNameValue_NativeScript = 55,
                        InputScopeNameValue_Text = 57,
                        InputScopeNameValue_Chat = 58,
                        InputScopeNameValue_NameOrPhoneNumber = 59,
                        InputScopeNameValue_EmailNameOrAddress = 60,
                        InputScopeNameValue_Maps = 62,
                        InputScopeNameValue_NumericPassword = 63,
                        InputScopeNameValue_NumericPin = 64,
                        InputScopeNameValue_AlphanumericPin = 65,
                        InputScopeNameValue_FormulaNumber = 67,
                        InputScopeNameValue_ChatWithoutEmoji = 68,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.KeyTipPlacementMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum KeyTipPlacementMode : int
                    {
                        KeyTipPlacementMode_Auto = 0,
                        KeyTipPlacementMode_Bottom = 1,
                        KeyTipPlacementMode_Top = 2,
                        KeyTipPlacementMode_Left = 3,
                        KeyTipPlacementMode_Right = 4,
                        KeyTipPlacementMode_Center = 5,
                        KeyTipPlacementMode_Hidden = 6,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.KeyboardAcceleratorPlacementMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum KeyboardAcceleratorPlacementMode : int
                    {
                        KeyboardAcceleratorPlacementMode_Auto = 0,
                        KeyboardAcceleratorPlacementMode_Hidden = 1,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.KeyboardNavigationMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum KeyboardNavigationMode : int
                    {
                        KeyboardNavigationMode_Local = 0,
                        KeyboardNavigationMode_Cycle = 1,
                        KeyboardNavigationMode_Once = 2,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.ManipulationModes
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum ManipulationModes : unsigned int
                    {
                        ManipulationModes_None = 0,
                        ManipulationModes_TranslateX = 0x1,
                        ManipulationModes_TranslateY = 0x2,
                        ManipulationModes_TranslateRailsX = 0x4,
                        ManipulationModes_TranslateRailsY = 0x8,
                        ManipulationModes_Rotate = 0x10,
                        ManipulationModes_Scale = 0x20,
                        ManipulationModes_TranslateInertia = 0x40,
                        ManipulationModes_RotateInertia = 0x80,
                        ManipulationModes_ScaleInertia = 0x100,
                        ManipulationModes_All = 0xffff,
                        ManipulationModes_System = 0x10000,
                    };

                    DEFINE_ENUM_FLAG_OPERATORS(ManipulationModes)
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.StandardUICommandKind
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum StandardUICommandKind : int
                    {
                        StandardUICommandKind_None = 0,
                        StandardUICommandKind_Cut = 1,
                        StandardUICommandKind_Copy = 2,
                        StandardUICommandKind_Paste = 3,
                        StandardUICommandKind_SelectAll = 4,
                        StandardUICommandKind_Delete = 5,
                        StandardUICommandKind_Share = 6,
                        StandardUICommandKind_Save = 7,
                        StandardUICommandKind_Open = 8,
                        StandardUICommandKind_Close = 9,
                        StandardUICommandKind_Pause = 10,
                        StandardUICommandKind_Play = 11,
                        StandardUICommandKind_Stop = 12,
                        StandardUICommandKind_Forward = 13,
                        StandardUICommandKind_Backward = 14,
                        StandardUICommandKind_Undo = 15,
                        StandardUICommandKind_Redo = 16,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.XYFocusKeyboardNavigationMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum XYFocusKeyboardNavigationMode : int
                    {
                        XYFocusKeyboardNavigationMode_Auto = 0,
                        XYFocusKeyboardNavigationMode_Enabled = 1,
                        XYFocusKeyboardNavigationMode_Disabled = 2,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.XYFocusNavigationStrategy
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum XYFocusNavigationStrategy : int
                    {
                        XYFocusNavigationStrategy_Auto = 0,
                        XYFocusNavigationStrategy_Projection = 1,
                        XYFocusNavigationStrategy_NavigationDirectionDistance = 2,
                        XYFocusNavigationStrategy_RectilinearDistance = 3,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.XYFocusNavigationStrategyOverride
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    enum XYFocusNavigationStrategyOverride : int
                    {
                        XYFocusNavigationStrategyOverride_None = 0,
                        XYFocusNavigationStrategyOverride_Auto = 1,
                        XYFocusNavigationStrategyOverride_Projection = 2,
                        XYFocusNavigationStrategyOverride_NavigationDirectionDistance = 3,
                        XYFocusNavigationStrategyOverride_RectilinearDistance = 4,
                    };
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.DoubleTappedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("f7a501b9-e277-5611-87b0-0e0607622183")
                    IDoubleTappedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IDoubleTappedRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDoubleTappedEventHandler = _uuidof(IDoubleTappedEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.HoldingEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("fe23c5bd-4984-56b6-b92b-fc9d1216b24e")
                    IHoldingEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IHoldingRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IHoldingEventHandler = _uuidof(IHoldingEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.KeyEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("db68e7cc-9a2b-527d-9989-25284daccc03")
                    IKeyEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IKeyRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKeyEventHandler = _uuidof(IKeyEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationCompletedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("d51df8db-71cd-5bfd-8426-767218ee55ec")
                    IManipulationCompletedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationCompletedRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationCompletedEventHandler = _uuidof(IManipulationCompletedEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationDeltaEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("83f2d4ce-105f-5392-a38a-b7467b7c2ea5")
                    IManipulationDeltaEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationDeltaRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationDeltaEventHandler = _uuidof(IManipulationDeltaEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationInertiaStartingEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("5de296bd-6f1c-5f60-9180-10705282576c")
                    IManipulationInertiaStartingEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationInertiaStartingRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationInertiaStartingEventHandler = _uuidof(IManipulationInertiaStartingEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationStartedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("41060669-304c-53ac-9d43-bc311235aae4")
                    IManipulationStartedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationStartedRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationStartedEventHandler = _uuidof(IManipulationStartedEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationStartingEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("44f528f1-f0e4-505c-a0bb-0c4839b29df5")
                    IManipulationStartingEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationStartingRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationStartingEventHandler = _uuidof(IManipulationStartingEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.PointerEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("a48a71e1-8bb4-5597-9e31-903a3f6a04fb")
                    IPointerEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IPointerRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPointerEventHandler = _uuidof(IPointerEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.RightTappedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("5070e32f-3dc7-56cf-8fdd-de1b40d0b472")
                    IRightTappedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::IRightTappedRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRightTappedEventHandler = _uuidof(IRightTappedEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.TappedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("b60074f3-125b-534e-8f9c-9769bd3f0f64")
                    ITappedEventHandler : public IUnknown
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Invoke(
                            IInspectable* sender,
                            ABI::Microsoft::UI::Xaml::Input::ITappedRoutedEventArgs* e
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITappedEventHandler = _uuidof(ITappedEventHandler);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyDisplayDismissedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyDisplayDismissedEventArgs[] = L"Microsoft.UI.Xaml.Input.IAccessKeyDisplayDismissedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("125a83d8-7f86-5ea9-9063-b9407e644587")
                    IAccessKeyDisplayDismissedEventArgs : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IAccessKeyDisplayDismissedEventArgs = _uuidof(IAccessKeyDisplayDismissedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyDisplayRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyDisplayRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.IAccessKeyDisplayRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("c4ed84d8-2b27-59b1-9cf0-7f9164de58cb")
                    IAccessKeyDisplayRequestedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PressedKeys(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAccessKeyDisplayRequestedEventArgs = _uuidof(IAccessKeyDisplayRequestedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.IAccessKeyInvokedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("d00c11a4-f9fb-5707-9692-98b80bb8546d")
                    IAccessKeyInvokedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAccessKeyInvokedEventArgs = _uuidof(IAccessKeyInvokedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyManager[] = L"Microsoft.UI.Xaml.Input.IAccessKeyManager";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("8f2a4402-a635-53dc-bc17-da911eabaade")
                    IAccessKeyManager : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IAccessKeyManager = _uuidof(IAccessKeyManager);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyManagerStatics[] = L"Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("3375aef7-742f-5e84-b76f-c187e08253bf")
                    IAccessKeyManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsDisplayModeEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AreKeyTipsEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AreKeyTipsEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_IsDisplayModeEnabledChanged(
                            __FITypedEventHandler_2_IInspectable_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_IsDisplayModeEnabledChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ExitDisplayMode(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAccessKeyManagerStatics = _uuidof(IAccessKeyManagerStatics);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyManagerStatics2[] = L"Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("512c9f63-24ad-5df2-b8ed-472406db31c0")
                    IAccessKeyManagerStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE EnterDisplayModeForXamlRoot(
                            ABI::Microsoft::UI::Xaml::IXamlRoot* XamlRoot
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAccessKeyManagerStatics2 = _uuidof(IAccessKeyManagerStatics2);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ICanExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ICanExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.ICanExecuteRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("e4bf6d7d-f6eb-53ca-a2d4-c741ec871e38")
                    ICanExecuteRequestedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Parameter(
                            IInspectable** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CanExecute(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CanExecute(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICanExecuteRequestedEventArgs = _uuidof(ICanExecuteRequestedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ICharacterReceivedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.CharacterReceivedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ICharacterReceivedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ICharacterReceivedRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("e26ca5bb-34c3-5c1e-9a16-00b80b07a899")
                    ICharacterReceivedRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Character(
                            WCHAR* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyStatus(
                            ABI::Windows::UI::Core::CorePhysicalKeyStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICharacterReceivedRoutedEventArgs = _uuidof(ICharacterReceivedRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ICommand[] = L"Microsoft.UI.Xaml.Input.ICommand";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("e5af3542-ca67-4081-995b-709dd13792df")
                    ICommand : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE add_CanExecuteChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_CanExecuteChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CanExecute(
                            IInspectable* parameter,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Execute(
                            IInspectable* parameter
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICommand = _uuidof(ICommand);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IContextRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ContextRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IContextRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.IContextRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("bcedcb98-77b5-53c0-802e-fd52f3806e51")
                    IContextRequestedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryGetPosition(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            ABI::Windows::Foundation::Point* point,
                            boolean* returnValue
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IContextRequestedEventArgs = _uuidof(IContextRequestedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IDoubleTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.DoubleTappedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IDoubleTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IDoubleTappedRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("32b9549d-11d8-53a5-a953-02409537a11f")
                    IDoubleTappedRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetPosition(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            ABI::Windows::Foundation::Point* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDoubleTappedRoutedEventArgs = _uuidof(IDoubleTappedRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.IExecuteRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("e1a9fd0c-34d0-5ae2-8f5d-377e7a8a2708")
                    IExecuteRequestedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Parameter(
                            IInspectable** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IExecuteRequestedEventArgs = _uuidof(IExecuteRequestedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFindNextElementOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FindNextElementOptions
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFindNextElementOptions[] = L"Microsoft.UI.Xaml.Input.IFindNextElementOptions";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("7f88e76b-7417-5447-aed4-2fabd291bdc6")
                    IFindNextElementOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_SearchRoot(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SearchRoot(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExclusionRect(
                            ABI::Windows::Foundation::Rect* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExclusionRect(
                            ABI::Windows::Foundation::Rect value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HintRect(
                            ABI::Windows::Foundation::Rect* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_HintRect(
                            ABI::Windows::Foundation::Rect value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_XYFocusNavigationStrategyOverride(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategyOverride* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_XYFocusNavigationStrategyOverride(
                            ABI::Microsoft::UI::Xaml::Input::XYFocusNavigationStrategyOverride value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFindNextElementOptions = _uuidof(IFindNextElementOptions);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManager[] = L"Microsoft.UI.Xaml.Input.IFocusManager";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("9fd07bc5-d2d4-53fe-a31a-846de8b7a257")
                    IFocusManager : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IFocusManager = _uuidof(IFocusManager);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManagerGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManagerGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.IFocusManagerGotFocusEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("50aca341-4519-59cf-83b1-c9c45cfdb816")
                    IFocusManagerGotFocusEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_NewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CorrelationId(
                            GUID* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFocusManagerGotFocusEventArgs = _uuidof(IFocusManagerGotFocusEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManagerLostFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManagerLostFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.IFocusManagerLostFocusEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("fdaf2c3f-a22e-5902-abce-b60758fbed1e")
                    IFocusManagerLostFocusEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_OldFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CorrelationId(
                            GUID* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFocusManagerLostFocusEventArgs = _uuidof(IFocusManagerLostFocusEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManagerStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManagerStatics[] = L"Microsoft.UI.Xaml.Input.IFocusManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("e73dce04-e23a-5fb3-96ab-7df04c51dff2")
                    IFocusManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE add_GotFocus(
                            __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_GotFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_LostFocus(
                            __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_LostFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_GettingFocus(
                            __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_GettingFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_LosingFocus(
                            __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_LosingFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryFocusAsync(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::FocusState value,
                            __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryMoveFocusAsync(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryMoveFocusWithOptionsAsync(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            ABI::Microsoft::UI::Xaml::Input::IFindNextElementOptions* focusNavigationOptions,
                            __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryMoveFocusWithOptions(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            ABI::Microsoft::UI::Xaml::Input::IFindNextElementOptions* focusNavigationOptions,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindNextElement(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            ABI::Microsoft::UI::Xaml::IDependencyObject** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindFirstFocusableElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* searchScope,
                            ABI::Microsoft::UI::Xaml::IDependencyObject** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindLastFocusableElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* searchScope,
                            ABI::Microsoft::UI::Xaml::IDependencyObject** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindNextElementWithOptions(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            ABI::Microsoft::UI::Xaml::Input::IFindNextElementOptions* focusNavigationOptions,
                            ABI::Microsoft::UI::Xaml::IDependencyObject** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindNextFocusableElement(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            ABI::Microsoft::UI::Xaml::IUIElement** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindNextFocusableElementWithHint(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            ABI::Windows::Foundation::Rect hintRect,
                            ABI::Microsoft::UI::Xaml::IUIElement** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryMoveFocus(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection focusNavigationDirection,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetFocusedElement(
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetFocusedElementWithRoot(
                            ABI::Microsoft::UI::Xaml::IXamlRoot* xamlRoot,
                            IInspectable** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFocusManagerStatics = _uuidof(IFocusManagerStatics);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusMovementResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusMovementResult
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusMovementResult[] = L"Microsoft.UI.Xaml.Input.IFocusMovementResult";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("a46259fd-3edd-554b-a188-0a47b71e4e1a")
                    IFocusMovementResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Succeeded(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFocusMovementResult = _uuidof(IFocusMovementResult);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IGettingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.GettingFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IGettingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.IGettingFocusEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("37fd3af0-bd3c-5bf5-a9cd-71a1e87af950")
                    IGettingFocusEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_OldFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_NewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FocusState(
                            ABI::Microsoft::UI::Xaml::FocusState* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Direction(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InputDevice(
                            ABI::Microsoft::UI::Xaml::Input::FocusInputDeviceKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Cancel(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Cancel(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CorrelationId(
                            GUID* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryCancel(
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TrySetNewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IGettingFocusEventArgs = _uuidof(IGettingFocusEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IHoldingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.HoldingRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IHoldingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IHoldingRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("8272a4b2-2221-551e-b0bb-16e29138ab20")
                    IHoldingRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HoldingState(
                            ABI::Microsoft::UI::Input::HoldingState* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetPosition(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            ABI::Windows::Foundation::Point* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IHoldingRoutedEventArgs = _uuidof(IHoldingRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInertiaExpansionBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InertiaExpansionBehavior
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInertiaExpansionBehavior[] = L"Microsoft.UI.Xaml.Input.IInertiaExpansionBehavior";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("d60029b7-f0cd-5aea-abe5-7410d09118c6")
                    IInertiaExpansionBehavior : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredDeceleration(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredDeceleration(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredExpansion(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredExpansion(
                            DOUBLE value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInertiaExpansionBehavior = _uuidof(IInertiaExpansionBehavior);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInertiaRotationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InertiaRotationBehavior
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInertiaRotationBehavior[] = L"Microsoft.UI.Xaml.Input.IInertiaRotationBehavior";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("27b4bd03-9149-5691-bce5-fa33b32c4a81")
                    IInertiaRotationBehavior : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredDeceleration(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredDeceleration(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredRotation(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredRotation(
                            DOUBLE value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInertiaRotationBehavior = _uuidof(IInertiaRotationBehavior);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInertiaTranslationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InertiaTranslationBehavior
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInertiaTranslationBehavior[] = L"Microsoft.UI.Xaml.Input.IInertiaTranslationBehavior";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("d4f91cf5-3317-5914-b25a-ea6ee55b96d0")
                    IInertiaTranslationBehavior : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredDeceleration(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredDeceleration(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredDisplacement(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredDisplacement(
                            DOUBLE value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInertiaTranslationBehavior = _uuidof(IInertiaTranslationBehavior);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInputScope
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InputScope
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInputScope[] = L"Microsoft.UI.Xaml.Input.IInputScope";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("76ea58b1-e910-5176-9147-695cc95e7da2")
                    IInputScope : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Names(
                            __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInputScope = _uuidof(IInputScope);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInputScopeName
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InputScopeName
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInputScopeName[] = L"Microsoft.UI.Xaml.Input.IInputScopeName";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("ee99a66d-28d0-53cb-82ee-1b6ee58bcc35")
                    IInputScopeName : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_NameValue(
                            ABI::Microsoft::UI::Xaml::Input::InputScopeNameValue* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_NameValue(
                            ABI::Microsoft::UI::Xaml::Input::InputScopeNameValue value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInputScopeName = _uuidof(IInputScopeName);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInputScopeNameFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InputScopeName
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInputScopeNameFactory[] = L"Microsoft.UI.Xaml.Input.IInputScopeNameFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("feec2efd-bc09-5cd6-9b47-6d35d1d87c61")
                    IInputScopeNameFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::UI::Xaml::Input::InputScopeNameValue nameValue,
                            ABI::Microsoft::UI::Xaml::Input::IInputScopeName** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInputScopeNameFactory = _uuidof(IInputScopeNameFactory);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IKeyRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("ee357007-a2d6-5c75-9431-05fd66ec7915")
                    IKeyRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Key(
                            ABI::Windows::System::VirtualKey* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyStatus(
                            ABI::Windows::UI::Core::CorePhysicalKeyStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OriginalKey(
                            ABI::Windows::System::VirtualKey* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeviceId(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKeyRoutedEventArgs = _uuidof(IKeyRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAccelerator
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAccelerator[] = L"Microsoft.UI.Xaml.Input.IKeyboardAccelerator";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("6f8bf1e2-4e91-5cf9-a6be-4770caf3d770")
                    IKeyboardAccelerator : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Key(
                            ABI::Windows::System::VirtualKey* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Key(
                            ABI::Windows::System::VirtualKey value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Modifiers(
                            ABI::Windows::System::VirtualKeyModifiers* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Modifiers(
                            ABI::Windows::System::VirtualKeyModifiers value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScopeOwner(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ScopeOwner(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_Invoked(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_Invoked(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKeyboardAccelerator = _uuidof(IKeyboardAccelerator);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAcceleratorFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAcceleratorFactory[] = L"Microsoft.UI.Xaml.Input.IKeyboardAcceleratorFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("ca1d410a-af2a-51b9-a1de-6c0af9f3b598")
                    IKeyboardAcceleratorFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKeyboardAcceleratorFactory = _uuidof(IKeyboardAcceleratorFactory);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAcceleratorInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAcceleratorInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.IKeyboardAcceleratorInvokedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("62c9fdb0-b574-527d-97eb-5c7f674441e0")
                    IKeyboardAcceleratorInvokedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Element(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyboardAccelerator(
                            ABI::Microsoft::UI::Xaml::Input::IKeyboardAccelerator** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKeyboardAcceleratorInvokedEventArgs = _uuidof(IKeyboardAcceleratorInvokedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAcceleratorStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAcceleratorStatics[] = L"Microsoft.UI.Xaml.Input.IKeyboardAcceleratorStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("73e674ca-73f4-5e77-b8d6-ff7852a63b0b")
                    IKeyboardAcceleratorStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_KeyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ModifiersProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsEnabledProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScopeOwnerProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKeyboardAcceleratorStatics = _uuidof(IKeyboardAcceleratorStatics);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ILosingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.LosingFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ILosingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.ILosingFocusEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("fa0e5ffa-2b1b-52f8-bb66-e35f51e73cf3")
                    ILosingFocusEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_OldFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_NewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FocusState(
                            ABI::Microsoft::UI::Xaml::FocusState* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Direction(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InputDevice(
                            ABI::Microsoft::UI::Xaml::Input::FocusInputDeviceKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Cancel(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Cancel(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CorrelationId(
                            GUID* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryCancel(
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TrySetNewFocusedElement(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ILosingFocusEventArgs = _uuidof(ILosingFocusEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationCompletedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("e3be9e4e-c5fb-5859-a81d-ce12fc3a2f4d")
                    IManipulationCompletedRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Container(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Point* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsInertial(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Cumulative(
                            ABI::Microsoft::UI::Input::ManipulationDelta* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Velocities(
                            ABI::Microsoft::UI::Input::ManipulationVelocities* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationCompletedRoutedEventArgs = _uuidof(IManipulationCompletedRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationDeltaRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("51369745-960f-54ac-93fa-763d22910dea")
                    IManipulationDeltaRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Container(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Point* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsInertial(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Delta(
                            ABI::Microsoft::UI::Input::ManipulationDelta* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Cumulative(
                            ABI::Microsoft::UI::Input::ManipulationDelta* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Velocities(
                            ABI::Microsoft::UI::Input::ManipulationVelocities* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Complete(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationDeltaRoutedEventArgs = _uuidof(IManipulationDeltaRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationInertiaStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("17d510be-5514-5952-9afd-959b60ab9394")
                    IManipulationInertiaStartingRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Container(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpansionBehavior(
                            ABI::Microsoft::UI::Xaml::Input::IInertiaExpansionBehavior** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExpansionBehavior(
                            ABI::Microsoft::UI::Xaml::Input::IInertiaExpansionBehavior* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RotationBehavior(
                            ABI::Microsoft::UI::Xaml::Input::IInertiaRotationBehavior** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RotationBehavior(
                            ABI::Microsoft::UI::Xaml::Input::IInertiaRotationBehavior* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TranslationBehavior(
                            ABI::Microsoft::UI::Xaml::Input::IInertiaTranslationBehavior** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TranslationBehavior(
                            ABI::Microsoft::UI::Xaml::Input::IInertiaTranslationBehavior* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Delta(
                            ABI::Microsoft::UI::Input::ManipulationDelta* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Cumulative(
                            ABI::Microsoft::UI::Input::ManipulationDelta* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Velocities(
                            ABI::Microsoft::UI::Input::ManipulationVelocities* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationInertiaStartingRoutedEventArgs = _uuidof(IManipulationInertiaStartingRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationPivot
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationPivot
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationPivot[] = L"Microsoft.UI.Xaml.Input.IManipulationPivot";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("286baba4-313d-507c-adc5-f739732cea27")
                    IManipulationPivot : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Center(
                            ABI::Windows::Foundation::Point* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Center(
                            ABI::Windows::Foundation::Point value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Radius(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Radius(
                            DOUBLE value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationPivot = _uuidof(IManipulationPivot);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationPivotFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationPivot
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationPivotFactory[] = L"Microsoft.UI.Xaml.Input.IManipulationPivotFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("67143ccd-ea6c-5fe2-bef2-adcbd7af52fd")
                    IManipulationPivotFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstanceWithCenterAndRadius(
                            ABI::Windows::Foundation::Point center,
                            DOUBLE radius,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationPivot** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationPivotFactory = _uuidof(IManipulationPivotFactory);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationStartedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("61857950-5821-5652-9fdf-c6277c5886f5")
                    IManipulationStartedRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Container(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Point* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Cumulative(
                            ABI::Microsoft::UI::Input::ManipulationDelta* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Complete(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationStartedRoutedEventArgs = _uuidof(IManipulationStartedRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgsFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationStartedRoutedEventArgsFactory[] = L"Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgsFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("5681b0de-3fa7-503e-9c46-a80339760292")
                    IManipulationStartedRoutedEventArgsFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Input::IManipulationStartedRoutedEventArgs** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationStartedRoutedEventArgsFactory = _uuidof(IManipulationStartedRoutedEventArgsFactory);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationStartingRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationStartingRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("93a99f86-f5a0-5326-91b0-851c897af79f")
                    IManipulationStartingRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Mode(
                            ABI::Microsoft::UI::Xaml::Input::ManipulationModes* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Mode(
                            ABI::Microsoft::UI::Xaml::Input::ManipulationModes value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Container(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Container(
                            ABI::Microsoft::UI::Xaml::IUIElement* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Pivot(
                            ABI::Microsoft::UI::Xaml::Input::IManipulationPivot** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Pivot(
                            ABI::Microsoft::UI::Xaml::Input::IManipulationPivot* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IManipulationStartingRoutedEventArgs = _uuidof(IManipulationStartingRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.INoFocusCandidateFoundEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.NoFocusCandidateFoundEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_INoFocusCandidateFoundEventArgs[] = L"Microsoft.UI.Xaml.Input.INoFocusCandidateFoundEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("a2d7153a-cd2a-59cb-a574-ac82e30b9201")
                    INoFocusCandidateFoundEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Direction(
                            ABI::Microsoft::UI::Xaml::Input::FocusNavigationDirection* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InputDevice(
                            ABI::Microsoft::UI::Xaml::Input::FocusInputDeviceKind* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_INoFocusCandidateFoundEventArgs = _uuidof(INoFocusCandidateFoundEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IPointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.Pointer
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IPointer[] = L"Microsoft.UI.Xaml.Input.IPointer";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("1f9afbf5-11a3-5e68-aa1b-72febfa0ab23")
                    IPointer : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PointerId(
                            UINT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsInContact(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsInRange(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPointer = _uuidof(IPointer);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IPointerRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.PointerRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IPointerRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IPointerRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("66e78a9a-1bec-5f92-b1a1-ea6334ee511c")
                    IPointerRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Pointer(
                            ABI::Microsoft::UI::Xaml::Input::IPointer** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyModifiers(
                            ABI::Windows::System::VirtualKeyModifiers* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsGenerated(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCurrentPoint(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            ABI::Microsoft::UI::Input::IPointerPoint** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetIntermediatePoints(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            __FIVector_1_Microsoft__CUI__CInput__CPointerPoint** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPointerRoutedEventArgs = _uuidof(IPointerRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IProcessKeyboardAcceleratorEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ProcessKeyboardAcceleratorEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IProcessKeyboardAcceleratorEventArgs[] = L"Microsoft.UI.Xaml.Input.IProcessKeyboardAcceleratorEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("9be0d058-3d26-5811-b50a-3bb80ca766c9")
                    IProcessKeyboardAcceleratorEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Key(
                            ABI::Windows::System::VirtualKey* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Modifiers(
                            ABI::Windows::System::VirtualKeyModifiers* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IProcessKeyboardAcceleratorEventArgs = _uuidof(IProcessKeyboardAcceleratorEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IRightTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IRightTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IRightTappedRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("3972fafb-2915-5c62-bb6b-54ad84ff400d")
                    IRightTappedRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetPosition(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            ABI::Windows::Foundation::Point* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRightTappedRoutedEventArgs = _uuidof(IRightTappedRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IStandardUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.StandardUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IStandardUICommand[] = L"Microsoft.UI.Xaml.Input.IStandardUICommand";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("5f395d50-5449-59ab-9cb2-4e3700033f03")
                    IStandardUICommand : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Kind(
                            ABI::Microsoft::UI::Xaml::Input::StandardUICommandKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Kind(
                            ABI::Microsoft::UI::Xaml::Input::StandardUICommandKind value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IStandardUICommand = _uuidof(IStandardUICommand);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IStandardUICommandFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.StandardUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IStandardUICommandFactory[] = L"Microsoft.UI.Xaml.Input.IStandardUICommandFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("5800f099-3746-5bcf-b1ce-af3d6bf8e83f")
                    IStandardUICommandFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Input::IStandardUICommand** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateInstanceWithKind(
                            ABI::Microsoft::UI::Xaml::Input::StandardUICommandKind kind,
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Input::IStandardUICommand** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IStandardUICommandFactory = _uuidof(IStandardUICommandFactory);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IStandardUICommandStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.StandardUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IStandardUICommandStatics[] = L"Microsoft.UI.Xaml.Input.IStandardUICommandStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("ab80c197-85cc-5d36-81aa-156cd63be31a")
                    IStandardUICommandStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_KindProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IStandardUICommandStatics = _uuidof(IStandardUICommandStatics);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ITappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.TappedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ITappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ITappedRoutedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("73f74b8c-3709-547e-8e0c-51c03c89126a")
                    ITappedRoutedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PointerDeviceType(
                            ABI::Microsoft::UI::Input::PointerDeviceType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Handled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Handled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetPosition(
                            ABI::Microsoft::UI::Xaml::IUIElement* relativeTo,
                            ABI::Windows::Foundation::Point* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITappedRoutedEventArgs = _uuidof(ITappedRoutedEventArgs);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IXamlUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.XamlUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IXamlUICommand[] = L"Microsoft.UI.Xaml.Input.IXamlUICommand";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("a457f2cb-51e0-541c-9c42-dd1dcbdf58fb")
                    IXamlUICommand : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Label(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Label(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IconSource(
                            ABI::Microsoft::UI::Xaml::Controls::IIconSource** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IconSource(
                            ABI::Microsoft::UI::Xaml::Controls::IIconSource* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyboardAccelerators(
                            __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessKey(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AccessKey(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Description(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Description(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Command(
                            ABI::Microsoft::UI::Xaml::Input::ICommand** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Command(
                            ABI::Microsoft::UI::Xaml::Input::ICommand* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_ExecuteRequested(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_ExecuteRequested(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_CanExecuteRequested(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_CanExecuteRequested(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE NotifyCanExecuteChanged(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlUICommand = _uuidof(IXamlUICommand);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IXamlUICommandFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.XamlUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IXamlUICommandFactory[] = L"Microsoft.UI.Xaml.Input.IXamlUICommandFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("f1f80a20-0e31-5505-8bc3-cdd1f0947f1d")
                    IXamlUICommandFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Input::IXamlUICommand** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlUICommandFactory = _uuidof(IXamlUICommandFactory);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IXamlUICommandStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.XamlUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IXamlUICommandStatics[] = L"Microsoft.UI.Xaml.Input.IXamlUICommandStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Input {
                    MIDL_INTERFACE("981dbda6-cdcb-5e35-b24b-c4f60ba148d9")
                    IXamlUICommandStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_LabelProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IconSourceProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyboardAcceleratorsProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessKeyProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DescriptionProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CommandProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlUICommandStatics = _uuidof(IXamlUICommandStatics);
                } /* Input */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyDisplayDismissedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayDismissedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayDismissedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyDisplayDismissedEventArgs[] = L"Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyDisplayRequestedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyDisplayRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyInvokedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyInvokedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyInvokedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics2 interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyManager[] = L"Microsoft.UI.Xaml.Input.AccessKeyManager";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ICanExecuteRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_CanExecuteRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_CanExecuteRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_CanExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.CharacterReceivedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ICharacterReceivedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_CharacterReceivedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_CharacterReceivedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_CharacterReceivedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.CharacterReceivedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ContextRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IContextRequestedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ContextRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ContextRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ContextRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.ContextRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.DoubleTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IDoubleTappedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_DoubleTappedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_DoubleTappedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_DoubleTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.DoubleTappedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IExecuteRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ExecuteRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ExecuteRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FindNextElementOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFindNextElementOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FindNextElementOptions_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FindNextElementOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FindNextElementOptions[] = L"Microsoft.UI.Xaml.Input.FindNextElementOptions";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IFocusManagerStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusManager[] = L"Microsoft.UI.Xaml.Input.FocusManager";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusManagerGotFocusEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerGotFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerGotFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusManagerGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusManagerLostFocusEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerLostFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerLostFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusManagerLostFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusMovementResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusMovementResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusMovementResult_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusMovementResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusMovementResult[] = L"Microsoft.UI.Xaml.Input.FocusMovementResult";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.GettingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IGettingFocusEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_GettingFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_GettingFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_GettingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.GettingFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.HoldingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IHoldingRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_HoldingRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_HoldingRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_HoldingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.HoldingRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InertiaExpansionBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInertiaExpansionBehavior ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaExpansionBehavior_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaExpansionBehavior_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InertiaExpansionBehavior[] = L"Microsoft.UI.Xaml.Input.InertiaExpansionBehavior";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InertiaRotationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInertiaRotationBehavior ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaRotationBehavior_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaRotationBehavior_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InertiaRotationBehavior[] = L"Microsoft.UI.Xaml.Input.InertiaRotationBehavior";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InertiaTranslationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInertiaTranslationBehavior ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaTranslationBehavior_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaTranslationBehavior_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InertiaTranslationBehavior[] = L"Microsoft.UI.Xaml.Input.InertiaTranslationBehavior";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InputScope
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInputScope ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScope_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScope_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InputScope[] = L"Microsoft.UI.Xaml.Input.InputScope";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InputScopeName
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Input.IInputScopeNameFactory interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInputScopeName ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScopeName_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScopeName_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InputScopeName[] = L"Microsoft.UI.Xaml.Input.InputScopeName";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.KeyRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IKeyRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_KeyRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.KeyRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IKeyboardAcceleratorStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IKeyboardAccelerator ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAccelerator_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAccelerator_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_KeyboardAccelerator[] = L"Microsoft.UI.Xaml.Input.KeyboardAccelerator";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IKeyboardAcceleratorInvokedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAcceleratorInvokedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAcceleratorInvokedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_KeyboardAcceleratorInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.LosingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ILosingFocusEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_LosingFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_LosingFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_LosingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.LosingFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationPivot
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Type can be activated via the Microsoft.UI.Xaml.Input.IManipulationPivotFactory interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationPivot ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationPivot_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationPivot_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationPivot[] = L"Microsoft.UI.Xaml.Input.ManipulationPivot";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationStartedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationStartingRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartingRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartingRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationStartingRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.NoFocusCandidateFoundEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.INoFocusCandidateFoundEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_NoFocusCandidateFoundEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_NoFocusCandidateFoundEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_NoFocusCandidateFoundEventArgs[] = L"Microsoft.UI.Xaml.Input.NoFocusCandidateFoundEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.Pointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IPointer ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_Pointer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_Pointer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_Pointer[] = L"Microsoft.UI.Xaml.Input.Pointer";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.PointerRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IPointerRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_PointerRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_PointerRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_PointerRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.PointerRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ProcessKeyboardAcceleratorEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IProcessKeyboardAcceleratorEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ProcessKeyboardAcceleratorEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ProcessKeyboardAcceleratorEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ProcessKeyboardAcceleratorEventArgs[] = L"Microsoft.UI.Xaml.Input.ProcessKeyboardAcceleratorEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IRightTappedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_RightTappedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_RightTappedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_RightTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.StandardUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IStandardUICommandStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IStandardUICommand ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_StandardUICommand_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_StandardUICommand_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_StandardUICommand[] = L"Microsoft.UI.Xaml.Input.StandardUICommand";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.TappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ITappedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_TappedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_TappedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_TappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.TappedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.XamlUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IXamlUICommandStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IXamlUICommand ** Default Interface **
 *    Microsoft.UI.Xaml.Input.ICommand
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_XamlUICommand_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_XamlUICommand_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_XamlUICommand[] = L"Microsoft.UI.Xaml.Input.XamlUICommand";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2 __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult;

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult;

typedef struct __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResultVtbl;

interface __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* This,
        __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResultVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CInput__CPointerPoint;

typedef struct __FIIterator_1_Microsoft__CUI__CInput__CPointerPointVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CInput__CPointerPointVtbl;

interface __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CInput__CPointerPointVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CInput__CPointerPoint;

typedef struct __FIIterable_1_Microsoft__CUI__CInput__CPointerPointVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CInput__CPointerPoint* This,
        __FIIterator_1_Microsoft__CUI__CInput__CPointerPoint** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CInput__CPointerPointVtbl;

interface __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CInput__CPointerPointVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

typedef struct __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl;

interface __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

typedef struct __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        __FIIterator_1_Microsoft__CUI__CXaml__CInput__CInputScopeName** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl;

interface __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

typedef struct __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl;

interface __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

typedef struct __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        __FIIterator_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl;

interface __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint;

typedef struct __FIVectorView_1_Microsoft__CUI__CInput__CPointerPointVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CInput__CPointerPointVtbl;

interface __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CInput__CPointerPointVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

typedef struct __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl;

interface __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

typedef struct __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl;

interface __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CUI__CInput__CPointerPoint __FIVector_1_Microsoft__CUI__CInput__CPointerPoint;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CUI__CInput__CPointerPoint;

typedef struct __FIVector_1_Microsoft__CUI__CInput__CPointerPointVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        __FIVectorView_1_Microsoft__CUI__CInput__CPointerPoint** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CUI__CInput__CPointerPoint* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CUI__CInput__CPointerPointVtbl;

interface __FIVector_1_Microsoft__CUI__CInput__CPointerPoint
{
    CONST_VTBL struct __FIVector_1_Microsoft__CUI__CInput__CPointerPointVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CUI__CInput__CPointerPoint_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName;

typedef struct __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CInputScopeName** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl;

interface __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName
{
    CONST_VTBL struct __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeNameVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator;

typedef struct __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        __FIVectorView_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl;

interface __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator
{
    CONST_VTBL struct __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs;

typedef struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* args);

    END_INTERFACE
} __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgsVtbl;

interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs
{
    CONST_VTBL struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs;

typedef struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* args);

    END_INTERFACE
} __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgsVtbl;

interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs
{
    CONST_VTBL struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs;

typedef struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* args);

    END_INTERFACE
} __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgsVtbl;

interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs
{
    CONST_VTBL struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs;

typedef struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* args);

    END_INTERFACE
} __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgsVtbl;

interface __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs
{
    CONST_VTBL struct __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if !defined(____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_IInspectable __FIEventHandler_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_IInspectable;

typedef struct __FIEventHandler_1_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_IInspectable* This,
        IInspectable* sender,
        IInspectable* args);

    END_INTERFACE
} __FIEventHandler_1_IInspectableVtbl;

interface __FIEventHandler_1_IInspectable
{
    CONST_VTBL struct __FIEventHandler_1_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#if !defined(____FITypedEventHandler_2_IInspectable_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_IInspectable_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_IInspectable_IInspectable __FITypedEventHandler_2_IInspectable_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_IInspectable_IInspectable;

typedef struct __FITypedEventHandler_2_IInspectable_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_IInspectable_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_IInspectable_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_IInspectable_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_IInspectable_IInspectable* This,
        IInspectable* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_IInspectable_IInspectableVtbl;

interface __FITypedEventHandler_2_IInspectable_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_IInspectable_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_IInspectable_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_IInspectable_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_IInspectable_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_IInspectable_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_IInspectable_IInspectable_INTERFACE_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CInput_CHoldingState __x_ABI_CMicrosoft_CUI_CInput_CHoldingState;

typedef struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta;

typedef struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationVelocities __x_ABI_CMicrosoft_CUI_CInput_CManipulationVelocities;

typedef enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState __x_ABI_CMicrosoft_CUI_CXaml_CFocusState;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

typedef enum __x_ABI_CWindows_CSystem_CVirtualKey __x_ABI_CWindows_CSystem_CVirtualKey;

typedef enum __x_ABI_CWindows_CSystem_CVirtualKeyModifiers __x_ABI_CWindows_CSystem_CVirtualKeyModifiers;

typedef struct __x_ABI_CWindows_CUI_CCore_CCorePhysicalKeyStatus __x_ABI_CWindows_CUI_CCore_CCorePhysicalKeyStatus;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusInputDeviceKind __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusInputDeviceKind;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CInputScopeNameValue __x_ABI_CMicrosoft_CUI_CXaml_CInput_CInputScopeNameValue;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CManipulationModes __x_ABI_CMicrosoft_CUI_CXaml_CInput_CManipulationModes;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CStandardUICommandKind __x_ABI_CMicrosoft_CUI_CXaml_CInput_CStandardUICommandKind;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategyOverride __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategyOverride;

/*
 *
 * Struct Microsoft.UI.Xaml.Input.FocusInputDeviceKind
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusInputDeviceKind
{
    FocusInputDeviceKind_None = 0,
    FocusInputDeviceKind_Mouse = 1,
    FocusInputDeviceKind_Touch = 2,
    FocusInputDeviceKind_Pen = 3,
    FocusInputDeviceKind_Keyboard = 4,
    FocusInputDeviceKind_GameController = 5,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.FocusNavigationDirection
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection
{
    FocusNavigationDirection_Next = 0,
    FocusNavigationDirection_Previous = 1,
    FocusNavigationDirection_Up = 2,
    FocusNavigationDirection_Down = 3,
    FocusNavigationDirection_Left = 4,
    FocusNavigationDirection_Right = 5,
    FocusNavigationDirection_None = 6,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.InputScopeNameValue
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CInputScopeNameValue
{
    InputScopeNameValue_Default = 0,
    InputScopeNameValue_Url = 1,
    InputScopeNameValue_EmailSmtpAddress = 5,
    InputScopeNameValue_PersonalFullName = 7,
    InputScopeNameValue_CurrencyAmountAndSymbol = 20,
    InputScopeNameValue_CurrencyAmount = 21,
    InputScopeNameValue_DateMonthNumber = 23,
    InputScopeNameValue_DateDayNumber = 24,
    InputScopeNameValue_DateYear = 25,
    InputScopeNameValue_Digits = 28,
    InputScopeNameValue_Number = 29,
    InputScopeNameValue_Password = 31,
    InputScopeNameValue_TelephoneNumber = 32,
    InputScopeNameValue_TelephoneCountryCode = 33,
    InputScopeNameValue_TelephoneAreaCode = 34,
    InputScopeNameValue_TelephoneLocalNumber = 35,
    InputScopeNameValue_TimeHour = 37,
    InputScopeNameValue_TimeMinutesOrSeconds = 38,
    InputScopeNameValue_NumberFullWidth = 39,
    InputScopeNameValue_AlphanumericHalfWidth = 40,
    InputScopeNameValue_AlphanumericFullWidth = 41,
    InputScopeNameValue_Hiragana = 44,
    InputScopeNameValue_KatakanaHalfWidth = 45,
    InputScopeNameValue_KatakanaFullWidth = 46,
    InputScopeNameValue_Hanja = 47,
    InputScopeNameValue_HangulHalfWidth = 48,
    InputScopeNameValue_HangulFullWidth = 49,
    InputScopeNameValue_Search = 50,
    InputScopeNameValue_Formula = 51,
    InputScopeNameValue_SearchIncremental = 52,
    InputScopeNameValue_ChineseHalfWidth = 53,
    InputScopeNameValue_ChineseFullWidth = 54,
    InputScopeNameValue_NativeScript = 55,
    InputScopeNameValue_Text = 57,
    InputScopeNameValue_Chat = 58,
    InputScopeNameValue_NameOrPhoneNumber = 59,
    InputScopeNameValue_EmailNameOrAddress = 60,
    InputScopeNameValue_Maps = 62,
    InputScopeNameValue_NumericPassword = 63,
    InputScopeNameValue_NumericPin = 64,
    InputScopeNameValue_AlphanumericPin = 65,
    InputScopeNameValue_FormulaNumber = 67,
    InputScopeNameValue_ChatWithoutEmoji = 68,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.KeyTipPlacementMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyTipPlacementMode
{
    KeyTipPlacementMode_Auto = 0,
    KeyTipPlacementMode_Bottom = 1,
    KeyTipPlacementMode_Top = 2,
    KeyTipPlacementMode_Left = 3,
    KeyTipPlacementMode_Right = 4,
    KeyTipPlacementMode_Center = 5,
    KeyTipPlacementMode_Hidden = 6,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.KeyboardAcceleratorPlacementMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyboardAcceleratorPlacementMode
{
    KeyboardAcceleratorPlacementMode_Auto = 0,
    KeyboardAcceleratorPlacementMode_Hidden = 1,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.KeyboardNavigationMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CKeyboardNavigationMode
{
    KeyboardNavigationMode_Local = 0,
    KeyboardNavigationMode_Cycle = 1,
    KeyboardNavigationMode_Once = 2,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.ManipulationModes
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CManipulationModes
{
    ManipulationModes_None = 0,
    ManipulationModes_TranslateX = 0x1,
    ManipulationModes_TranslateY = 0x2,
    ManipulationModes_TranslateRailsX = 0x4,
    ManipulationModes_TranslateRailsY = 0x8,
    ManipulationModes_Rotate = 0x10,
    ManipulationModes_Scale = 0x20,
    ManipulationModes_TranslateInertia = 0x40,
    ManipulationModes_RotateInertia = 0x80,
    ManipulationModes_ScaleInertia = 0x100,
    ManipulationModes_All = 0xffff,
    ManipulationModes_System = 0x10000,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.StandardUICommandKind
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CStandardUICommandKind
{
    StandardUICommandKind_None = 0,
    StandardUICommandKind_Cut = 1,
    StandardUICommandKind_Copy = 2,
    StandardUICommandKind_Paste = 3,
    StandardUICommandKind_SelectAll = 4,
    StandardUICommandKind_Delete = 5,
    StandardUICommandKind_Share = 6,
    StandardUICommandKind_Save = 7,
    StandardUICommandKind_Open = 8,
    StandardUICommandKind_Close = 9,
    StandardUICommandKind_Pause = 10,
    StandardUICommandKind_Play = 11,
    StandardUICommandKind_Stop = 12,
    StandardUICommandKind_Forward = 13,
    StandardUICommandKind_Backward = 14,
    StandardUICommandKind_Undo = 15,
    StandardUICommandKind_Redo = 16,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.XYFocusKeyboardNavigationMode
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusKeyboardNavigationMode
{
    XYFocusKeyboardNavigationMode_Auto = 0,
    XYFocusKeyboardNavigationMode_Enabled = 1,
    XYFocusKeyboardNavigationMode_Disabled = 2,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.XYFocusNavigationStrategy
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategy
{
    XYFocusNavigationStrategy_Auto = 0,
    XYFocusNavigationStrategy_Projection = 1,
    XYFocusNavigationStrategy_NavigationDirectionDistance = 2,
    XYFocusNavigationStrategy_RectilinearDistance = 3,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Input.XYFocusNavigationStrategyOverride
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategyOverride
{
    XYFocusNavigationStrategyOverride_None = 0,
    XYFocusNavigationStrategyOverride_Auto = 1,
    XYFocusNavigationStrategyOverride_Projection = 2,
    XYFocusNavigationStrategyOverride_NavigationDirectionDistance = 3,
    XYFocusNavigationStrategyOverride_RectilinearDistance = 4,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.DoubleTappedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.HoldingEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.KeyEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationCompletedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationDeltaEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationInertiaStartingEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationStartedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.ManipulationStartingEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.PointerEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.RightTappedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.Xaml.Input.TappedEventHandler
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* e);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_Invoke(This, sender, e) \
    ((This)->lpVtbl->Invoke(This, sender, e))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyDisplayDismissedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyDisplayDismissedEventArgs[] = L"Microsoft.UI.Xaml.Input.IAccessKeyDisplayDismissedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayDismissedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyDisplayRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyDisplayRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.IAccessKeyDisplayRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PressedKeys)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_get_PressedKeys(This, value) \
    ((This)->lpVtbl->get_PressedKeys(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyDisplayRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.IAccessKeyInvokedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyInvokedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyManager[] = L"Microsoft.UI.Xaml.Input.IAccessKeyManager";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyManagerStatics[] = L"Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsDisplayModeEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_AreKeyTipsEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AreKeyTipsEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* add_IsDisplayModeEnabledChanged)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        __FITypedEventHandler_2_IInspectable_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_IsDisplayModeEnabledChanged)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* ExitDisplayMode)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_get_IsDisplayModeEnabled(This, value) \
    ((This)->lpVtbl->get_IsDisplayModeEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_get_AreKeyTipsEnabled(This, value) \
    ((This)->lpVtbl->get_AreKeyTipsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_put_AreKeyTipsEnabled(This, value) \
    ((This)->lpVtbl->put_AreKeyTipsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_add_IsDisplayModeEnabledChanged(This, handler, token) \
    ((This)->lpVtbl->add_IsDisplayModeEnabledChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_remove_IsDisplayModeEnabledChanged(This, token) \
    ((This)->lpVtbl->remove_IsDisplayModeEnabledChanged(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_ExitDisplayMode(This) \
    ((This)->lpVtbl->ExitDisplayMode(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IAccessKeyManagerStatics2[] = L"Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* EnterDisplayModeForXamlRoot)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot* XamlRoot);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_EnterDisplayModeForXamlRoot(This, XamlRoot) \
    ((This)->lpVtbl->EnterDisplayModeForXamlRoot(This, XamlRoot))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIAccessKeyManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ICanExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ICanExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.ICanExecuteRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Parameter)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_CanExecute)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_CanExecute)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_get_Parameter(This, value) \
    ((This)->lpVtbl->get_Parameter(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_get_CanExecute(This, value) \
    ((This)->lpVtbl->get_CanExecute(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_put_CanExecute(This, value) \
    ((This)->lpVtbl->put_CanExecute(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICanExecuteRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ICharacterReceivedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.CharacterReceivedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ICharacterReceivedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ICharacterReceivedRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Character)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        WCHAR* value);
    HRESULT (STDMETHODCALLTYPE* get_KeyStatus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        struct __x_ABI_CWindows_CUI_CCore_CCorePhysicalKeyStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_get_Character(This, value) \
    ((This)->lpVtbl->get_Character(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_get_KeyStatus(This, value) \
    ((This)->lpVtbl->get_KeyStatus(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICharacterReceivedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ICommand[] = L"Microsoft.UI.Xaml.Input.ICommand";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommandVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* add_CanExecuteChanged)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_CanExecuteChanged)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* CanExecute)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        IInspectable* parameter,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Execute)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* This,
        IInspectable* parameter);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommandVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommandVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_add_CanExecuteChanged(This, handler, token) \
    ((This)->lpVtbl->add_CanExecuteChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_remove_CanExecuteChanged(This, token) \
    ((This)->lpVtbl->remove_CanExecuteChanged(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_CanExecute(This, parameter, result) \
    ((This)->lpVtbl->CanExecute(This, parameter, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_Execute(This, parameter) \
    ((This)->lpVtbl->Execute(This, parameter))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IContextRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ContextRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IContextRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.IContextRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* TryGetPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        struct __x_ABI_CWindows_CFoundation_CPoint* point,
        boolean* returnValue);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_TryGetPosition(This, relativeTo, point, returnValue) \
    ((This)->lpVtbl->TryGetPosition(This, relativeTo, point, returnValue))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIContextRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IDoubleTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.DoubleTappedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IDoubleTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IDoubleTappedRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* GetPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        struct __x_ABI_CWindows_CFoundation_CPoint* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_GetPosition(This, relativeTo, result) \
    ((This)->lpVtbl->GetPosition(This, relativeTo, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.IExecuteRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Parameter)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs* This,
        IInspectable** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_get_Parameter(This, value) \
    ((This)->lpVtbl->get_Parameter(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIExecuteRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFindNextElementOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FindNextElementOptions
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFindNextElementOptions[] = L"Microsoft.UI.Xaml.Input.IFindNextElementOptions";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SearchRoot)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_SearchRoot)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_ExclusionRect)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        struct __x_ABI_CWindows_CFoundation_CRect* value);
    HRESULT (STDMETHODCALLTYPE* put_ExclusionRect)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        struct __x_ABI_CWindows_CFoundation_CRect value);
    HRESULT (STDMETHODCALLTYPE* get_HintRect)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        struct __x_ABI_CWindows_CFoundation_CRect* value);
    HRESULT (STDMETHODCALLTYPE* put_HintRect)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        struct __x_ABI_CWindows_CFoundation_CRect value);
    HRESULT (STDMETHODCALLTYPE* get_XYFocusNavigationStrategyOverride)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategyOverride* value);
    HRESULT (STDMETHODCALLTYPE* put_XYFocusNavigationStrategyOverride)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CXYFocusNavigationStrategyOverride value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptionsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_get_SearchRoot(This, value) \
    ((This)->lpVtbl->get_SearchRoot(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_put_SearchRoot(This, value) \
    ((This)->lpVtbl->put_SearchRoot(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_get_ExclusionRect(This, value) \
    ((This)->lpVtbl->get_ExclusionRect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_put_ExclusionRect(This, value) \
    ((This)->lpVtbl->put_ExclusionRect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_get_HintRect(This, value) \
    ((This)->lpVtbl->get_HintRect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_put_HintRect(This, value) \
    ((This)->lpVtbl->put_HintRect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_get_XYFocusNavigationStrategyOverride(This, value) \
    ((This)->lpVtbl->get_XYFocusNavigationStrategyOverride(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_put_XYFocusNavigationStrategyOverride(This, value) \
    ((This)->lpVtbl->put_XYFocusNavigationStrategyOverride(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManager[] = L"Microsoft.UI.Xaml.Input.IFocusManager";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManagerGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManagerGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.IFocusManagerGotFocusEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_NewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* get_CorrelationId)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs* This,
        GUID* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_get_NewFocusedElement(This, value) \
    ((This)->lpVtbl->get_NewFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_get_CorrelationId(This, value) \
    ((This)->lpVtbl->get_CorrelationId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerGotFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManagerLostFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManagerLostFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.IFocusManagerLostFocusEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_OldFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* get_CorrelationId)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs* This,
        GUID* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_get_OldFocusedElement(This, value) \
    ((This)->lpVtbl->get_OldFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_get_CorrelationId(This, value) \
    ((This)->lpVtbl->get_CorrelationId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerLostFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusManagerStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusManagerStatics[] = L"Microsoft.UI.Xaml.Input.IFocusManagerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* add_GotFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerGotFocusEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_GotFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_LostFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CFocusManagerLostFocusEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_LostFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_GettingFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CGettingFocusEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_GettingFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_LosingFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __FIEventHandler_1_Microsoft__CUI__CXaml__CInput__CLosingFocusEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_LosingFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* TryFocusAsync)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState value,
        __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** operation);
    HRESULT (STDMETHODCALLTYPE* TryMoveFocusAsync)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** operation);
    HRESULT (STDMETHODCALLTYPE* TryMoveFocusWithOptionsAsync)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* focusNavigationOptions,
        __FIAsyncOperation_1_Microsoft__CUI__CXaml__CInput__CFocusMovementResult** operation);
    HRESULT (STDMETHODCALLTYPE* TryMoveFocusWithOptions)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* focusNavigationOptions,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* FindNextElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** result);
    HRESULT (STDMETHODCALLTYPE* FindFirstFocusableElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* searchScope,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** result);
    HRESULT (STDMETHODCALLTYPE* FindLastFocusableElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* searchScope,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** result);
    HRESULT (STDMETHODCALLTYPE* FindNextElementWithOptions)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFindNextElementOptions* focusNavigationOptions,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** result);
    HRESULT (STDMETHODCALLTYPE* FindNextFocusableElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** result);
    HRESULT (STDMETHODCALLTYPE* FindNextFocusableElementWithHint)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        struct __x_ABI_CWindows_CFoundation_CRect hintRect,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** result);
    HRESULT (STDMETHODCALLTYPE* TryMoveFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection focusNavigationDirection,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* GetFocusedElementWithRoot)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIXamlRoot* xamlRoot,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_add_GotFocus(This, handler, token) \
    ((This)->lpVtbl->add_GotFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_remove_GotFocus(This, token) \
    ((This)->lpVtbl->remove_GotFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_add_LostFocus(This, handler, token) \
    ((This)->lpVtbl->add_LostFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_remove_LostFocus(This, token) \
    ((This)->lpVtbl->remove_LostFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_add_GettingFocus(This, handler, token) \
    ((This)->lpVtbl->add_GettingFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_remove_GettingFocus(This, token) \
    ((This)->lpVtbl->remove_GettingFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_add_LosingFocus(This, handler, token) \
    ((This)->lpVtbl->add_LosingFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_remove_LosingFocus(This, token) \
    ((This)->lpVtbl->remove_LosingFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_TryFocusAsync(This, element, value, operation) \
    ((This)->lpVtbl->TryFocusAsync(This, element, value, operation))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_TryMoveFocusAsync(This, focusNavigationDirection, operation) \
    ((This)->lpVtbl->TryMoveFocusAsync(This, focusNavigationDirection, operation))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_TryMoveFocusWithOptionsAsync(This, focusNavigationDirection, focusNavigationOptions, operation) \
    ((This)->lpVtbl->TryMoveFocusWithOptionsAsync(This, focusNavigationDirection, focusNavigationOptions, operation))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_TryMoveFocusWithOptions(This, focusNavigationDirection, focusNavigationOptions, result) \
    ((This)->lpVtbl->TryMoveFocusWithOptions(This, focusNavigationDirection, focusNavigationOptions, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FindNextElement(This, focusNavigationDirection, result) \
    ((This)->lpVtbl->FindNextElement(This, focusNavigationDirection, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FindFirstFocusableElement(This, searchScope, result) \
    ((This)->lpVtbl->FindFirstFocusableElement(This, searchScope, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FindLastFocusableElement(This, searchScope, result) \
    ((This)->lpVtbl->FindLastFocusableElement(This, searchScope, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FindNextElementWithOptions(This, focusNavigationDirection, focusNavigationOptions, result) \
    ((This)->lpVtbl->FindNextElementWithOptions(This, focusNavigationDirection, focusNavigationOptions, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FindNextFocusableElement(This, focusNavigationDirection, result) \
    ((This)->lpVtbl->FindNextFocusableElement(This, focusNavigationDirection, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_FindNextFocusableElementWithHint(This, focusNavigationDirection, hintRect, result) \
    ((This)->lpVtbl->FindNextFocusableElementWithHint(This, focusNavigationDirection, hintRect, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_TryMoveFocus(This, focusNavigationDirection, result) \
    ((This)->lpVtbl->TryMoveFocus(This, focusNavigationDirection, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_GetFocusedElement(This, result) \
    ((This)->lpVtbl->GetFocusedElement(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_GetFocusedElementWithRoot(This, xamlRoot, result) \
    ((This)->lpVtbl->GetFocusedElementWithRoot(This, xamlRoot, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IFocusMovementResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.FocusMovementResult
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IFocusMovementResult[] = L"Microsoft.UI.Xaml.Input.IFocusMovementResult";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Succeeded)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResultVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_get_Succeeded(This, value) \
    ((This)->lpVtbl->get_Succeeded(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIFocusMovementResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IGettingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.GettingFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IGettingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.IGettingFocusEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_OldFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* get_NewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_NewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_FocusState)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState* value);
    HRESULT (STDMETHODCALLTYPE* get_Direction)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_InputDevice)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusInputDeviceKind* value);
    HRESULT (STDMETHODCALLTYPE* get_Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_CorrelationId)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        GUID* value);
    HRESULT (STDMETHODCALLTYPE* TryCancel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* TrySetNewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_OldFocusedElement(This, value) \
    ((This)->lpVtbl->get_OldFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_NewFocusedElement(This, value) \
    ((This)->lpVtbl->get_NewFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_put_NewFocusedElement(This, value) \
    ((This)->lpVtbl->put_NewFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_FocusState(This, value) \
    ((This)->lpVtbl->get_FocusState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_Direction(This, value) \
    ((This)->lpVtbl->get_Direction(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_InputDevice(This, value) \
    ((This)->lpVtbl->get_InputDevice(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_Cancel(This, value) \
    ((This)->lpVtbl->get_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_put_Cancel(This, value) \
    ((This)->lpVtbl->put_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_get_CorrelationId(This, value) \
    ((This)->lpVtbl->get_CorrelationId(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_TryCancel(This, result) \
    ((This)->lpVtbl->TryCancel(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_TrySetNewFocusedElement(This, element, result) \
    ((This)->lpVtbl->TrySetNewFocusedElement(This, element, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIGettingFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IHoldingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.HoldingRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IHoldingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IHoldingRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_HoldingState)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CHoldingState* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* GetPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        struct __x_ABI_CWindows_CFoundation_CPoint* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_get_HoldingState(This, value) \
    ((This)->lpVtbl->get_HoldingState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_GetPosition(This, relativeTo, result) \
    ((This)->lpVtbl->GetPosition(This, relativeTo, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInertiaExpansionBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InertiaExpansionBehavior
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInertiaExpansionBehavior[] = L"Microsoft.UI.Xaml.Input.IInertiaExpansionBehavior";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehaviorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DesiredDeceleration)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredDeceleration)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_DesiredExpansion)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredExpansion)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehaviorVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehaviorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_get_DesiredDeceleration(This, value) \
    ((This)->lpVtbl->get_DesiredDeceleration(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_put_DesiredDeceleration(This, value) \
    ((This)->lpVtbl->put_DesiredDeceleration(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_get_DesiredExpansion(This, value) \
    ((This)->lpVtbl->get_DesiredExpansion(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_put_DesiredExpansion(This, value) \
    ((This)->lpVtbl->put_DesiredExpansion(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInertiaRotationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InertiaRotationBehavior
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInertiaRotationBehavior[] = L"Microsoft.UI.Xaml.Input.IInertiaRotationBehavior";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehaviorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DesiredDeceleration)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredDeceleration)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_DesiredRotation)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredRotation)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehaviorVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehaviorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_get_DesiredDeceleration(This, value) \
    ((This)->lpVtbl->get_DesiredDeceleration(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_put_DesiredDeceleration(This, value) \
    ((This)->lpVtbl->put_DesiredDeceleration(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_get_DesiredRotation(This, value) \
    ((This)->lpVtbl->get_DesiredRotation(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_put_DesiredRotation(This, value) \
    ((This)->lpVtbl->put_DesiredRotation(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInertiaTranslationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InertiaTranslationBehavior
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInertiaTranslationBehavior[] = L"Microsoft.UI.Xaml.Input.IInertiaTranslationBehavior";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehaviorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DesiredDeceleration)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredDeceleration)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_DesiredDisplacement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredDisplacement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehaviorVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehaviorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_get_DesiredDeceleration(This, value) \
    ((This)->lpVtbl->get_DesiredDeceleration(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_put_DesiredDeceleration(This, value) \
    ((This)->lpVtbl->put_DesiredDeceleration(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_get_DesiredDisplacement(This, value) \
    ((This)->lpVtbl->get_DesiredDisplacement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_put_DesiredDisplacement(This, value) \
    ((This)->lpVtbl->put_DesiredDisplacement(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInputScope
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InputScope
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInputScope[] = L"Microsoft.UI.Xaml.Input.IInputScope";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Names)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope* This,
        __FIVector_1_Microsoft__CUI__CXaml__CInput__CInputScopeName** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_get_Names(This, value) \
    ((This)->lpVtbl->get_Names(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInputScopeName
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InputScopeName
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInputScopeName[] = L"Microsoft.UI.Xaml.Input.IInputScopeName";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_NameValue)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CInputScopeNameValue* value);
    HRESULT (STDMETHODCALLTYPE* put_NameValue)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CInputScopeNameValue value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_get_NameValue(This, value) \
    ((This)->lpVtbl->get_NameValue(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_put_NameValue(This, value) \
    ((This)->lpVtbl->put_NameValue(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IInputScopeNameFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.InputScopeName
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IInputScopeNameFactory[] = L"Microsoft.UI.Xaml.Input.IInputScopeNameFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CInputScopeNameValue nameValue,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeName** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_CreateInstance(This, nameValue, value) \
    ((This)->lpVtbl->CreateInstance(This, nameValue, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IKeyRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKey* value);
    HRESULT (STDMETHODCALLTYPE* get_KeyStatus)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        struct __x_ABI_CWindows_CUI_CCore_CCorePhysicalKeyStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_OriginalKey)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKey* value);
    HRESULT (STDMETHODCALLTYPE* get_DeviceId)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_get_Key(This, value) \
    ((This)->lpVtbl->get_Key(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_get_KeyStatus(This, value) \
    ((This)->lpVtbl->get_KeyStatus(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_get_OriginalKey(This, value) \
    ((This)->lpVtbl->get_OriginalKey(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_get_DeviceId(This, value) \
    ((This)->lpVtbl->get_DeviceId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAccelerator
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAccelerator[] = L"Microsoft.UI.Xaml.Input.IKeyboardAccelerator";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKey* value);
    HRESULT (STDMETHODCALLTYPE* put_Key)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKey value);
    HRESULT (STDMETHODCALLTYPE* get_Modifiers)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKeyModifiers* value);
    HRESULT (STDMETHODCALLTYPE* put_Modifiers)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKeyModifiers value);
    HRESULT (STDMETHODCALLTYPE* get_IsEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ScopeOwner)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_ScopeOwner)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* add_Invoked)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator_Microsoft__CUI__CXaml__CInput__CKeyboardAcceleratorInvokedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Invoked)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_get_Key(This, value) \
    ((This)->lpVtbl->get_Key(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_put_Key(This, value) \
    ((This)->lpVtbl->put_Key(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_get_Modifiers(This, value) \
    ((This)->lpVtbl->get_Modifiers(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_put_Modifiers(This, value) \
    ((This)->lpVtbl->put_Modifiers(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_get_IsEnabled(This, value) \
    ((This)->lpVtbl->get_IsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_put_IsEnabled(This, value) \
    ((This)->lpVtbl->put_IsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_get_ScopeOwner(This, value) \
    ((This)->lpVtbl->get_ScopeOwner(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_put_ScopeOwner(This, value) \
    ((This)->lpVtbl->put_ScopeOwner(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_add_Invoked(This, handler, token) \
    ((This)->lpVtbl->add_Invoked(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_remove_Invoked(This, token) \
    ((This)->lpVtbl->remove_Invoked(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAcceleratorFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAcceleratorFactory[] = L"Microsoft.UI.Xaml.Input.IKeyboardAcceleratorFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAcceleratorInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAcceleratorInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.IKeyboardAcceleratorInvokedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_Element)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyboardAccelerator)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAccelerator** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_get_Element(This, value) \
    ((This)->lpVtbl->get_Element(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_get_KeyboardAccelerator(This, value) \
    ((This)->lpVtbl->get_KeyboardAccelerator(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorInvokedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IKeyboardAcceleratorStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IKeyboardAcceleratorStatics[] = L"Microsoft.UI.Xaml.Input.IKeyboardAcceleratorStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_KeyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ModifiersProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IsEnabledProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_ScopeOwnerProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_get_KeyProperty(This, value) \
    ((This)->lpVtbl->get_KeyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_get_ModifiersProperty(This, value) \
    ((This)->lpVtbl->get_ModifiersProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_get_IsEnabledProperty(This, value) \
    ((This)->lpVtbl->get_IsEnabledProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_get_ScopeOwnerProperty(This, value) \
    ((This)->lpVtbl->get_ScopeOwnerProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIKeyboardAcceleratorStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ILosingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.LosingFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ILosingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.ILosingFocusEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_OldFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* get_NewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject** value);
    HRESULT (STDMETHODCALLTYPE* put_NewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* value);
    HRESULT (STDMETHODCALLTYPE* get_FocusState)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CFocusState* value);
    HRESULT (STDMETHODCALLTYPE* get_Direction)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_InputDevice)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusInputDeviceKind* value);
    HRESULT (STDMETHODCALLTYPE* get_Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_CorrelationId)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        GUID* value);
    HRESULT (STDMETHODCALLTYPE* TryCancel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* TrySetNewFocusedElement)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_OldFocusedElement(This, value) \
    ((This)->lpVtbl->get_OldFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_NewFocusedElement(This, value) \
    ((This)->lpVtbl->get_NewFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_put_NewFocusedElement(This, value) \
    ((This)->lpVtbl->put_NewFocusedElement(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_FocusState(This, value) \
    ((This)->lpVtbl->get_FocusState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_Direction(This, value) \
    ((This)->lpVtbl->get_Direction(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_InputDevice(This, value) \
    ((This)->lpVtbl->get_InputDevice(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_Cancel(This, value) \
    ((This)->lpVtbl->get_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_put_Cancel(This, value) \
    ((This)->lpVtbl->put_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_get_CorrelationId(This, value) \
    ((This)->lpVtbl->get_CorrelationId(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_TryCancel(This, result) \
    ((This)->lpVtbl->TryCancel(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_TrySetNewFocusedElement(This, element, result) \
    ((This)->lpVtbl->TrySetNewFocusedElement(This, element, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CILosingFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationCompletedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Container)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_IsInertial)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Cumulative)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta* value);
    HRESULT (STDMETHODCALLTYPE* get_Velocities)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationVelocities* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_Container(This, value) \
    ((This)->lpVtbl->get_Container(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_IsInertial(This, value) \
    ((This)->lpVtbl->get_IsInertial(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_Cumulative(This, value) \
    ((This)->lpVtbl->get_Cumulative(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_Velocities(This, value) \
    ((This)->lpVtbl->get_Velocities(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationDeltaRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Container)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_IsInertial)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Delta)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta* value);
    HRESULT (STDMETHODCALLTYPE* get_Cumulative)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta* value);
    HRESULT (STDMETHODCALLTYPE* get_Velocities)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationVelocities* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* Complete)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_Container(This, value) \
    ((This)->lpVtbl->get_Container(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_IsInertial(This, value) \
    ((This)->lpVtbl->get_IsInertial(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_Delta(This, value) \
    ((This)->lpVtbl->get_Delta(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_Cumulative(This, value) \
    ((This)->lpVtbl->get_Cumulative(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_Velocities(This, value) \
    ((This)->lpVtbl->get_Velocities(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_Complete(This) \
    ((This)->lpVtbl->Complete(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationInertiaStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Container)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* get_ExpansionBehavior)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior** value);
    HRESULT (STDMETHODCALLTYPE* put_ExpansionBehavior)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaExpansionBehavior* value);
    HRESULT (STDMETHODCALLTYPE* get_RotationBehavior)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior** value);
    HRESULT (STDMETHODCALLTYPE* put_RotationBehavior)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaRotationBehavior* value);
    HRESULT (STDMETHODCALLTYPE* get_TranslationBehavior)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior** value);
    HRESULT (STDMETHODCALLTYPE* put_TranslationBehavior)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIInertiaTranslationBehavior* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_Delta)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta* value);
    HRESULT (STDMETHODCALLTYPE* get_Cumulative)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta* value);
    HRESULT (STDMETHODCALLTYPE* get_Velocities)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationVelocities* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_Container(This, value) \
    ((This)->lpVtbl->get_Container(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_ExpansionBehavior(This, value) \
    ((This)->lpVtbl->get_ExpansionBehavior(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_put_ExpansionBehavior(This, value) \
    ((This)->lpVtbl->put_ExpansionBehavior(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_RotationBehavior(This, value) \
    ((This)->lpVtbl->get_RotationBehavior(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_put_RotationBehavior(This, value) \
    ((This)->lpVtbl->put_RotationBehavior(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_TranslationBehavior(This, value) \
    ((This)->lpVtbl->get_TranslationBehavior(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_put_TranslationBehavior(This, value) \
    ((This)->lpVtbl->put_TranslationBehavior(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_Delta(This, value) \
    ((This)->lpVtbl->get_Delta(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_Cumulative(This, value) \
    ((This)->lpVtbl->get_Cumulative(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_get_Velocities(This, value) \
    ((This)->lpVtbl->get_Velocities(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationPivot
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationPivot
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationPivot[] = L"Microsoft.UI.Xaml.Input.IManipulationPivot";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Center)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* put_Center)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        struct __x_ABI_CWindows_CFoundation_CPoint value);
    HRESULT (STDMETHODCALLTYPE* get_Radius)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_Radius)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_get_Center(This, value) \
    ((This)->lpVtbl->get_Center(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_put_Center(This, value) \
    ((This)->lpVtbl->put_Center(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_get_Radius(This, value) \
    ((This)->lpVtbl->get_Radius(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_put_Radius(This, value) \
    ((This)->lpVtbl->put_Radius(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationPivotFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationPivot
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationPivotFactory[] = L"Microsoft.UI.Xaml.Input.IManipulationPivotFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstanceWithCenterAndRadius)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory* This,
        struct __x_ABI_CWindows_CFoundation_CPoint center,
        DOUBLE radius,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_CreateInstanceWithCenterAndRadius(This, center, radius, value) \
    ((This)->lpVtbl->CreateInstanceWithCenterAndRadius(This, center, radius, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationStartedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Container)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_Cumulative)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This,
        struct __x_ABI_CMicrosoft_CUI_CInput_CManipulationDelta* value);
    HRESULT (STDMETHODCALLTYPE* Complete)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_get_Container(This, value) \
    ((This)->lpVtbl->get_Container(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_get_Cumulative(This, value) \
    ((This)->lpVtbl->get_Cumulative(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_Complete(This) \
    ((This)->lpVtbl->Complete(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgsFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationStartedRoutedEventArgsFactory[] = L"Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgsFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IManipulationStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ManipulationStartingRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IManipulationStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IManipulationStartingRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Mode)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CManipulationModes* value);
    HRESULT (STDMETHODCALLTYPE* put_Mode)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CManipulationModes value);
    HRESULT (STDMETHODCALLTYPE* get_Container)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* put_Container)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* value);
    HRESULT (STDMETHODCALLTYPE* get_Pivot)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot** value);
    HRESULT (STDMETHODCALLTYPE* put_Pivot)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationPivot* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_get_Mode(This, value) \
    ((This)->lpVtbl->get_Mode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_put_Mode(This, value) \
    ((This)->lpVtbl->put_Mode(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_get_Container(This, value) \
    ((This)->lpVtbl->get_Container(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_put_Container(This, value) \
    ((This)->lpVtbl->put_Container(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_get_Pivot(This, value) \
    ((This)->lpVtbl->get_Pivot(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_put_Pivot(This, value) \
    ((This)->lpVtbl->put_Pivot(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.INoFocusCandidateFoundEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.NoFocusCandidateFoundEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_INoFocusCandidateFoundEventArgs[] = L"Microsoft.UI.Xaml.Input.INoFocusCandidateFoundEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Direction)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusNavigationDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_InputDevice)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CFocusInputDeviceKind* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_get_Direction(This, value) \
    ((This)->lpVtbl->get_Direction(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_get_InputDevice(This, value) \
    ((This)->lpVtbl->get_InputDevice(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CINoFocusCandidateFoundEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IPointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.Pointer
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IPointer[] = L"Microsoft.UI.Xaml.Input.IPointer";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PointerId)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_IsInContact)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsInRange)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_get_PointerId(This, value) \
    ((This)->lpVtbl->get_PointerId(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_get_IsInContact(This, value) \
    ((This)->lpVtbl->get_IsInContact(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_get_IsInRange(This, value) \
    ((This)->lpVtbl->get_IsInRange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IPointerRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.PointerRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IPointerRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IPointerRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Pointer)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointer** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyModifiers)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKeyModifiers* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsGenerated)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* GetCurrentPoint)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint** result);
    HRESULT (STDMETHODCALLTYPE* GetIntermediatePoints)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        __FIVector_1_Microsoft__CUI__CInput__CPointerPoint** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_get_Pointer(This, value) \
    ((This)->lpVtbl->get_Pointer(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_get_KeyModifiers(This, value) \
    ((This)->lpVtbl->get_KeyModifiers(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_get_IsGenerated(This, value) \
    ((This)->lpVtbl->get_IsGenerated(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_GetCurrentPoint(This, relativeTo, result) \
    ((This)->lpVtbl->GetCurrentPoint(This, relativeTo, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_GetIntermediatePoints(This, relativeTo, result) \
    ((This)->lpVtbl->GetIntermediatePoints(This, relativeTo, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IProcessKeyboardAcceleratorEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.ProcessKeyboardAcceleratorEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IProcessKeyboardAcceleratorEventArgs[] = L"Microsoft.UI.Xaml.Input.IProcessKeyboardAcceleratorEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKey* value);
    HRESULT (STDMETHODCALLTYPE* get_Modifiers)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        enum __x_ABI_CWindows_CSystem_CVirtualKeyModifiers* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_get_Key(This, value) \
    ((This)->lpVtbl->get_Key(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_get_Modifiers(This, value) \
    ((This)->lpVtbl->get_Modifiers(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIProcessKeyboardAcceleratorEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IRightTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IRightTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.IRightTappedRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* GetPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        struct __x_ABI_CWindows_CFoundation_CPoint* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_GetPosition(This, relativeTo, result) \
    ((This)->lpVtbl->GetPosition(This, relativeTo, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IStandardUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.StandardUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IStandardUICommand[] = L"Microsoft.UI.Xaml.Input.IStandardUICommand";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CStandardUICommandKind* value);
    HRESULT (STDMETHODCALLTYPE* put_Kind)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CStandardUICommandKind value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_put_Kind(This, value) \
    ((This)->lpVtbl->put_Kind(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IStandardUICommandFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.StandardUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IStandardUICommandFactory[] = L"Microsoft.UI.Xaml.Input.IStandardUICommandFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand** value);
    HRESULT (STDMETHODCALLTYPE* CreateInstanceWithKind)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CInput_CStandardUICommandKind kind,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommand** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_CreateInstanceWithKind(This, kind, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstanceWithKind(This, kind, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IStandardUICommandStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.StandardUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IStandardUICommandStatics[] = L"Microsoft.UI.Xaml.Input.IStandardUICommandStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_KindProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_get_KindProperty(This, value) \
    ((This)->lpVtbl->get_KindProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIStandardUICommandStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.ITappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.TappedRoutedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_ITappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ITappedRoutedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PointerDeviceType)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        enum __x_ABI_CMicrosoft_CUI_CInput_CPointerDeviceType* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* GetPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* relativeTo,
        struct __x_ABI_CWindows_CFoundation_CPoint* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_get_PointerDeviceType(This, value) \
    ((This)->lpVtbl->get_PointerDeviceType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_GetPosition(This, relativeTo, result) \
    ((This)->lpVtbl->GetPosition(This, relativeTo, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IXamlUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.XamlUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IXamlUICommand[] = L"Microsoft.UI.Xaml.Input.IXamlUICommand";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Label)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Label)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_IconSource)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource** value);
    HRESULT (STDMETHODCALLTYPE* put_IconSource)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIIconSource* value);
    HRESULT (STDMETHODCALLTYPE* get_KeyboardAccelerators)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __FIVector_1_Microsoft__CUI__CXaml__CInput__CKeyboardAccelerator** value);
    HRESULT (STDMETHODCALLTYPE* get_AccessKey)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_AccessKey)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Description)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Description)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Command)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand** value);
    HRESULT (STDMETHODCALLTYPE* put_Command)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CICommand* value);
    HRESULT (STDMETHODCALLTYPE* add_ExecuteRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CExecuteRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ExecuteRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_CanExecuteRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CInput__CXamlUICommand_Microsoft__CUI__CXaml__CInput__CCanExecuteRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_CanExecuteRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* NotifyCanExecuteChanged)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_get_Label(This, value) \
    ((This)->lpVtbl->get_Label(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_put_Label(This, value) \
    ((This)->lpVtbl->put_Label(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_get_IconSource(This, value) \
    ((This)->lpVtbl->get_IconSource(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_put_IconSource(This, value) \
    ((This)->lpVtbl->put_IconSource(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_get_KeyboardAccelerators(This, value) \
    ((This)->lpVtbl->get_KeyboardAccelerators(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_get_AccessKey(This, value) \
    ((This)->lpVtbl->get_AccessKey(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_put_AccessKey(This, value) \
    ((This)->lpVtbl->put_AccessKey(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_get_Description(This, value) \
    ((This)->lpVtbl->get_Description(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_put_Description(This, value) \
    ((This)->lpVtbl->put_Description(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_get_Command(This, value) \
    ((This)->lpVtbl->get_Command(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_put_Command(This, value) \
    ((This)->lpVtbl->put_Command(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_add_ExecuteRequested(This, handler, token) \
    ((This)->lpVtbl->add_ExecuteRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_remove_ExecuteRequested(This, token) \
    ((This)->lpVtbl->remove_ExecuteRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_add_CanExecuteRequested(This, handler, token) \
    ((This)->lpVtbl->add_CanExecuteRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_remove_CanExecuteRequested(This, token) \
    ((This)->lpVtbl->remove_CanExecuteRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_NotifyCanExecuteChanged(This) \
    ((This)->lpVtbl->NotifyCanExecuteChanged(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IXamlUICommandFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.XamlUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IXamlUICommandFactory[] = L"Microsoft.UI.Xaml.Input.IXamlUICommandFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommand** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Input.IXamlUICommandStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Input.XamlUICommand
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Input_IXamlUICommandStatics[] = L"Microsoft.UI.Xaml.Input.IXamlUICommandStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_LabelProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_IconSourceProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyboardAcceleratorsProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_AccessKeyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_DescriptionProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* get_CommandProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_get_LabelProperty(This, value) \
    ((This)->lpVtbl->get_LabelProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_get_IconSourceProperty(This, value) \
    ((This)->lpVtbl->get_IconSourceProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_get_KeyboardAcceleratorsProperty(This, value) \
    ((This)->lpVtbl->get_KeyboardAcceleratorsProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_get_AccessKeyProperty(This, value) \
    ((This)->lpVtbl->get_AccessKeyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_get_DescriptionProperty(This, value) \
    ((This)->lpVtbl->get_DescriptionProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_get_CommandProperty(This, value) \
    ((This)->lpVtbl->get_CommandProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CInput_CIXamlUICommandStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyDisplayDismissedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayDismissedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayDismissedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyDisplayDismissedEventArgs[] = L"Microsoft.UI.Xaml.Input.AccessKeyDisplayDismissedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyDisplayRequestedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyDisplayRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyDisplayRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.AccessKeyDisplayRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyInvokedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyInvokedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyInvokedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.AccessKeyInvokedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.AccessKeyManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics2 interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IAccessKeyManagerStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IAccessKeyManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_AccessKeyManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_AccessKeyManager[] = L"Microsoft.UI.Xaml.Input.AccessKeyManager";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ICanExecuteRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_CanExecuteRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_CanExecuteRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_CanExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.CanExecuteRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.CharacterReceivedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ICharacterReceivedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_CharacterReceivedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_CharacterReceivedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_CharacterReceivedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.CharacterReceivedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ContextRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IContextRequestedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ContextRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ContextRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ContextRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.ContextRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.DoubleTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IDoubleTappedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_DoubleTappedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_DoubleTappedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_DoubleTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.DoubleTappedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IExecuteRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ExecuteRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ExecuteRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ExecuteRequestedEventArgs[] = L"Microsoft.UI.Xaml.Input.ExecuteRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FindNextElementOptions
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFindNextElementOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FindNextElementOptions_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FindNextElementOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FindNextElementOptions[] = L"Microsoft.UI.Xaml.Input.FindNextElementOptions";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IFocusManagerStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusManager[] = L"Microsoft.UI.Xaml.Input.FocusManager";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusManagerGotFocusEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerGotFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerGotFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusManagerGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.FocusManagerGotFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusManagerLostFocusEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerLostFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusManagerLostFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusManagerLostFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.FocusManagerLostFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.FocusMovementResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IFocusMovementResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusMovementResult_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_FocusMovementResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_FocusMovementResult[] = L"Microsoft.UI.Xaml.Input.FocusMovementResult";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.GettingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IGettingFocusEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_GettingFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_GettingFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_GettingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.GettingFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.HoldingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IHoldingRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_HoldingRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_HoldingRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_HoldingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.HoldingRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InertiaExpansionBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInertiaExpansionBehavior ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaExpansionBehavior_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaExpansionBehavior_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InertiaExpansionBehavior[] = L"Microsoft.UI.Xaml.Input.InertiaExpansionBehavior";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InertiaRotationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInertiaRotationBehavior ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaRotationBehavior_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaRotationBehavior_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InertiaRotationBehavior[] = L"Microsoft.UI.Xaml.Input.InertiaRotationBehavior";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InertiaTranslationBehavior
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInertiaTranslationBehavior ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaTranslationBehavior_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InertiaTranslationBehavior_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InertiaTranslationBehavior[] = L"Microsoft.UI.Xaml.Input.InertiaTranslationBehavior";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InputScope
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInputScope ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScope_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScope_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InputScope[] = L"Microsoft.UI.Xaml.Input.InputScope";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.InputScopeName
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Input.IInputScopeNameFactory interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IInputScopeName ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScopeName_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_InputScopeName_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_InputScopeName[] = L"Microsoft.UI.Xaml.Input.InputScopeName";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.KeyRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IKeyRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_KeyRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.KeyRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.KeyboardAccelerator
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IKeyboardAcceleratorStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IKeyboardAccelerator ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAccelerator_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAccelerator_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_KeyboardAccelerator[] = L"Microsoft.UI.Xaml.Input.KeyboardAccelerator";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IKeyboardAcceleratorInvokedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAcceleratorInvokedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_KeyboardAcceleratorInvokedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_KeyboardAcceleratorInvokedEventArgs[] = L"Microsoft.UI.Xaml.Input.KeyboardAcceleratorInvokedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.LosingFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ILosingFocusEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_LosingFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_LosingFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_LosingFocusEventArgs[] = L"Microsoft.UI.Xaml.Input.LosingFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationPivot
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Type can be activated via the Microsoft.UI.Xaml.Input.IManipulationPivotFactory interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationPivot ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationPivot_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationPivot_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationPivot[] = L"Microsoft.UI.Xaml.Input.ManipulationPivot";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationStartedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationStartedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationStartedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ManipulationStartingRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IManipulationStartingRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartingRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ManipulationStartingRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ManipulationStartingRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.ManipulationStartingRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.NoFocusCandidateFoundEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.INoFocusCandidateFoundEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_NoFocusCandidateFoundEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_NoFocusCandidateFoundEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_NoFocusCandidateFoundEventArgs[] = L"Microsoft.UI.Xaml.Input.NoFocusCandidateFoundEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.Pointer
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IPointer ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_Pointer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_Pointer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_Pointer[] = L"Microsoft.UI.Xaml.Input.Pointer";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.PointerRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IPointerRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_PointerRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_PointerRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_PointerRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.PointerRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.ProcessKeyboardAcceleratorEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IProcessKeyboardAcceleratorEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_ProcessKeyboardAcceleratorEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_ProcessKeyboardAcceleratorEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_ProcessKeyboardAcceleratorEventArgs[] = L"Microsoft.UI.Xaml.Input.ProcessKeyboardAcceleratorEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IRightTappedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_RightTappedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_RightTappedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_RightTappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.RightTappedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.StandardUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IStandardUICommandStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IStandardUICommand ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_StandardUICommand_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_StandardUICommand_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_StandardUICommand[] = L"Microsoft.UI.Xaml.Input.StandardUICommand";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.TappedRoutedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.ITappedRoutedEventArgs ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_TappedRoutedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_TappedRoutedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_TappedRoutedEventArgs[] = L"Microsoft.UI.Xaml.Input.TappedRoutedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Input.XamlUICommand
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Input.IXamlUICommandStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Input.IXamlUICommand ** Default Interface **
 *    Microsoft.UI.Xaml.Input.ICommand
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Input_XamlUICommand_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Input_XamlUICommand_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Input_XamlUICommand[] = L"Microsoft.UI.Xaml.Input.XamlUICommand";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Einput_p_h__

#endif // __microsoft2Eui2Examl2Einput_h__
