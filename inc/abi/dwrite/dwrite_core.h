//+--------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  Abstract:
//     DirectX Typography Services public API definitions.
//
//----------------------------------------------------------------------------

#ifndef DWRITE_CORE_H_INCLUDED
#define DWRITE_CORE_H_INCLUDED
#pragma once

#define DWRITE_CORE 1
#include "dwrite_3.h"

/// <summary>
/// Specifies the data type of a parameter passed to
/// IDWriteEventSink::LogEvent.
/// </summary>
enum DWRITE_EVENT_PARAM_TYPE : INT32
{
    /// <summary>
    /// An event tag, which is a UINT64 value encoding up to eight ASCII characters
    /// in little-endian order.
    /// </summary>
    DWRITE_EVENT_PARAM_TYPE_TAG,

    /// <summary>
    /// 32-bit unsigned value.
    /// </summary>
    DWRITE_EVENT_PARAM_TYPE_UINT32,

    /// <summary>
    /// Time in system clock ticks as reported by std::chrono::system_clock.
    /// </summary>
    DWRITE_EVENT_PARAM_TYPE_DATETIME,

    /// <summary>
    /// Null-terminated string of WCHAR.
    /// </summary>
    DWRITE_EVENT_PARAM_TYPE_STRINGW,

    /// <summary>
    /// Null-terminated UTF-8 string.
    /// </summary>
    DWRITE_EVENT_PARAM_TYPE_STRINGA
};

/// <summary>
/// Represents a parameter passed to IDWriteEventSink::LogEvent.
/// </summary>
struct DWRITE_EVENT_PARAM
{
    DWRITE_EVENT_PARAM_TYPE paramType;

    union DWRITE_EVENT_PARAM_VALUE
    {
        UINT64 tag;                         // DWRITE_EVENT_PARAM_TYPE_TAG
        UINT32 uint32;                      // DWRITE_EVENT_PARAM_TYPE_UINT32
        UINT64 dateTime;                    // DWRITE_EVENT_PARAM_TYPE_DATETIME
        _Field_z_ WCHAR const* stringW;     // DWRITE_EVENT_PARAM_TYPE_STRINGW
        _Field_z_ char const* stringA;      // DWRITE_EVENT_PARAM_TYPE_STRINGA
    } paramValue;
};

/// <summary>
/// Callback interface that receives internal events from DWriteCore.
/// </summary>
/// <remarks>
/// Events sent to this interface should be used for diagnostic purposes only,
/// they may change from version to version.
/// 
/// Each type of event is idenfied by a "tag" comprising up to 8 ASCII characters
/// encoded as a UINT64. The first character of the tag is in the low-order byte.
/// Following are some well-known event tags and the expected parameters for each.
/// 
///     "state" (TAG newState) ...
///         Indicates an object is transitioning to the state specified by newState.
///         Common states are "ctor" for a new object and "dtor" for a destroyed
///         object.
/// 
///     "error" (UINT32 errorCode) (TAG taskID) (UINT32 lineNumber) ...
///     
///     "warning" (STRINGA message) (UINT32 lineNumber)?
/// 
///     "badfont" (STRINGA message)
/// 
///     "assert" (STRINGA fileName) (UINT32 lineNumber) (STRINGA expression)
/// 
/// </remarks>
DWRITE_BEGIN_INTERFACE(IDWriteEventSink, "b2839dc9-5419-4223-a069-c792d2dc6ba0") : IUnknown
{
    /// <summary>
    /// Notifies the event sink of an internal DWriteCore event.
    /// </summary>
    /// <param name="objectId">Unique integer ID of the object that logged the
    /// event, or zero if the event did not come from a specific object.</param>
    /// <param name="classTag">Event tag identifying the type of object that
    /// logged the event, or zero if the event did not come from a specific
    /// object.</param>
    /// <param name="eventTag">Event tag identifying the type of event.</param>
    /// <param name="eventParams">Array of additional event parameters.</param>
    /// <param name="eventParamCount">Number of additional event parameters.</param>
    STDMETHOD_(void, LogEvent)(
        UINT32 objectId,
        UINT64 classTag,
        UINT64 eventTag,
        _In_reads_(eventParamCount) DWRITE_EVENT_PARAM const* eventParams,
        UINT32 eventParamCount
        ) PURE;
};

/// <summary>
/// Creates a factory object that is used for subsequent creation of individual DWriteCore objects.
/// </summary>
/// <param name="factoryType">Identifies whether the factory object will be shared or isolated.</param>
/// <param name="iid">Identifies the DirectWrite factory interface, such as UUIDOF(IDWriteFactory).</param>
/// <param name="factory">Receives the DirectWrite factory object.</param>
/// <returns>
/// Standard HRESULT error code.
/// </returns>
/// <remarks>
/// This is functionally the same as the DWriteCreateFactory function exported by the system version
/// of DirectWrite. The DWriteCore function has a different name to avoid ambiguity.
/// </remarks>
EXTERN_C HRESULT DWRITE_EXPORT DWriteCoreCreateFactory(
    _In_ DWRITE_FACTORY_TYPE factoryType,
    _In_ REFIID iid,
    _COM_Outptr_ IUnknown** factory
);

/// <summary>
/// Registers an object that receives internal DWriteCore events.
/// </summary>
/// <param name="eventSink">Event sink object to register.</param>
/// <returns>Standard HRESULT error code.</returns>
/// <remarks>This method does NOT add a reference to the event sink object.
/// The caller is expected to hold a reference to the event sink object until
/// it later unregisters it by calling DWriteUnregisterEventSink.</remarks>
EXTERN_C HRESULT DWRITE_EXPORT DWriteCoreRegisterEventSink(
    IDWriteEventSink* eventSink
);

/// <summary>
/// Unregisters an event sink object that was previously registered
/// using DWriteCoreRegisterEventSink.
/// </summary>
/// <param name="eventSink">Event sink object to unregister.</param>
/// </remarks>Since DWriteCore does not hold a reference to the event sink, this 
/// call can be made by the event sink object's destructor.</remarks>
EXTERN_C void DWRITE_EXPORT DWriteCoreUnregisterEventSink(
    IDWriteEventSink* eventSink
);

#endif // DWRITE_CORE_H_INCLUDED
