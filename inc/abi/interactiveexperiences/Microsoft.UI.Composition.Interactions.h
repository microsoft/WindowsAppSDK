// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.


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
#ifndef __microsoft2Eui2Ecomposition2Einteractions_h__
#define __microsoft2Eui2Ecomposition2Einteractions_h__
#ifndef __microsoft2Eui2Ecomposition2Einteractions_p_h__
#define __microsoft2Eui2Ecomposition2Einteractions_p_h__


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
#include "Microsoft.UI.Composition.h"
#include "Microsoft.UI.Input.h"
#include "Windows.Foundation.Numerics.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface ICompositionConditionalValue;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue ABI::Microsoft::UI::Composition::Interactions::ICompositionConditionalValue

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface ICompositionConditionalValueStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics ABI::Microsoft::UI::Composition::Interactions::ICompositionConditionalValueStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface ICompositionInteractionSource;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface ICompositionInteractionSourceCollection;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSourceCollection

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionSourceConfiguration;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration ABI::Microsoft::UI::Composition::Interactions::IInteractionSourceConfiguration

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTracker;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTracker2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2 ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTracker3;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3 ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker3

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTracker4;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4 ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker4

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTracker5;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5 ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker5

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerCustomAnimationStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerCustomAnimationStateEnteredArgs

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerCustomAnimationStateEnteredArgs2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2 ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerCustomAnimationStateEnteredArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerIdleStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerIdleStateEnteredArgs

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerIdleStateEnteredArgs2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2 ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerIdleStateEnteredArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaModifier;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaModifier

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaModifierFactory;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaModifierFactory

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaMotion;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaMotion

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaMotionStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaMotionStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaNaturalMotion;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaNaturalMotion

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaNaturalMotionStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaNaturalMotionStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaRestingValue;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaRestingValue

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaRestingValueStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaRestingValueStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaStateEnteredArgs

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaStateEnteredArgs2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2 ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaStateEnteredArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInertiaStateEnteredArgs3;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3 ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaStateEnteredArgs3

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInteractingStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInteractingStateEnteredArgs

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerInteractingStateEnteredArgs2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2 ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInteractingStateEnteredArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerOwner;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerOwner

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerRequestIgnoredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerRequestIgnoredArgs

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerStatics2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2 ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerValuesChangedArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerValuesChangedArgs

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerVector2InertiaModifier;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaModifier

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerVector2InertiaModifierFactory;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaModifierFactory

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerVector2InertiaNaturalMotion;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaNaturalMotion

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IInteractionTrackerVector2InertiaNaturalMotionStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaNaturalMotionStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IVisualInteractionSource;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSource

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IVisualInteractionSource2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2 ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSource2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IVisualInteractionSource3;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3 ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSource3

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IVisualInteractionSourceObjectFactory;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSourceObjectFactory

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IVisualInteractionSourceStatics;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSourceStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    interface IVisualInteractionSourceStatics2;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2 ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSourceStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class CompositionConditionalValue;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_USE
#define DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("1bf57a13-c5b6-5d31-805b-6f009b24e360"))
IIterator<ABI::Microsoft::UI::Composition::Interactions::CompositionConditionalValue*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Interactions::CompositionConditionalValue*, ABI::Microsoft::UI::Composition::Interactions::ICompositionConditionalValue*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Composition.Interactions.CompositionConditionalValue>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Composition::Interactions::CompositionConditionalValue*> __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_t;
#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_USE
#define DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("bfe6e6f0-29d3-5d7b-ac52-9ff2f2faa5c1"))
IIterable<ABI::Microsoft::UI::Composition::Interactions::CompositionConditionalValue*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Interactions::CompositionConditionalValue*, ABI::Microsoft::UI::Composition::Interactions::ICompositionConditionalValue*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Composition.Interactions.CompositionConditionalValue>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Composition::Interactions::CompositionConditionalValue*> __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_t;
#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_USE
#define DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f21f2a85-e3f0-557c-8cff-6cfbc39754bb"))
IIterator<ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource*> : IIterator_impl<ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Composition.Interactions.ICompositionInteractionSource>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource*> __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_t;
#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_USE
#define DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ef893131-12b4-5e2d-9a98-b083ab218918"))
IIterable<ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource*> : IIterable_impl<ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Composition.Interactions.ICompositionInteractionSource>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource*> __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_t;
#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerInertiaModifier;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_USE
#define DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ad8bcabc-22a3-5fea-9edc-20e8c4fa3905"))
IIterator<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerInertiaModifier*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerInertiaModifier*, ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaModifier*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerInertiaModifier*> __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_t;
#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_USE
#define DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c2ab0a9f-2518-5c81-9ada-72169f0f00a3"))
IIterable<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerInertiaModifier*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerInertiaModifier*, ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaModifier*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerInertiaModifier*> __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_t;
#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerVector2InertiaModifier;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_USE
#define DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e666655f-2a16-5a78-bd73-7f81bba7c2c4"))
IIterator<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerVector2InertiaModifier*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerVector2InertiaModifier*, ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaModifier*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerVector2InertiaModifier*> __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_t;
#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_USE
#define DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("6a242990-7db7-57bd-8d01-e20b6581320a"))
IIterable<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerVector2InertiaModifier*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerVector2InertiaModifier*, ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaModifier*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerVector2InertiaModifier*> __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_t;
#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIReference_1_float_USE
#define DEF___FIReference_1_float_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("719cc2ba-3e76-5def-9f1a-38d85a145ea8"))
IReference<float> : IReference_impl<float>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Single>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<float> __FIReference_1_float_t;
#define __FIReference_1_float ABI::Windows::Foundation::__FIReference_1_float_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_float_USE */


namespace ABI {
    namespace Windows {
        namespace Foundation {
            namespace Numerics {
                typedef struct Vector3 Vector3;
            } /* Numerics */
        } /* Foundation */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIReference_1_Windows__CFoundation__CNumerics__CVector3_USE
#define DEF___FIReference_1_Windows__CFoundation__CNumerics__CVector3_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1ee770ff-c954-59ca-a754-6199a9be282c"))
IReference<struct ABI::Windows::Foundation::Numerics::Vector3> : IReference_impl<struct ABI::Windows::Foundation::Numerics::Vector3>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Windows.Foundation.Numerics.Vector3>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<struct ABI::Windows::Foundation::Numerics::Vector3> __FIReference_1_Windows__CFoundation__CNumerics__CVector3_t;
#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3 ABI::Windows::Foundation::__FIReference_1_Windows__CFoundation__CNumerics__CVector3_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_Windows__CFoundation__CNumerics__CVector3_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class CompositionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation ABI::Microsoft::UI::Composition::ICompositionAnimation

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation_FWD_DEFINED__

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
                class ExpressionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IExpressionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation ABI::Microsoft::UI::Composition::IExpressionAnimation

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IVisualElement;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement ABI::Microsoft::UI::Composition::IVisualElement

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class ScalarNaturalMotionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IScalarNaturalMotionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation ABI::Microsoft::UI::Composition::IScalarNaturalMotionAnimation

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class Vector2NaturalMotionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IVector2NaturalMotionAnimation;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation ABI::Microsoft::UI::Composition::IVector2NaturalMotionAnimation

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation_FWD_DEFINED__

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

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IPropertyValue;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIPropertyValue ABI::Windows::Foundation::IPropertyValue

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum InteractionBindingAxisModes : unsigned int InteractionBindingAxisModes;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum InteractionChainingMode : int InteractionChainingMode;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum InteractionSourceMode : int InteractionSourceMode;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum InteractionSourceRedirectionMode : int InteractionSourceRedirectionMode;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum InteractionTrackerClampingOption : int InteractionTrackerClampingOption;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum InteractionTrackerPositionUpdateOption : int InteractionTrackerPositionUpdateOption;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    typedef enum VisualInteractionSourceRedirectionMode : int VisualInteractionSourceRedirectionMode;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class CompositionInteractionSourceCollection;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionSourceConfiguration;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTracker;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerCustomAnimationStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerIdleStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerInertiaMotion;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerInertiaNaturalMotion;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerInertiaRestingValue;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerInertiaStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerInteractingStateEnteredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerRequestIgnoredArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerValuesChangedArgs;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class InteractionTrackerVector2InertiaNaturalMotion;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    class VisualInteractionSource;
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionBindingAxisModes
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum InteractionBindingAxisModes : unsigned int
                    {
                        InteractionBindingAxisModes_None = 0,
                        InteractionBindingAxisModes_PositionX = 0x1,
                        InteractionBindingAxisModes_PositionY = 0x2,
                        InteractionBindingAxisModes_Scale = 0x4,
                    };

