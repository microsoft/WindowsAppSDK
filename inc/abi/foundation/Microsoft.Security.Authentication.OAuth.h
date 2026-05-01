
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
#ifndef __microsoft2Esecurity2Eauthentication2Eoauth_h__
#define __microsoft2Esecurity2Eauthentication2Eoauth_h__
#ifndef __microsoft2Esecurity2Eauthentication2Eoauth_p_h__
#define __microsoft2Esecurity2Eauthentication2Eoauth_p_h__


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
#if !defined(MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION)
#define MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION)

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
#include "Windows.Data.Json.h"
#include "Windows.Web.Http.h"
#include "Windows.Web.Http.Headers.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IAuthFailure;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure ABI::Microsoft::Security::Authentication::OAuth::IAuthFailure

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IAuthRequestParams;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParams

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IAuthRequestParamsFactory;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParamsFactory

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IAuthRequestParamsStatics;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParamsStatics

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IAuthRequestResult;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestResult

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IAuthResponse;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse ABI::Microsoft::Security::Authentication::OAuth::IAuthResponse

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IClientAuthentication;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication ABI::Microsoft::Security::Authentication::OAuth::IClientAuthentication

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IClientAuthenticationFactory;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory ABI::Microsoft::Security::Authentication::OAuth::IClientAuthenticationFactory

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IClientAuthenticationStatics;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics ABI::Microsoft::Security::Authentication::OAuth::IClientAuthenticationStatics

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface IOAuth2ManagerStatics;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics ABI::Microsoft::Security::Authentication::OAuth::IOAuth2ManagerStatics

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface ITokenFailure;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure ABI::Microsoft::Security::Authentication::OAuth::ITokenFailure

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface ITokenRequestParams;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface ITokenRequestParamsFactory;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParamsFactory

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface ITokenRequestParamsStatics;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParamsStatics

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface ITokenRequestResult;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestResult

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    interface ITokenResponse;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse ABI::Microsoft::Security::Authentication::OAuth::ITokenResponse

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class AuthRequestResult;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_USE
#define DEF___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("90c43237-b071-547a-b4e1-b786e230e9de"))
IAsyncOperation<ABI::Microsoft::Security::Authentication::OAuth::AuthRequestResult*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Security::Authentication::OAuth::AuthRequestResult*, ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Security.Authentication.OAuth.AuthRequestResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Security::Authentication::OAuth::AuthRequestResult*> __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_t;
#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_USE */

#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("96903c4b-0624-56df-932e-bfd561d87f02"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Security::Authentication::OAuth::AuthRequestResult*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Security::Authentication::OAuth::AuthRequestResult*, ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Security.Authentication.OAuth.AuthRequestResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Security::Authentication::OAuth::AuthRequestResult*> __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_USE */

#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class TokenRequestResult;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_USE
#define DEF___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("001a3d77-0c75-5e5c-910b-d143e639a03f"))
IAsyncOperation<ABI::Microsoft::Security::Authentication::OAuth::TokenRequestResult*> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Security::Authentication::OAuth::TokenRequestResult*, ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Security.Authentication.OAuth.TokenRequestResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Microsoft::Security::Authentication::OAuth::TokenRequestResult*> __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_t;
#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_USE */

#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("4d1279f5-8a74-5874-a820-fec85ac06a2d"))
IAsyncOperationCompletedHandler<ABI::Microsoft::Security::Authentication::OAuth::TokenRequestResult*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Security::Authentication::OAuth::TokenRequestResult*, ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Security.Authentication.OAuth.TokenRequestResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Microsoft::Security::Authentication::OAuth::TokenRequestResult*> __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_USE */

#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000


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


#ifndef ____x_ABI_CWindows_CData_CJson_CIJsonValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CData_CJson_CIJsonValue_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Data {
            namespace Json {
                interface IJsonValue;
            } /* Json */
        } /* Data */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CData_CJson_CIJsonValue ABI::Windows::Data::Json::IJsonValue

#endif // ____x_ABI_CWindows_CData_CJson_CIJsonValue_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4deecc89-b0b8-5ee8-a51d-1c25ad9a5b01"))
IKeyValuePair<HSTRING, ABI::Windows::Data::Json::IJsonValue*> : IKeyValuePair_impl<HSTRING, ABI::Windows::Data::Json::IJsonValue*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Data.Json.IJsonValue>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, ABI::Windows::Data::Json::IJsonValue*> __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f948eac5-33eb-50f5-b5af-e7cecf0e4501"))
IIterator<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Data.Json.IJsonValue>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("dfabb6e1-0411-5a8f-aa87-354e7110f099"))
IIterable<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Windows.Data.Json.IJsonValue>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue*> __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000


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


