// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(__LOGGING_H)
#define __LOGGING_H

#include <Windows.h>
#include <source_location>
#include <sstream>

namespace Common::Logging
{

    // use std::format in msg parameter to have a printf like varargs syntax for the debug message
    inline void DebugLog(const wchar_t* msg,  const std::source_location location = std::source_location::current())
    {
        
        std::wstringstream filename ;
        filename << location.file_name(); // converting char to wstring (and wchar_t implicitly)
        // format is "foo.cpp (66) : debug message"
        const std::wstring printmsg = std::format(L"{} ({}) : {}\n", filename.str(), location.line(), msg);
        OutputDebugStringW(printmsg.c_str());
    }

    inline void DebugLog(const std::wstring& msg, const std::source_location location = std::source_location::current())
    {
        DebugLog(msg.c_str(), location);
    }
}

#endif