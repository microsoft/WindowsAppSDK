// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

/* DEFRESULT 
     * DEF error result type.  DEF results are 32-bits and have the structure:
     *     0xDEFXXXYY
     * Where 'XXX' is an 12-bit facility code and 'YY' is an 8-bit error code.
     */
typedef long DEFRESULT;

#if defined(__cplusplus)
#define RESOURCE_SUPPRESS_STL
#include <wil\resource.h>
#endif

#include "mrm/common/Platform.h"

#ifdef DBG
#define _DEBUG 1
#endif

#if !defined(__cplusplus) || defined(_DEF_TESTING_C)
#define _DEF_C
#endif

/*!
 * \defgroup CommonBase Common data structures and macros for C/C++ Interop
 * @{
 */

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
     * \defgroup Atom Atom: Unique, relocatable, fixed-size string reference
     * @{
     * \name Common
     * @{
     */

    typedef INT32 DEF_ATOM_POOL_INDEX; //!< Index of an atom pool in an atom pool group.
    typedef INT32 DEF_ATOM_INDEX; //!< Index of an atom in an atom pool.

    typedef INT32 DEF_ATOM_POOL_COUNT; //!< Count of number of atom pools
    typedef INT32 DEF_ATOM_COUNT; //!< Count of number of atoms in a pool

    typedef UINT32 DEF_ATOM_HASH; //!< Simple hash value for an atom string.

    typedef UINT16 DEF_ATOM_POOL_INDEX_SMALL;
    typedef UINT16 DEF_ATOM_INDEX_SMALL;
    typedef UINT16 DEF_ATOM_POOL_COUNT_SMALL;
    typedef UINT16 DEF_ATOM_COUNT_SMALL;
    typedef UINT16 DEF_ATOM_HASH_SMALL;

#define DEF_ATOM_MAX_POOL_COUNT_SMALL 0x7FFF
#define DEF_ATOM_MAX_POOL_INDEX_SMALL (DEF_ATOM_MAX_POOL_COUNT_SMALL - 1)

#define DEF_ATOM_MAX_COUNT_SMALL 0x7FFF
#define DEF_ATOM_MAX_INDEX_SMALL (DEF_ATOM_MAX_COUNT_SMALL - 1)

#define DEF_ATOM_MAX_COUNT 0x7FFFFFFF
#define DEF_ATOM_MAX_INDEX (DEF_ATOM_MAX_COUNT - 1)

#define DEF_ATOM_INDEX_NONE -1
#define DEF_ATOM_POOL_INDEX_NONE -1

#define DEF_ATOM_NULL_POOL_INDEX 0
#define DEF_ATOM_MAX_POOL_COUNT 0x7FFFFFFF
#define DEF_ATOM_MIN_POOL_INDEX 1
#define DEF_ATOM_MAX_POOL_INDEX (DEF_ATOM_MAX_POOL_COUNT - 1)

    /*!
     * A DEF_ATOM structure consists of a 16-bit pool index (type \ref 
     * DEF_ATOM_POOL_INDEX) and a 16-bit atom index (of type \ref DEF_ATOM_INDEX),
     * which can also be referenced or set as a single 32-bit value.
     */
    typedef union _DEF_ATOM
    {
        struct
        {
            DEF_ATOM_POOL_INDEX poolIndex;
            DEF_ATOM_INDEX index;
        } s;
        UINT64 uVal;
        INT64 val;
    } DEF_ATOM;

    /*!
     * A shorter representation of an \ref DEF_ATOM, which can be used when
     * the total number of pools or atoms in any individual pool fits in
     * 16 bits.   Used primarily in file-based, directly mapped data structures
     * to conserve memory.
     */
    typedef union _DEF_ATOM_SMALL
    {
        struct
        {
            DEF_ATOM_POOL_INDEX_SMALL poolIndex;
            DEF_ATOM_INDEX_SMALL index;
        } s;
        UINT32 uVal;
        INT32 val;
    } DEF_ATOM_SMALL;

    /*!
  * Initializer of DEF_ATOM_NULL*
  */
    static const DEF_ATOM DEF_ATOM_NULL = {0};
    static const DEF_ATOM_SMALL DEF_ATOM_NULL_SMALL = {0};
    /*! \enum DEF_ATOM_HASH_METHOD
     * Specifies a method used to hash a string.
     */
    typedef enum
    {
        DEF_HASH_DEFAULT = 0, //!< Use the default hash function
        DEF_HASH_CASE_INSENSITIVE = 1 //!< Use a case-insensitive hash function
    } DEF_ATOM_HASH_METHOD;

    /*! \enum DEF_ATOM_COMPARISON
     * Specifies the result of a comparison of two atoms or an atom
     * and a string.
     */
    typedef enum
    {
        DEF_ATOMS_EQUAL = 0,
        DEF_ATOMS_UNEQUAL = 1,
        DEF_ATOMS_INDETERMINATE = 2
    } DEF_ATOM_COMPARISON;

    /*!@}*/
    /*!@}*/

    /*!
     * DEF files use checksums (CRC-32) to detect data changes and incompatibilites
     */
    typedef UINT32 DEF_CHECKSUM;

    /*!
     * Use the _DEF_MAKE_STATUS() macro to define DEF status values.
     */
#define _DEF_MAKE_STATUS(FACILITY, CODE) ((DEFRESULT)(0xdef00000 | ((((UINT32)(FACILITY)) & 0xFFF) << 8) | (((UINT32)(CODE)) & 0xFF)))

    /*!
     * The DEFSTATUS structure holds current status and any details if an error
     * occurred.  In typical usage, a DEFSTATUS is allocated on the stack and a
     * pointer is passed to any called function;  if an error occurs, callee
     * functions store error details in the DEFSTATUS and report failure.
     */
    typedef struct _DEFSTATUS
    {
        DEFRESULT what; //!< DEFRESULT describing the error
        PCWSTR where; //!< Function or file where error occurred
        PCWSTR desc; /*!< Descriptive string, such as the name of the variable
                                 or argument primarily associated with the error. */
        UINT32 line; //!< Line number where error occurred.
        UINT32 details; //!< Additional detail about the error (optional)
    } DEFSTATUS, *PDEFSTATUS;

#define STRINGIFY(THIS) TEXT(#THIS)
#define TO_S(THIS) STRINGIFY(THIS)

#define Def_SetError0(WHAT, STATUS) Def_SetError((WHAT), L"", (STATUS))

#define Def_Check(WHY, DESC, WHAT, STATUS) ((WHY) ? Def_SetError((WHAT), (DESC), (STATUS)), TRUE : FALSE)

#define Def_Check0(WHY, WHAT, STATUS) Def_Check((WHY), L"", (WHAT), (STATUS))

// Basic Checks
#define Def_CheckIsNull(WHO, DESC, WHAT, STATUS) Def_CheckIsEqual(WHO, NULL, DESC, WHAT, STATUS)

#define Def_CheckIsNotNull(WHO, DESC, WHAT, STATUS) Def_CheckIsNotEqual(WHO, NULL, DESC, WHAT, STATUS)

#define Def_CheckIsEqual(WHO, VAL, DESC, WHAT, STATUS) Def_Check((WHO) == (VAL), DESC, (WHAT), (STATUS))

#define Def_CheckIsNotEqual(WHO, VAL, DESC, WHAT, STATUS) Def_Check((WHO) != (VAL), DESC, (WHAT), (STATUS))

#define Def_CheckIsGreater(WHO, VAL, DESC, WHAT, STATUS) Def_Check((WHO) > (VAL), DESC, WHAT, STATUS)

#define Def_CheckIsGreaterOrEqual(WHO, VAL, DESC, WHAT, STATUS) Def_Check((WHO) >= (VAL), DESC, WHAT, STATUS)

#define Def_CheckIsLesser(WHO, VAL, DESC, WHAT, STATUS) Def_Check((WHO) < (VAL), DESC, WHAT, STATUS)

#define Def_CheckIsLesserOrEqual(WHO, VAL, DESC, WHAT, STATUS) Def_Check((WHO) <= (VAL), DESC, WHAT, STATUS)

#define Def_CheckIsNotInRangeInclusive(LOW, WHO, HIGH, DESC, WHAT, STATUS) \
    (Def_CheckIsGreater(WHO, (HIGH), DESC, (WHAT), (STATUS)) || Def_CheckIsLesser(WHO, (LOW), DESC, (WHAT), (STATUS)))

#define Def_CheckIsNotInRangeInclusive0(LOW, WHO, HIGH, STATUS) \
    (Def_CheckIsGreater(WHO, (HIGH), L"", E_DEF_OUT_OF_RANGE, (STATUS)) || Def_CheckIsLesser(WHO, (LOW), L"", E_DEF_OUT_OF_RANGE, (STATUS)))

#define Def_CheckSizeTIsNotValidUInt32(SVAL, UIOUT, STATUS) Def_Check0(FAILED(SizeTToUInt((SVAL), (UIOUT))), E_DEF_OUT_OF_RANGE, (STATUS))

#define Def_CheckIntIsNotValidUInt16(IVAL, USOUT, STATUS) Def_Check0(FAILED(IntToUShort((IVAL), (USOUT))), E_DEF_OUT_OF_RANGE, (STATUS))

#define Def_CheckFlagsInvalid(FLAGS, VALIDFLAGS, DESC, WHAT, STATUS) (Def_Check((FLAGS) & !(VALIDFLAGS), DESC, WHAT, STATUS))

#define Def_CheckFlagsInclude(FLAGS, EXCLUDED, DESC, WHAT, STATUS) (Def_Check((FLAGS) & (EXCLUDED), DESC, WHAT, STATUS))

// Arg Checks
#define Def_CheckArg(WHY, WHO, STATUS) Def_Check((WHY), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsNull(WHO, STATUS) Def_CheckIsNull((WHO), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsNotNull(WHO, STATUS) Def_CheckIsNotNull((WHO), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsNullOrEmptyString(WHO, STATUS) Def_Check(((!(WHO)) || (!(*(WHO)))), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsEqual(WHO, VAL, STATUS) Def_CheckIsEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsNotEqual(WHO, VAL, STATUS) Def_CheckIsNotEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsGreater(WHO, VAL, STATUS) Def_CheckIsGreater((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsGreaterOrEqual(WHO, VAL, STATUS) Def_CheckIsGreaterOrEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsLesser(WHO, VAL, STATUS) Def_CheckIsLesser((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsLesserOrEqual(WHO, VAL, STATUS) Def_CheckIsLesserOrEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgIsNotInRangeInclusive(LOW, WHO, HIGH, STATUS) \
    Def_CheckIsNotInRangeInclusive((LOW), (WHO), (HIGH), TO_S(WHO), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgFlagsInvalid(FLAGS, VALIDFLAGS, STATUS) Def_CheckFlagsInvalid(FLAGS, VALIDFLAGS, TO_S(FLAGS), E_DEF_INVALID_ARG, (STATUS))

#define Def_ArgFlagsInclude(FLAGS, INCLUDED, STATUS) Def_CheckFlagsInclude(FLAGS, INCLUDED, TO_S(FLAGS), E_DEF_INVALID_ARG, (STATUS))

// Object/Member Checks
#define Def_CheckObject(WHY, WHO, STATUS) Def_Check((WHY), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsNull(WHO, STATUS) Def_CheckIsNull((WHO), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsNotNull(WHO, STATUS) Def_CheckIsNotNull((WHO), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsEqual(WHO, VAL, STATUS) Def_CheckIsEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsNotEqual(WHO, VAL, STATUS) Def_CheckIsNotEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsGreater(WHO, VAL, STATUS) Def_CheckIsGreater((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsGreaterOrEqual(WHO, VAL, STATUS) Def_CheckIsGreaterOrEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsLesser(WHO, VAL, STATUS) Def_CheckIsLesser((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsLesserOrEqual(WHO, VAL, STATUS) Def_CheckIsLesserOrEqual((WHO), (VAL), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectIsNotInRange(LOW, WHO, HIGH, STATUS) \
    Def_CheckIsNotInRange((LOW), (WHO), (HIGH), TO_S(WHO), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectFlagsInvalid(FLAGS, VALIDFLAGS, STATUS) \
    Def_CheckFlagsInvalid(FLAGS, VALIDFLAGS, TO_S(FLAGS), E_DEF_INVALID_OBJECT, (STATUS))

#define Def_ObjectFlagsInclude(FLAGS, INCLUDED, STATUS) Def_CheckFlagsInclude(FLAGS, INCLUDED, TO_S(FLAGS), E_DEF_INVALID_OBJECT, (STATUS))

// Failure Checks
#define Def_AllocFailed(ALLOCATED, STATUS) Def_CheckIsNull((ALLOCATED), TO_S(ALLOCATED), E_DEF_OUT_OF_MEMORY, (STATUS))

    /*!@}*/
    /*!@}*/

    /*!
     * \defgroup ResultObjects Results held internally or referenced
     * \copydoc DEFSTRINGRESULT
     * @{
     * \name Common
     * @{
     */

#ifndef DEFRESULT_MAX
#define DEFRESULT_MAX UINT32_MAX
#endif

    /*!
     * The type of the ::DEFRESULTSTRING object
     */
    typedef enum _DEFRESULTTYPE
    {
        DefResultType_None, //!< Not a valid type
        DefResultType_Buffer, //!< Buffer type, _DEFSTRINGRESULT::pRef refers to a string stored in _DEFSTRINGRESULT::pBuf
        DefResultType_Reference //!< Reference type, _DEFSTRINGRESULT::pRef refers to a read-only, foreign pStr
    } DEFRESULTTYPE;

    /*!
 *  ::DEFRESULT refers either to an internal buffer or to an externally 
 */
    typedef struct _DEFBLOBRESULT
    {
        void* pBuf; //!< The buffer managed by ::DEFRESULT
        UINT32 cbBuf; //!< The allocated size of the buffer
        const void* pRef; //!< The current value of the result, which might or might not be resident in pBuf.
        UINT32 cbRef; //!< The current size of the result which is equal to cbBuf if pRef regers to pBuf.
    } DEFBLOBRESULT;

    typedef DEFBLOBRESULT* PDEFBLOBRESULT;

    /*!
     * The ::DEFSTRINGRESULT object functions as a str reference refering either
     * to it's own internal buffer or a foreign, read-only, long-lived object
     *
     * To directly access the str value referenced by a ::DEFSTRINGRESULT, use
     * the _DEFSTRINGRESULT::pRef element.  Accessing the _DEFSTRINGRESULT::pBuf
     * element directly may or may not yield the proper result, depending upon the
     * ::DEFRESULTTYPE of the object.
     *
     * _DEFSTRINGRESULT::cchBuf must be >= the length of _DEFSTRINGRESULT::pBuf + 1
     * and < STRSAFE_MAX_CCH at all times
     */
    typedef struct _DEFSTRINGRESULT
    {
        __ecount(cchBuf) PWSTR pBuf; //!< The buffer managed by ::DEFSTRINGRESULT
        UINT32 cchBuf; //!< The allocated size of the buffer
        PCWSTR pRef; /*!< The current pStr value of the string, which might
                               or might no be resident in buf. */
    } DEFSTRINGRESULT;

    typedef DEFSTRINGRESULT* PDEFSTRINGRESULT;

    /*! The result of a comparison
 *
 *  Comparison is relative to the compared objects' position in a parameter list.  For
 *  example, _Def_Less indicates that the first object is less than the second object.
 */
    typedef enum _DEFCOMPARISON
    {
        Def_Less = -1,
        Def_Equal = 0,
        Def_Greater = 1,
        Def_CompareError = _NLSCMPERROR
    } DEFCOMPARISON;

    /*! Option flags for comparison operations */
    typedef enum _DEFCOMPAREOPTIONS
    {
        DefCompare_Default = 0, //!< Default - Case-sensitive
        DefCompare_CaseInsensitive = 1 //!< Case-insensitive
    } DEFCOMPAREOPTIONS;

#define Def_CompareFlagsInvalid(COMPAREFLAGS, STATUS) Def_ArgFlagsInvalid(COMPAREFLAGS, DefCompare_CaseInsensitive, STATUS)

#define Def_Alloc(SIZE) _DefPlatformAlloc(SIZE)
#define Def_Free(PTR) _DefPlatformFree(PTR)

    /*!@}*/
    /*!@}*/

    /*!
     * \defgroup Errors Commonly used error codes
     * @{
     * \name Common
     * @{
     */

#define _DEF_FACILITY_BASE 0
#define _DEF_FACILITY_FILE 1
#define _DEF_FACILITY_BUILD 2
#define _DEF_FACILITY_RUNTIME 3
#define _DEF_FACILITY_UTILS 4
#define _DEF_FACILITY_IBC 5
#define _DEF_FACILITY_EXTENSIONS 6

#define _DEF_DECLARE_BASE_STATUS(NAME, INDEX) static const DEFRESULT E_DEF_##NAME = _DEF_MAKE_STATUS(_DEF_FACILITY_BASE, INDEX)

    //general errors

    _DEF_DECLARE_BASE_STATUS(BAD_VALUE, 0x01);
    _DEF_DECLARE_BASE_STATUS(OUT_OF_RANGE, 0x02);
    _DEF_DECLARE_BASE_STATUS(INVALID_ARG, 0x03);
    _DEF_DECLARE_BASE_STATUS(INVALID_OBJECT, 0x04);
    _DEF_DECLARE_BASE_STATUS(OUT_OF_MEMORY, 0x05);
    _DEF_DECLARE_BASE_STATUS(NOT_INITIALIZED, 0x06);
    _DEF_DECLARE_BASE_STATUS(NOT_WRITABLE, 0x07);
    _DEF_DECLARE_BASE_STATUS(INSUFFICIENT_BUFFER, 0x08);
    _DEF_DECLARE_BASE_STATUS(NOT_READY, 0x09);
    _DEF_DECLARE_BASE_STATUS(ALREADY_INITIALIZED, 0x0a);
    _DEF_DECLARE_BASE_STATUS(BAD_PATH, 0x0b);
    _DEF_DECLARE_BASE_STATUS(NOT_IMPLEMENTED, 0x0e);
    _DEF_DECLARE_BASE_STATUS(INTERNAL_ERROR, 0x0f);

    //atom pool errrors

    _DEF_DECLARE_BASE_STATUS(BAD_ATOM, 0x10);
    _DEF_DECLARE_BASE_STATUS(ATOM_BAD_POOL, 0x11);
    _DEF_DECLARE_BASE_STATUS(ATOM_BAD_INDEX, 0x12);
    _DEF_DECLARE_BASE_STATUS(ATOM_BAD_STRING, 0x14);
    _DEF_DECLARE_BASE_STATUS(ATOM_NAME_NOT_FOUND, 0x15);
    _DEF_DECLARE_BASE_STATUS(ATOM_POOL_MISMATCH, 0x16);
    _DEF_DECLARE_BASE_STATUS(ATOM_BAD_HASH, 0x17);

    // collection errors

    _DEF_DECLARE_BASE_STATUS(ENTRY_ALREADY_EXISTS, 0x20);
    _DEF_DECLARE_BASE_STATUS(RANGE_NOT_FOUND, 0x21);
    _DEF_DECLARE_BASE_STATUS(NO_MORE_MATCHES, 0x22);
    _DEF_DECLARE_BASE_STATUS(COUNT_BEYOND_MAX_RANGE, 0x24);
    _DEF_DECLARE_BASE_STATUS(LIST_HASH_CALCULATE_FAILED, 0x25);
    _DEF_DECLARE_BASE_STATUS(KEY_NOT_FOUND, 0x26);
    _DEF_DECLARE_BASE_STATUS(VALUE_NOT_FOUND, 0x27);
    _DEF_DECLARE_BASE_STATUS(COLLECTION_OWNER_MISMATCH, 0x29);
    _DEF_DECLARE_BASE_STATUS(DUPLICATE_INVALID_ENTRY, 0x30);

    // version errors - includes ResourceSchema specific version errors also.
    _DEF_DECLARE_BASE_STATUS(UNSUPPORTED_VERSION, 0x30);
    _DEF_DECLARE_BASE_STATUS(VERSION_MISMATCH, 0x31);
    _DEF_DECLARE_BASE_STATUS(SIZE_MISMATCH, 0x32);
    _DEF_DECLARE_BASE_STATUS(SCHEMA_MISMATCH, 0x33);
    _DEF_DECLARE_BASE_STATUS(MAJOR_VERSION_MISMATCH, 0x34);
    _DEF_DECLARE_BASE_STATUS(MINOR_VERSION_PRIOR, 0x35);
    _DEF_DECLARE_BASE_STATUS(MINOR_VERSION_LATER, 0x36);
    _DEF_DECLARE_BASE_STATUS(MINOR_VERSION_INCOMPATIBLE, 0x37);
    _DEF_DECLARE_BASE_STATUS(SCHEMA_NOT_FOUND, 0x38);
    _DEF_DECLARE_BASE_STATUS(DUPLICATE_SCHEMA_NAME, 0x39);

    // 0x4x is for Environment and writable string pool errors
    _DEF_DECLARE_BASE_STATUS(INVALID_QUALIFIER_NAME, 0x40);
    _DEF_DECLARE_BASE_STATUS(INVALID_CONDITION_OPERATOR, 0x41);
    _DEF_DECLARE_BASE_STATUS(INVALID_ATTRIBUTE_VALUE, 0x42);
    _DEF_DECLARE_BASE_STATUS(STRING_NOT_FOUND, 0x4f);

    // 0x5x is for Conditions
    _DEF_DECLARE_BASE_STATUS(CONDITION_ILLEGAL_OPERATOR, 0x51);
    _DEF_DECLARE_BASE_STATUS(CONDITION_OPERAND_NOT_ATTRIBUTE, 0x52);
    _DEF_DECLARE_BASE_STATUS(CONDITION_OPERAND_NOT_LITERAL, 0x53);
    _DEF_DECLARE_BASE_STATUS(CONDITION_INVALID_WEIGHT, 0x54);
    _DEF_DECLARE_BASE_STATUS(CONDITIONSET_RESULT_ERROR, 0x59);
    _DEF_DECLARE_BASE_STATUS(CONDITION_GETORADD_ERROR, 0x5A);
    _DEF_DECLARE_BASE_STATUS(WCONDITION_GETORADD_ERROR, 0x5B);
    _DEF_DECLARE_BASE_STATUS(WCONDITION_REF_GETORADD_ERROR, 0x5C);
    _DEF_DECLARE_BASE_STATUS(CONDITIONSET_GETORADD_ERROR, 0x5D);
    _DEF_DECLARE_BASE_STATUS(CONDITIONVALUE_GETORADD_ERROR, 0x5E);

    // 0x6x is for Condition Pools
    _DEF_DECLARE_BASE_STATUS(CP_BAD_TOTAL_CONDITION_COUNT, 0x60);
    _DEF_DECLARE_BASE_STATUS(CP_HANDLE_MISMATCH, 0x61);
    _DEF_DECLARE_BASE_STATUS(CONDITIONPOOL_RESULT_ERROR, 0x64);
    _DEF_DECLARE_BASE_STATUS(CONDITIONSETPOOL_RESULT_ERROR, 0x65);

    // 0x7x is for file system errors
    _DEF_DECLARE_BASE_STATUS(FOLDER_NOT_FOUND, 0x70);
    _DEF_DECLARE_BASE_STATUS(FILE_NOT_FOUND, 0x71);
    _DEF_DECLARE_BASE_STATUS(INVALID_PATH, 0x72);
    _DEF_DECLARE_BASE_STATUS(EMPTY_MERGED_INDEX, 0x74);
    _DEF_DECLARE_BASE_STATUS(INVALID_HANDLE, 0x75);
    _DEF_DECLARE_BASE_STATUS(UNABLE_TO_CALCULATE_SIZE, 0x76);
    _DEF_DECLARE_BASE_STATUS(UNABLE_TO_CLOSE_HANDLE, 0x77);
    _DEF_DECLARE_BASE_STATUS(UNABLE_TO_READ_FILE, 0x78);
    _DEF_DECLARE_BASE_STATUS(FILE_ALREADY_EXISTS, 0x79);
    _DEF_DECLARE_BASE_STATUS(ACCESS_DENIED, 0x7a);
    _DEF_DECLARE_BASE_STATUS(UNABLE_TO_OPEN_OVERLAY_FILE, 0x7b);

    // 0x8x is for ResourceIndex
    _DEF_DECLARE_BASE_STATUS(ITEM_NAME_NOT_FOUND, 0x81);
    _DEF_DECLARE_BASE_STATUS(TYPE_MISMATCH, 0x82);
    _DEF_DECLARE_BASE_STATUS(INCOMPATIBLE_LOCATOR_TYPE, 0x83);
    _DEF_DECLARE_BASE_STATUS(INCOMPATIBLE_VALUE_TYPE, 0x84);

// BUILD error codes
#define _DEF_DECLARE_BUILD_STATUS(NAME, INDEX) static const DEFRESULT E_DEFFILE_BUILD_##NAME = _DEF_MAKE_STATUS(_DEF_FACILITY_BUILD, INDEX)

    //File builder error codes
    _DEF_DECLARE_BUILD_STATUS(SECTIONS_FULL, 0x01);
    _DEF_DECLARE_BUILD_STATUS(BAD_PHASE, 0x02);
    _DEF_DECLARE_BUILD_STATUS(SECTION_DATA_TOO_LARGE, 0x03);
    _DEF_DECLARE_BUILD_STATUS(SECTION_TRAILER_DAMAGED, 0x04);
    _DEF_DECLARE_BUILD_STATUS(UNABLE_TO_OPEN_FOR_WRITE, 0x05);
    _DEF_DECLARE_BUILD_STATUS(SECTION_BUILDER_NOT_READY, 0x06);
    _DEF_DECLARE_BUILD_STATUS(EMPTY_ELEMENT, 0x07);

    //Namespace builder codes
    _DEF_DECLARE_BUILD_STATUS(DUPLICATE_REFERENCE, 0x20);
    _DEF_DECLARE_BUILD_STATUS(INVALID_REF_FILE, 0x21);
    _DEF_DECLARE_BUILD_STATUS(LINK_TO_LINKED_RESOURCE, 0x22);
    _DEF_DECLARE_BUILD_STATUS(LINK_TO_INCOMPATIBLE_RESOURCE, 0x23);

    // Resource pack merge
    _DEF_DECLARE_BUILD_STATUS(DEPLOYMENT_MERGE_UNSUPPORTED_FILE_TYPE, 0x40);

#define _DEF_FACILITY_MRM 0x10
#define _MRM_DECLARE_STATUS(NAME, INDEX) static const DEFRESULT E_MRM_##NAME = _DEF_MAKE_STATUS(_DEF_FACILITY_MRM, INDEX)

    _MRM_DECLARE_STATUS(UNSUPPORTED_ENVIRONMENT, 0x01);
    _MRM_DECLARE_STATUS(UNKNOWN_ENVIRONMENT, 0x02);
    _MRM_DECLARE_STATUS(BAD_ENVIRONMENT, 0x03);
    _MRM_DECLARE_STATUS(UNKNOWN_SCHEMA, 0x04);
    _MRM_DECLARE_STATUS(BAD_SCHEMA, 0x05);

    _MRM_DECLARE_STATUS(BAD_NAME, 0x10);

    _MRM_DECLARE_STATUS(COLLECTION_NOT_FOUND, 0x20);
    _MRM_DECLARE_STATUS(ITEM_NOT_FOUND, 0x21);
    _MRM_DECLARE_STATUS(BAD_ITEM_TYPE, 0x22);
    _MRM_DECLARE_STATUS(BAD_INSTANCE_TYPE, 0x23);
    _MRM_DECLARE_STATUS(READ_ONLY_SCHEMA, 0x24);
    _MRM_DECLARE_STATUS(NO_PRIMARY_INDEX, 0x25);
    _MRM_DECLARE_STATUS(NO_MATCHING_CANDIDATE, 0x26);
    _MRM_DECLARE_STATUS(INVALID_MAP_NAME, 0x27);
    _MRM_DECLARE_STATUS(MULTIPLE_MAPS, 0x28);
    _MRM_DECLARE_STATUS(PRI_MANAGER_MISMATCH, 0x30);
    _MRM_DECLARE_STATUS(PACKAGE_ROOT_MISMATCH, 0x31);
    _MRM_DECLARE_STATUS(PACKAGE_NOT_FOUND, 0x33);
    _MRM_DECLARE_STATUS(UNSUPPORTED_PROFILE_TYPE, 0x37);
    _MRM_DECLARE_STATUS(API_PERMISSION_DENIED, 0x38);
    _MRM_DECLARE_STATUS(UNSUPPORTED_PLATFORM, 0x39);

    _MRM_DECLARE_STATUS(TOO_MANY_RESOURCES, 0x50);
    _MRM_DECLARE_STATUS(NO_DEFAULT_OR_NEUTRAL_VALUE, 0x51);

    _MRM_DECLARE_STATUS(MANAGER_REQUIRED, 0x60);
    _MRM_DECLARE_STATUS(UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILES, 0x61);
    _MRM_DECLARE_STATUS(GET_PER_VIEW_SCALE_VALUE_FAILED, 0x62);
    _MRM_DECLARE_STATUS(SCHEMALESS_PRI_LOAD_FAILED, 0x63);
    _MRM_DECLARE_STATUS(MERGE_MISSING_SCHEMA, 0x64);
    _MRM_DECLARE_STATUS(MERGE_LOAD_FILE_FAILED, 0x65);
    _MRM_DECLARE_STATUS(MERGE_ADD_FILE_FAILED, 0x66);
    _MRM_DECLARE_STATUS(MERGE_WRITE_FILE_FAILED, 0x67);

    _MRM_DECLARE_STATUS(MULTIPLE_PACKAGE_FAMILIES_NOT_ALLOWED, 0x70);
    _MRM_DECLARE_STATUS(MULTIPLE_MAIN_PACKAGES_NOT_ALLOWED, 0x71);
    _MRM_DECLARE_STATUS(BUNDLE_PACKAGES_NOT_ALLOWED, 0x72);
    _MRM_DECLARE_STATUS(MAIN_PACKAGE_REQUIRED, 0x73);
    _MRM_DECLARE_STATUS(RESOURCE_PACKAGE_REQUIRED, 0x74);

#define _DEF_DECLARE_IBC_STATUS(NAME, INDEX) static const DEFRESULT E_DEF_##NAME = _DEF_MAKE_STATUS(_DEF_FACILITY_IBC, INDEX)

    _DEF_DECLARE_IBC_STATUS(XML_SCHEMA_VALIDATION_FAIL, 0x01);
    _DEF_DECLARE_IBC_STATUS(XML_NODE_NOT_FOUND, 0x02);
    _DEF_DECLARE_IBC_STATUS(XML_ATTRIB_NOT_FOUND, 0x03);

    _DEF_DECLARE_IBC_STATUS(PRICONFIG_MISSING_ATTRIB, 0x04);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_UKNOWN, 0x05);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_MULTIPLE_CONFIG, 0x06);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_NO_MAIN_PACKAGE, 0x07);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_EMPTY_PACKAGING, 0x08);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_PATH, 0x09);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_QUAL, 0x0a);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_ATTRIB_VALUE, 0x0b);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_PACKAGING_INVALID_OS, 0x0d);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_IDM_AM, 0x0e);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_IDM_WIN8, 0x0f);

    _DEF_DECLARE_IBC_STATUS(FSI_FILE_PATH_TOO_LONG, 0x10);
    _DEF_DECLARE_IBC_STATUS(FSI_UNSUPPORTED_DIR_TYPE, 0x11);
    _DEF_DECLARE_IBC_STATUS(FSI_INVALID_FILE_TYPE, 0x12);
    _DEF_DECLARE_IBC_STATUS(FSI_INVALID_DELIMITER, 0x13);
    _DEF_DECLARE_IBC_STATUS(FSI_INSTANTIATION_FAILED, 0x14);

    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_DUPLICATE, 0x15);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_MULTIPLE_OBJECTS, 0x16);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_MISSING_COMMA_BRACE, 0x17);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_MISSING_OBJECT_NAME, 0x18);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_MISSING_COLON, 0x19);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_INVALID_INPUTSTR, 0x1a);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_INVALID_CHAR, 0x1b);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_MISSING_ROOT_OBJ, 0x1c);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_INVALID_PROP_OBJ, 0x1d);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_INVALID_ITEM_TYPE, 0x1e);
    _DEF_DECLARE_IBC_STATUS(FSI_RESJSON_NODE_DEPTH_MAX_EXCEEDED, 0x1f);

    _DEF_DECLARE_IBC_STATUS(QUALAPPL_INVALID_QUALIFIER, 0x20); // -> ERROR_MRM_UNKNOWN_QUALIFIER (in DefStatus.cpp)
    _DEF_DECLARE_IBC_STATUS(QUALAPPL_INVALID_QUAL_FILENAME, 0x21);
    _DEF_DECLARE_IBC_STATUS(QUALAPPL_MISSING_DEFAULT_LANG, 0x22);

    _DEF_DECLARE_IBC_STATUS(IBC_INVALID_CANDIDATE, 0x23);
    _DEF_DECLARE_IBC_STATUS(IBC_INVALID_STATE, 0x24);

    _DEF_DECLARE_IBC_STATUS(IBC_CANDIDATE_NOT_EMBEDDED, 0x25);

    _DEF_DECLARE_IBC_STATUS(PRICONFIG_PACKAGING_INVALID_IDM, 0x26);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_MRT_ARP, 0x27);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_MRP_MULTIQUAL, 0x28);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_MRP_DUP_NAME, 0x29);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_MRP_DUP_QSI, 0x2a);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_MRP_DEFAULT, 0x2b);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_MRP_EMPTY, 0x2c);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_NON_ARP_QUALIFIER, 0x2d);

    _DEF_DECLARE_IBC_STATUS(INCOMPLETE_SCHEMA, 0x30);

    _DEF_DECLARE_IBC_STATUS(IBC_SCOPE_ITEM_CONFLICT, 0x31);
    _DEF_DECLARE_IBC_STATUS(IBC_CONFLICTING_VALUES, 0x32);

    _DEF_DECLARE_IBC_STATUS(QUALAPPL_VALUE_NOT_ALLOWED, 0x33);
    _DEF_DECLARE_IBC_STATUS(PRICONFIG_INVALID_ALLOWED_NODE, 0x34);

    _DEF_DECLARE_IBC_STATUS(FSI_SPECIAL_FILE_IGNORED, 0x35);
    _DEF_DECLARE_IBC_STATUS(INDEXER_SCHEMA_NOT_FOUND, 0x36);
    _DEF_DECLARE_IBC_STATUS(UNSUPPORTED_FILE_TYPE, 0x37);

#define _DEF_DECLARE_EXTENSIONS_STATUS(NAME, INDEX) \
    static const DEFRESULT E_MRMEXT_##NAME = _DEF_MAKE_STATUS(_DEF_FACILITY_EXTENSIONS, INDEX)

    // API set related
    _DEF_DECLARE_EXTENSIONS_STATUS(APISET_NOT_PRESENT, 0x00);
    _DEF_DECLARE_EXTENSIONS_STATUS(EXTENSION_NOT_SUPPORTED, 0x10);
    // Qualifier type related
    // -- offset 0x10: delegate qualifier type to client
    _DEF_DECLARE_EXTENSIONS_STATUS(QT_DELEGATE_TO_CLIENT, 0x10);
    // Qualifier value provider related
    // -- offset 0x20: delegate qualifier value provider to client
    _DEF_DECLARE_EXTENSIONS_STATUS(QVP_DELEGATE_TO_CLIENT, 0x20);

#ifdef __cplusplus
}
#endif
