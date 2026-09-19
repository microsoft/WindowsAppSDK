// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
//
// MsixDynamicDependency.js for NodeJS
//
// Uses koffi (https://koffi.dev) to call the Windows Dynamic Dependency Win32 APIs.
//
// JavaScript has no `out` parameters so APIs with return a result object,
// e.g. { hr, packageDependencyId } where `hr` is the raw HRESULT (>= 0 means success).
//
// Requires 64-bit Node on Windows and koffi => npm install koffi

// Dynamic Dependency API surface
// • PackageFamilyName.Verify(pfn)
// • PackageDependency.TryCreate / TryCreate2 / Delete / Add / Add2 / Remove / GetResolvedPackageFullName / GetResolvedPackageFullName2 / GetIdForContext / Find / GetInfo / GetProcesses / IsSupported
// • PackageGraph.RevisionId
// • Enums: CreatePackageDependencyOptions, PackageDependencyLifetimeKind, AddPackageDependencyOptions(2), PackageDependencyProcessorArchitectures, Rank
// • Helpers: PackageVersion.pack/unpack, succeeded/failed/throwIfFailed
//
// Usage:
//   const dd = require('./MsixDynamicDependency');
//   const { hr, packageDependencyId } = dd.PackageDependency.TryCreate({
//     packageFamilyName: 'Microsoft.VCLibs.140.00.UWPDesktop_8wekyb3d8bbwe',
//     minVersion: dd.PackageVersion.pack(14),
//   });

// Key koffi techniques used (each verified experimentally):
//
// • koffi.disposable('HeapPWSTR','str16', freeHeap) - auto-decodes callee-allocated PWSTR out-params to JS strings and auto- HeapFree's them (matches the C# Marshal.PtrToStringUni + HeapFree).
// • Named opaque pointers (DdOpaque*) for PACKAGEDEPENDENCY_CONTEXT /array bases, because raw void** outputs come back as un-re-decodable addresses.
// • koffi.decode(base, koffi.array('str16'|'uint32', count)) for the Find / GetProcesses arrays.
// • FILETIME ? Date conversion; _In_ FILETIME* for TryCreate2, _Out_ FILETIME* for GetInfo.

// Verified lifecycle (real Microsoft.VCLibs... framework pkg):
//   TryCreate -> GetInfo -> Find -> Add -> GetIdForContext -> GetProcesses -> Remove -> Delete -> TryCreate2
// All return hr == 0.
//
// Run node MsixDynamicDependency.js for a built-in smoke test.

'use strict';

const koffi = require('koffi');

// ---------------------------------------------------------------------------
// Native libraries
// ---------------------------------------------------------------------------

const kernelbase = koffi.load('kernelbase.dll');
const kernel32 = koffi.load('kernel32.dll');

// ---------------------------------------------------------------------------
// Native types
//
// koffi represents callee-allocated `void*` output values as raw addresses that
// cannot be safely re-decoded. To get usable pointers we model them as pointers
// to a named opaque type; koffi then hands back real (external) pointer handles.
// ---------------------------------------------------------------------------

// Generic opaque byte target; DdOpaque* behaves like a usable void*/PWSTR/HANDLE.
const DdOpaque = koffi.opaque('DdOpaque');

// FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; }
const FILETIME = koffi.struct('FILETIME', {
    dwLowDateTime: 'uint32',
    dwHighDateTime: 'uint32',
});

// FindPackageDependencyCriteria
//   PSID   User;             -> void*
//   BOOL   ScopeIsSystem;    -> int32 (Win32 BOOL is 4 bytes)
//   PCWSTR PackageFamilyName; -> str16 (LPWSTR)
const FindPackageDependencyCriteria = koffi.struct('FindPackageDependencyCriteria', {
    User: 'void *',
    ScopeIsSystem: 'int32',
    PackageFamilyName: 'str16',
});

// ---------------------------------------------------------------------------
// Heap helpers
//
// The Dynamic Dependency APIs allocate PWSTR/array results on the process heap;
// the caller must release them with HeapFree (matching the C# HeapFree helper).
// `HeapPWSTR` is a koffi "disposable" str16: koffi decodes it to a JS string and
// then automatically calls freeHeap() on the original pointer, so single-string
// outputs are both marshalled and freed for us.
// ---------------------------------------------------------------------------