                    DEFINE_ENUM_FLAG_OPERATORS(InteractionBindingAxisModes)
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionChainingMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum InteractionChainingMode : int
                    {
                        InteractionChainingMode_Auto = 0,
                        InteractionChainingMode_Always = 1,
                        InteractionChainingMode_Never = 2,
                    };
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionSourceMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum InteractionSourceMode : int
                    {
                        InteractionSourceMode_Disabled = 0,
                        InteractionSourceMode_EnabledWithInertia = 1,
                        InteractionSourceMode_EnabledWithoutInertia = 2,
                    };
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionSourceRedirectionMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum InteractionSourceRedirectionMode : int
                    {
                        InteractionSourceRedirectionMode_Disabled = 0,
                        InteractionSourceRedirectionMode_Enabled = 1,
                    };
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionTrackerClampingOption
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum InteractionTrackerClampingOption : int
                    {
                        InteractionTrackerClampingOption_Auto = 0,
                        InteractionTrackerClampingOption_Disabled = 1,
                    };
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionTrackerPositionUpdateOption
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum InteractionTrackerPositionUpdateOption : int
                    {
                        InteractionTrackerPositionUpdateOption_Default = 0,
                        InteractionTrackerPositionUpdateOption_AllowActiveCustomScaleAnimation = 1,
                    };
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.VisualInteractionSourceRedirectionMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    enum VisualInteractionSourceRedirectionMode : int
                    {
                        VisualInteractionSourceRedirectionMode_Off = 0,
                        VisualInteractionSourceRedirectionMode_CapableTouchpadOnly = 1,
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
                        VisualInteractionSourceRedirectionMode_PointerWheelOnly = 2,
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
                        VisualInteractionSourceRedirectionMode_CapableTouchpadAndPointerWheel = 3,
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
                    };
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionConditionalValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.CompositionConditionalValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionConditionalValue[] = L"Microsoft.UI.Composition.Interactions.ICompositionConditionalValue";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("3743dda0-fbe2-5ecf-9e80-4638a011f707")
                    ICompositionConditionalValue : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Value(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Value(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositionConditionalValue = _uuidof(ICompositionConditionalValue);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionConditionalValueStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.CompositionConditionalValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionConditionalValueStatics[] = L"Microsoft.UI.Composition.Interactions.ICompositionConditionalValueStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("df133c1f-a185-536c-b54b-8f369212a581")
                    ICompositionConditionalValueStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::ICompositionConditionalValue** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositionConditionalValueStatics = _uuidof(ICompositionConditionalValueStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionInteractionSource
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionInteractionSource[] = L"Microsoft.UI.Composition.Interactions.ICompositionInteractionSource";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("711c72c0-c406-4a12-859b-b44f651af046")
                    ICompositionInteractionSource : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ICompositionInteractionSource = _uuidof(ICompositionInteractionSource);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionInteractionSourceCollection
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.CompositionInteractionSourceCollection
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionInteractionSourceCollection[] = L"Microsoft.UI.Composition.Interactions.ICompositionInteractionSourceCollection";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("9aa1b86b-b002-5e2e-bb2b-0e2c547445e1")
                    ICompositionInteractionSourceCollection : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Count(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Add(
                            ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Remove(
                            ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSource* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveAll(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositionInteractionSourceCollection = _uuidof(ICompositionInteractionSourceCollection);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionSourceConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionSourceConfiguration
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionSourceConfiguration[] = L"Microsoft.UI.Composition.Interactions.IInteractionSourceConfiguration";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("099e0124-dadf-5bc6-a895-90387657550f")
                    IInteractionSourceConfiguration : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PositionXSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceRedirectionMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionXSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceRedirectionMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionYSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceRedirectionMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionYSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceRedirectionMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceRedirectionMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ScaleSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceRedirectionMode value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionSourceConfiguration = _uuidof(IInteractionSourceConfiguration);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("02d8ec1f-8f04-505e-bd1e-47b2a204de51")
                    IInteractionTracker : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_InteractionSources(
                            ABI::Microsoft::UI::Composition::Interactions::ICompositionInteractionSourceCollection** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsPositionRoundingSuggested(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxPosition(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxPosition(
                            ABI::Windows::Foundation::Numerics::Vector3 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxScale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxScale(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MinPosition(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MinPosition(
                            ABI::Windows::Foundation::Numerics::Vector3 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MinScale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MinScale(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NaturalRestingPosition(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NaturalRestingScale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Owner(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerOwner** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionInertiaDecayRate(
                            __FIReference_1_Windows__CFoundation__CNumerics__CVector3** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionInertiaDecayRate(
                            __FIReference_1_Windows__CFoundation__CNumerics__CVector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionVelocityInPixelsPerSecond(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleInertiaDecayRate(
                            __FIReference_1_float** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ScaleInertiaDecayRate(
                            __FIReference_1_float* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleVelocityInPercentPerSecond(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AdjustPositionXIfGreaterThanThreshold(
                            FLOAT adjustment,
                            FLOAT positionThreshold
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AdjustPositionYIfGreaterThanThreshold(
                            FLOAT adjustment,
                            FLOAT positionThreshold
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigurePositionXInertiaModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* modifiers
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigurePositionYInertiaModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* modifiers
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureScaleInertiaModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* modifiers
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePosition(
                            ABI::Windows::Foundation::Numerics::Vector3 value,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePositionBy(
                            ABI::Windows::Foundation::Numerics::Vector3 amount,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePositionWithAnimation(
                            ABI::Microsoft::UI::Composition::ICompositionAnimation* animation,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePositionWithAdditionalVelocity(
                            ABI::Windows::Foundation::Numerics::Vector3 velocityInPixelsPerSecond,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdateScale(
                            FLOAT value,
                            ABI::Windows::Foundation::Numerics::Vector3 centerPoint,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdateScaleWithAnimation(
                            ABI::Microsoft::UI::Composition::ICompositionAnimation* animation,
                            ABI::Windows::Foundation::Numerics::Vector3 centerPoint,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdateScaleWithAdditionalVelocity(
                            FLOAT velocityInPercentPerSecond,
                            ABI::Windows::Foundation::Numerics::Vector3 centerPoint,
                            INT32* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTracker = _uuidof(IInteractionTracker);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("396d7fb1-2fad-5508-8591-4ff0dc5a7484")
                    IInteractionTracker2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE ConfigureCenterPointXInertiaModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureCenterPointYInertiaModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTracker2 = _uuidof(IInteractionTracker2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker3[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("239752cf-266c-5acb-acc3-b3e3ecaf4d3f")
                    IInteractionTracker3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE ConfigureVector2PositionInertiaModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* modifiers
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTracker3 = _uuidof(IInteractionTracker3);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker4
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker4[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker4";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("a9a9ce02-53c9-5690-a575-f340b7c2fdf2")
                    IInteractionTracker4 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePositionWithOption(
                            ABI::Windows::Foundation::Numerics::Vector3 value,
                            ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerClampingOption option,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePositionByWithOption(
                            ABI::Windows::Foundation::Numerics::Vector3 amount,
                            ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerClampingOption option,
                            INT32* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsInertiaFromImpulse(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTracker4 = _uuidof(IInteractionTracker4);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker5
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker5[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker5";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("dbfcd333-c3bf-5057-a45e-25edf06ebd8f")
                    IInteractionTracker5 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE TryUpdatePositionWithOption(
                            ABI::Windows::Foundation::Numerics::Vector3 value,
                            ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerClampingOption option,
                            ABI::Microsoft::UI::Composition::Interactions::InteractionTrackerPositionUpdateOption posUpdateOption,
                            INT32* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTracker5 = _uuidof(IInteractionTracker5);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerCustomAnimationStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("7464035c-cfce-56da-9472-420f276bd0a5")
                    IInteractionTrackerCustomAnimationStateEnteredArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RequestId(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerCustomAnimationStateEnteredArgs = _uuidof(IInteractionTrackerCustomAnimationStateEnteredArgs);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerCustomAnimationStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("06b99fbc-d6a8-5ae3-88b8-e91621becbd6")
                    IInteractionTrackerCustomAnimationStateEnteredArgs2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsFromBinding(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerCustomAnimationStateEnteredArgs2 = _uuidof(IInteractionTrackerCustomAnimationStateEnteredArgs2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerIdleStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("199094ab-15fd-539c-97b8-964a8196f777")
                    IInteractionTrackerIdleStateEnteredArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RequestId(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerIdleStateEnteredArgs = _uuidof(IInteractionTrackerIdleStateEnteredArgs);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerIdleStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("4eb213c0-931c-5164-8965-11c0186d3390")
                    IInteractionTrackerIdleStateEnteredArgs2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsFromBinding(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerIdleStateEnteredArgs2 = _uuidof(IInteractionTrackerIdleStateEnteredArgs2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaModifier[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifier";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("4d3a0c6b-c508-5029-a47a-cbf64636f010")
                    IInteractionTrackerInertiaModifier : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaModifier = _uuidof(IInteractionTrackerInertiaModifier);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifierFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaModifierFactory[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifierFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("6dee5b33-0b5a-57b1-8537-93d4fd038f9f")
                    IInteractionTrackerInertiaModifierFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaModifierFactory = _uuidof(IInteractionTrackerInertiaModifierFactory);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaMotion[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotion";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("91f662c0-3141-5b5e-862f-cfc60bee8cd6")
                    IInteractionTrackerInertiaMotion : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Motion(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Motion(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaMotion = _uuidof(IInteractionTrackerInertiaMotion);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotionStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaMotionStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotionStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("b0185a4f-0059-52c6-a660-9aed0c44ff7d")
                    IInteractionTrackerInertiaMotionStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaMotion** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaMotionStatics = _uuidof(IInteractionTrackerInertiaMotionStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotion";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("8c7482e0-185d-56b1-b67f-fca4fcd13cd2")
                    IInteractionTrackerInertiaNaturalMotion : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NaturalMotion(
                            ABI::Microsoft::UI::Composition::IScalarNaturalMotionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_NaturalMotion(
                            ABI::Microsoft::UI::Composition::IScalarNaturalMotionAnimation* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaNaturalMotion = _uuidof(IInteractionTrackerInertiaNaturalMotion);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotionStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaNaturalMotionStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotionStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("860ec143-f165-5298-abf2-47369dd07f10")
                    IInteractionTrackerInertiaNaturalMotionStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaNaturalMotion** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaNaturalMotionStatics = _uuidof(IInteractionTrackerInertiaNaturalMotionStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaRestingValue[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValue";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("1a2b20cd-3371-53ff-a560-f4847b467d73")
                    IInteractionTrackerInertiaRestingValue : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RestingValue(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RestingValue(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaRestingValue = _uuidof(IInteractionTrackerInertiaRestingValue);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValueStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaRestingValueStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValueStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("cf0f0414-7fdf-5284-aeef-28b71b62aa4f")
                    IInteractionTrackerInertiaRestingValueStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaRestingValue** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaRestingValueStatics = _uuidof(IInteractionTrackerInertiaRestingValueStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("5b76c949-a4d0-5c9d-9292-7013ae9656c7")
                    IInteractionTrackerInertiaStateEnteredArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ModifiedRestingPosition(
                            __FIReference_1_Windows__CFoundation__CNumerics__CVector3** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ModifiedRestingScale(
                            __FIReference_1_float** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NaturalRestingPosition(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NaturalRestingScale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionVelocityInPixelsPerSecond(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RequestId(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleVelocityInPercentPerSecond(
                            FLOAT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaStateEnteredArgs = _uuidof(IInteractionTrackerInertiaStateEnteredArgs);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("c42d7e8f-7199-57a9-8aec-8727552b13e6")
                    IInteractionTrackerInertiaStateEnteredArgs2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsInertiaFromImpulse(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaStateEnteredArgs2 = _uuidof(IInteractionTrackerInertiaStateEnteredArgs2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaStateEnteredArgs3[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("ce726ca0-1c04-531b-9951-4aec996952e4")
                    IInteractionTrackerInertiaStateEnteredArgs3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsFromBinding(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInertiaStateEnteredArgs3 = _uuidof(IInteractionTrackerInertiaStateEnteredArgs3);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInteractingStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("70d29b84-0931-5f17-a8a1-82f8f8782532")
                    IInteractionTrackerInteractingStateEnteredArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RequestId(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInteractingStateEnteredArgs = _uuidof(IInteractionTrackerInteractingStateEnteredArgs);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInteractingStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("2f1ff38d-2f51-5ceb-8d09-bda1519f9342")
                    IInteractionTrackerInteractingStateEnteredArgs2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsFromBinding(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerInteractingStateEnteredArgs2 = _uuidof(IInteractionTrackerInteractingStateEnteredArgs2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerOwner
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerOwner[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerOwner";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("8869779d-1d2a-5816-836a-68a910507d87")
                    IInteractionTrackerOwner : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CustomAnimationStateEntered(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* sender,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerCustomAnimationStateEnteredArgs* args
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IdleStateEntered(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* sender,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerIdleStateEnteredArgs* args
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE InertiaStateEntered(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* sender,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInertiaStateEnteredArgs* args
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE InteractingStateEntered(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* sender,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerInteractingStateEnteredArgs* args
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RequestIgnored(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* sender,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerRequestIgnoredArgs* args
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ValuesChanged(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* sender,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerValuesChangedArgs* args
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerOwner = _uuidof(IInteractionTrackerOwner);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerRequestIgnoredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerRequestIgnoredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerRequestIgnoredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerRequestIgnoredArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("c276205e-f7a5-5ba2-ad45-d12c3c339149")
                    IInteractionTrackerRequestIgnoredArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RequestId(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerRequestIgnoredArgs = _uuidof(IInteractionTrackerRequestIgnoredArgs);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("7ac9867a-e16e-56ef-9809-f6e404240f50")
                    IInteractionTrackerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateWithOwner(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerOwner* owner,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerStatics = _uuidof(IInteractionTrackerStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerStatics2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("25658e4c-b99f-5108-aab7-1cc44f11508b")
                    IInteractionTrackerStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SetBindingMode(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* boundTracker1,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* boundTracker2,
                            ABI::Microsoft::UI::Composition::Interactions::InteractionBindingAxisModes axisMode
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetBindingMode(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* boundTracker1,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTracker* boundTracker2,
                            ABI::Microsoft::UI::Composition::Interactions::InteractionBindingAxisModes* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerStatics2 = _uuidof(IInteractionTrackerStatics2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerValuesChangedArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerValuesChangedArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerValuesChangedArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerValuesChangedArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("9b495bed-1cf7-55c1-82b9-8022cbf3c766")
                    IInteractionTrackerValuesChangedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RequestId(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scale(
                            FLOAT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerValuesChangedArgs = _uuidof(IInteractionTrackerValuesChangedArgs);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaModifier[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifier";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("4b8ed310-cb61-5f0a-b99a-940cdd2c42b1")
                    IInteractionTrackerVector2InertiaModifier : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerVector2InertiaModifier = _uuidof(IInteractionTrackerVector2InertiaModifier);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifierFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaModifierFactory[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifierFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("1b3fd240-ba66-5296-b801-62a2a3606613")
                    IInteractionTrackerVector2InertiaModifierFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerVector2InertiaModifierFactory = _uuidof(IInteractionTrackerVector2InertiaModifierFactory);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotion";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("097ba1a6-e077-52d1-86d3-38e3f6619ddf")
                    IInteractionTrackerVector2InertiaNaturalMotion : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Condition(
                            ABI::Microsoft::UI::Composition::IExpressionAnimation* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NaturalMotion(
                            ABI::Microsoft::UI::Composition::IVector2NaturalMotionAnimation** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_NaturalMotion(
                            ABI::Microsoft::UI::Composition::IVector2NaturalMotionAnimation* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerVector2InertiaNaturalMotion = _uuidof(IInteractionTrackerVector2InertiaNaturalMotion);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotionStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaNaturalMotionStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotionStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("cc24ab87-9131-5286-b3ce-1ef97e0974e6")
                    IInteractionTrackerVector2InertiaNaturalMotionStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::ICompositor* compositor,
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionTrackerVector2InertiaNaturalMotion** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IInteractionTrackerVector2InertiaNaturalMotionStatics = _uuidof(IInteractionTrackerVector2InertiaNaturalMotionStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSource
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSource[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSource";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("ea595c95-b9cb-5cd4-bb9c-4934ff329063")
                    IVisualInteractionSource : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsPositionXRailsEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsPositionXRailsEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsPositionYRailsEnabled(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsPositionYRailsEnabled(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ManipulationRedirectionMode(
                            ABI::Microsoft::UI::Composition::Interactions::VisualInteractionSourceRedirectionMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ManipulationRedirectionMode(
                            ABI::Microsoft::UI::Composition::Interactions::VisualInteractionSourceRedirectionMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionXChainingMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionChainingMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionXChainingMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionChainingMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionXSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionXSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionYChainingMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionChainingMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionYChainingMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionChainingMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionYSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PositionYSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleChainingMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionChainingMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ScaleChainingMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionChainingMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceMode* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ScaleSourceMode(
                            ABI::Microsoft::UI::Composition::Interactions::InteractionSourceMode value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Source(
                            ABI::Microsoft::UI::Composition::IVisual** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryRedirectForManipulation(
                            ABI::Microsoft::UI::Input::IPointerPoint* pointerPoint
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVisualInteractionSource = _uuidof(IVisualInteractionSource);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSource2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSource2[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSource2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("ff1132ba-dc0d-519e-be49-be301e52306a")
                    IVisualInteractionSource2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_DeltaPosition(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeltaScale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Position(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PositionVelocity(
                            ABI::Windows::Foundation::Numerics::Vector3* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scale(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ScaleVelocity(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureCenterPointXModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureCenterPointYModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureDeltaPositionXModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureDeltaPositionYModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConfigureDeltaScaleModifiers(
                            __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVisualInteractionSource2 = _uuidof(IVisualInteractionSource2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSource3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSource3[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSource3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("d523bd66-a05d-5417-8e07-84ae3caf9752")
                    IVisualInteractionSource3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PointerWheelConfig(
                            ABI::Microsoft::UI::Composition::Interactions::IInteractionSourceConfiguration** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVisualInteractionSource3 = _uuidof(IVisualInteractionSource3);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSourceObjectFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSourceObjectFactory[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSourceObjectFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("feb73102-238c-52aa-8e03-b68d5ecc44b3")
                    IVisualInteractionSourceObjectFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IVisualInteractionSourceObjectFactory = _uuidof(IVisualInteractionSourceObjectFactory);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSourceStatics[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("5fc9c763-e2e5-530e-87cd-b93118ade8a3")
                    IVisualInteractionSourceStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            ABI::Microsoft::UI::Composition::IVisual* source,
                            ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSource** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVisualInteractionSourceStatics = _uuidof(IVisualInteractionSourceStatics);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSourceStatics2[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Interactions {
                    MIDL_INTERFACE("a6b494fe-12a1-5a73-b87e-4c4ef58eac6c")
                    IVisualInteractionSourceStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateFromIVisualElement(
                            ABI::Microsoft::UI::Composition::IVisualElement* source,
                            ABI::Microsoft::UI::Composition::Interactions::IVisualInteractionSource** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IVisualInteractionSourceStatics2 = _uuidof(IVisualInteractionSourceStatics2);
                } /* Interactions */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.CompositionConditionalValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.ICompositionConditionalValueStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.ICompositionConditionalValue ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionConditionalValue_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionConditionalValue_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_CompositionConditionalValue[] = L"Microsoft.UI.Composition.Interactions.CompositionConditionalValue";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.CompositionInteractionSourceCollection
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.ICompositionInteractionSourceCollection ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Composition.Interactions.ICompositionInteractionSource>
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionInteractionSourceCollection_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionInteractionSourceCollection_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_CompositionInteractionSourceCollection[] = L"Microsoft.UI.Composition.Interactions.CompositionInteractionSourceCollection";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionSourceConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionSourceConfiguration ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionSourceConfiguration_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionSourceConfiguration_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionSourceConfiguration[] = L"Microsoft.UI.Composition.Interactions.InteractionSourceConfiguration";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics2 interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker2
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker3
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker4
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker5
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTracker_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTracker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTracker[] = L"Microsoft.UI.Composition.Interactions.InteractionTracker";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerCustomAnimationStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerCustomAnimationStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerCustomAnimationStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerIdleStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerIdleStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerIdleStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifier ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaModifier_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaModifier_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaModifier[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotionStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaMotion_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaMotion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaMotion[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotionStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaNaturalMotion_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaNaturalMotion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValueStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValue ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaRestingValue_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaRestingValue_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaRestingValue[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs2
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs3
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInteractingStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInteractingStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInteractingStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerRequestIgnoredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerRequestIgnoredArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerRequestIgnoredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerRequestIgnoredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerRequestIgnoredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerRequestIgnoredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerValuesChangedArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerValuesChangedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerValuesChangedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerValuesChangedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerValuesChangedArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerValuesChangedArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifier ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaModifier_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaModifier_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaModifier[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotionStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaNaturalMotion_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaNaturalMotion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics2 interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IVisualInteractionSource ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IVisualInteractionSource2
 *    Microsoft.UI.Composition.Interactions.IVisualInteractionSource3
 *    Microsoft.UI.Composition.Interactions.ICompositionInteractionSource
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_VisualInteractionSource_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_VisualInteractionSource_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_VisualInteractionSource[] = L"Microsoft.UI.Composition.Interactions.VisualInteractionSource";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2 __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue;

typedef struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValueVtbl;

interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue;

typedef struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* This,
        __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValueVtbl;

interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource;

typedef struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSourceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSourceVtbl;

interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSourceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource;

typedef struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSourceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource* This,
        __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSourceVtbl;

interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSourceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CICompositionInteractionSource_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier;

typedef struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifierVtbl;

interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier;

typedef struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* This,
        __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifierVtbl;

interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier;

typedef struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifierVtbl;

interface __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier;

typedef struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* This,
        __FIIterator_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifierVtbl;

interface __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if !defined(____FIReference_1_float_INTERFACE_DEFINED__)
#define ____FIReference_1_float_INTERFACE_DEFINED__

typedef interface __FIReference_1_float __FIReference_1_float;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_float;

typedef struct __FIReference_1_floatVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_float* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_float* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_float* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_float* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_float* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_float* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_float* This,
        FLOAT* result);

    END_INTERFACE
} __FIReference_1_floatVtbl;

interface __FIReference_1_float
{
    CONST_VTBL struct __FIReference_1_floatVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_float_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_float_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_float_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_float_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_float_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_float_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_float_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_float_INTERFACE_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 __x_ABI_CWindows_CFoundation_CNumerics_CVector3;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIReference_1_Windows__CFoundation__CNumerics__CVector3_INTERFACE_DEFINED__)
#define ____FIReference_1_Windows__CFoundation__CNumerics__CVector3_INTERFACE_DEFINED__

typedef interface __FIReference_1_Windows__CFoundation__CNumerics__CVector3 __FIReference_1_Windows__CFoundation__CNumerics__CVector3;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_Windows__CFoundation__CNumerics__CVector3;

typedef struct __FIReference_1_Windows__CFoundation__CNumerics__CVector3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_Windows__CFoundation__CNumerics__CVector3* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* result);

    END_INTERFACE
} __FIReference_1_Windows__CFoundation__CNumerics__CVector3Vtbl;

interface __FIReference_1_Windows__CFoundation__CNumerics__CVector3
{
    CONST_VTBL struct __FIReference_1_Windows__CFoundation__CNumerics__CVector3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_Windows__CFoundation__CNumerics__CVector3_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_Windows__CFoundation__CNumerics__CVector3_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositor __x_ABI_CMicrosoft_CUI_CComposition_CICompositor;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement __x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation __x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation __x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIVisual __x_ABI_CMicrosoft_CUI_CComposition_CIVisual;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIPropertyValue __x_ABI_CWindows_CFoundation_CIPropertyValue;

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionBindingAxisModes __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionBindingAxisModes;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerClampingOption __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerClampingOption;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerPositionUpdateOption __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerPositionUpdateOption;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CVisualInteractionSourceRedirectionMode __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CVisualInteractionSourceRedirectionMode;

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionBindingAxisModes
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionBindingAxisModes
{
    InteractionBindingAxisModes_None = 0,
    InteractionBindingAxisModes_PositionX = 0x1,
    InteractionBindingAxisModes_PositionY = 0x2,
    InteractionBindingAxisModes_Scale = 0x4,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionChainingMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode
{
    InteractionChainingMode_Auto = 0,
    InteractionChainingMode_Always = 1,
    InteractionChainingMode_Never = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionSourceMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode
{
    InteractionSourceMode_Disabled = 0,
    InteractionSourceMode_EnabledWithInertia = 1,
    InteractionSourceMode_EnabledWithoutInertia = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionSourceRedirectionMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode
{
    InteractionSourceRedirectionMode_Disabled = 0,
    InteractionSourceRedirectionMode_Enabled = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionTrackerClampingOption
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerClampingOption
{
    InteractionTrackerClampingOption_Auto = 0,
    InteractionTrackerClampingOption_Disabled = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.InteractionTrackerPositionUpdateOption
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerPositionUpdateOption
{
    InteractionTrackerPositionUpdateOption_Default = 0,
    InteractionTrackerPositionUpdateOption_AllowActiveCustomScaleAnimation = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Composition.Interactions.VisualInteractionSourceRedirectionMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CVisualInteractionSourceRedirectionMode
{
    VisualInteractionSourceRedirectionMode_Off = 0,
    VisualInteractionSourceRedirectionMode_CapableTouchpadOnly = 1,
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
    VisualInteractionSourceRedirectionMode_PointerWheelOnly = 2,
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
    VisualInteractionSourceRedirectionMode_CapableTouchpadAndPointerWheel = 3,
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionConditionalValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.CompositionConditionalValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionConditionalValue[] = L"Microsoft.UI.Composition.Interactions.ICompositionConditionalValue";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Value)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_get_Condition(This, value) \
    ((This)->lpVtbl->get_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_put_Condition(This, value) \
    ((This)->lpVtbl->put_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_get_Value(This, value) \
    ((This)->lpVtbl->get_Value(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_put_Value(This, value) \
    ((This)->lpVtbl->put_Value(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionConditionalValueStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.CompositionConditionalValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionConditionalValueStatics[] = L"Microsoft.UI.Composition.Interactions.ICompositionConditionalValueStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValue** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_Create(This, compositor, result) \
    ((This)->lpVtbl->Create(This, compositor, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionConditionalValueStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionInteractionSource
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionInteractionSource[] = L"Microsoft.UI.Composition.Interactions.ICompositionInteractionSource";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.ICompositionInteractionSourceCollection
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.CompositionInteractionSourceCollection
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_ICompositionInteractionSourceCollection[] = L"Microsoft.UI.Composition.Interactions.ICompositionInteractionSourceCollection";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollectionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Count)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* Add)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* value);
    HRESULT (STDMETHODCALLTYPE* Remove)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSource* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAll)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollectionVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollectionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_get_Count(This, value) \
    ((This)->lpVtbl->get_Count(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_Add(This, value) \
    ((This)->lpVtbl->Add(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_Remove(This, value) \
    ((This)->lpVtbl->Remove(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_RemoveAll(This) \
    ((This)->lpVtbl->RemoveAll(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionSourceConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionSourceConfiguration
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionSourceConfiguration[] = L"Microsoft.UI.Composition.Interactions.IInteractionSourceConfiguration";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfigurationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PositionXSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode* value);
    HRESULT (STDMETHODCALLTYPE* put_PositionXSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode value);
    HRESULT (STDMETHODCALLTYPE* get_PositionYSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode* value);
    HRESULT (STDMETHODCALLTYPE* put_PositionYSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceRedirectionMode value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfigurationVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfigurationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_get_PositionXSourceMode(This, value) \
    ((This)->lpVtbl->get_PositionXSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_put_PositionXSourceMode(This, value) \
    ((This)->lpVtbl->put_PositionXSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_get_PositionYSourceMode(This, value) \
    ((This)->lpVtbl->get_PositionYSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_put_PositionYSourceMode(This, value) \
    ((This)->lpVtbl->put_PositionYSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_get_ScaleSourceMode(This, value) \
    ((This)->lpVtbl->get_ScaleSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_put_ScaleSourceMode(This, value) \
    ((This)->lpVtbl->put_ScaleSourceMode(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_InteractionSources)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CICompositionInteractionSourceCollection** value);
    HRESULT (STDMETHODCALLTYPE* get_IsPositionRoundingSuggested)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_MaxPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 value);
    HRESULT (STDMETHODCALLTYPE* get_MaxScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_MinPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* put_MinPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 value);
    HRESULT (STDMETHODCALLTYPE* get_MinScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_MinScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_NaturalRestingPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_NaturalRestingScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_Owner)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner** value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_PositionInertiaDecayRate)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIReference_1_Windows__CFoundation__CNumerics__CVector3** value);
    HRESULT (STDMETHODCALLTYPE* put_PositionInertiaDecayRate)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIReference_1_Windows__CFoundation__CNumerics__CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_PositionVelocityInPixelsPerSecond)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_Scale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleInertiaDecayRate)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIReference_1_float** value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleInertiaDecayRate)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIReference_1_float* value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleVelocityInPercentPerSecond)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* AdjustPositionXIfGreaterThanThreshold)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT adjustment,
        FLOAT positionThreshold);
    HRESULT (STDMETHODCALLTYPE* AdjustPositionYIfGreaterThanThreshold)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT adjustment,
        FLOAT positionThreshold);
    HRESULT (STDMETHODCALLTYPE* ConfigurePositionXInertiaModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* modifiers);
    HRESULT (STDMETHODCALLTYPE* ConfigurePositionYInertiaModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* modifiers);
    HRESULT (STDMETHODCALLTYPE* ConfigureScaleInertiaModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerInertiaModifier* modifiers);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 value,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePositionBy)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 amount,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePositionWithAnimation)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation* animation,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePositionWithAdditionalVelocity)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 velocityInPixelsPerSecond,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdateScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT value,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 centerPoint,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdateScaleWithAnimation)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimation* animation,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 centerPoint,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdateScaleWithAdditionalVelocity)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* This,
        FLOAT velocityInPercentPerSecond,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 centerPoint,
        INT32* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_InteractionSources(This, value) \
    ((This)->lpVtbl->get_InteractionSources(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_IsPositionRoundingSuggested(This, value) \
    ((This)->lpVtbl->get_IsPositionRoundingSuggested(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_MaxPosition(This, value) \
    ((This)->lpVtbl->get_MaxPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_put_MaxPosition(This, value) \
    ((This)->lpVtbl->put_MaxPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_MaxScale(This, value) \
    ((This)->lpVtbl->get_MaxScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_put_MaxScale(This, value) \
    ((This)->lpVtbl->put_MaxScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_MinPosition(This, value) \
    ((This)->lpVtbl->get_MinPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_put_MinPosition(This, value) \
    ((This)->lpVtbl->put_MinPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_MinScale(This, value) \
    ((This)->lpVtbl->get_MinScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_put_MinScale(This, value) \
    ((This)->lpVtbl->put_MinScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_NaturalRestingPosition(This, value) \
    ((This)->lpVtbl->get_NaturalRestingPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_NaturalRestingScale(This, value) \
    ((This)->lpVtbl->get_NaturalRestingScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_Owner(This, value) \
    ((This)->lpVtbl->get_Owner(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_PositionInertiaDecayRate(This, value) \
    ((This)->lpVtbl->get_PositionInertiaDecayRate(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_put_PositionInertiaDecayRate(This, value) \
    ((This)->lpVtbl->put_PositionInertiaDecayRate(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_PositionVelocityInPixelsPerSecond(This, value) \
    ((This)->lpVtbl->get_PositionVelocityInPixelsPerSecond(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_Scale(This, value) \
    ((This)->lpVtbl->get_Scale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_ScaleInertiaDecayRate(This, value) \
    ((This)->lpVtbl->get_ScaleInertiaDecayRate(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_put_ScaleInertiaDecayRate(This, value) \
    ((This)->lpVtbl->put_ScaleInertiaDecayRate(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_get_ScaleVelocityInPercentPerSecond(This, value) \
    ((This)->lpVtbl->get_ScaleVelocityInPercentPerSecond(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_AdjustPositionXIfGreaterThanThreshold(This, adjustment, positionThreshold) \
    ((This)->lpVtbl->AdjustPositionXIfGreaterThanThreshold(This, adjustment, positionThreshold))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_AdjustPositionYIfGreaterThanThreshold(This, adjustment, positionThreshold) \
    ((This)->lpVtbl->AdjustPositionYIfGreaterThanThreshold(This, adjustment, positionThreshold))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_ConfigurePositionXInertiaModifiers(This, modifiers) \
    ((This)->lpVtbl->ConfigurePositionXInertiaModifiers(This, modifiers))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_ConfigurePositionYInertiaModifiers(This, modifiers) \
    ((This)->lpVtbl->ConfigurePositionYInertiaModifiers(This, modifiers))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_ConfigureScaleInertiaModifiers(This, modifiers) \
    ((This)->lpVtbl->ConfigureScaleInertiaModifiers(This, modifiers))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdatePosition(This, value, result) \
    ((This)->lpVtbl->TryUpdatePosition(This, value, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdatePositionBy(This, amount, result) \
    ((This)->lpVtbl->TryUpdatePositionBy(This, amount, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdatePositionWithAnimation(This, animation, result) \
    ((This)->lpVtbl->TryUpdatePositionWithAnimation(This, animation, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdatePositionWithAdditionalVelocity(This, velocityInPixelsPerSecond, result) \
    ((This)->lpVtbl->TryUpdatePositionWithAdditionalVelocity(This, velocityInPixelsPerSecond, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdateScale(This, value, centerPoint, result) \
    ((This)->lpVtbl->TryUpdateScale(This, value, centerPoint, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdateScaleWithAnimation(This, animation, centerPoint, result) \
    ((This)->lpVtbl->TryUpdateScaleWithAnimation(This, animation, centerPoint, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_TryUpdateScaleWithAdditionalVelocity(This, velocityInPercentPerSecond, centerPoint, result) \
    ((This)->lpVtbl->TryUpdateScaleWithAdditionalVelocity(This, velocityInPercentPerSecond, centerPoint, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ConfigureCenterPointXInertiaModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);
    HRESULT (STDMETHODCALLTYPE* ConfigureCenterPointYInertiaModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_ConfigureCenterPointXInertiaModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureCenterPointXInertiaModifiers(This, conditionalValues))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_ConfigureCenterPointYInertiaModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureCenterPointYInertiaModifiers(This, conditionalValues))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker3[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker3";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ConfigureVector2PositionInertiaModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CInteractionTrackerVector2InertiaModifier* modifiers);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_ConfigureVector2PositionInertiaModifiers(This, modifiers) \
    ((This)->lpVtbl->ConfigureVector2PositionInertiaModifiers(This, modifiers))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker4
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker4[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker4";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePositionWithOption)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 value,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerClampingOption option,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePositionByWithOption)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 amount,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerClampingOption option,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* get_IsInertiaFromImpulse)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_TryUpdatePositionWithOption(This, value, option, result) \
    ((This)->lpVtbl->TryUpdatePositionWithOption(This, value, option, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_TryUpdatePositionByWithOption(This, amount, option, result) \
    ((This)->lpVtbl->TryUpdatePositionByWithOption(This, amount, option, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_get_IsInertiaFromImpulse(This, value) \
    ((This)->lpVtbl->get_IsInertiaFromImpulse(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker4_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTracker5
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTracker5[] = L"Microsoft.UI.Composition.Interactions.IInteractionTracker5";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* TryUpdatePositionWithOption)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3 value,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerClampingOption option,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionTrackerPositionUpdateOption posUpdateOption,
        INT32* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_TryUpdatePositionWithOption(This, value, option, posUpdateOption, result) \
    ((This)->lpVtbl->TryUpdatePositionWithOption(This, value, option, posUpdateOption, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker5_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerCustomAnimationStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RequestId)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_get_RequestId(This, value) \
    ((This)->lpVtbl->get_RequestId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerCustomAnimationStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsFromBinding)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_get_IsFromBinding(This, value) \
    ((This)->lpVtbl->get_IsFromBinding(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerIdleStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RequestId)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_get_RequestId(This, value) \
    ((This)->lpVtbl->get_RequestId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerIdleStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsFromBinding)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_get_IsFromBinding(This, value) \
    ((This)->lpVtbl->get_IsFromBinding(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaModifier[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifier";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifier_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifierFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaModifierFactory[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifierFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaModifierFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaMotion[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotion";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);
    HRESULT (STDMETHODCALLTYPE* get_Motion)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Motion)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_get_Condition(This, value) \
    ((This)->lpVtbl->get_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_put_Condition(This, value) \
    ((This)->lpVtbl->put_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_get_Motion(This, value) \
    ((This)->lpVtbl->get_Motion(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_put_Motion(This, value) \
    ((This)->lpVtbl->put_Motion(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotionStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaMotionStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotionStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotion** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_Create(This, compositor, result) \
    ((This)->lpVtbl->Create(This, compositor, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaMotionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotion";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);
    HRESULT (STDMETHODCALLTYPE* get_NaturalMotion)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_NaturalMotion)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIScalarNaturalMotionAnimation* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_get_Condition(This, value) \
    ((This)->lpVtbl->get_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_put_Condition(This, value) \
    ((This)->lpVtbl->put_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_get_NaturalMotion(This, value) \
    ((This)->lpVtbl->get_NaturalMotion(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_put_NaturalMotion(This, value) \
    ((This)->lpVtbl->put_NaturalMotion(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotionStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaNaturalMotionStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotionStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotion** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_Create(This, compositor, result) \
    ((This)->lpVtbl->Create(This, compositor, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaNaturalMotionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaRestingValue[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValue";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);
    HRESULT (STDMETHODCALLTYPE* get_RestingValue)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_RestingValue)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_get_Condition(This, value) \
    ((This)->lpVtbl->get_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_put_Condition(This, value) \
    ((This)->lpVtbl->put_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_get_RestingValue(This, value) \
    ((This)->lpVtbl->get_RestingValue(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_put_RestingValue(This, value) \
    ((This)->lpVtbl->put_RestingValue(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValueStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaRestingValueStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValueStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValue** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_Create(This, compositor, result) \
    ((This)->lpVtbl->Create(This, compositor, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaRestingValueStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ModifiedRestingPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        __FIReference_1_Windows__CFoundation__CNumerics__CVector3** value);
    HRESULT (STDMETHODCALLTYPE* get_ModifiedRestingScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        __FIReference_1_float** value);
    HRESULT (STDMETHODCALLTYPE* get_NaturalRestingPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_NaturalRestingScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_PositionVelocityInPixelsPerSecond)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_RequestId)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleVelocityInPercentPerSecond)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_ModifiedRestingPosition(This, value) \
    ((This)->lpVtbl->get_ModifiedRestingPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_ModifiedRestingScale(This, value) \
    ((This)->lpVtbl->get_ModifiedRestingScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_NaturalRestingPosition(This, value) \
    ((This)->lpVtbl->get_NaturalRestingPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_NaturalRestingScale(This, value) \
    ((This)->lpVtbl->get_NaturalRestingScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_PositionVelocityInPixelsPerSecond(This, value) \
    ((This)->lpVtbl->get_PositionVelocityInPixelsPerSecond(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_RequestId(This, value) \
    ((This)->lpVtbl->get_RequestId(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_get_ScaleVelocityInPercentPerSecond(This, value) \
    ((This)->lpVtbl->get_ScaleVelocityInPercentPerSecond(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsInertiaFromImpulse)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_get_IsInertiaFromImpulse(This, value) \
    ((This)->lpVtbl->get_IsInertiaFromImpulse(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInertiaStateEnteredArgs3[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs3";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsFromBinding)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_get_IsFromBinding(This, value) \
    ((This)->lpVtbl->get_IsFromBinding(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInteractingStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RequestId)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_get_RequestId(This, value) \
    ((This)->lpVtbl->get_RequestId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerInteractingStateEnteredArgs2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsFromBinding)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_get_IsFromBinding(This, value) \
    ((This)->lpVtbl->get_IsFromBinding(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerOwner
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerOwner[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerOwner";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwnerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CustomAnimationStateEntered)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* sender,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerCustomAnimationStateEnteredArgs* args);
    HRESULT (STDMETHODCALLTYPE* IdleStateEntered)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* sender,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerIdleStateEnteredArgs* args);
    HRESULT (STDMETHODCALLTYPE* InertiaStateEntered)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* sender,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInertiaStateEnteredArgs* args);
    HRESULT (STDMETHODCALLTYPE* InteractingStateEntered)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* sender,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerInteractingStateEnteredArgs* args);
    HRESULT (STDMETHODCALLTYPE* RequestIgnored)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* sender,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* args);
    HRESULT (STDMETHODCALLTYPE* ValuesChanged)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* sender,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwnerVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwnerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_CustomAnimationStateEntered(This, sender, args) \
    ((This)->lpVtbl->CustomAnimationStateEntered(This, sender, args))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_IdleStateEntered(This, sender, args) \
    ((This)->lpVtbl->IdleStateEntered(This, sender, args))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_InertiaStateEntered(This, sender, args) \
    ((This)->lpVtbl->InertiaStateEntered(This, sender, args))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_InteractingStateEntered(This, sender, args) \
    ((This)->lpVtbl->InteractingStateEntered(This, sender, args))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_RequestIgnored(This, sender, args) \
    ((This)->lpVtbl->RequestIgnored(This, sender, args))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_ValuesChanged(This, sender, args) \
    ((This)->lpVtbl->ValuesChanged(This, sender, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerRequestIgnoredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerRequestIgnoredArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerRequestIgnoredArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerRequestIgnoredArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RequestId)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_get_RequestId(This, value) \
    ((This)->lpVtbl->get_RequestId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerRequestIgnoredArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker** result);
    HRESULT (STDMETHODCALLTYPE* CreateWithOwner)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerOwner* owner,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_Create(This, compositor, result) \
    ((This)->lpVtbl->Create(This, compositor, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_CreateWithOwner(This, compositor, owner, result) \
    ((This)->lpVtbl->CreateWithOwner(This, compositor, owner, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerStatics2[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SetBindingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* boundTracker1,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* boundTracker2,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionBindingAxisModes axisMode);
    HRESULT (STDMETHODCALLTYPE* GetBindingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* boundTracker1,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTracker* boundTracker2,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionBindingAxisModes* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_SetBindingMode(This, boundTracker1, boundTracker2, axisMode) \
    ((This)->lpVtbl->SetBindingMode(This, boundTracker1, boundTracker2, axisMode))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_GetBindingMode(This, boundTracker1, boundTracker2, result) \
    ((This)->lpVtbl->GetBindingMode(This, boundTracker1, boundTracker2, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerValuesChangedArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerValuesChangedArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerValuesChangedArgs[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerValuesChangedArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_RequestId)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_Scale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_get_RequestId(This, value) \
    ((This)->lpVtbl->get_RequestId(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_get_Scale(This, value) \
    ((This)->lpVtbl->get_Scale(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerValuesChangedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaModifier[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifier";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifier_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifierFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaModifierFactory[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifierFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaModifierFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotion";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_Condition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIExpressionAnimation* value);
    HRESULT (STDMETHODCALLTYPE* get_NaturalMotion)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation** value);
    HRESULT (STDMETHODCALLTYPE* put_NaturalMotion)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVector2NaturalMotionAnimation* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_get_Condition(This, value) \
    ((This)->lpVtbl->get_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_put_Condition(This, value) \
    ((This)->lpVtbl->put_Condition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_get_NaturalMotion(This, value) \
    ((This)->lpVtbl->get_NaturalMotion(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_put_NaturalMotion(This, value) \
    ((This)->lpVtbl->put_NaturalMotion(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotionStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IInteractionTrackerVector2InertiaNaturalMotionStatics[] = L"Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotionStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotion** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_Create(This, compositor, result) \
    ((This)->lpVtbl->Create(This, compositor, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionTrackerVector2InertiaNaturalMotionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSource
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSource[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSource";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsPositionXRailsEnabled)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsPositionXRailsEnabled)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsPositionYRailsEnabled)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsPositionYRailsEnabled)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ManipulationRedirectionMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CVisualInteractionSourceRedirectionMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ManipulationRedirectionMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CVisualInteractionSourceRedirectionMode value);
    HRESULT (STDMETHODCALLTYPE* get_PositionXChainingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode* value);
    HRESULT (STDMETHODCALLTYPE* put_PositionXChainingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode value);
    HRESULT (STDMETHODCALLTYPE* get_PositionXSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode* value);
    HRESULT (STDMETHODCALLTYPE* put_PositionXSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode value);
    HRESULT (STDMETHODCALLTYPE* get_PositionYChainingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode* value);
    HRESULT (STDMETHODCALLTYPE* put_PositionYChainingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode value);
    HRESULT (STDMETHODCALLTYPE* get_PositionYSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode* value);
    HRESULT (STDMETHODCALLTYPE* put_PositionYSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleChainingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleChainingMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionChainingMode value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode* value);
    HRESULT (STDMETHODCALLTYPE* put_ScaleSourceMode)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CInteractionSourceMode value);
    HRESULT (STDMETHODCALLTYPE* get_Source)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual** value);
    HRESULT (STDMETHODCALLTYPE* TryRedirectForManipulation)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource* This,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* pointerPoint);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_IsPositionXRailsEnabled(This, value) \
    ((This)->lpVtbl->get_IsPositionXRailsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_IsPositionXRailsEnabled(This, value) \
    ((This)->lpVtbl->put_IsPositionXRailsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_IsPositionYRailsEnabled(This, value) \
    ((This)->lpVtbl->get_IsPositionYRailsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_IsPositionYRailsEnabled(This, value) \
    ((This)->lpVtbl->put_IsPositionYRailsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_ManipulationRedirectionMode(This, value) \
    ((This)->lpVtbl->get_ManipulationRedirectionMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_ManipulationRedirectionMode(This, value) \
    ((This)->lpVtbl->put_ManipulationRedirectionMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_PositionXChainingMode(This, value) \
    ((This)->lpVtbl->get_PositionXChainingMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_PositionXChainingMode(This, value) \
    ((This)->lpVtbl->put_PositionXChainingMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_PositionXSourceMode(This, value) \
    ((This)->lpVtbl->get_PositionXSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_PositionXSourceMode(This, value) \
    ((This)->lpVtbl->put_PositionXSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_PositionYChainingMode(This, value) \
    ((This)->lpVtbl->get_PositionYChainingMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_PositionYChainingMode(This, value) \
    ((This)->lpVtbl->put_PositionYChainingMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_PositionYSourceMode(This, value) \
    ((This)->lpVtbl->get_PositionYSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_PositionYSourceMode(This, value) \
    ((This)->lpVtbl->put_PositionYSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_ScaleChainingMode(This, value) \
    ((This)->lpVtbl->get_ScaleChainingMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_ScaleChainingMode(This, value) \
    ((This)->lpVtbl->put_ScaleChainingMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_ScaleSourceMode(This, value) \
    ((This)->lpVtbl->get_ScaleSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_put_ScaleSourceMode(This, value) \
    ((This)->lpVtbl->put_ScaleSourceMode(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_get_Source(This, value) \
    ((This)->lpVtbl->get_Source(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_TryRedirectForManipulation(This, pointerPoint) \
    ((This)->lpVtbl->TryRedirectForManipulation(This, pointerPoint))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSource2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSource2[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSource2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DeltaPosition)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_DeltaScale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_PositionVelocity)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector3* value);
    HRESULT (STDMETHODCALLTYPE* get_Scale)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_ScaleVelocity)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* ConfigureCenterPointXModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);
    HRESULT (STDMETHODCALLTYPE* ConfigureCenterPointYModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);
    HRESULT (STDMETHODCALLTYPE* ConfigureDeltaPositionXModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);
    HRESULT (STDMETHODCALLTYPE* ConfigureDeltaPositionYModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);
    HRESULT (STDMETHODCALLTYPE* ConfigureDeltaScaleModifiers)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2* This,
        __FIIterable_1_Microsoft__CUI__CComposition__CInteractions__CCompositionConditionalValue* conditionalValues);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_get_DeltaPosition(This, value) \
    ((This)->lpVtbl->get_DeltaPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_get_DeltaScale(This, value) \
    ((This)->lpVtbl->get_DeltaScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_get_PositionVelocity(This, value) \
    ((This)->lpVtbl->get_PositionVelocity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_get_Scale(This, value) \
    ((This)->lpVtbl->get_Scale(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_get_ScaleVelocity(This, value) \
    ((This)->lpVtbl->get_ScaleVelocity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_ConfigureCenterPointXModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureCenterPointXModifiers(This, conditionalValues))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_ConfigureCenterPointYModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureCenterPointYModifiers(This, conditionalValues))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_ConfigureDeltaPositionXModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureDeltaPositionXModifiers(This, conditionalValues))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_ConfigureDeltaPositionYModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureDeltaPositionYModifiers(This, conditionalValues))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_ConfigureDeltaScaleModifiers(This, conditionalValues) \
    ((This)->lpVtbl->ConfigureDeltaScaleModifiers(This, conditionalValues))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSource3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSource3[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSource3";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PointerWheelConfig)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIInteractionSourceConfiguration** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_get_PointerWheelConfig(This, value) \
    ((This)->lpVtbl->get_PointerWheelConfig(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSourceObjectFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSourceObjectFactory[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSourceObjectFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceObjectFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSourceStatics[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* source,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_Create(This, source, result) \
    ((This)->lpVtbl->Create(This, source, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Interactions_IVisualInteractionSourceStatics2[] = L"Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateFromIVisualElement)(__x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisualElement* source,
        __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSource** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_CreateFromIVisualElement(This, source, result) \
    ((This)->lpVtbl->CreateFromIVisualElement(This, source, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CInteractions_CIVisualInteractionSourceStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.CompositionConditionalValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.ICompositionConditionalValueStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.ICompositionConditionalValue ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionConditionalValue_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionConditionalValue_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_CompositionConditionalValue[] = L"Microsoft.UI.Composition.Interactions.CompositionConditionalValue";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.CompositionInteractionSourceCollection
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.ICompositionInteractionSourceCollection ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Composition.Interactions.ICompositionInteractionSource>
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionInteractionSourceCollection_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_CompositionInteractionSourceCollection_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_CompositionInteractionSourceCollection[] = L"Microsoft.UI.Composition.Interactions.CompositionInteractionSourceCollection";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionSourceConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionSourceConfiguration ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionSourceConfiguration_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionSourceConfiguration_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionSourceConfiguration[] = L"Microsoft.UI.Composition.Interactions.InteractionSourceConfiguration";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTracker
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics2 interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker2
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker3
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker4
 *    Microsoft.UI.Composition.Interactions.IInteractionTracker5
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTracker_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTracker_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTracker[] = L"Microsoft.UI.Composition.Interactions.InteractionTracker";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerCustomAnimationStateEnteredArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerCustomAnimationStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerCustomAnimationStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerCustomAnimationStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerCustomAnimationStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerIdleStateEnteredArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerIdleStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerIdleStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerIdleStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerIdleStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaModifier ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaModifier_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaModifier_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaModifier[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaModifier";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotionStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaMotion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaMotion_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaMotion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaMotion[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaMotion";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotionStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaNaturalMotion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaNaturalMotion_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaNaturalMotion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaNaturalMotion";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValueStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaRestingValue ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaRestingValue_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaRestingValue_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaRestingValue[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaRestingValue";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs2
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInertiaStateEnteredArgs3
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInertiaStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInertiaStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerInteractingStateEnteredArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInteractingStateEnteredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerInteractingStateEnteredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerInteractingStateEnteredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerInteractingStateEnteredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerRequestIgnoredArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerRequestIgnoredArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerRequestIgnoredArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerRequestIgnoredArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerRequestIgnoredArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerRequestIgnoredArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerValuesChangedArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerValuesChangedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerValuesChangedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerValuesChangedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerValuesChangedArgs[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerValuesChangedArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaModifier ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaModifier_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaModifier_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaModifier[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaModifier";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotionStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IInteractionTrackerVector2InertiaNaturalMotion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaNaturalMotion_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaNaturalMotion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_InteractionTrackerVector2InertiaNaturalMotion[] = L"Microsoft.UI.Composition.Interactions.InteractionTrackerVector2InertiaNaturalMotion";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Interactions.VisualInteractionSource
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics2 interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Composition.Interactions.IVisualInteractionSourceStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Interactions.IVisualInteractionSource ** Default Interface **
 *    Microsoft.UI.Composition.Interactions.IVisualInteractionSource2
 *    Microsoft.UI.Composition.Interactions.IVisualInteractionSource3
 *    Microsoft.UI.Composition.Interactions.ICompositionInteractionSource
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Interactions_VisualInteractionSource_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Interactions_VisualInteractionSource_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Interactions_VisualInteractionSource[] = L"Microsoft.UI.Composition.Interactions.VisualInteractionSource";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Ecomposition2Einteractions_p_h__

#endif // __microsoft2Eui2Ecomposition2Einteractions_h__