#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#define DEF___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("eecd690c-1ff3-529f-923f-9b1c31fd3d0f"))
IMapView<HSTRING, ABI::Windows::Data::Json::IJsonValue*> : IMapView_impl<HSTRING, ABI::Windows::Data::Json::IJsonValue*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, Windows.Data.Json.IJsonValue>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, ABI::Windows::Data::Json::IJsonValue*> __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_t;
#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000


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
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
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
    namespace Windows {
        namespace Web {
            namespace Http {
                namespace Headers {
                    class HttpCredentialsHeaderValue;
                } /* Headers */
            } /* Http */
        } /* Web */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Web {
            namespace Http {
                namespace Headers {
                    interface IHttpCredentialsHeaderValue;
                } /* Headers */
            } /* Http */
        } /* Web */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue ABI::Windows::Web::Http::Headers::IHttpCredentialsHeaderValue

#endif // ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Web {
            namespace Http {
                class HttpResponseMessage;
            } /* Http */
        } /* Web */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_FWD_DEFINED__
#define ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Web {
            namespace Http {
                interface IHttpResponseMessage;
            } /* Http */
        } /* Web */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage ABI::Windows::Web::Http::IHttpResponseMessage

#endif // ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    typedef enum CodeChallengeMethodKind : int CodeChallengeMethodKind;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    typedef enum TokenFailureKind : int TokenFailureKind;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class AuthFailure;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class AuthRequestParams;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class AuthResponse;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class ClientAuthentication;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class TokenFailure;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class TokenRequestParams;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    class TokenResponse;
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Security.Authentication.OAuth.CodeChallengeMethodKind
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    enum CodeChallengeMethodKind : int
                    {
                        CodeChallengeMethodKind_None = 0,
                        CodeChallengeMethodKind_S256 = 1,
                        CodeChallengeMethodKind_Plain = 2,
                    };
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Security.Authentication.OAuth.TokenFailureKind
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    enum TokenFailureKind : int
                    {
                        TokenFailureKind_ErrorResponse = 0,
                        TokenFailureKind_HttpFailure = 1,
                        TokenFailureKind_InvalidResponse = 2,
                    };
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthFailure
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthFailure[] = L"Microsoft.Security.Authentication.OAuth.IAuthFailure";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("ec55ed5f-0497-53cb-976b-abd146350175")
                    IAuthFailure : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Error(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorDescription(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_State(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalParams(
                            __FIMapView_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAuthFailure = _uuidof(IAuthFailure);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestParams[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestParams";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("aac61e23-9155-551a-ac37-cdb2995f88d2")
                    IAuthRequestParams : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ResponseType(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ResponseType(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ClientId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ClientId(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RedirectUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RedirectUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_State(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_State(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scope(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Scope(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CodeChallenge(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CodeChallenge(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CodeChallengeMethod(
                            ABI::Microsoft::Security::Authentication::OAuth::CodeChallengeMethodKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CodeChallengeMethod(
                            ABI::Microsoft::Security::Authentication::OAuth::CodeChallengeMethodKind value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalParams(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAuthRequestParams = _uuidof(IAuthRequestParams);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestParamsFactory
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestParamsFactory[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestParamsFactory";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("539bdca7-bde4-5a63-85d1-33403f6e3452")
                    IAuthRequestParamsFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING responseType,
                            HSTRING clientId,
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParams** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance2(
                            HSTRING responseType,
                            HSTRING clientId,
                            ABI::Windows::Foundation::IUriRuntimeClass* redirectUri,
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParams** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAuthRequestParamsFactory = _uuidof(IAuthRequestParamsFactory);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestParamsStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestParamsStatics[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestParamsStatics";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("0befd4f0-6864-5bf4-bd8e-2f3bf98906b5")
                    IAuthRequestParamsStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateForAuthorizationCodeRequest(
                            HSTRING clientId,
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParams** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateForAuthorizationCodeRequest2(
                            HSTRING clientId,
                            ABI::Windows::Foundation::IUriRuntimeClass* redirectUri,
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParams** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAuthRequestParamsStatics = _uuidof(IAuthRequestParamsStatics);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestResult
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestResult[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestResult";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("10f8b804-04cf-5651-bd52-7da9346debc1")
                    IAuthRequestResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ResponseUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Response(
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthResponse** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Failure(
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthFailure** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAuthRequestResult = _uuidof(IAuthRequestResult);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthResponse
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthResponse[] = L"Microsoft.Security.Authentication.OAuth.IAuthResponse";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("5bc1fa62-fded-5769-9d40-ded1eea90d72")
                    IAuthResponse : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_State(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Code(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AccessToken(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TokenType(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpiresIn(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scope(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalParams(
                            __FIMapView_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAuthResponse = _uuidof(IAuthResponse);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IClientAuthentication
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IClientAuthentication[] = L"Microsoft.Security.Authentication.OAuth.IClientAuthentication";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("ef99342d-d597-5eff-878a-8de0cb597172")
                    IClientAuthentication : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Authorization(
                            ABI::Windows::Web::Http::Headers::IHttpCredentialsHeaderValue** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Authorization(
                            ABI::Windows::Web::Http::Headers::IHttpCredentialsHeaderValue* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ProxyAuthorization(
                            ABI::Windows::Web::Http::Headers::IHttpCredentialsHeaderValue** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ProxyAuthorization(
                            ABI::Windows::Web::Http::Headers::IHttpCredentialsHeaderValue* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalHeaders(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IClientAuthentication = _uuidof(IClientAuthentication);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IClientAuthenticationFactory
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IClientAuthenticationFactory[] = L"Microsoft.Security.Authentication.OAuth.IClientAuthenticationFactory";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("0d50e9f5-c37f-57cc-b9ec-2b193b0f9cec")
                    IClientAuthenticationFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Windows::Web::Http::Headers::IHttpCredentialsHeaderValue* authorization,
                            ABI::Microsoft::Security::Authentication::OAuth::IClientAuthentication** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IClientAuthenticationFactory = _uuidof(IClientAuthenticationFactory);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IClientAuthenticationStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IClientAuthenticationStatics[] = L"Microsoft.Security.Authentication.OAuth.IClientAuthenticationStatics";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("65613560-2b6f-52fd-a479-3a96624682ae")
                    IClientAuthenticationStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateForBasicAuthorization(
                            HSTRING clientId,
                            HSTRING clientSecret,
                            ABI::Microsoft::Security::Authentication::OAuth::IClientAuthentication** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IClientAuthenticationStatics = _uuidof(IClientAuthenticationStatics);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IOAuth2ManagerStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.OAuth2Manager
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IOAuth2ManagerStatics[] = L"Microsoft.Security.Authentication.OAuth.IOAuth2ManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("ac9d0dd1-c07e-5302-8150-199c7d343f57")
                    IOAuth2ManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE RequestAuthWithParamsAsync(
                            ABI::Microsoft::UI::WindowId parentWindowId,
                            ABI::Windows::Foundation::IUriRuntimeClass* authEndpoint,
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthRequestParams* params,
                            __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CompleteAuthRequest(
                            ABI::Windows::Foundation::IUriRuntimeClass* responseUri,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RequestTokenAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* tokenEndpoint,
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams* params,
                            __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RequestTokenAsync2(
                            ABI::Windows::Foundation::IUriRuntimeClass* tokenEndpoint,
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams* params,
                            ABI::Microsoft::Security::Authentication::OAuth::IClientAuthentication* clientAuth,
                            __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult** operation
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IOAuth2ManagerStatics = _uuidof(IOAuth2ManagerStatics);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenFailure
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenFailure[] = L"Microsoft.Security.Authentication.OAuth.ITokenFailure";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("60f8d417-ea6a-51d2-8ad7-f0e5177aef0a")
                    ITokenFailure : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Kind(
                            ABI::Microsoft::Security::Authentication::OAuth::TokenFailureKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorCode(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Error(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorDescription(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalParams(
                            __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITokenFailure = _uuidof(ITokenFailure);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestParams[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestParams";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("49134dbc-aab5-5ba4-bcdf-950214d81182")
                    ITokenRequestParams : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_GrantType(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_GrantType(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Code(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Code(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RedirectUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RedirectUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CodeVerifier(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CodeVerifier(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ClientId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ClientId(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Username(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Username(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Password(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Password(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scope(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Scope(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RefreshToken(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RefreshToken(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalParams(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITokenRequestParams = _uuidof(ITokenRequestParams);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestParamsFactory
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestParamsFactory[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestParamsFactory";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("2bf39c30-2f30-5788-98d2-a8ba622be809")
                    ITokenRequestParamsFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING grantType,
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITokenRequestParamsFactory = _uuidof(ITokenRequestParamsFactory);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestParamsStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestParamsStatics[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestParamsStatics";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("68b7af65-4381-5593-8820-f74a605b9f3b")
                    ITokenRequestParamsStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateForAuthorizationCodeRequest(
                            ABI::Microsoft::Security::Authentication::OAuth::IAuthResponse* authResponse,
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateForClientCredentials(
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateForExtension(
                            ABI::Windows::Foundation::IUriRuntimeClass* extensionUri,
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateForRefreshToken(
                            HSTRING refreshToken,
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenRequestParams** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITokenRequestParamsStatics = _uuidof(ITokenRequestParamsStatics);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestResult
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestResult[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestResult";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("35b31f77-f166-50df-a837-ec0460215166")
                    ITokenRequestResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ResponseMessage(
                            ABI::Windows::Web::Http::IHttpResponseMessage** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Response(
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenResponse** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Failure(
                            ABI::Microsoft::Security::Authentication::OAuth::ITokenFailure** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITokenRequestResult = _uuidof(ITokenRequestResult);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenResponse
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenResponse[] = L"Microsoft.Security.Authentication.OAuth.ITokenResponse";
namespace ABI {
    namespace Microsoft {
        namespace Security {
            namespace Authentication {
                namespace OAuth {
                    MIDL_INTERFACE("9d9d8cd3-04b2-5df6-bfd2-e8a6859745da")
                    ITokenResponse : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AccessToken(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TokenType(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpiresIn(
                            DOUBLE* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RefreshToken(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scope(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AdditionalParams(
                            __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITokenResponse = _uuidof(ITokenResponse);
                } /* OAuth */
            } /* Authentication */
        } /* Security */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthFailure ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthFailure_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthFailure_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthFailure[] = L"Microsoft.Security.Authentication.OAuth.AuthFailure";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Security.Authentication.OAuth.IAuthRequestParamsFactory interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.IAuthRequestParamsStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthRequestParams ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestParams_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestParams_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthRequestParams[] = L"Microsoft.Security.Authentication.OAuth.AuthRequestParams";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthRequestResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestResult_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthRequestResult[] = L"Microsoft.Security.Authentication.OAuth.AuthRequestResult";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthResponse ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthResponse[] = L"Microsoft.Security.Authentication.OAuth.AuthResponse";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Security.Authentication.OAuth.IClientAuthenticationFactory interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.IClientAuthenticationStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IClientAuthentication ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_ClientAuthentication_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_ClientAuthentication_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_ClientAuthentication[] = L"Microsoft.Security.Authentication.OAuth.ClientAuthentication";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.OAuth2Manager
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.IOAuth2ManagerStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_OAuth2Manager_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_OAuth2Manager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_OAuth2Manager[] = L"Microsoft.Security.Authentication.OAuth.OAuth2Manager";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenFailure ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenFailure_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenFailure_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenFailure[] = L"Microsoft.Security.Authentication.OAuth.TokenFailure";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Security.Authentication.OAuth.ITokenRequestParamsFactory interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.ITokenRequestParamsStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenRequestParams ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestParams_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestParams_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenRequestParams[] = L"Microsoft.Security.Authentication.OAuth.TokenRequestParams";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenRequestResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestResult_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenRequestResult[] = L"Microsoft.Security.Authentication.OAuth.TokenRequestResult";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenResponse ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenResponse[] = L"Microsoft.Security.Authentication.OAuth.TokenResponse";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse;

#endif // ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult;

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult;

typedef struct __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResultVtbl;

interface __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_INTERFACE_DEFINED__
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* This,
        __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResultVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult_INTERFACE_DEFINED__
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult;

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult;

typedef struct __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult** result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResultVtbl;

interface __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_INTERFACE_DEFINED__
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* This,
        __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResultVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult_INTERFACE_DEFINED__
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

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

#ifndef ____x_ABI_CWindows_CData_CJson_CIJsonValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CData_CJson_CIJsonValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CData_CJson_CIJsonValue __x_ABI_CWindows_CData_CJson_CIJsonValue;

#endif // ____x_ABI_CWindows_CData_CJson_CIJsonValue_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue;

typedef struct __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        __x_ABI_CWindows_CData_CJson_CIJsonValue** result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl;

interface __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

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

typedef interface __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue;

typedef struct __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING key,
        __x_ABI_CWindows_CData_CJson_CIJsonValue** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue* This,
        __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue** first,
        __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue** second);

    END_INTERFACE
} __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl;

interface __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue
{
    CONST_VTBL struct __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

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

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue;

#endif // ____x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_FWD_DEFINED__
#define ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage __x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage;

#endif // ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CCodeChallengeMethodKind __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CCodeChallengeMethodKind;

typedef enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CTokenFailureKind __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CTokenFailureKind;

/*
 *
 * Struct Microsoft.Security.Authentication.OAuth.CodeChallengeMethodKind
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CCodeChallengeMethodKind
{
    CodeChallengeMethodKind_None = 0,
    CodeChallengeMethodKind_S256 = 1,
    CodeChallengeMethodKind_Plain = 2,
};
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Security.Authentication.OAuth.TokenFailureKind
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CTokenFailureKind
{
    TokenFailureKind_ErrorResponse = 0,
    TokenFailureKind_HttpFailure = 1,
    TokenFailureKind_InvalidResponse = 2,
};
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthFailure
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthFailure[] = L"Microsoft.Security.Authentication.OAuth.IAuthFailure";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailureVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Error)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorDescription)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* get_State)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalParams)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure* This,
        __FIMapView_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailureVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailureVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_get_Error(This, value) \
    ((This)->lpVtbl->get_Error(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_get_ErrorDescription(This, value) \
    ((This)->lpVtbl->get_ErrorDescription(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_get_ErrorUri(This, value) \
    ((This)->lpVtbl->get_ErrorUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_get_State(This, value) \
    ((This)->lpVtbl->get_State(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_get_AdditionalParams(This, value) \
    ((This)->lpVtbl->get_AdditionalParams(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestParams[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestParams";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ResponseType)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_ResponseType)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_ClientId)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_ClientId)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_RedirectUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_RedirectUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_State)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_State)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Scope)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Scope)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_CodeChallenge)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CodeChallenge)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_CodeChallengeMethod)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CCodeChallengeMethodKind* value);
    HRESULT (STDMETHODCALLTYPE* put_CodeChallengeMethod)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CCodeChallengeMethodKind value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalParams)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_ResponseType(This, value) \
    ((This)->lpVtbl->get_ResponseType(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_ResponseType(This, value) \
    ((This)->lpVtbl->put_ResponseType(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_ClientId(This, value) \
    ((This)->lpVtbl->get_ClientId(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_ClientId(This, value) \
    ((This)->lpVtbl->put_ClientId(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_RedirectUri(This, value) \
    ((This)->lpVtbl->get_RedirectUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_RedirectUri(This, value) \
    ((This)->lpVtbl->put_RedirectUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_State(This, value) \
    ((This)->lpVtbl->get_State(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_State(This, value) \
    ((This)->lpVtbl->put_State(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_Scope(This, value) \
    ((This)->lpVtbl->get_Scope(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_Scope(This, value) \
    ((This)->lpVtbl->put_Scope(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_CodeChallenge(This, value) \
    ((This)->lpVtbl->get_CodeChallenge(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_CodeChallenge(This, value) \
    ((This)->lpVtbl->put_CodeChallenge(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_CodeChallengeMethod(This, value) \
    ((This)->lpVtbl->get_CodeChallengeMethod(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_put_CodeChallengeMethod(This, value) \
    ((This)->lpVtbl->put_CodeChallengeMethod(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_get_AdditionalParams(This, value) \
    ((This)->lpVtbl->get_AdditionalParams(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestParamsFactory
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestParamsFactory[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestParamsFactory";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This,
        HSTRING responseType,
        HSTRING clientId,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams** value);
    HRESULT (STDMETHODCALLTYPE* CreateInstance2)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory* This,
        HSTRING responseType,
        HSTRING clientId,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* redirectUri,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactoryVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_CreateInstance(This, responseType, clientId, value) \
    ((This)->lpVtbl->CreateInstance(This, responseType, clientId, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_CreateInstance2(This, responseType, clientId, redirectUri, value) \
    ((This)->lpVtbl->CreateInstance2(This, responseType, clientId, redirectUri, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestParamsStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestParamsStatics[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestParamsStatics";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForAuthorizationCodeRequest)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This,
        HSTRING clientId,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams** result);
    HRESULT (STDMETHODCALLTYPE* CreateForAuthorizationCodeRequest2)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics* This,
        HSTRING clientId,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* redirectUri,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStaticsVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_CreateForAuthorizationCodeRequest(This, clientId, result) \
    ((This)->lpVtbl->CreateForAuthorizationCodeRequest(This, clientId, result))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_CreateForAuthorizationCodeRequest2(This, clientId, redirectUri, result) \
    ((This)->lpVtbl->CreateForAuthorizationCodeRequest2(This, clientId, redirectUri, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParamsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthRequestResult
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthRequestResult[] = L"Microsoft.Security.Authentication.OAuth.IAuthRequestResult";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ResponseUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* get_Response)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse** value);
    HRESULT (STDMETHODCALLTYPE* get_Failure)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthFailure** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResultVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_get_ResponseUri(This, value) \
    ((This)->lpVtbl->get_ResponseUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_get_Response(This, value) \
    ((This)->lpVtbl->get_Response(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_get_Failure(This, value) \
    ((This)->lpVtbl->get_Failure(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IAuthResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.AuthResponse
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IAuthResponse[] = L"Microsoft.Security.Authentication.OAuth.IAuthResponse";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponseVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_State)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Code)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AccessToken)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_TokenType)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ExpiresIn)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Scope)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalParams)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* This,
        __FIMapView_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponseVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponseVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_State(This, value) \
    ((This)->lpVtbl->get_State(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_Code(This, value) \
    ((This)->lpVtbl->get_Code(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_AccessToken(This, value) \
    ((This)->lpVtbl->get_AccessToken(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_TokenType(This, value) \
    ((This)->lpVtbl->get_TokenType(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_ExpiresIn(This, value) \
    ((This)->lpVtbl->get_ExpiresIn(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_Scope(This, value) \
    ((This)->lpVtbl->get_Scope(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_get_AdditionalParams(This, value) \
    ((This)->lpVtbl->get_AdditionalParams(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IClientAuthentication
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IClientAuthentication[] = L"Microsoft.Security.Authentication.OAuth.IClientAuthentication";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Authorization)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue** value);
    HRESULT (STDMETHODCALLTYPE* put_Authorization)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue* value);
    HRESULT (STDMETHODCALLTYPE* get_ProxyAuthorization)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue** value);
    HRESULT (STDMETHODCALLTYPE* put_ProxyAuthorization)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue* value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalHeaders)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_get_Authorization(This, value) \
    ((This)->lpVtbl->get_Authorization(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_put_Authorization(This, value) \
    ((This)->lpVtbl->put_Authorization(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_get_ProxyAuthorization(This, value) \
    ((This)->lpVtbl->get_ProxyAuthorization(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_put_ProxyAuthorization(This, value) \
    ((This)->lpVtbl->put_ProxyAuthorization(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_get_AdditionalHeaders(This, value) \
    ((This)->lpVtbl->get_AdditionalHeaders(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IClientAuthenticationFactory
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IClientAuthenticationFactory[] = L"Microsoft.Security.Authentication.OAuth.IClientAuthenticationFactory";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory* This,
        __x_ABI_CWindows_CWeb_CHttp_CHeaders_CIHttpCredentialsHeaderValue* authorization,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactoryVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_CreateInstance(This, authorization, value) \
    ((This)->lpVtbl->CreateInstance(This, authorization, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IClientAuthenticationStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IClientAuthenticationStatics[] = L"Microsoft.Security.Authentication.OAuth.IClientAuthenticationStatics";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForBasicAuthorization)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics* This,
        HSTRING clientId,
        HSTRING clientSecret,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStaticsVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_CreateForBasicAuthorization(This, clientId, clientSecret, result) \
    ((This)->lpVtbl->CreateForBasicAuthorization(This, clientId, clientSecret, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthenticationStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.IOAuth2ManagerStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.OAuth2Manager
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_IOAuth2ManagerStatics[] = L"Microsoft.Security.Authentication.OAuth.IOAuth2ManagerStatics";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RequestAuthWithParamsAsync)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId parentWindowId,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* authEndpoint,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthRequestParams* params,
        __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CAuthRequestResult** operation);
    HRESULT (STDMETHODCALLTYPE* CompleteAuthRequest)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* responseUri,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* RequestTokenAsync)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* tokenEndpoint,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* params,
        __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult** operation);
    HRESULT (STDMETHODCALLTYPE* RequestTokenAsync2)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* tokenEndpoint,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* params,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIClientAuthentication* clientAuth,
        __FIAsyncOperation_1_Microsoft__CSecurity__CAuthentication__COAuth__CTokenRequestResult** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_RequestAuthWithParamsAsync(This, parentWindowId, authEndpoint, params, operation) \
    ((This)->lpVtbl->RequestAuthWithParamsAsync(This, parentWindowId, authEndpoint, params, operation))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_CompleteAuthRequest(This, responseUri, result) \
    ((This)->lpVtbl->CompleteAuthRequest(This, responseUri, result))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_RequestTokenAsync(This, tokenEndpoint, params, operation) \
    ((This)->lpVtbl->RequestTokenAsync(This, tokenEndpoint, params, operation))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_RequestTokenAsync2(This, tokenEndpoint, params, clientAuth, operation) \
    ((This)->lpVtbl->RequestTokenAsync2(This, tokenEndpoint, params, clientAuth, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIOAuth2ManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenFailure
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenFailure[] = L"Microsoft.Security.Authentication.OAuth.ITokenFailure";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailureVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        enum __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CTokenFailureKind* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorCode)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_Error)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorDescription)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalParams)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure* This,
        __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailureVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailureVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_get_ErrorCode(This, value) \
    ((This)->lpVtbl->get_ErrorCode(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_get_Error(This, value) \
    ((This)->lpVtbl->get_Error(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_get_ErrorDescription(This, value) \
    ((This)->lpVtbl->get_ErrorDescription(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_get_ErrorUri(This, value) \
    ((This)->lpVtbl->get_ErrorUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_get_AdditionalParams(This, value) \
    ((This)->lpVtbl->get_AdditionalParams(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestParams[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestParams";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_GrantType)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_GrantType)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Code)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Code)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_RedirectUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_RedirectUri)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_CodeVerifier)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CodeVerifier)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_ClientId)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_ClientId)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Username)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Username)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Password)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Password)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Scope)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Scope)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_RefreshToken)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_RefreshToken)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalParams)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_GrantType(This, value) \
    ((This)->lpVtbl->get_GrantType(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_GrantType(This, value) \
    ((This)->lpVtbl->put_GrantType(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_Code(This, value) \
    ((This)->lpVtbl->get_Code(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_Code(This, value) \
    ((This)->lpVtbl->put_Code(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_RedirectUri(This, value) \
    ((This)->lpVtbl->get_RedirectUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_RedirectUri(This, value) \
    ((This)->lpVtbl->put_RedirectUri(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_CodeVerifier(This, value) \
    ((This)->lpVtbl->get_CodeVerifier(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_CodeVerifier(This, value) \
    ((This)->lpVtbl->put_CodeVerifier(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_ClientId(This, value) \
    ((This)->lpVtbl->get_ClientId(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_ClientId(This, value) \
    ((This)->lpVtbl->put_ClientId(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_Username(This, value) \
    ((This)->lpVtbl->get_Username(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_Username(This, value) \
    ((This)->lpVtbl->put_Username(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_Password(This, value) \
    ((This)->lpVtbl->get_Password(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_Password(This, value) \
    ((This)->lpVtbl->put_Password(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_Scope(This, value) \
    ((This)->lpVtbl->get_Scope(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_Scope(This, value) \
    ((This)->lpVtbl->put_Scope(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_RefreshToken(This, value) \
    ((This)->lpVtbl->get_RefreshToken(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_put_RefreshToken(This, value) \
    ((This)->lpVtbl->put_RefreshToken(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_get_AdditionalParams(This, value) \
    ((This)->lpVtbl->get_AdditionalParams(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestParamsFactory
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestParamsFactory[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestParamsFactory";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory* This,
        HSTRING grantType,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactoryVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_CreateInstance(This, grantType, value) \
    ((This)->lpVtbl->CreateInstance(This, grantType, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestParamsStatics
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestParamsStatics[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestParamsStatics";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForAuthorizationCodeRequest)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CIAuthResponse* authResponse,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams** result);
    HRESULT (STDMETHODCALLTYPE* CreateForClientCredentials)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams** result);
    HRESULT (STDMETHODCALLTYPE* CreateForExtension)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* extensionUri,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams** result);
    HRESULT (STDMETHODCALLTYPE* CreateForRefreshToken)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics* This,
        HSTRING refreshToken,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParams** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStaticsVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_CreateForAuthorizationCodeRequest(This, authResponse, result) \
    ((This)->lpVtbl->CreateForAuthorizationCodeRequest(This, authResponse, result))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_CreateForClientCredentials(This, result) \
    ((This)->lpVtbl->CreateForClientCredentials(This, result))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_CreateForExtension(This, extensionUri, result) \
    ((This)->lpVtbl->CreateForExtension(This, extensionUri, result))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_CreateForRefreshToken(This, refreshToken, result) \
    ((This)->lpVtbl->CreateForRefreshToken(This, refreshToken, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestParamsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenRequestResult
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenRequestResult[] = L"Microsoft.Security.Authentication.OAuth.ITokenRequestResult";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ResponseMessage)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        __x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage** value);
    HRESULT (STDMETHODCALLTYPE* get_Response)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse** value);
    HRESULT (STDMETHODCALLTYPE* get_Failure)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult* This,
        __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenFailure** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResultVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_get_ResponseMessage(This, value) \
    ((This)->lpVtbl->get_ResponseMessage(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_get_Response(This, value) \
    ((This)->lpVtbl->get_Response(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_get_Failure(This, value) \
    ((This)->lpVtbl->get_Failure(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenRequestResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Security.Authentication.OAuth.ITokenResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Security.Authentication.OAuth.TokenResponse
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Security_Authentication_OAuth_ITokenResponse[] = L"Microsoft.Security.Authentication.OAuth.ITokenResponse";
typedef struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponseVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AccessToken)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_TokenType)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ExpiresIn)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_RefreshToken)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Scope)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AdditionalParams)(__x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse* This,
        __FIMapView_2_HSTRING_Windows__CData__CJson__CIJsonValue** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponseVtbl;

interface __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponseVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_get_AccessToken(This, value) \
    ((This)->lpVtbl->get_AccessToken(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_get_TokenType(This, value) \
    ((This)->lpVtbl->get_TokenType(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_get_ExpiresIn(This, value) \
    ((This)->lpVtbl->get_ExpiresIn(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_get_RefreshToken(This, value) \
    ((This)->lpVtbl->get_RefreshToken(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_get_Scope(This, value) \
    ((This)->lpVtbl->get_Scope(This, value))

#define __x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_get_AdditionalParams(This, value) \
    ((This)->lpVtbl->get_AdditionalParams(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CSecurity_CAuthentication_COAuth_CITokenResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthFailure ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthFailure_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthFailure_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthFailure[] = L"Microsoft.Security.Authentication.OAuth.AuthFailure";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Security.Authentication.OAuth.IAuthRequestParamsFactory interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.IAuthRequestParamsStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthRequestParams ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestParams_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestParams_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthRequestParams[] = L"Microsoft.Security.Authentication.OAuth.AuthRequestParams";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthRequestResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestResult_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthRequestResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthRequestResult[] = L"Microsoft.Security.Authentication.OAuth.AuthRequestResult";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.AuthResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IAuthResponse ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_AuthResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_AuthResponse[] = L"Microsoft.Security.Authentication.OAuth.AuthResponse";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.ClientAuthentication
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Security.Authentication.OAuth.IClientAuthenticationFactory interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.IClientAuthenticationStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.IClientAuthentication ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_ClientAuthentication_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_ClientAuthentication_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_ClientAuthentication[] = L"Microsoft.Security.Authentication.OAuth.ClientAuthentication";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.OAuth2Manager
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.IOAuth2ManagerStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_OAuth2Manager_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_OAuth2Manager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_OAuth2Manager[] = L"Microsoft.Security.Authentication.OAuth.OAuth2Manager";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenFailure
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenFailure ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenFailure_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenFailure_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenFailure[] = L"Microsoft.Security.Authentication.OAuth.TokenFailure";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenRequestParams
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Security.Authentication.OAuth.ITokenRequestParamsFactory interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Security.Authentication.OAuth.ITokenRequestParamsStatics interface starting with version 1.0 of the Microsoft.Security.Authentication.OAuth.OAuthContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenRequestParams ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestParams_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestParams_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenRequestParams[] = L"Microsoft.Security.Authentication.OAuth.TokenRequestParams";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenRequestResult
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenRequestResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestResult_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenRequestResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenRequestResult[] = L"Microsoft.Security.Authentication.OAuth.TokenRequestResult";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Security.Authentication.OAuth.TokenResponse
 *
 * Introduced to Microsoft.Security.Authentication.OAuth.OAuthContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Security.Authentication.OAuth.ITokenResponse ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Security_Authentication_OAuth_TokenResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Security_Authentication_OAuth_TokenResponse[] = L"Microsoft.Security.Authentication.OAuth.TokenResponse";
#endif
#endif // MICROSOFT_SECURITY_AUTHENTICATION_OAUTH_OAUTHCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Esecurity2Eauthentication2Eoauth_p_h__

#endif // __microsoft2Esecurity2Eauthentication2Eoauth_h__