const GetProcessHeap = kernelbase.func('void * __stdcall GetProcessHeap()');
const HeapFree = kernelbase.func('bool __stdcall HeapFree(void *hHeap, uint32 dwFlags, void *lpMem)');

function freeHeap(ptr) {
    if (ptr) {
        HeapFree(GetProcessHeap(), 0, ptr);
    }
}

const HeapPWSTR = koffi.disposable('HeapPWSTR', 'str16', freeHeap);

// ---------------------------------------------------------------------------
// Lazily-bound native functions
//
// Binding is deferred so `require()` never throws on Windows builds missing one
// of the (newer) Dynamic Dependency exports; only the first call to an
// unavailable API fails, with a clear koffi error.
// ---------------------------------------------------------------------------

function lazy(lib, signature) {
    let fn;
    return (...args) => {
        if (!fn) {
            fn = lib.func(signature);
        }
        return fn(...args);
    };
}

const native = {
    VerifyPackageFamilyName: lazy(kernelbase,
        'int __stdcall VerifyPackageFamilyName(str16 packageFamilyName)'),

    TryCreatePackageDependency: lazy(kernelbase,
        'int __stdcall TryCreatePackageDependency(void *user, str16 packageFamilyName, int64 minVersion, ' +
        'int32 architectures, int32 lifetimeKind, str16 lifetimeArtifact, int32 options, _Out_ HeapPWSTR *packageDependencyId)'),

    TryCreatePackageDependency2: lazy(kernelbase,
        'int __stdcall TryCreatePackageDependency2(void *user, str16 packageFamilyName, int64 minVersion, ' +
        'int32 architectures, int32 lifetimeKind, str16 lifetimeArtifact, int32 options, ' +
        '_In_ FILETIME *lifetimeExpiration, _Out_ HeapPWSTR *packageDependencyId)'),

    DeletePackageDependency: lazy(kernelbase,
        'int __stdcall DeletePackageDependency(str16 packageDependencyId)'),

    AddPackageDependency: lazy(kernelbase,
        'int __stdcall AddPackageDependency(str16 packageDependencyId, int32 rank, int32 options, ' +
        '_Out_ DdOpaque **packageDependencyContext, _Out_ HeapPWSTR *packageFullName)'),

    AddPackageDependency2: lazy(kernelbase,
        'int __stdcall AddPackageDependency2(str16 packageDependencyId, int32 rank, int32 options, ' +
        '_Out_ DdOpaque **packageDependencyContext, _Out_ HeapPWSTR *packageFullName)'),

    RemovePackageDependency: lazy(kernelbase,
        'int __stdcall RemovePackageDependency(DdOpaque *packageDependencyContext)'),

    GetResolvedPackageFullNameForPackageDependency: lazy(kernelbase,
        'int __stdcall GetResolvedPackageFullNameForPackageDependency(str16 packageDependencyId, _Out_ HeapPWSTR *packageFullName)'),

    GetResolvedPackageFullNameForPackageDependency2: lazy(kernelbase,
        'int __stdcall GetResolvedPackageFullNameForPackageDependency2(str16 packageDependencyId, _Out_ HeapPWSTR *packageFullName)'),

    GetIdForPackageDependencyContext: lazy(kernelbase,
        'int __stdcall GetIdForPackageDependencyContext(DdOpaque *packageDependencyContext, _Out_ HeapPWSTR *packageDependencyId)'),

    FindPackageDependency: lazy(kernelbase,
        'int __stdcall FindPackageDependency(_In_ FindPackageDependencyCriteria *criteria, ' +
        '_Out_ uint32 *packageDependencyIdsCount, _Out_ DdOpaque **packageDependencyIds)'),

    GetPackageDependencyInformation: lazy(kernelbase,
        'int __stdcall GetPackageDependencyInformation(str16 packageDependencyId, _Out_ DdOpaque **user, ' +
        '_Out_ HeapPWSTR *packageFamilyName, _Out_ uint64 *minVersion, _Out_ int32 *architectures, ' +
        '_Out_ int32 *lifetimeKind, _Out_ HeapPWSTR *lifetimeArtifact, _Out_ int32 *options, _Out_ FILETIME *lifetimeExpiration)'),

    GetProcessesUsingPackageDependency: lazy(kernelbase,
        'int __stdcall GetProcessesUsingPackageDependency(str16 packageDependencyId, void *user, int32 scopeIsSystem, ' +
        '_Out_ uint32 *processIdsCount, _Out_ DdOpaque **processIds)'),

    GetPackageGraphRevisionId: lazy(kernelbase,
        'uint32 __stdcall GetPackageGraphRevisionId()'),

    // kernel32.dll (export-presence probing)
    LoadLibraryExW: lazy(kernel32,
        'void * __stdcall LoadLibraryExW(str16 lpFileName, void *hReservedNull, uint32 dwFlags)'),

    FreeLibrary: lazy(kernel32,
        'bool __stdcall FreeLibrary(void *hModule)'),

    GetProcAddress: lazy(kernel32,
        'void * __stdcall GetProcAddress(void *hModule, str procName)'),
};

