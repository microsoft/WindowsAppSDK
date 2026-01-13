
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
#ifndef __microsoft2Ewindows2Eai2Econtentsafety_h__
#define __microsoft2Ewindows2Eai2Econtentsafety_h__
#ifndef __microsoft2Ewindows2Eai2Econtentsafety_p_h__
#define __microsoft2Ewindows2Eai2Econtentsafety_p_h__


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
#if !defined(MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    interface IContentFilterOptions;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions ABI::Microsoft::Windows::AI::ContentSafety::IContentFilterOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    interface IImageContentFilterSeverity;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity ABI::Microsoft::Windows::AI::ContentSafety::IImageContentFilterSeverity

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    interface IImageContentFilterSeverityFactory;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory ABI::Microsoft::Windows::AI::ContentSafety::IImageContentFilterSeverityFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    interface ITextContentFilterSeverity;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverity

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    interface ITextContentFilterSeverityFactory;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverityFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    typedef enum SeverityLevel : int SeverityLevel;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    class ImageContentFilterSeverity;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    class TextContentFilterSeverity;
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AI.ContentSafety.SeverityLevel
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    enum SeverityLevel : int
                    {
                        SeverityLevel_Minimum = 10,
                        SeverityLevel_Low = 11,
                        SeverityLevel_Medium = 12,
                        SeverityLevel_High = 13,
                    };
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.IContentFilterOptions
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.ContentFilterOptions
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_IContentFilterOptions[] = L"Microsoft.Windows.AI.ContentSafety.IContentFilterOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    MIDL_INTERFACE("6808be9f-80d2-5136-8a8a-1f5c52c824ad")
                    IContentFilterOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PromptMaxAllowedSeverityLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverity** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PromptMaxAllowedSeverityLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverity* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ResponseMaxAllowedSeverityLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverity** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ResponseMaxAllowedSeverityLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverity* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ImageMaxAllowedSeverityLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::IImageContentFilterSeverity** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ImageMaxAllowedSeverityLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::IImageContentFilterSeverity* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IContentFilterOptions = _uuidof(IContentFilterOptions);
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_IImageContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverity";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    MIDL_INTERFACE("f1563582-c66a-5861-9995-1440b05191ac")
                    IImageContentFilterSeverity : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AdultContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AdultContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RacyContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RacyContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_GoryContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_GoryContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ViolentContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ViolentContentLevel(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageContentFilterSeverity = _uuidof(IImageContentFilterSeverity);
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverityFactory
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_IImageContentFilterSeverityFactory[] = L"Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverityFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    MIDL_INTERFACE("ead11457-81b1-5b81-9ca3-c5b04b4df043")
                    IImageContentFilterSeverityFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel severityForALlCategories,
                            ABI::Microsoft::Windows::AI::ContentSafety::IImageContentFilterSeverity** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageContentFilterSeverityFactory = _uuidof(IImageContentFilterSeverityFactory);
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_ITextContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverity";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    MIDL_INTERFACE("68c1ee47-c35c-5f4c-a647-b0c0f64aa0d5")
                    ITextContentFilterSeverity : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Hate(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Hate(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Sexual(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Sexual(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Violent(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Violent(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SelfHarm(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SelfHarm(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextContentFilterSeverity = _uuidof(ITextContentFilterSeverity);
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverityFactory
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_ITextContentFilterSeverityFactory[] = L"Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverityFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace ContentSafety {
                    MIDL_INTERFACE("e0ca501e-4004-501e-8984-442d091607d4")
                    ITextContentFilterSeverityFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::AI::ContentSafety::SeverityLevel severityForAllCategories,
                            ABI::Microsoft::Windows::AI::ContentSafety::ITextContentFilterSeverity** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextContentFilterSeverityFactory = _uuidof(ITextContentFilterSeverityFactory);
                } /* ContentSafety */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.ContentSafety.ContentFilterOptions
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.ContentSafety.IContentFilterOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ContentFilterOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ContentFilterOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_ContentSafety_ContentFilterOptions[] = L"Microsoft.Windows.AI.ContentSafety.ContentFilterOptions";
#endif
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverityFactory interface starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverity ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ImageContentFilterSeverity_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ImageContentFilterSeverity_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_ContentSafety_ImageContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity";
#endif
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverityFactory interface starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverity ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_TextContentFilterSeverity_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_TextContentFilterSeverity_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_ContentSafety_TextContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity";
#endif
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel;

/*
 *
 * Struct Microsoft.Windows.AI.ContentSafety.SeverityLevel
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel
{
    SeverityLevel_Minimum = 10,
    SeverityLevel_Low = 11,
    SeverityLevel_Medium = 12,
    SeverityLevel_High = 13,
};
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.IContentFilterOptions
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.ContentFilterOptions
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_IContentFilterOptions[] = L"Microsoft.Windows.AI.ContentSafety.IContentFilterOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PromptMaxAllowedSeverityLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity** value);
    HRESULT (STDMETHODCALLTYPE* put_PromptMaxAllowedSeverityLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* value);
    HRESULT (STDMETHODCALLTYPE* get_ResponseMaxAllowedSeverityLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity** value);
    HRESULT (STDMETHODCALLTYPE* put_ResponseMaxAllowedSeverityLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* value);
    HRESULT (STDMETHODCALLTYPE* get_ImageMaxAllowedSeverityLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity** value);
    HRESULT (STDMETHODCALLTYPE* put_ImageMaxAllowedSeverityLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions* This,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_get_PromptMaxAllowedSeverityLevel(This, value) \
    ((This)->lpVtbl->get_PromptMaxAllowedSeverityLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_put_PromptMaxAllowedSeverityLevel(This, value) \
    ((This)->lpVtbl->put_PromptMaxAllowedSeverityLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_get_ResponseMaxAllowedSeverityLevel(This, value) \
    ((This)->lpVtbl->get_ResponseMaxAllowedSeverityLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_put_ResponseMaxAllowedSeverityLevel(This, value) \
    ((This)->lpVtbl->put_ResponseMaxAllowedSeverityLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_get_ImageMaxAllowedSeverityLevel(This, value) \
    ((This)->lpVtbl->get_ImageMaxAllowedSeverityLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_put_ImageMaxAllowedSeverityLevel(This, value) \
    ((This)->lpVtbl->put_ImageMaxAllowedSeverityLevel(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIContentFilterOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_IImageContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverity";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AdultContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_AdultContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);
    HRESULT (STDMETHODCALLTYPE* get_RacyContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_RacyContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);
    HRESULT (STDMETHODCALLTYPE* get_GoryContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_GoryContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);
    HRESULT (STDMETHODCALLTYPE* get_ViolentContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_ViolentContentLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_get_AdultContentLevel(This, value) \
    ((This)->lpVtbl->get_AdultContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_put_AdultContentLevel(This, value) \
    ((This)->lpVtbl->put_AdultContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_get_RacyContentLevel(This, value) \
    ((This)->lpVtbl->get_RacyContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_put_RacyContentLevel(This, value) \
    ((This)->lpVtbl->put_RacyContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_get_GoryContentLevel(This, value) \
    ((This)->lpVtbl->get_GoryContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_put_GoryContentLevel(This, value) \
    ((This)->lpVtbl->put_GoryContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_get_ViolentContentLevel(This, value) \
    ((This)->lpVtbl->get_ViolentContentLevel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_put_ViolentContentLevel(This, value) \
    ((This)->lpVtbl->put_ViolentContentLevel(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverityFactory
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_IImageContentFilterSeverityFactory[] = L"Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverityFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel severityForALlCategories,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverity** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_CreateInstance(This, severityForALlCategories, value) \
    ((This)->lpVtbl->CreateInstance(This, severityForALlCategories, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CIImageContentFilterSeverityFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_ITextContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverity";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Hate)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_Hate)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);
    HRESULT (STDMETHODCALLTYPE* get_Sexual)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_Sexual)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);
    HRESULT (STDMETHODCALLTYPE* get_Violent)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_Violent)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);
    HRESULT (STDMETHODCALLTYPE* get_SelfHarm)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel* value);
    HRESULT (STDMETHODCALLTYPE* put_SelfHarm)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_get_Hate(This, value) \
    ((This)->lpVtbl->get_Hate(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_put_Hate(This, value) \
    ((This)->lpVtbl->put_Hate(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_get_Sexual(This, value) \
    ((This)->lpVtbl->get_Sexual(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_put_Sexual(This, value) \
    ((This)->lpVtbl->put_Sexual(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_get_Violent(This, value) \
    ((This)->lpVtbl->get_Violent(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_put_Violent(This, value) \
    ((This)->lpVtbl->put_Violent(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_get_SelfHarm(This, value) \
    ((This)->lpVtbl->get_SelfHarm(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_put_SelfHarm(This, value) \
    ((This)->lpVtbl->put_SelfHarm(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverityFactory
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_ContentSafety_ITextContentFilterSeverityFactory[] = L"Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverityFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CSeverityLevel severityForAllCategories,
        __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverity** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_CreateInstance(This, severityForAllCategories, value) \
    ((This)->lpVtbl->CreateInstance(This, severityForAllCategories, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CContentSafety_CITextContentFilterSeverityFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.ContentSafety.ContentFilterOptions
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.ContentSafety.IContentFilterOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ContentFilterOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ContentFilterOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_ContentSafety_ContentFilterOptions[] = L"Microsoft.Windows.AI.ContentSafety.ContentFilterOptions";
#endif
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverityFactory interface starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.ContentSafety.IImageContentFilterSeverity ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ImageContentFilterSeverity_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_ImageContentFilterSeverity_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_ContentSafety_ImageContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.ImageContentFilterSeverity";
#endif
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity
 *
 * Introduced to Microsoft.Windows.AI.ContentSafety.ContentSafetyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverityFactory interface starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.AI.ContentSafety.ContentSafetyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.ContentSafety.ITextContentFilterSeverity ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_TextContentFilterSeverity_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_ContentSafety_TextContentFilterSeverity_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_ContentSafety_TextContentFilterSeverity[] = L"Microsoft.Windows.AI.ContentSafety.TextContentFilterSeverity";
#endif
#endif // MICROSOFT_WINDOWS_AI_CONTENTSAFETY_CONTENTSAFETYCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eai2Econtentsafety_p_h__

#endif // __microsoft2Ewindows2Eai2Econtentsafety_h__
