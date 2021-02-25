# DWriteCore

DWriteCore is the Project Reunion version of DirectWrite, the text rendering and layout
component that ships in Windows. DWriteCore implements the same API as DirectWrite,
with a few additions described in this document. See the [DirectWrite documentation](https://docs.microsoft.com/en-us/windows/win32/api/_directwrite/)
for more information.

For an application that already uses DirectWrite, switching to DWriteCore requires minimal changes:

 - Add a reference to the Project Reunion package.
 - Include dwrite_core.h instead of dwrite_3.h.
 - Link to DWriteCore.lib instead of DWrite.lib.
 - Call DWriteCoreCreateFactory instead of DWriteCreateFactory.

In return, the application gets the benefits of Project Reunion, namely, access to the newest APIs
and functionality regardless of what version of Windows your customer is running.

# Background

The DWriteCore API is the same as the existing public DirectWrite API, with a few additions. These
additions should eventually be incorporated into the in-box DirectWrite as well, so it is appropriate
to think of the DWriteCore API as just the latest version of the DirectWrite API. This document focuses 
primarily on the additions.

## API Versioning

The DirectWrite API has grown over time, and many APIs have multiple versions: IDWriteFactory, 
IDWriteFactory1, IDWriteFactory2, etc. Prior to Windows 10, each new version got a new header file.
Starting in TH1, new APIs have been added to dwrite_3.h, but conditionalized based on NTDDI_VERSION.
API definitions in dwrite_3.h in the Windows SDK are conditionalized as follows:

```c++
#if NTDDI_VERSION >= NTDDI_WIN10_MN
    . . . APIs introduced in MN . . .
#endif // NTDDI_VERSION >= NTDDI_WIN10_MN
```

DWriteCore always implements the latest version of the API, so there needs to be a mechanism for an
application using DWriteCore to get access to all the latest APIs regardless of NTDDI_VERSION. The
copy of dwrite_3.h in the DWriteCore package therefore uses the following convention to conditinalize
API definitions:

```c++
#if DWRITE_CORE || NTDDI_VERSION >= NTDDI_WIN10_MN
    . . . APIs introduced in MN . . .
#endif // DWRITE_CORE || NTDDI_VERSION >= NTDDI_WIN10_MN

#if DWRITE_CORE
    . . . New APIs not yet in any in-box version of DWrite . . .
#endif // DWRITE_CORE
```

The DWriteCore NuGet package includes a header file named dwrite_core.h as well as the newest
versions of the existing DirectWrite header files (dwrite_3.h, dwrite_2.h, and dwrite_1.h, dwrite.h).
The dwrite_core.h simply defines the DWRITE_CORE preprocessor symbol and then includes dwrite_3.h.
In this way, an application that includes dwrite_core.h has access to all DirectWrite APIs regardless
of the NTDDI_VERSION.

## Cross-Platform Considerations

DWriteCore runs on non-Windows platforms in addition to the down-level Windows versions targetted by
Project Reunion. In order to compile cross-platform, it is necessary to have definitions of Windows types
and constants used by the DirectWrite API -- for example, IUnknown, HRESULT, etc. The DWriteCore project
has an “xplatwin” directory with a set of header files that contain portable definitions of these things, 
as well as mechanisms to avoid the use of compiler extensions like __declspec(uuid(x)) and __uuidof.

Another consideration on non-Windows platforms is the definition of WCHAR. Most projects define WCHAR as 
wchar_t which is a 32-bit type everywhere except Windows, but Office relies on WCHAR being 16 bits. 
Therefore, DWriteCore’s cross-platform headers defines WCHAR as either char16_t or wchar_t, depending on 
a preprocessor definition, and we build both 16-bit and 32-bit flavors.

This is outside the scope of the API itself, but is mentioned here because other cross-platform libraries 
will have to solve the same problem, and if each library solves the problem in its own way, we may end up
with interoperability issues.

# Description

New APIs introduced by DWriteCore include:

 - The exported function is renamed `DWriteCoreCreateFactory` to avoid a naming collision with the
   `DWriteCreateFactory` function exported by the Windows DLL (DWrite.dll).
 - A new DWRITE_FACTORY_TYPE enumeration for creating an isolated factory object
 - A new method for getting pixel data from a bitmap render target

The new DWRITE_FACTORY_TYPE_ISOLATED2 enum value complements the existing factory types. It is similar to
DWRITE_FACTORY_TYPE_ISOLATED, but is more locked down in two ways. First, it only caches data in-process, and
will not attempt to either read from or write to a cross-process font cache or persisted cache file. Second,
a restricted factory only enumerates well-known fonts in the system font collection. The well-known-fonts
restriction enables DWriteCore to efficiently construct the system font collection without depending on a
cross-process or persistent cache. An example use case for the new factory type would be a web browser
rendering process with very limited permissions.

A _bitmap render target_ (IDWriteBitmapRenderTarget) is an API object that encapsulates a system memory bitmap
and enables rendering glyphs to the bitmap. On Windows, the object encapsulates a GDI memory DC with a GDI
device-dependent bitmap (DIB) selected into it. However, on non-Windows platforms, there is no GDI DC,
and the bitmap is just a system memory array. DWriteCore introduces a new version of the bitmap render target
interface that an application can use to access the bitmap data without going through GDI.

# Examples

## Creating an isolated factory

An application calls the DWriteCoreCreateFactory function to create a factory object, which is the entry-point 
to all other DirectWrite APIs. An application can specify the new DWRITE_FACTORY_TYPE_ISOLATED2 enum value if it 
wants to minimize interaction between DirectWriteCore and the host system. Specifically, the resulting factory only 
caches data in-process. It neither reads from nor writes to a cross-process cache (e.g., a font cache process) or 
persistent cache (i.e., a file). In addition, the resulting factory's sysetm font collection only includes 
well-known system fonts.

The following example creates an isolated factory.

```c++
ComPtr<IDWriteFactory7> spFactory;
HRESULT hr = DWriteCoreCreateFactory(
    DWRITE_FACTORY_TYPE_ISOLATED2,
    __uuidof(IDWriteFactory7),
    (IUnknown**)&spFactory
    );
```

## Drawing glyphs to a system memory bitmap

An application creates a bitmap render target by calling [IDWriteGdiInterop::CreateBitmapRenderTarget](https://docs.microsoft.com/en-us/windows/win32/api/dwrite/nf-dwrite-idwritegdiinterop-createbitmaprendertarget).
A bitmap render target encapsulates a bitmap in system memory, and enables rendering glyphs to the bitmap. On Windows,
the bitmap is actually a GDI DIB selected into a memory HDC, and it is possible to get the bitmap pixels using GDI
functions. However, DWriteCore introduces a simpler method through the new IDWriteBitmapRenderTarget2 interface.
The following example shows both the old way and the new way.

```c++
DWRITE_BITMAP_DATA_BGRA32 TextRenderer::GetBitmapData(_In_ IDWriteBitmapRenderTarget* renderTarget)
{
    DWRITE_BITMAP_DATA_BGRA32 result = {};

    // Query the bitmap render target for the new interface.
    ComPtr<IDWriteBitmapRenderTarget2> renderTarget2;
    HRESULT hr = renderTarget->QueryInterface(&renderTarget2);
    if (SUCCEEDED(hr))
    {
        // IDWriteBitmapRenderTarget2 exists, so we can get the bitmap the easy way.
        hr = renderTarget2->GetBitmapData(&result);
        if (FAILED(hr))
        {
            throw Exception{ hr };
        }
    }
    else
    {
        // We're using an older version that doesn't implement IDWriteBitmapRenderTarget2,
        // so we have to get the bitmap by going through GDI. First get the bitmap handle.
        HDC hdc = renderTarget->GetMemoryDC();
        HGDIOBJ dibHandle = GetCurrentObject(hdc, OBJ_BITMAP);
        if (dibHandle == nullptr)
        {
            throw Exception{ HRESULT_FROM_WIN32(GetLastError()) };
        }

        // Call a GDI function to fill in the DIBSECTION structure for the bitmap.
        DIBSECTION dib;
        if (GetObjectW(dibHandle, sizeof(dib), &dib) != sizeof(dib))
        {
            throw Exception{ HRESULT_FROM_WIN32(GetLastError()) };
        }

        result.width = dib.dsBm.bmWidth;
        result.height = 0u - dib.dsBm.bmHeight; // bmHeight is negative for top-down DIB
        result.pixels = static_cast<uint32_t*>(dib.dsBm.bmBits);
    }

    return result;
}
```

# API Details

```c++
/// <summary>
/// Specifies the type of DirectWrite factory object.
/// DirectWrite factory contains internal state such as font loader registration and cached font data.
/// In most cases it is recommended to use the shared factory object, because it allows multiple components
/// that use DirectWrite to share internal DirectWrite state and reduce memory usage.
/// However, there are cases when it is desirable to reduce the impact of a component,
/// such as a plug-in from an untrusted source, on the rest of the process by sandboxing and isolating it
/// from the rest of the process components. In such cases, it is recommended to use an isolated factory 
/// for the sandboxed component.
/// </summary>
enum DWRITE_FACTORY_TYPE
{
    /// <summary>
    /// This is the recommended value in most cases. The shared factory is a singleton, so mulitiple
    /// components in a process that create a shared factory share a single instance. This enables
    /// reuse of cached font data and other state across multiple components. In addition, objects
    /// created from a shared factory can read from and/or modify a cross-process or persistent cache.
    /// </summary>
    DWRITE_FACTORY_TYPE_SHARED,

    /// <summary>
    /// Objects created from an isolated factory do not modify internal state or cached data used by
    /// objects from other factories. However, they may still read from a cross-process or persistent
    /// cache.
    /// </summary>
    DWRITE_FACTORY_TYPE_ISOLATED,

#if DWRITE_CORE
    /// <summary>
    /// Objects created from an "isolated2" factory do not use or modify internal state or cached data
    /// used by other factories. In addition, the system font collection contains only well-known fonts.
    /// </summary>
    // Warning: Make sure any additional new enum values are consistent between different versions of
    // this header in DWriteCore and the Windows SDK.
    DWRITE_FACTORY_TYPE_ISOLATED2
#endif // DWRITE_CORE
};
```

```c++
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
```

```c++
#if DWRITE_CORE

/// <summary>
/// Contains information about a bitmap associated with an IDWriteBitmapRenderTarget.
/// The bitmap is top-down with 32-bits per pixel and no padding between scan lines.
/// </summary>
struct DWRITE_BITMAP_DATA_BGRA32
{
    UINT32 width;
    UINT32 height;
    _Field_size_(width * height) UINT32* pixels;
};

/// <summary>
/// Encapsulates a bitmap which can be used for rendering glyphs.
/// </summary>
DWRITE_BEGIN_INTERFACE(IDWriteBitmapRenderTarget2, "C553A742-FC01-44DA-A66E-B8B9ED6C3995") : IDWriteBitmapRenderTarget1
{
    /// <summary>
    /// Gets the demensions and a pointer to the system memory bitmap encapsulated by this
    /// bitmap render target object. The pointer is owned by the render target object, and
    /// remains valid as long as the object exists.
    /// </summary>
    STDMETHOD(GetBitmapData)(_Out_ DWRITE_BITMAP_DATA_BGRA32* bitmapData) PURE;
};
#endif // DWRITE_CORE
```