// ---------------------------------------------------------------------------
// Enums (mirroring the C# public enums)
// ---------------------------------------------------------------------------

const CreatePackageDependencyOptions = Object.freeze({
    None: 0,
    DoNotVerifyDependencyResolution: 0x00000001,
    ScopeIsSystem: 0x00000002,
});

const PackageDependencyLifetimeKind = Object.freeze({
    Process: 0,
    FilePath: 1,
    RegistryKey: 2,
});

const AddPackageDependencyOptions = Object.freeze({
    None: 0,
    PrependIfRankCollision: 0x00000001,
});

const AddPackageDependencyOptions2 = Object.freeze({
    None: 0,
    PrependIfRankCollision: 0x00000001,
    SpecifiedPackageFamilyOnly: 0x00000002,
});

const PackageDependencyProcessorArchitectures = Object.freeze({
    None: 0,
    Neutral: 0x00000001,
    X86: 0x00000002,
    X64: 0x00000004,
    Arm: 0x00000008,
    Arm64: 0x00000010,
    X86A64: 0x00000020,
});

const Rank = Object.freeze({
    Default: 0,
});

// ---------------------------------------------------------------------------
// HRESULT helpers
// ---------------------------------------------------------------------------

const succeeded = (hr) => hr >= 0;
const failed = (hr) => hr < 0;

function throwIfFailed(hr, message) {
    if (failed(hr)) {
        const code = '0x' + (hr >>> 0).toString(16).padStart(8, '0');
        const err = new Error(`${message || 'Operation failed'} (hr=${code})`);
        err.hr = hr;
        throw err;
    }
    return hr;
}

// ---------------------------------------------------------------------------
// FILETIME <-> JS Date conversion
// (FILETIME = 100ns ticks since 1601-01-01 UTC; Date = ms since 1970-01-01 UTC)
// ---------------------------------------------------------------------------

const FILETIME_EPOCH_DIFF = 116444736000000000n; // ticks between 1601 and 1970
const TICKS_PER_MS = 10000n;

function filetimeToDate(ft) {
    const ticks = (BigInt(ft.dwHighDateTime >>> 0) << 32n) | BigInt(ft.dwLowDateTime >>> 0);
    if (ticks === 0n) {
        return null; // zero == "no expiration" (C# used DateTime.MinValue)
    }
    return new Date(Number((ticks - FILETIME_EPOCH_DIFF) / TICKS_PER_MS));
}

function toFiletimeStruct(value) {
    // Accepts: null/undefined (=> zero), Date, BigInt ticks, or {dwLowDateTime,dwHighDateTime}.
    if (value === null || value === undefined) {
        return { dwLowDateTime: 0, dwHighDateTime: 0 };
    }
    if (value instanceof Date) {
        const ticks = BigInt(value.getTime()) * TICKS_PER_MS + FILETIME_EPOCH_DIFF;
        return {
            dwLowDateTime: Number(ticks & 0xFFFFFFFFn),
            dwHighDateTime: Number((ticks >> 32n) & 0xFFFFFFFFn),
        };
    }
    if (typeof value === 'bigint') {
        return {
            dwLowDateTime: Number(value & 0xFFFFFFFFn),
            dwHighDateTime: Number((value >> 32n) & 0xFFFFFFFFn),
        };
    }
    if (typeof value === 'object' &&
        'dwLowDateTime' in value && 'dwHighDateTime' in value) {
        return value;
    }
    throw new TypeError('lifetimeExpiration must be a Date, BigInt ticks, {dwLowDateTime,dwHighDateTime}, or null');
}

