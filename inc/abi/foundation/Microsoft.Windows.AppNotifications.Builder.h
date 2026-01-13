
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
#ifndef __microsoft2Ewindows2Eappnotifications2Ebuilder_h__
#define __microsoft2Ewindows2Eappnotifications2Ebuilder_h__
#ifndef __microsoft2Ewindows2Eappnotifications2Ebuilder_p_h__
#define __microsoft2Ewindows2Eappnotifications2Ebuilder_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION 0x40000
#endif // defined(MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION)

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
#include "Microsoft.Windows.AppNotifications.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationBuilder;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationBuilderStatics;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilderStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationButton;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationButtonFactory;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButtonFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationButtonStatics;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButtonStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationComboBox;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBox

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationComboBoxFactory;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBoxFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationProgressBar;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    interface IAppNotificationTextProperties;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationTextProperties

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions

#ifndef DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("60310303-49c5-52e6-abc6-a9b36eccc716"))
IKeyValuePair<HSTRING, HSTRING> : IKeyValuePair_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, HSTRING> __FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("05eb86f1-7140-5517-b88d-cbaebe57e6b1"))
IIterator<__FIKeyValuePair_2_HSTRING_HSTRING*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING_HSTRING*> __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e9bdaaf0-cbf6-5c72-be90-29cbf3a1319b"))
IIterable<__FIKeyValuePair_2_HSTRING_HSTRING*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING_HSTRING*> __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIMapView_2_HSTRING_HSTRING_USE
#define DEF___FIMapView_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ac7f26f2-feb7-5b2a-8ac4-345bc62caede"))
IMapView<HSTRING, HSTRING> : IMapView_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, HSTRING> __FIMapView_2_HSTRING_HSTRING_t;
#define __FIMapView_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIMap_2_HSTRING_HSTRING_USE
#define DEF___FIMap_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f6d1f700-49c2-52ae-8154-826f9908773c"))
IMap<HSTRING, HSTRING> : IMap_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMap`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMap<HSTRING, HSTRING> __FIMap_2_HSTRING_HSTRING_t;
#define __FIMap_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIMap_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMap_2_HSTRING_HSTRING_USE */


namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                class AppNotification;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotification;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification ABI::Microsoft::Windows::AppNotifications::IAppNotification

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct DateTime DateTime;
        } /* Foundation */
    } /* Windows */
} /* ABI */

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
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    typedef enum AppNotificationAudioLooping : int AppNotificationAudioLooping;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    typedef enum AppNotificationButtonStyle : int AppNotificationButtonStyle;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    typedef enum AppNotificationDuration : int AppNotificationDuration;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    typedef enum AppNotificationImageCrop : int AppNotificationImageCrop;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    typedef enum AppNotificationScenario : int AppNotificationScenario;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    typedef enum AppNotificationSoundEvent : int AppNotificationSoundEvent;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    class AppNotificationBuilder;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    class AppNotificationButton;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    class AppNotificationComboBox;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    class AppNotificationProgressBar;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    class AppNotificationTextProperties;
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationAudioLooping
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    enum AppNotificationAudioLooping : int
                    {
                        AppNotificationAudioLooping_None = 0,
                        AppNotificationAudioLooping_Loop = 1,
                    };
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationButtonStyle
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    enum AppNotificationButtonStyle : int
                    {
                        AppNotificationButtonStyle_Default = 0,
                        AppNotificationButtonStyle_Success = 1,
                        AppNotificationButtonStyle_Critical = 2,
                    };
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationDuration
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    enum AppNotificationDuration : int
                    {
                        AppNotificationDuration_Default = 0,
                        AppNotificationDuration_Long = 1,
                    };
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationImageCrop
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    enum AppNotificationImageCrop : int
                    {
                        AppNotificationImageCrop_Default = 0,
                        AppNotificationImageCrop_Circle = 1,
                    };
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationScenario
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    enum AppNotificationScenario : int
                    {
                        AppNotificationScenario_Default = 0,
                        AppNotificationScenario_Reminder = 1,
                        AppNotificationScenario_Alarm = 2,
                        AppNotificationScenario_IncomingCall = 3,
                        AppNotificationScenario_Urgent = 4,
                    };
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationSoundEvent
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    enum AppNotificationSoundEvent : int
                    {
                        AppNotificationSoundEvent_Default = 0,
                        AppNotificationSoundEvent_IM = 1,
                        AppNotificationSoundEvent_Mail = 2,
                        AppNotificationSoundEvent_Reminder = 3,
                        AppNotificationSoundEvent_SMS = 4,
                        AppNotificationSoundEvent_Alarm = 5,
                        AppNotificationSoundEvent_Alarm2 = 6,
                        AppNotificationSoundEvent_Alarm3 = 7,
                        AppNotificationSoundEvent_Alarm4 = 8,
                        AppNotificationSoundEvent_Alarm5 = 9,
                        AppNotificationSoundEvent_Alarm6 = 10,
                        AppNotificationSoundEvent_Alarm7 = 11,
                        AppNotificationSoundEvent_Alarm8 = 12,
                        AppNotificationSoundEvent_Alarm9 = 13,
                        AppNotificationSoundEvent_Alarm10 = 14,
                        AppNotificationSoundEvent_Call = 15,
                        AppNotificationSoundEvent_Call2 = 16,
                        AppNotificationSoundEvent_Call3 = 17,
                        AppNotificationSoundEvent_Call4 = 18,
                        AppNotificationSoundEvent_Call5 = 19,
                        AppNotificationSoundEvent_Call6 = 20,
                        AppNotificationSoundEvent_Call7 = 21,
                        AppNotificationSoundEvent_Call8 = 22,
                        AppNotificationSoundEvent_Call9 = 23,
                        AppNotificationSoundEvent_Call10 = 24,
                    };
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilder
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationBuilder[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilder";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("e801d31f-ce03-505c-adec-8a02724ec9de")
                    IAppNotificationBuilder : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE AddArgument(
                            HSTRING key,
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetTimeStamp(
                            ABI::Windows::Foundation::DateTime value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetDuration(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationDuration duration,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetScenario(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationScenario value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddText(
                            HSTRING text,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddText2(
                            HSTRING text,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationTextProperties* properties,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAttributionText(
                            HSTRING text,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAttributionText2(
                            HSTRING text,
                            HSTRING language,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetInlineImage(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetInlineImage2(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageCrop imageCrop,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetInlineImage3(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageCrop imagecrop,
                            HSTRING alternateText,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAppLogoOverride(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAppLogoOverride2(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageCrop imageCrop,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAppLogoOverride3(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageCrop imageCrop,
                            HSTRING alternateText,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetHeroImage(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetHeroImage2(
                            ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
                            HSTRING alternateText,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAudioUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* audioUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAudioUri2(
                            ABI::Windows::Foundation::IUriRuntimeClass* audioUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationAudioLooping loop,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAudioEvent(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationSoundEvent appNotificationSoundEvent,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetAudioEvent2(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationSoundEvent appNotificationSoundEvent,
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationAudioLooping loop,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE MuteAudio(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddTextBox(
                            HSTRING id,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddTextBox2(
                            HSTRING id,
                            HSTRING placeHolderText,
                            HSTRING title,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddButton(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton* value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddComboBox(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBox* value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddProgressBar(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar* value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE BuildNotification(
                            ABI::Microsoft::Windows::AppNotifications::IAppNotification** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetTag(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetGroup(
                            HSTRING group,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationBuilder** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationBuilder = _uuidof(IAppNotificationBuilder);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilderStatics
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationBuilderStatics[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilderStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("c7042d2a-d319-520e-a314-50081c8888cc")
                    IAppNotificationBuilderStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsUrgentScenarioSupported(
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationBuilderStatics = _uuidof(IAppNotificationBuilderStatics);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationButton
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationButton[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationButton";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("a7c03031-5634-5098-aec9-47ecb60c3499")
                    IAppNotificationButton : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Content(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Content(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Arguments(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Arguments(
                            __FIMap_2_HSTRING_HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Icon(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Icon(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ToolTip(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ToolTip(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContextMenuPlacement(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ContextMenuPlacement(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ButtonStyle(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationButtonStyle* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ButtonStyle(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationButtonStyle value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InputId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_InputId(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InvokeUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_InvokeUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TargetAppId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TargetAppId(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddArgument(
                            HSTRING key,
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetIcon(
                            ABI::Windows::Foundation::IUriRuntimeClass* value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetToolTip(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetContextMenuPlacement(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetButtonStyle(
                            ABI::Microsoft::Windows::AppNotifications::Builder::AppNotificationButtonStyle value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetInputId(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetInvokeUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* protocolUri,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetInvokeUri2(
                            ABI::Windows::Foundation::IUriRuntimeClass* protocolUri,
                            HSTRING targetAppId,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationButton = _uuidof(IAppNotificationButton);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationButtonFactory[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("4f109286-0a6d-5a5e-9e8f-9fe31669fbb8")
                    IAppNotificationButtonFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING content,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationButton** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationButtonFactory = _uuidof(IAppNotificationButtonFactory);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonStatics
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationButtonStatics[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("fead7c18-4144-59a4-9611-86b7e8191853")
                    IAppNotificationButtonStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsToolTipSupported(
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsButtonStyleSupported(
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationButtonStatics = _uuidof(IAppNotificationButtonStatics);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBox
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationComboBox[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBox";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("4547c9e2-4815-538c-be26-040ce17f8b62")
                    IAppNotificationComboBox : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Items(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Items(
                            __FIMap_2_HSTRING_HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Title(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Title(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SelectedItem(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SelectedItem(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddItem(
                            HSTRING id,
                            HSTRING content,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBox** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetTitle(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBox** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetSelectedItem(
                            HSTRING id,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBox** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationComboBox = _uuidof(IAppNotificationComboBox);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBoxFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationComboBoxFactory[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBoxFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("1b31b5b0-9d86-59ed-8629-a79498ab5d4b")
                    IAppNotificationComboBoxFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING id,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationComboBox** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationComboBoxFactory = _uuidof(IAppNotificationComboBoxFactory);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationProgressBar
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationProgressBar[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationProgressBar";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("fced62f2-2074-5641-8630-87a14315ac86")
                    IAppNotificationProgressBar : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Title(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Title(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Status(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Value(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Value(
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ValueStringOverride(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ValueStringOverride(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetTitle(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE BindTitle(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetStatus(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE BindStatus(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetValue(
                            DOUBLE value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE BindValue(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetValueStringOverride(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE BindValueStringOverride(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationProgressBar** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationProgressBar = _uuidof(IAppNotificationProgressBar);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationTextProperties
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationTextProperties[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationTextProperties";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                namespace Builder {
                    MIDL_INTERFACE("23a30d0b-5258-5853-932e-9521a3642afb")
                    IAppNotificationTextProperties : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Language(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IncomingCallAlignment(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IncomingCallAlignment(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MaxLines(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MaxLines(
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetLanguage(
                            HSTRING value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationTextProperties** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetIncomingCallAlignment(
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationTextProperties** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetMaxLines(
                            INT32 value,
                            ABI::Microsoft::Windows::AppNotifications::Builder::IAppNotificationTextProperties** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppNotificationTextProperties = _uuidof(IAppNotificationTextProperties);
                } /* Builder */
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilderStatics interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilder ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationBuilder_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationBuilder_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationBuilder[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *   Type can be activated via the Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonStatics interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationButton ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationButton_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationButton_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationButton[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationButton";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBoxFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBox ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationComboBox_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationComboBox_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationComboBox[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationProgressBar ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationProgressBar_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationProgressBar_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationProgressBar[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationTextProperties ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationTextProperties_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationTextProperties_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationTextProperties[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if !defined(____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_HSTRING __FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_HSTRING_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_HSTRING_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        __FIKeyValuePair_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING_HSTRING** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_HSTRING __FIMapView_2_HSTRING_HSTRING;

#if !defined(____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_HSTRING __FIMapView_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING_HSTRING;

typedef struct __FIMapView_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING_HSTRING* This,
        __FIMapView_2_HSTRING_HSTRING** first,
        __FIMapView_2_HSTRING_HSTRING** second);

    END_INTERFACE
} __FIMapView_2_HSTRING_HSTRINGVtbl;

interface __FIMapView_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIMapView_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING_HSTRING_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMap_2_HSTRING_HSTRING __FIMap_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMap_2_HSTRING_HSTRING;

typedef struct __FIMap_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMap_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMap_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMap_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMap_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMap_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMap_2_HSTRING_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIMap_2_HSTRING_HSTRING* This,
        __FIMapView_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* Insert)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Remove)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIMap_2_HSTRING_HSTRING* This);

    END_INTERFACE
} __FIMap_2_HSTRING_HSTRINGVtbl;

interface __FIMap_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIMap_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMap_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMap_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMap_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMap_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMap_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMap_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMap_2_HSTRING_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMap_2_HSTRING_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMap_2_HSTRING_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMap_2_HSTRING_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIMap_2_HSTRING_HSTRING_Insert(This, key, value, result) \
    ((This)->lpVtbl->Insert(This, key, value, result))

#define __FIMap_2_HSTRING_HSTRING_Remove(This, key) \
    ((This)->lpVtbl->Remove(This, key))

#define __FIMap_2_HSTRING_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#endif /* COBJMACROS */

#endif // ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CDateTime __x_ABI_CWindows_CFoundation_CDateTime;

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationAudioLooping __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationAudioLooping;

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationButtonStyle __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationButtonStyle;

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationDuration __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationDuration;

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop;

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationScenario __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationScenario;

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationSoundEvent __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationSoundEvent;

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationAudioLooping
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationAudioLooping
{
    AppNotificationAudioLooping_None = 0,
    AppNotificationAudioLooping_Loop = 1,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationButtonStyle
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationButtonStyle
{
    AppNotificationButtonStyle_Default = 0,
    AppNotificationButtonStyle_Success = 1,
    AppNotificationButtonStyle_Critical = 2,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationDuration
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationDuration
{
    AppNotificationDuration_Default = 0,
    AppNotificationDuration_Long = 1,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationImageCrop
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop
{
    AppNotificationImageCrop_Default = 0,
    AppNotificationImageCrop_Circle = 1,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationScenario
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationScenario
{
    AppNotificationScenario_Default = 0,
    AppNotificationScenario_Reminder = 1,
    AppNotificationScenario_Alarm = 2,
    AppNotificationScenario_IncomingCall = 3,
    AppNotificationScenario_Urgent = 4,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.Builder.AppNotificationSoundEvent
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationSoundEvent
{
    AppNotificationSoundEvent_Default = 0,
    AppNotificationSoundEvent_IM = 1,
    AppNotificationSoundEvent_Mail = 2,
    AppNotificationSoundEvent_Reminder = 3,
    AppNotificationSoundEvent_SMS = 4,
    AppNotificationSoundEvent_Alarm = 5,
    AppNotificationSoundEvent_Alarm2 = 6,
    AppNotificationSoundEvent_Alarm3 = 7,
    AppNotificationSoundEvent_Alarm4 = 8,
    AppNotificationSoundEvent_Alarm5 = 9,
    AppNotificationSoundEvent_Alarm6 = 10,
    AppNotificationSoundEvent_Alarm7 = 11,
    AppNotificationSoundEvent_Alarm8 = 12,
    AppNotificationSoundEvent_Alarm9 = 13,
    AppNotificationSoundEvent_Alarm10 = 14,
    AppNotificationSoundEvent_Call = 15,
    AppNotificationSoundEvent_Call2 = 16,
    AppNotificationSoundEvent_Call3 = 17,
    AppNotificationSoundEvent_Call4 = 18,
    AppNotificationSoundEvent_Call5 = 19,
    AppNotificationSoundEvent_Call6 = 20,
    AppNotificationSoundEvent_Call7 = 21,
    AppNotificationSoundEvent_Call8 = 22,
    AppNotificationSoundEvent_Call9 = 23,
    AppNotificationSoundEvent_Call10 = 24,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilder
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationBuilder[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilder";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* AddArgument)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING key,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetTimeStamp)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetDuration)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationDuration duration,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetScenario)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationScenario value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddText)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddText2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* properties,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAttributionText)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAttributionText2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING text,
        HSTRING language,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetInlineImage)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetInlineImage2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop imageCrop,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetInlineImage3)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop imagecrop,
        HSTRING alternateText,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAppLogoOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAppLogoOverride2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop imageCrop,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAppLogoOverride3)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationImageCrop imageCrop,
        HSTRING alternateText,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetHeroImage)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetHeroImage2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* imageUri,
        HSTRING alternateText,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAudioUri)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* audioUri,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAudioUri2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* audioUri,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationAudioLooping loop,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAudioEvent)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationSoundEvent appNotificationSoundEvent,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetAudioEvent2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationSoundEvent appNotificationSoundEvent,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationAudioLooping loop,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* MuteAudio)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddTextBox)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING id,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddTextBox2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING id,
        HSTRING placeHolderText,
        HSTRING title,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddButton)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddComboBox)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* AddProgressBar)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* BuildNotification)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** result);
    HRESULT (STDMETHODCALLTYPE* SetTag)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);
    HRESULT (STDMETHODCALLTYPE* SetGroup)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder* This,
        HSTRING group,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddArgument(This, key, value, result) \
    ((This)->lpVtbl->AddArgument(This, key, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetTimeStamp(This, value, result) \
    ((This)->lpVtbl->SetTimeStamp(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetDuration(This, duration, result) \
    ((This)->lpVtbl->SetDuration(This, duration, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetScenario(This, value, result) \
    ((This)->lpVtbl->SetScenario(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddText(This, text, result) \
    ((This)->lpVtbl->AddText(This, text, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddText2(This, text, properties, result) \
    ((This)->lpVtbl->AddText2(This, text, properties, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAttributionText(This, text, result) \
    ((This)->lpVtbl->SetAttributionText(This, text, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAttributionText2(This, text, language, result) \
    ((This)->lpVtbl->SetAttributionText2(This, text, language, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetInlineImage(This, imageUri, result) \
    ((This)->lpVtbl->SetInlineImage(This, imageUri, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetInlineImage2(This, imageUri, imageCrop, result) \
    ((This)->lpVtbl->SetInlineImage2(This, imageUri, imageCrop, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetInlineImage3(This, imageUri, imagecrop, alternateText, result) \
    ((This)->lpVtbl->SetInlineImage3(This, imageUri, imagecrop, alternateText, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAppLogoOverride(This, imageUri, result) \
    ((This)->lpVtbl->SetAppLogoOverride(This, imageUri, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAppLogoOverride2(This, imageUri, imageCrop, result) \
    ((This)->lpVtbl->SetAppLogoOverride2(This, imageUri, imageCrop, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAppLogoOverride3(This, imageUri, imageCrop, alternateText, result) \
    ((This)->lpVtbl->SetAppLogoOverride3(This, imageUri, imageCrop, alternateText, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetHeroImage(This, imageUri, result) \
    ((This)->lpVtbl->SetHeroImage(This, imageUri, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetHeroImage2(This, imageUri, alternateText, result) \
    ((This)->lpVtbl->SetHeroImage2(This, imageUri, alternateText, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAudioUri(This, audioUri, result) \
    ((This)->lpVtbl->SetAudioUri(This, audioUri, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAudioUri2(This, audioUri, loop, result) \
    ((This)->lpVtbl->SetAudioUri2(This, audioUri, loop, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAudioEvent(This, appNotificationSoundEvent, result) \
    ((This)->lpVtbl->SetAudioEvent(This, appNotificationSoundEvent, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetAudioEvent2(This, appNotificationSoundEvent, loop, result) \
    ((This)->lpVtbl->SetAudioEvent2(This, appNotificationSoundEvent, loop, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_MuteAudio(This, result) \
    ((This)->lpVtbl->MuteAudio(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddTextBox(This, id, result) \
    ((This)->lpVtbl->AddTextBox(This, id, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddTextBox2(This, id, placeHolderText, title, result) \
    ((This)->lpVtbl->AddTextBox2(This, id, placeHolderText, title, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddButton(This, value, result) \
    ((This)->lpVtbl->AddButton(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddComboBox(This, value, result) \
    ((This)->lpVtbl->AddComboBox(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_AddProgressBar(This, value, result) \
    ((This)->lpVtbl->AddProgressBar(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_BuildNotification(This, result) \
    ((This)->lpVtbl->BuildNotification(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetTag(This, value, result) \
    ((This)->lpVtbl->SetTag(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_SetGroup(This, group, result) \
    ((This)->lpVtbl->SetGroup(This, group, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilder_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilderStatics
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationBuilderStatics[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilderStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsUrgentScenarioSupported)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_IsUrgentScenarioSupported(This, result) \
    ((This)->lpVtbl->IsUrgentScenarioSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationBuilderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationButton
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationButton[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationButton";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Content)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Arguments)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __FIMap_2_HSTRING_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* put_Arguments)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __FIMap_2_HSTRING_HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Icon)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_Icon)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_ToolTip)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_ToolTip)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_ContextMenuPlacement)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ContextMenuPlacement)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonStyle)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationButtonStyle* value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonStyle)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationButtonStyle value);
    HRESULT (STDMETHODCALLTYPE* get_InputId)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_InputId)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_InvokeUri)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_InvokeUri)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_TargetAppId)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_TargetAppId)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* AddArgument)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING key,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetIcon)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetToolTip)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetContextMenuPlacement)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetButtonStyle)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CAppNotificationButtonStyle value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetInputId)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetInvokeUri)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* protocolUri,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);
    HRESULT (STDMETHODCALLTYPE* SetInvokeUri2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* protocolUri,
        HSTRING targetAppId,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_Content(This, value) \
    ((This)->lpVtbl->put_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_Arguments(This, value) \
    ((This)->lpVtbl->get_Arguments(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_Arguments(This, value) \
    ((This)->lpVtbl->put_Arguments(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_Icon(This, value) \
    ((This)->lpVtbl->get_Icon(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_Icon(This, value) \
    ((This)->lpVtbl->put_Icon(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_ToolTip(This, value) \
    ((This)->lpVtbl->get_ToolTip(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_ToolTip(This, value) \
    ((This)->lpVtbl->put_ToolTip(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_ContextMenuPlacement(This, value) \
    ((This)->lpVtbl->get_ContextMenuPlacement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_ContextMenuPlacement(This, value) \
    ((This)->lpVtbl->put_ContextMenuPlacement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_ButtonStyle(This, value) \
    ((This)->lpVtbl->get_ButtonStyle(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_ButtonStyle(This, value) \
    ((This)->lpVtbl->put_ButtonStyle(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_InputId(This, value) \
    ((This)->lpVtbl->get_InputId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_InputId(This, value) \
    ((This)->lpVtbl->put_InputId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_InvokeUri(This, value) \
    ((This)->lpVtbl->get_InvokeUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_InvokeUri(This, value) \
    ((This)->lpVtbl->put_InvokeUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_get_TargetAppId(This, value) \
    ((This)->lpVtbl->get_TargetAppId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_put_TargetAppId(This, value) \
    ((This)->lpVtbl->put_TargetAppId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_AddArgument(This, key, value, result) \
    ((This)->lpVtbl->AddArgument(This, key, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetIcon(This, value, result) \
    ((This)->lpVtbl->SetIcon(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetToolTip(This, value, result) \
    ((This)->lpVtbl->SetToolTip(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetContextMenuPlacement(This, result) \
    ((This)->lpVtbl->SetContextMenuPlacement(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetButtonStyle(This, value, result) \
    ((This)->lpVtbl->SetButtonStyle(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetInputId(This, value, result) \
    ((This)->lpVtbl->SetInputId(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetInvokeUri(This, protocolUri, result) \
    ((This)->lpVtbl->SetInvokeUri(This, protocolUri, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_SetInvokeUri2(This, protocolUri, targetAppId, result) \
    ((This)->lpVtbl->SetInvokeUri2(This, protocolUri, targetAppId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationButtonFactory[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory* This,
        HSTRING content,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButton** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_CreateInstance(This, content, value) \
    ((This)->lpVtbl->CreateInstance(This, content, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonStatics
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationButtonStatics[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsToolTipSupported)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsButtonStyleSupported)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_IsToolTipSupported(This, result) \
    ((This)->lpVtbl->IsToolTipSupported(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_IsButtonStyleSupported(This, result) \
    ((This)->lpVtbl->IsButtonStyleSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationButtonStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBox
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationComboBox[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBox";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Items)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        __FIMap_2_HSTRING_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* put_Items)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        __FIMap_2_HSTRING_HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Title)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Title)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_SelectedItem)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_SelectedItem)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* AddItem)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING id,
        HSTRING content,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox** result);
    HRESULT (STDMETHODCALLTYPE* SetTitle)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox** result);
    HRESULT (STDMETHODCALLTYPE* SetSelectedItem)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox* This,
        HSTRING id,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_get_Items(This, value) \
    ((This)->lpVtbl->get_Items(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_put_Items(This, value) \
    ((This)->lpVtbl->put_Items(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_get_Title(This, value) \
    ((This)->lpVtbl->get_Title(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_put_Title(This, value) \
    ((This)->lpVtbl->put_Title(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_get_SelectedItem(This, value) \
    ((This)->lpVtbl->get_SelectedItem(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_put_SelectedItem(This, value) \
    ((This)->lpVtbl->put_SelectedItem(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_AddItem(This, id, content, result) \
    ((This)->lpVtbl->AddItem(This, id, content, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_SetTitle(This, value, result) \
    ((This)->lpVtbl->SetTitle(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_SetSelectedItem(This, id, result) \
    ((This)->lpVtbl->SetSelectedItem(This, id, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBoxFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationComboBoxFactory[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBoxFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory* This,
        HSTRING id,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBox** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_CreateInstance(This, id, value) \
    ((This)->lpVtbl->CreateInstance(This, id, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationComboBoxFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationProgressBar
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationProgressBar[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationProgressBar";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBarVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Title)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Title)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Status)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_Value)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_ValueStringOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_ValueStringOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* SetTitle)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* BindTitle)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* SetStatus)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* BindStatus)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* SetValue)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        DOUBLE value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* BindValue)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* SetValueStringOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);
    HRESULT (STDMETHODCALLTYPE* BindValueStringOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBarVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBarVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_get_Title(This, value) \
    ((This)->lpVtbl->get_Title(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_put_Title(This, value) \
    ((This)->lpVtbl->put_Title(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_put_Status(This, value) \
    ((This)->lpVtbl->put_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_get_Value(This, value) \
    ((This)->lpVtbl->get_Value(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_put_Value(This, value) \
    ((This)->lpVtbl->put_Value(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_get_ValueStringOverride(This, value) \
    ((This)->lpVtbl->get_ValueStringOverride(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_put_ValueStringOverride(This, value) \
    ((This)->lpVtbl->put_ValueStringOverride(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_SetTitle(This, value, result) \
    ((This)->lpVtbl->SetTitle(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_BindTitle(This, result) \
    ((This)->lpVtbl->BindTitle(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_SetStatus(This, value, result) \
    ((This)->lpVtbl->SetStatus(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_BindStatus(This, result) \
    ((This)->lpVtbl->BindStatus(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_SetValue(This, value, result) \
    ((This)->lpVtbl->SetValue(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_BindValue(This, result) \
    ((This)->lpVtbl->BindValue(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_SetValueStringOverride(This, value, result) \
    ((This)->lpVtbl->SetValueStringOverride(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_BindValueStringOverride(This, result) \
    ((This)->lpVtbl->BindValueStringOverride(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationProgressBar_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.Builder.IAppNotificationTextProperties
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_Builder_IAppNotificationTextProperties[] = L"Microsoft.Windows.AppNotifications.Builder.IAppNotificationTextProperties";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextPropertiesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Language)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_IncomingCallAlignment)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IncomingCallAlignment)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_MaxLines)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_MaxLines)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* SetLanguage)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        HSTRING value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties** result);
    HRESULT (STDMETHODCALLTYPE* SetIncomingCallAlignment)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties** result);
    HRESULT (STDMETHODCALLTYPE* SetMaxLines)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties* This,
        INT32 value,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextPropertiesVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextPropertiesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_put_Language(This, value) \
    ((This)->lpVtbl->put_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_get_IncomingCallAlignment(This, value) \
    ((This)->lpVtbl->get_IncomingCallAlignment(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_put_IncomingCallAlignment(This, value) \
    ((This)->lpVtbl->put_IncomingCallAlignment(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_get_MaxLines(This, value) \
    ((This)->lpVtbl->get_MaxLines(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_put_MaxLines(This, value) \
    ((This)->lpVtbl->put_MaxLines(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_SetLanguage(This, value, result) \
    ((This)->lpVtbl->SetLanguage(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_SetIncomingCallAlignment(This, result) \
    ((This)->lpVtbl->SetIncomingCallAlignment(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_SetMaxLines(This, value, result) \
    ((This)->lpVtbl->SetMaxLines(This, value, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CBuilder_CIAppNotificationTextProperties_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilderStatics interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationBuilder ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationBuilder_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationBuilder_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationBuilder[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationButton
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *   Type can be activated via the Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.Builder.IAppNotificationButtonStatics interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationButton ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationButton_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationButton_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationButton[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationButton";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBoxFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationComboBox ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationComboBox_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationComboBox_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationComboBox[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationProgressBar ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationProgressBar_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationProgressBar_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationProgressBar[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties
 *
 * Introduced to Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilderContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.Builder.IAppNotificationTextProperties ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationTextProperties_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_Builder_AppNotificationTextProperties_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_Builder_AppNotificationTextProperties[] = L"Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_BUILDER_APPNOTIFICATIONBUILDERCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eappnotifications2Ebuilder_p_h__

#endif // __microsoft2Ewindows2Eappnotifications2Ebuilder_h__
