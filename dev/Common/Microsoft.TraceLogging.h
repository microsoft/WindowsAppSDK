// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSOFT_TRACELOGGING_H
#define __MICROSOFT_TRACELOGGING_H

#define Microsoft_TraceLogging_Std_String(_s_, _name_) \
    TraceLoggingCountedString(_s_.c_str(), static_cast<ULONG>(_s_.size()), _name_)

#define Microsoft_TraceLogging_Std_WString(_s_, _name_) \
    TraceLoggingCountedWideString(_s_.c_str(), static_cast<ULONG>(_s_.size()), _name_)

#define Microsoft_TraceLogging_Std_StringView(_sv_, _name_) \
    TraceLoggingCountedString(_sv_.empty() ? "" : _sv_.data(), static_cast<ULONG>(_sv_.size()), _name_)

#define Microsoft_TraceLogging_Std_WStringView(_sv_, _name_) \
    TraceLoggingCountedWideString(_sv_.empty() ? "" : _sv_.data(), static_cast<ULONG>(_sv_.size()), _name_)

#endif // __MICROSOFT_TRACELOGGING_H