// ---------------------------------------------------------------------------
// PACKAGE_VERSION (64-bit packed major.minor.build.revision) helper.
// Convenient for building `minVersion` values.
// ---------------------------------------------------------------------------

const PackageVersion = Object.freeze({
    pack(major, minor = 0, build = 0, revision = 0) {
        return (BigInt(major & 0xFFFF) << 48n) |
               (BigInt(minor & 0xFFFF) << 32n) |
               (BigInt(build & 0xFFFF) << 16n) |
               BigInt(revision & 0xFFFF);
    },
    unpack(version) {
        const v = BigInt(version);
        return {
            major: Number((v >> 48n) & 0xFFFFn),
            minor: Number((v >> 32n) & 0xFFFFn),
            build: Number((v >> 16n) & 0xFFFFn),
            revision: Number(v & 0xFFFFn),
        };
    },
});

// ---------------------------------------------------------------------------
// Export-presence probing
// ---------------------------------------------------------------------------

function isExport(moduleName, procName) {
    const hmodule = native.LoadLibraryExW(moduleName, null, 0);
    if (!hmodule) {
        return false;
    }
    try {
        return native.GetProcAddress(hmodule, procName) !== null;
    } finally {
        native.FreeLibrary(hmodule);
    }
}

// ===========================================================================
// Public API
// ===========================================================================

// namespace Microsoft.Windows.ApplicationModel
class PackageFamilyName {
    /**
     * Verify a package family name is well-formed.
     * @param {string} packageFamilyName
     * @returns {number} HRESULT (0 / S_OK when valid).
     */
    static Verify(packageFamilyName) {
        return native.VerifyPackageFamilyName(packageFamilyName);
    }
}

// namespace Microsoft.Windows.ApplicationModel.DynamicDependency
class PackageDependency {
    /**
     * @param {string} feature e.g. "AddPackageDependency2"
     * @returns {boolean}
     */
    static IsSupported(feature) {
        switch (feature) {
            case 'AddPackageDependency2':
                return isExport('kernelbase.dll', 'AddPackageDependency2');
            default:
                return false;
        }
    }

    /**
     * Define (pin) a package dependency.
     * @returns {{hr:number, packageDependencyId:(string|null)}}
     */
    static TryCreate({
        packageFamilyName,
        minVersion = 0,
        architectures = PackageDependencyProcessorArchitectures.None,
        lifetimeKind = PackageDependencyLifetimeKind.Process,
        lifetimeArtifact = null,
        options = CreatePackageDependencyOptions.None,
    } = {}) {
        const idOut = [null];
        const hr = native.TryCreatePackageDependency(
            null, packageFamilyName, minVersion, architectures,
            lifetimeKind, lifetimeArtifact, options, idOut);
        return { hr, packageDependencyId: succeeded(hr) ? idOut[0] : null };
    }

    /**
     * Define (pin) a package dependency, with a lifetime expiration.
     * @returns {{hr:number, packageDependencyId:(string|null)}}
     */
    static TryCreate2({
        packageFamilyName,
        minVersion = 0,
        architectures = PackageDependencyProcessorArchitectures.None,
        lifetimeKind = PackageDependencyLifetimeKind.Process,
        lifetimeArtifact = null,
        options = CreatePackageDependencyOptions.None,
        lifetimeExpiration = null,
    } = {}) {
        const idOut = [null];
        const hr = native.TryCreatePackageDependency2(
            null, packageFamilyName, minVersion, architectures,
            lifetimeKind, lifetimeArtifact, options,
            toFiletimeStruct(lifetimeExpiration), idOut);
        return { hr, packageDependencyId: succeeded(hr) ? idOut[0] : null };
    }

