
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
#ifndef __microsoft2Ewindows2Efoundation_h__
#define __microsoft2Ewindows2Efoundation_h__
#ifndef __microsoft2Ewindows2Efoundation_p_h__
#define __microsoft2Ewindows2Efoundation_p_h__


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
#if !defined(MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Foundation {
                interface IDecimalHelperStatics;
            } /* Foundation */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics ABI::Microsoft::Windows::Foundation::IDecimalHelperStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Foundation {
                typedef struct DecimalValue DecimalValue;
            } /* Foundation */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Foundation.DecimalValue
 *
 * Introduced to Microsoft.Windows.Foundation.DecimalContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Foundation {
                struct DecimalValue
                {
                    UINT16 Reserved;
                    BYTE Scale;
                    BYTE Sign;
                    UINT32 Hi32;
                    UINT64 Lo64;
                };
            } /* Foundation */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Foundation.IDecimalHelperStatics
 *
 * Introduced to Microsoft.Windows.Foundation.DecimalContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Foundation.DecimalHelper
 *
 */
#if MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Foundation_IDecimalHelperStatics[] = L"Microsoft.Windows.Foundation.IDecimalHelperStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Foundation {
                MIDL_INTERFACE("ba09a415-e26c-55b3-9b76-b3affd556a7f")
                IDecimalHelperStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE FromBoolean(
                        boolean value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromInt16(
                        INT16 value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromInt32(
                        INT32 value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromInt64(
                        INT64 value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromUInt8(
                        BYTE value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromUInt16(
                        UINT16 value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromUInt32(
                        UINT32 value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromUInt64(
                        UINT64 value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromSingle(
                        FLOAT value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromDouble(
                        DOUBLE value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromString(
                        HSTRING source,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromStringInvariant(
                        HSTRING source,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FromStringWithLocale(
                        HSTRING source,
                        HSTRING localeName,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE TryFromString(
                        HSTRING source,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* value,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE TryFromStringInvariant(
                        HSTRING source,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* value,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE TryFromStringWithLocale(
                        HSTRING source,
                        HSTRING localeName,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* value,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToBoolean(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToInt16(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        INT16* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToInt32(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToInt64(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        INT64* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToUInt8(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        BYTE* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToUInt16(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        UINT16* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToUInt32(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        UINT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToUInt64(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        UINT64* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToSingle(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        FLOAT* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToDouble(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        DOUBLE* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToString(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        HSTRING* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToStringInvariant(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        HSTRING* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ToStringWithLocale(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        HSTRING localeName,
                        HSTRING* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Equals(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Compare(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsValid(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsInteger(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Scale(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        BYTE* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Sign(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        INT32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MaxScale(
                        BYTE* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MaxValue(
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MinValue(
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Negate(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Abs(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Truncate(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Floor(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Ceiling(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Round(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        INT32 decimalPlaces,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Clamp(
                        ABI::Microsoft::Windows::Foundation::DecimalValue value,
                        ABI::Microsoft::Windows::Foundation::DecimalValue min,
                        ABI::Microsoft::Windows::Foundation::DecimalValue max,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Add(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Subtract(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Multiply(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Divide(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Modulo(
                        ABI::Microsoft::Windows::Foundation::DecimalValue left,
                        ABI::Microsoft::Windows::Foundation::DecimalValue right,
                        ABI::Microsoft::Windows::Foundation::DecimalValue* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDecimalHelperStatics = _uuidof(IDecimalHelperStatics);
            } /* Foundation */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Foundation.DecimalHelper
 *
 * Introduced to Microsoft.Windows.Foundation.DecimalContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Foundation.IDecimalHelperStatics interface starting with version 1.0 of the Microsoft.Windows.Foundation.DecimalContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Foundation_DecimalHelper_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Foundation_DecimalHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Foundation_DecimalHelper[] = L"Microsoft.Windows.Foundation.DecimalHelper";
#endif
#endif // MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue;

/*
 *
 * Struct Microsoft.Windows.Foundation.DecimalValue
 *
 * Introduced to Microsoft.Windows.Foundation.DecimalContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue
{
    UINT16 Reserved;
    BYTE Scale;
    BYTE Sign;
    UINT32 Hi32;
    UINT64 Lo64;
};
#endif // MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Foundation.IDecimalHelperStatics
 *
 * Introduced to Microsoft.Windows.Foundation.DecimalContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Foundation.DecimalHelper
 *
 */
#if MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Foundation_IDecimalHelperStatics[] = L"Microsoft.Windows.Foundation.IDecimalHelperStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* FromBoolean)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        boolean value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromInt16)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        INT16 value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromInt32)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        INT32 value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromInt64)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        INT64 value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromUInt8)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        BYTE value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromUInt16)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        UINT16 value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromUInt32)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        UINT32 value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromUInt64)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        UINT64 value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromSingle)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        FLOAT value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromDouble)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        DOUBLE value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromString)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING source,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromStringInvariant)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING source,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* FromStringWithLocale)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING source,
        HSTRING localeName,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* TryFromString)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING source,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* TryFromStringInvariant)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING source,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* TryFromStringWithLocale)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        HSTRING source,
        HSTRING localeName,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* ToBoolean)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* ToInt16)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        INT16* result);
    HRESULT (STDMETHODCALLTYPE* ToInt32)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* ToInt64)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        INT64* result);
    HRESULT (STDMETHODCALLTYPE* ToUInt8)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        BYTE* result);
    HRESULT (STDMETHODCALLTYPE* ToUInt16)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        UINT16* result);
    HRESULT (STDMETHODCALLTYPE* ToUInt32)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ToUInt64)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        UINT64* result);
    HRESULT (STDMETHODCALLTYPE* ToSingle)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        FLOAT* result);
    HRESULT (STDMETHODCALLTYPE* ToDouble)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        DOUBLE* result);
    HRESULT (STDMETHODCALLTYPE* ToString)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* ToStringInvariant)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* ToStringWithLocale)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        HSTRING localeName,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* Equals)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Compare)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* IsValid)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsInteger)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Scale)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        BYTE* result);
    HRESULT (STDMETHODCALLTYPE* Sign)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MaxScale)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        BYTE* result);
    HRESULT (STDMETHODCALLTYPE* MaxValue)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* MinValue)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Negate)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Abs)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Truncate)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Floor)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Ceiling)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Round)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        INT32 decimalPlaces,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Clamp)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue value,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue min,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue max,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Add)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Subtract)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Multiply)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Divide)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);
    HRESULT (STDMETHODCALLTYPE* Modulo)(__x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics* This,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue left,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue right,
        struct __x_ABI_CMicrosoft_CWindows_CFoundation_CDecimalValue* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromBoolean(This, value, result) \
    ((This)->lpVtbl->FromBoolean(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromInt16(This, value, result) \
    ((This)->lpVtbl->FromInt16(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromInt32(This, value, result) \
    ((This)->lpVtbl->FromInt32(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromInt64(This, value, result) \
    ((This)->lpVtbl->FromInt64(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromUInt8(This, value, result) \
    ((This)->lpVtbl->FromUInt8(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromUInt16(This, value, result) \
    ((This)->lpVtbl->FromUInt16(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromUInt32(This, value, result) \
    ((This)->lpVtbl->FromUInt32(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromUInt64(This, value, result) \
    ((This)->lpVtbl->FromUInt64(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromSingle(This, value, result) \
    ((This)->lpVtbl->FromSingle(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromDouble(This, value, result) \
    ((This)->lpVtbl->FromDouble(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromString(This, source, result) \
    ((This)->lpVtbl->FromString(This, source, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromStringInvariant(This, source, result) \
    ((This)->lpVtbl->FromStringInvariant(This, source, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_FromStringWithLocale(This, source, localeName, result) \
    ((This)->lpVtbl->FromStringWithLocale(This, source, localeName, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_TryFromString(This, source, value, result) \
    ((This)->lpVtbl->TryFromString(This, source, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_TryFromStringInvariant(This, source, value, result) \
    ((This)->lpVtbl->TryFromStringInvariant(This, source, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_TryFromStringWithLocale(This, source, localeName, value, result) \
    ((This)->lpVtbl->TryFromStringWithLocale(This, source, localeName, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToBoolean(This, value, result) \
    ((This)->lpVtbl->ToBoolean(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToInt16(This, value, result) \
    ((This)->lpVtbl->ToInt16(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToInt32(This, value, result) \
    ((This)->lpVtbl->ToInt32(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToInt64(This, value, result) \
    ((This)->lpVtbl->ToInt64(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToUInt8(This, value, result) \
    ((This)->lpVtbl->ToUInt8(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToUInt16(This, value, result) \
    ((This)->lpVtbl->ToUInt16(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToUInt32(This, value, result) \
    ((This)->lpVtbl->ToUInt32(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToUInt64(This, value, result) \
    ((This)->lpVtbl->ToUInt64(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToSingle(This, value, result) \
    ((This)->lpVtbl->ToSingle(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToDouble(This, value, result) \
    ((This)->lpVtbl->ToDouble(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToString(This, value, result) \
    ((This)->lpVtbl->ToString(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToStringInvariant(This, value, result) \
    ((This)->lpVtbl->ToStringInvariant(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_ToStringWithLocale(This, value, localeName, result) \
    ((This)->lpVtbl->ToStringWithLocale(This, value, localeName, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Equals(This, left, right, result) \
    ((This)->lpVtbl->Equals(This, left, right, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Compare(This, left, right, result) \
    ((This)->lpVtbl->Compare(This, left, right, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_IsValid(This, value, result) \
    ((This)->lpVtbl->IsValid(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_IsInteger(This, value, result) \
    ((This)->lpVtbl->IsInteger(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Scale(This, value, result) \
    ((This)->lpVtbl->Scale(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Sign(This, value, result) \
    ((This)->lpVtbl->Sign(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_MaxScale(This, result) \
    ((This)->lpVtbl->MaxScale(This, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_MaxValue(This, result) \
    ((This)->lpVtbl->MaxValue(This, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_MinValue(This, result) \
    ((This)->lpVtbl->MinValue(This, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Negate(This, value, result) \
    ((This)->lpVtbl->Negate(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Abs(This, value, result) \
    ((This)->lpVtbl->Abs(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Truncate(This, value, result) \
    ((This)->lpVtbl->Truncate(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Floor(This, value, result) \
    ((This)->lpVtbl->Floor(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Ceiling(This, value, result) \
    ((This)->lpVtbl->Ceiling(This, value, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Round(This, value, decimalPlaces, result) \
    ((This)->lpVtbl->Round(This, value, decimalPlaces, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Clamp(This, value, min, max, result) \
    ((This)->lpVtbl->Clamp(This, value, min, max, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Add(This, left, right, result) \
    ((This)->lpVtbl->Add(This, left, right, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Subtract(This, left, right, result) \
    ((This)->lpVtbl->Subtract(This, left, right, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Multiply(This, left, right, result) \
    ((This)->lpVtbl->Multiply(This, left, right, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Divide(This, left, right, result) \
    ((This)->lpVtbl->Divide(This, left, right, result))

#define __x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_Modulo(This, left, right, result) \
    ((This)->lpVtbl->Modulo(This, left, right, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CFoundation_CIDecimalHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Foundation.DecimalHelper
 *
 * Introduced to Microsoft.Windows.Foundation.DecimalContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Foundation.IDecimalHelperStatics interface starting with version 1.0 of the Microsoft.Windows.Foundation.DecimalContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Foundation_DecimalHelper_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Foundation_DecimalHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Foundation_DecimalHelper[] = L"Microsoft.Windows.Foundation.DecimalHelper";
#endif
#endif // MICROSOFT_WINDOWS_FOUNDATION_DECIMALCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Efoundation_p_h__

#endif // __microsoft2Ewindows2Efoundation_h__
