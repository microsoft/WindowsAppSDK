Zero-copy access to embedded MRT resource data
===

# Background

MRT Core ("Modern Resource Technology") lets an app read the resources embedded in its compiled
`.pri` file. At runtime the `.pri` is memory-mapped read-only, so the bytes of an embedded/binary
resource already live in memory that the resource manager owns and keeps alive.

Both of the existing ways to read an embedded resource copy those bytes anyway:

* The WinRT accessor
  [`ResourceCandidate.ValueAsBytes`](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applicationmodel.resources.resourcecandidate.valueasbytes)
  returns a `byte[]`. Marshaling a `byte[]` across the WinRT ABI copies the whole blob on **every**
  call.
* The flat-C loaders
  ([`MrmLoadStringOrEmbeddedResource`](https://learn.microsoft.com/windows/windows-app-sdk/api/win32/mrm/nf-mrm-mrmloadstringorembeddedresource)
  and [`MrmLoadStringOrEmbeddedResourceByIndex`](https://learn.microsoft.com/windows/windows-app-sdk/api/win32/mrm/nf-mrm-mrmloadstringorembeddedresourcebyindex),
  declared in `MRM.h`) hand back an `MrmResourceData` whose `data` pointer is **always** a freshly
  heap-allocated copy of the mapped bytes, so that the returned buffer can outlive the resource manager.

For large embedded resources (images, XBF, fonts, ML models) this per-read allocate-and-copy shows
up in both working set and CPU. This spec adds **additive, opt-in, zero-copy** accessors on both
API sets that hand out a non-owning view directly over the memory-mapped `.pri`, while leaving the
existing copying APIs and their ABI untouched.

The defining constraint of these new APIs is **lifetime**. The WinRT buffer and its references retain
the backing resource data in memory and manage its lifetime. For the flat-C APIs, the view borrows
memory owned by the resource manager, so the caller of the flat-C APIs must keep the resource manager
alive for as long as it reads the view, and these callers must release the memory with `MrmFreeResourceData`
when done.

This spec covers two API sets:

1. WinRT: `Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate.ValueAsMemoryBuffer()`.
2. Flat-C (`MRM.h`): `MrmResourceData2`, the `*AsView` loader variants, and `MrmFreeResourceData`.

# Examples

## Read an embedded resource without copying (C#)

`ValueAsMemoryBuffer()` returns a read-only
[`IMemoryBuffer`](https://learn.microsoft.com/uwp/api/windows.foundation.imemorybuffer). Create a
reference from it, access the bytes through C#/WinRT's
`WindowsRuntimeMarshal.TryGetDataUnsafe`, and dispose both when finished.

```c#
using Microsoft.Windows.ApplicationModel.Resources;
using System;

unsafe void ReadEmbeddedResource(ResourceCandidate candidate)
{
    // Only valid for embedded/binary resources; ValueAsMemoryBuffer() throws otherwise.
    if (candidate.Kind != ResourceCandidateKind.EmbeddedData)
    {
        throw new ArgumentException("The candidate must contain embedded data.", nameof(candidate));
    }

    using var buffer = candidate.ValueAsMemoryBuffer();
    using var reference = buffer.CreateReference();

    if (WindowsRuntime.WindowsRuntimeMarshal.TryGetDataUnsafe(
            reference, out IntPtr data, out uint capacity))
    {
        // 'data'/'capacity' are valid only while 'reference' is alive and not disposed.
        var span = new ReadOnlySpan<byte>((byte*)data, (int)capacity);
        Process(span);
    }
}
```

## Read an embedded resource without copying (C++/WinRT)

```cpp
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>

using namespace winrt::Microsoft::Windows::ApplicationModel::Resources;

void ReadEmbeddedResource(ResourceCandidate const& candidate)
{
    // Only valid for embedded/binary resources; ValueAsMemoryBuffer() throws otherwise.
    if (candidate.Kind() != ResourceCandidateKind::EmbeddedData)
    {
        return;
    }

    auto buffer = candidate.ValueAsMemoryBuffer();
    auto reference = buffer.CreateReference();

    Process(reference.data(), reference.Capacity());
    // The destructors close the reference and buffer at scope exit.
}
```

## Read an embedded resource without copying (flat-C)

```cpp
MrmResourceData2 data{};
if (SUCCEEDED(MrmLoadStringOrEmbeddedResourceAsView(
        resourceManager, nullptr, nullptr, L"Files/Logo.png",
        &resourceType, &resourceString, &data)))
{
    if (resourceType == MrmType_Embedded)
    {
        // data.data points directly into the mapped .pri when data.isView is nonzero.
        // Keep 'resourceManager' alive while you read it.
        Process(static_cast<const BYTE*>(data.data), data.size);
    }

    // Safe whether the load produced a view or an owned buffer.
    MrmFreeResourceData(&data);
}
```

# API Pages

## ResourceCandidate.ValueAsMemoryBuffer method

Returns the bytes of an embedded (binary) resource as a read-only
[`IMemoryBuffer`](https://learn.microsoft.com/uwp/api/windows.foundation.imemorybuffer), **without
copying** them.

```c#
public Windows.Foundation.IMemoryBuffer ValueAsMemoryBuffer();
```

Use this in place of
[`ValueAsBytes`](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applicationmodel.resources.resourcecandidate.valueasbytes)
when you want to access an embedded resource's bytes directly, without a copy. `ValueAsBytes` creates
a new `byte[]` copy on every call; `ValueAsMemoryBuffer` instead projects the resource's bytes directly
from the memory-mapped `.pri`.

The returned `IMemoryBuffer` (and every
[`IMemoryBufferReference`](https://learn.microsoft.com/uwp/api/windows.foundation.imemorybufferreference)
you create from it) is **read-only**, and retains the resource data in memory until the last buffer or
reference is closed or destroyed. You can access the raw pointer by querying the reference for
[`IMemoryBufferByteAccess`](https://learn.microsoft.com/windows/win32/winrt/imemorybufferbyteaccess). In
C++/WinRT, you can use the `data()` and `Capacity()` helpers added on the reference by C++/WinRT. In C#/WinRT,
you can use `WindowsRuntimeMarshal.TryGetDataUnsafe()`.

### Remarks

* This method is only valid for candidates whose
  [`Kind`](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applicationmodel.resources.resourcecandidate.kind)
  is `EmbeddedData`. For any other kind it throws `HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH)`
  (`0x80073B0D`), matching the behavior of `ValueAsBytes` on non-embedded candidates. The
  `ValueAsBytes` documentation should also state this restriction.
* **Lifetime.** The pointer accessed via the `IMemoryBufferReference` is valid only while the
  `IMemoryBufferReference` it came from is alive and has not been closed. Keep both the buffer and the
  reference alive for the entire time you read the bytes, and `Close`/`Dispose` them (or use a `using`
  / `winrt` scope) when you are done to ensure the underlying memory can be released promptly.
  Explicit `Close`/`Dispose` is not strictly required, as releasing all references to the buffer and
  reference also releases the backing memory, though possibly later (for managed callers, whenever the GC
  finalizes them). After the reference is
  closed, `GetBuffer` returns `RO_E_CLOSED` (`0x80000013`) and the reported capacity is `0`.
* Each call creates a fresh `IMemoryBuffer`; this is a method, not a property, because each returned
  object owns an independent
  [`IClosable`](https://learn.microsoft.com/uwp/api/windows.foundation.iclosable) lifetime.
* The buffer is a **view**, so writing through it is not supported; treat the bytes as read-only.
* This API does not change `ValueAsBytes`. If you need a standalone, caller-owned `byte[]` (such
  as to retain past the resource manager's lifetime), use `ValueAsBytes`.

## Other MRT Core (flat-C) additions

These additions to `MRM.h` are the flat-C counterpart of `ValueAsMemoryBuffer`. They let native
callers of the `Mrm*` loader functions opt into the same zero-copy view.

| Name | Description |
|-|-|
| `MrmResourceData2` | Versioned extension of `MrmResourceData` that adds an `isView` discriminator. Used only by the `*AsView` loaders and `MrmFreeResourceData`. |
| `MrmLoadStringOrEmbeddedResourceAsView` | Like `MrmLoadStringOrEmbeddedResource`, but for embedded resources may return `data` as a non-owning view (`isView` is nonzero) into the mapped `.pri` instead of a heap copy. |
| `MrmLoadStringOrEmbeddedResourceByIndexAsView` | The by-index counterpart of the above. |
| `MrmFreeResourceData` | Releases an `MrmResourceData2` produced by an `*AsView` loader. Frees the buffer when it is owned; a no-op that just clears the descriptor when it is a view. |

### MrmResourceData2 structure

```c
struct MrmResourceData2
{
    UINT32 size;
    void*  data;
    BOOL   isView;
};
```

`MrmResourceData2` mirrors the leading `size`/`data` members of the pre-existing `MrmResourceData`
and adds `isView`:

* When `isView` is nonzero, `data` is a non-owning pointer directly into the memory-mapped, read-only
  `.pri` owned by the resource manager. You must keep that resource manager alive for as long as you
  use `data`.
* When `isView` is zero, `data` is a heap allocation owned by you.

Always release the descriptor with `MrmFreeResourceData`; do not pass `data` to `MrmFreeResource`.
`MrmFreeResourceData` handles both views and owned buffers.

`MrmResourceData` itself is unchanged; only the `*AsView` loaders and `MrmFreeResourceData` use
`MrmResourceData2`. See the Appendix for why the state lives on a separate struct.

### MrmLoadStringOrEmbeddedResourceAsView

```c
STDAPI MrmLoadStringOrEmbeddedResourceAsView(
    _In_ MrmManagerHandle  resourceManager,
    _In_opt_ MrmContextHandle  resourceContext,
    _In_opt_ MrmMapHandle      resourceMap,
    _In_ PCWSTR                resourceId,
    _Out_ MrmType*             resourceType,
    _Outptr_result_maybenull_ PWSTR* resourceString, // set for string/path resources
    _Out_ MrmResourceData2*    data);                // set for embedded resources
```

Loads the resource named by `resourceId`. Behaves exactly like `MrmLoadStringOrEmbeddedResource`
except that, for an embedded/binary resource whose bytes are stored directly in the mapped `.pri`,
`data` is returned as a view (`isView` is nonzero) with no allocation or copy. String and path
resources are unaffected: they are returned through `resourceString` with `data` cleared and
`isView` zero, exactly as with the copying variant.

Not every embedded resource can be returned as a view. If the resource was materialized into its own buffer by
the loader (for example a compressed resource that had to be decompressed), the function transparently
falls back to returning an **owned** buffer (`isView` is zero). Callers therefore must not assume `isView`
is nonzero for embedded resources. `MrmFreeResourceData` handles both cases.

Always release `data` with `MrmFreeResourceData`, and free `resourceString` with
`MrmFreeResource` when done. While `isView` is nonzero, keep `resourceManager` alive for as long
as you use `data`.

### MrmLoadStringOrEmbeddedResourceByIndexAsView

```c
STDAPI MrmLoadStringOrEmbeddedResourceByIndexAsView(
    _In_ MrmManagerHandle  resourceManager,
    _In_opt_ MrmContextHandle  resourceContext,
    _In_opt_ MrmMapHandle      resourceMap,
    _In_ UINT32                index,
    _Out_ MrmType*             resourceType,
    _Outptr_ PWSTR*            resourceName,   // receives the resource's name
    _Outptr_result_maybenull_ PWSTR* resourceString, // set for string/path resources
    _Out_ MrmResourceData2*    data);          // set for embedded resources
```

Loads the resource at `index` within `resourceMap` (walk a map by index together with
`MrmGetResourceCount`) and additionally returns the resolved resource name through `resourceName`.
Behaves exactly like `MrmLoadStringOrEmbeddedResourceByIndex` except that, for an embedded/binary
resource whose bytes are stored directly in the mapped `.pri`, `data` is returned as a view
(`isView` is nonzero) with no allocation or copy. String and path resources are unaffected: they are
returned through `resourceString` with `data` cleared and `isView` zero, exactly as with the copying
variant.

Not every embedded resource can be returned as a view. If the resource was materialized into its own buffer by
the loader (for example a compressed resource that had to be decompressed), the function transparently
falls back to returning an **owned** buffer (`isView` is zero) so the pointer can never dangle.
Callers therefore must not assume `isView` is nonzero for embedded resources. `MrmFreeResourceData` handles
both cases.

Always release `data` with `MrmFreeResourceData`, and free `resourceName` and `resourceString` with
`MrmFreeResource` when done. While `isView` is nonzero, keep `resourceManager` alive for as long
as you use `data`.

### MrmFreeResourceData

```c
STDAPI_(void) MrmFreeResourceData(_Inout_opt_ MrmResourceData2* data);
```

Releases an `MrmResourceData2` produced by an `*AsView` loader and clears the descriptor
(`data`/`size`/`isView` reset). If the descriptor is an owned buffer it is freed; if it is a view the
call is a no-op beyond clearing the descriptor. `data` may be `NULL`, and calling it again on an
already-cleared descriptor is safe.

Results of the existing copying loaders remain `MrmResourceData` and continue to be freed with
`MrmFreeResource(data.data)` as before.

# API Details

## WinRT (MIDL3)

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.Resources
{
    [contractversion(3)]
    apicontract MrtCoreContract{};

    [contract(MrtCoreContract, 1)]
    runtimeclass ResourceCandidate
    {
        ResourceCandidate(ResourceCandidateKind kind, String data);
        ResourceCandidate(byte[] data);

        String ValueAsString { get; };
        byte[] ValueAsBytes { get; };
        ResourceCandidateKind Kind { get; };

        /// Zero-copy accessor for embedded/binary resources: returns a read-only IMemoryBuffer that
        /// projects the resource bytes directly (no copy). The buffer (and any reference created
        /// from it) retains the backing resource data for its lifetime; Close it when done. Throws
        /// for Kind != EmbeddedData. Prefer this over ValueAsBytes to avoid a per-call copy.
        [contract(MrtCoreContract, 3)]
        Windows.Foundation.IMemoryBuffer ValueAsMemoryBuffer();

        IMapView<String, String> QualifierValues { get; };
    }
}
```

## Flat-C (MRM.h)

```c
    // Frozen, pre-existing ABI - unchanged.
    struct MrmResourceData
    {
        UINT32 size;
        void* data;
    };

    // New: versioned extension used only by the *AsView loaders and MrmFreeResourceData.
    struct MrmResourceData2
    {
        UINT32 size;
        void* data;
        BOOL isView;
    };

    STDAPI MrmLoadStringOrEmbeddedResourceAsView(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        _In_ PCWSTR resourceId,
        _Out_ MrmType* resourceType,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData2* data);

    STDAPI MrmLoadStringOrEmbeddedResourceByIndexAsView(
        _In_ MrmManagerHandle resourceManager,
        _In_opt_ MrmContextHandle resourceContext,
        _In_opt_ MrmMapHandle resourceMap,
        UINT32 index,
        _Out_ MrmType* resourceType,
        _Outptr_ PWSTR* resourceName,
        _Outptr_result_maybenull_ PWSTR* resourceString,
        _Out_ MrmResourceData2* data);

    STDAPI_(void) MrmFreeResourceData(_Inout_opt_ MrmResourceData2* data);
```

# Appendix

## Lifetime and safety model

* **WinRT.** The lifetime chain is
  `IMemoryBufferReference` → `IMemoryBuffer` → `ResourceCandidate` → `ResourceManager` → file mapping.
  A created reference holds its own strong reference to the candidate, so the borrowed bytes remain
  valid until the reference is closed or released, even if the parent `IMemoryBuffer` is released
  first. Closing the reference (or letting the GC finalize it) releases the backing memory.
* **Flat-C.** A view (`isView` is nonzero) borrows the resource manager's mapping; the caller is
  responsible for keeping `resourceManager` alive while the view is in use. The loader only returns a
  view when the blob is a direct reference into the mapping; any loader-owned buffer (for example a
  decompressed blob) is returned as an owned allocation so the pointer cannot dangle.

## Why `MrmResourceData2` instead of adding a field to `MrmResourceData`

`MRM.h` ships in the SDK's public include folder, so `MrmResourceData` is a frozen ABI. Appending a
field to it is a binary-breaking change: an app compiled against the old (smaller) struct running
against a newer binary would have `isView` written past the end of its allocation.

To stay compatible in both directions, the new `isView` state lives on a **separate, versioned
struct** (`MrmResourceData2`) that duplicates the leading `size`/`data` members (the same pattern as
`WNDCLASSEX` / `MEMORYSTATUSEX`). Only the additive `*AsView` exports and `MrmFreeResourceData` use
the larger struct, so no legacy caller ever sees the larger size, and `MrmResourceData`'s layout is
unchanged. `isView` is typed `BOOL` (not C++ `bool`) to be consistent with the `extern "C"` in the
header.

## Why `IMemoryBuffer` for the WinRT accessor

`IMemoryBuffer` is the modern WinRT primitive for sharing raw memory across the ABI without copying,
and its `IClosable` contract gives callers a deterministic way to release the backing memory. Alternatives such
as returning `IBuffer`, a stream, or a `CopyTo(...)` sink were rejected because they either reintroduce
a copy or lack a deterministic release of the borrowed mapping.