    /**
     * Undefine (unpin) a package dependency.
     * @param {string} packageDependencyId
     * @returns {number} HRESULT
     */
    static Delete(packageDependencyId) {
        return native.DeletePackageDependency(packageDependencyId);
    }

    /**
     * Resolve a pinned package dependency and add it to this process' package graph.
     * @returns {{hr:number, packageDependencyContext:*, packageFullName:(string|null)}}
     */
    static Add({
        packageDependencyId,
        rank = Rank.Default,
        options = AddPackageDependencyOptions.None,
    } = {}) {
        const ctxOut = [null];
        const pfnOut = [null];
        const hr = native.AddPackageDependency(packageDependencyId, rank, options, ctxOut, pfnOut);
        return {
            hr,
            packageDependencyContext: succeeded(hr) ? ctxOut[0] : null,
            packageFullName: succeeded(hr) ? pfnOut[0] : null,
        };
    }

    /**
     * Resolve a pinned package dependency and add it to this process' package graph (v2).
     * @returns {{hr:number, packageDependencyContext:*, packageFullName:(string|null)}}
     */
    static Add2({
        packageDependencyId,
        rank = Rank.Default,
        options = AddPackageDependencyOptions2.None,
    } = {}) {
        const ctxOut = [null];
        const pfnOut = [null];
        const hr = native.AddPackageDependency2(packageDependencyId, rank, options, ctxOut, pfnOut);
        return {
            hr,
            packageDependencyContext: succeeded(hr) ? ctxOut[0] : null,
            packageFullName: succeeded(hr) ? pfnOut[0] : null,
        };
    }

    /**
     * Remove a resolved package dependency from this process' package graph.
     * @param {*} packageDependencyContext the context returned by Add/Add2.
     * @returns {number} HRESULT
     */
    static Remove(packageDependencyContext) {
        return native.RemovePackageDependency(packageDependencyContext);
    }

    /**
     * Package full name a dependency would resolve to (without adding it).
     * @returns {{hr:number, packageFullName:(string|null)}}
     */
    static GetResolvedPackageFullName(packageDependencyId) {
        const pfnOut = [null];
        const hr = native.GetResolvedPackageFullNameForPackageDependency(packageDependencyId, pfnOut);
        return { hr, packageFullName: succeeded(hr) ? pfnOut[0] : null };
    }

    /**
     * Package full name a dependency would resolve to, using the v2 export.
     * @returns {{hr:number, packageFullName:(string|null)}}
     */
    static GetResolvedPackageFullName2(packageDependencyId) {
        const pfnOut = [null];
        const hr = native.GetResolvedPackageFullNameForPackageDependency2(packageDependencyId, pfnOut);
        return { hr, packageFullName: succeeded(hr) ? pfnOut[0] : null };
    }

    /**
     * Get the package dependency id for a resolved context.
     * @returns {{hr:number, packageDependencyId:(string|null)}}
     */
    static GetIdForContext(packageDependencyContext) {
        const idOut = [null];
        const hr = native.GetIdForPackageDependencyContext(packageDependencyContext, idOut);
        return { hr, packageDependencyId: succeeded(hr) ? idOut[0] : null };
    }

    /**
     * Retrieve package dependency ids matching criteria.
     * @returns {{hr:number, count:number, packageDependencyIds:string[]}}
     */
    static Find({
        user = null,
        scopeIsSystem = false,
        packageFamilyName = null,
    } = {}) {
        const criteria = {
            User: user,
            ScopeIsSystem: scopeIsSystem ? 1 : 0,
            PackageFamilyName: packageFamilyName,
        };
        const countOut = [0];
        const idsOut = [null];
        const hr = native.FindPackageDependency(criteria, countOut, idsOut);
        const count = countOut[0] >>> 0;
        let packageDependencyIds = [];
        if (succeeded(hr) && count > 0) {
            packageDependencyIds = koffi.decode(idsOut[0], koffi.array('str16', count));
        }
        freeHeap(idsOut[0]); // free the HeapAlloc'd PWSTR[] block
        return { hr, count, packageDependencyIds };
    }

