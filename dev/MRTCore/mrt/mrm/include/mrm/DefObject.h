// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{

using namespace std;

const nothrow_t nothrow;

class DefObject
{
public:
    static void* operator new(size_t size)
    {
        void* p = _DefPlatformAllocZeroed(size);
        return p;
    }

    static void* operator new(size_t, void* p) { return p; }

    static void* operator new(size_t size, const struct nothrow_t&) { return _DefPlatformAllocZeroed(size); }

    static void* operator new[](size_t size)
    {
        void* p = _DefPlatformAllocZeroed(size);
        return p;
    }

    static void* operator new[](size_t size, const nothrow_t&) { return _DefPlatformAllocZeroed(size); }

    static void __cdecl operator delete(_In_opt_ void* p)
    {
        // delete must be safe, but we can't assume our platform
        // handles free(NULL)
        if (p)
        {
            _DefPlatformFree(p);
        }
    }

    static void operator delete(_In_opt_ void* p, const nothrow_t&)
    {
        if (p)
        {
            _DefPlatformFree(p);
        }
    }

    static void operator delete[](_In_opt_ void* p)
    {
        if (p)
        {
            _DefPlatformFree(p);
        }
    }

    static void operator delete[](_In_opt_ void* p, const nothrow_t&)
    {
        if (p)
        {
            _DefPlatformFree(p);
        }
    }

    DefObject() {}
    ~DefObject() {}
};

} // namespace Microsoft::Resources