    /**
     * Retrieve information about a package dependency.
     * @returns {{hr:number, packageFamilyName:(string|null), minVersion:(number|bigint),
     *            architectures:number, lifetimeKind:number, lifetimeArtifact:(string|null),
     *            options:number, lifetimeExpiration:(Date|null)}}
     */
    static GetInfo(packageDependencyId) {
        const userOut = [null];
        const pfnOut = [null];
        const minVersionOut = [0];
        const archOut = [0];
        const lifetimeKindOut = [0];
        const lifetimeArtifactOut = [null];
        const optionsOut = [0];
        const lifetimeExpirationOut = {};

        const hr = native.GetPackageDependencyInformation(
            packageDependencyId, userOut, pfnOut, minVersionOut, archOut,
            lifetimeKindOut, lifetimeArtifactOut, optionsOut, lifetimeExpirationOut);

        const result = {
            hr,
            packageFamilyName: null,
            minVersion: 0,
            architectures: PackageDependencyProcessorArchitectures.None,
            lifetimeKind: PackageDependencyLifetimeKind.Process,
            lifetimeArtifact: null,
            options: CreatePackageDependencyOptions.None,
            lifetimeExpiration: null,
        };

        if (succeeded(hr)) {
            result.packageFamilyName = pfnOut[0];               // disposable: already a string, freed
            result.minVersion = minVersionOut[0];
            result.architectures = archOut[0];
            result.lifetimeKind = lifetimeKindOut[0];
            result.lifetimeArtifact = lifetimeArtifactOut[0];   // disposable: string or null, freed
            result.options = optionsOut[0];
            result.lifetimeExpiration = filetimeToDate(lifetimeExpirationOut);
        }

        freeHeap(userOut[0]); // the HeapAlloc'd PSID (unused, but released to avoid a leak)
        return result;
    }

    /**
     * Retrieve the process ids using a package dependency.
     * @returns {{hr:number, count:number, processIds:number[]}}
     */
    static GetProcesses(packageDependencyId, scopeIsSystem = false) {
        const countOut = [0];
        const pidsOut = [null];
        const hr = native.GetProcessesUsingPackageDependency(
            packageDependencyId, null, scopeIsSystem ? 1 : 0, countOut, pidsOut);
        const count = countOut[0] >>> 0;
        let processIds = [];
        if (succeeded(hr) && count > 0) {
            processIds = Array.from(koffi.decode(pidsOut[0], koffi.array('uint32', count)));
        }
        freeHeap(pidsOut[0]); // free the HeapAlloc'd DWORD[] block
        return { hr, count, processIds };
    }
}

class PackageGraph {
    /** @returns {number} the package graph's current revision id. */
    static get RevisionId() {
        return native.GetPackageGraphRevisionId();
    }
}

// ---------------------------------------------------------------------------
// Exports
// ---------------------------------------------------------------------------

module.exports = {
    // classes
    PackageFamilyName,
    PackageDependency,
    PackageGraph,
    // enums / constants
    CreatePackageDependencyOptions,
    PackageDependencyLifetimeKind,
    AddPackageDependencyOptions,
    AddPackageDependencyOptions2,
    PackageDependencyProcessorArchitectures,
    Rank,
    // helpers
    PackageVersion,
    succeeded,
    failed,
    throwIfFailed,
    // low-level structs/types (for advanced callers)
    types: { FILETIME, FindPackageDependencyCriteria, DdOpaque, HeapPWSTR },
};

// ---------------------------------------------------------------------------
// Tiny self-test when run directly: `node MsixDynamicDependency.js`
// ---------------------------------------------------------------------------

if (require.main === module) {
    const hex = (hr) => '0x' + (hr >>> 0).toString(16);

    console.log('PackageGraph.RevisionId              :', PackageGraph.RevisionId);
    console.log('IsSupported(AddPackageDependency2)   :', PackageDependency.IsSupported('AddPackageDependency2'));

    const goodPfn = 'Contoso.App_8wekyb3d8bbwe';
    console.log(`Verify("${goodPfn}")  :`, hex(PackageFamilyName.Verify(goodPfn)));
    console.log('Verify("not a pfn")                  :', hex(PackageFamilyName.Verify('not a pfn')));

    const found = PackageDependency.Find({ packageFamilyName: goodPfn });
    console.log('Find(no-match) hr/count              :', hex(found.hr), '/', found.count);
}
