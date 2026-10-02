# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
Functions to use Windows' Dynamic Dependency API.

.DESCRIPTION
TBD

.INPUTS
None

.OUTPUTS
None

.NOTES
    Version : 0.1.0
#>

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
using FILETIME = System.Runtime.InteropServices.ComTypes.FILETIME;

namespace Microsoft.Windows.ApplicationModel
{
    public class PackageFamilyName
    {
        [DllImport("kernelbase.dll", EntryPoint="VerifyPackageFamilyName", ExactSpelling=true, CharSet = CharSet.Unicode)]
        private static extern int kernelbase_VerifyPackageFamilyName(
            /*_In_ PCWSTR*/ string packageFamilyName);

        public static int Verify(string packageFamilyName)
        {
            return kernelbase_VerifyPackageFamilyName(packageFamilyName);
        }
    }
}

namespace Microsoft.Windows.ApplicationModel.DynamicDependency
{
    public enum CreatePackageDependencyOptions
    {
        None = 0,

        // Disable dependency resolution when pinning a package dependency.
        DoNotVerifyDependencyResolution = 0x00000001,

         // Define the package dependency for the system, accessible to all users
         // (default is the package dependency is defined for a specific user).
         // This option requires the caller has adminitrative privileges.
        ScopeIsSystem = 0x00000002,
    }

    public enum PackageDependencyLifetimeKind
    {
        // The current process is the lifetime artifact. The package dependency
        // is implicitly deleted when the process terminates.
        Process = 0,

        // The lifetime artifact is an absolute filename or path.
        // The package dependency is implicitly deleted when this is deleted.
        FilePath = 1,

        // The lifetime artifact is a registry key in the format
        // 'root\\subkey' where root is one of the following: HKLM, HKCU, HKCR, HKU.
        // The package dependency is implicitly deleted when this is deleted.
        RegistryKey = 2,
    }

    public enum AddPackageDependencyOptions
    {
        None                   = 0,
        PrependIfRankCollision = 0x00000001,
    };

    public enum AddPackageDependencyOptions2
    {
        None                       = 0,
        PrependIfRankCollision     = 0x00000001,
        SpecifiedPackageFamilyOnly = 0x00000002,
    };

    public class Rank
    {
        public const int Default = 0;
    }

    public enum PackageDependencyProcessorArchitectures
    {
        None    = 0,
        Neutral = 0x00000001,
        X86     = 0x00000002,
        X64     = 0x00000004,
        Arm     = 0x00000008,
        Arm64   = 0x00000010,
        X86A64  = 0x00000020,
    };

    [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
    public struct FindPackageDependencyCriteria
    {
        /// Match package dependencies for this user if not NULL.
        /// Match package dependencies for the current user if NULL (and ScopeIsSystem=FALSE).
        /// @note This MUST be NULL if ScopeIsSystem=TRUE.
        /// @note Admin privilege is required if User is not NULL and not the current user.
        public /*PSID*/ IntPtr User;

        /// Match package dependencies created with CreatePackageDependencyOptions_ScopeIsSystem this is TRUE.
        /// @note Admin privilege is required if ScopeIsSystem is TRUE.
        [MarshalAs(UnmanagedType.Bool)]
        public bool ScopeIsSystem;

        /// Match package dependencies with this package family. Ignore if NULL or empty ("").
        public string PackageFamilyName;
    }

    public class PackageDependency
    {
        [DllImport("kernelbase.dll", EntryPoint="GetProcessHeap", ExactSpelling=true, SetLastError=true)]
        public static extern IntPtr kernel32_GetProcessHeap();

        [DllImport("kernelbase.dll", EntryPoint="HeapFree", ExactSpelling=true, SetLastError=true)]
        private static extern bool kernel32_HeapFree(IntPtr hHeap, uint dwFlags, IntPtr lpMem);

        private static bool HeapFree(IntPtr p)
        {
            return kernel32_HeapFree(kernel32_GetProcessHeap(), 0, p);
        }

        [System.Flags]
        enum LoadLibraryFlags : uint
        {
              DONT_RESOLVE_DLL_REFERENCES = 0x00000001,
              LOAD_IGNORE_CODE_AUTHZ_LEVEL = 0x00000010,
              LOAD_LIBRARY_AS_DATAFILE = 0x00000002,
              LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 0x00000040,
              LOAD_LIBRARY_AS_IMAGE_RESOURCE = 0x00000020,
              LOAD_LIBRARY_SEARCH_APPLICATION_DIR = 0x00000200,
              LOAD_LIBRARY_SEARCH_DEFAULT_DIRS = 0x00001000,
              LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR = 0x00000100,
              LOAD_LIBRARY_SEARCH_SYSTEM32 = 0x00000800,
              LOAD_LIBRARY_SEARCH_USER_DIRS = 0x00000400,
              LOAD_WITH_ALTERED_SEARCH_PATH = 0x00000008
        }

        [DllImport("kernel32.dll", EntryPoint="LoadLibraryExW", ExactSpelling=true, SetLastError=true)]
        static extern IntPtr LoadLibraryExW(string lpFileName, IntPtr hReservedNull, LoadLibraryFlags dwFlags);

        [DllImport("kernel32.dll", EntryPoint="FreeLibrary", ExactSpelling=true, SetLastError=true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool FreeLibrary(IntPtr hModule);

        [DllImport("kernel32", CharSet=CharSet.Ansi, ExactSpelling=true, SetLastError=true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        private static bool IsExport(string feature)
        {
            IntPtr hmodule = LoadLibraryExW("kernelbase.dll", IntPtr.Zero, 0);
            IntPtr fn = GetProcAddress(hmodule, "AddPackageDependency2");
            FreeLibrary(hmodule);
            return fn != IntPtr.Zero;
        }

        private static bool IsSupported(string feature)
        {
            switch (feature)
            {
                case "AddPackageDependency2": return IsExport(feature);
                default: return false;
            }
        }

        /// Define a package dependency. The criteria for a PackageDependency
        /// (package family name, minimum version, etc)
        /// may match multiple packages, but ensures Deployment won't remove
        /// a package if it's the only one satisfying the PackageDependency.
        ///
        /// @note A package matching a PackageDependency pin can still be removed
        ///       as long as there's another package that satisfies the PackageDependency.
        ///       For example, if Fwk-v1 is installed and a PackageDependency specifies
        ///       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
        ///       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
        ///       is removed Deployment won't remove Fwk-v2 because it's the only package
        ///       satisfying the PackageDependency. Thus Fwk-v1 and Fwk-v2 (and any other
        ///       package matching the PackageDependency) are 'loosely pinned'. Deployment
        ///       guarantees it won't remove a package if it would make a PackageDependency
        ///       unsatisfied.
        ///
        /// A PackageDependency specifies criteria (package family, minimum version, etc)
        /// and not a specific package. Deployment reserves the right to use a different
        /// package (e.g. higher version) to satisfy the PackageDependency if/when
        /// one becomes available.
        ///
        /// @param user the user scope of the package dependency. If NULL the caller's
        ///        user context is used. MUST be NULL if CreatePackageDependencyOptions_ScopeIsSystem
        ///        is specified
        /// @param lifetimeArtifact MUST be NULL if lifetimeKind=PackageDependencyLifetimeKind_Process
        /// @param packageDependencyId allocated via HeapAlloc; use HeapFree to deallocate
        ///
        /// @note TryCreatePackageDependency() fails if the PackageDependency cannot be resolved to a specific
        ///       package. This package resolution check is skipped if
        ///       CreatePackageDependencyOptions_DoNotVerifyDependencyResolution is specified. This is useful
        ///       for installers running as user contexts other than the target user (e.g. installers
        ///       running as LocalSystem).
        /// @see TryCreatePackageDependency2
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int TryCreatePackageDependency(
            /*PSID*/ IntPtr user,
            string packageFamilyName,
            /*PACKAGE_VERSION*/ long minVersion,
            /*PackageDependencyProcessorArchitectures*/ int packageDependencyProcessorArchitectures,
            /*PackageDependencyLifetimeKind*/ int lifetimeKind,
            string lifetimeArtifact,
            /*CreatePackageDependencyOptions*/ int options,
            /*_Outptr_result_maybenull_ PWSTR* */ out IntPtr packageDependencyId);

        public static int TryCreate(
            string packageFamilyName,
            long minVersion,
            /*PackageDependencyProcessorArchitectures*/ int packageDependencyProcessorArchitectures,
            /*PackageDependencyLifetimeKind*/ int lifetimeKind,
            string lifetimeArtifact,
            /*CreatePackageDependencyOptions*/ int options,
            /*_Outptr_result_maybenull_ PWSTR* */ out string packageDependencyId)
        {
            packageDependencyId = null;

            IntPtr pdi = IntPtr.Zero;
            int hr = TryCreatePackageDependency(IntPtr.Zero, packageFamilyName, minVersion, packageDependencyProcessorArchitectures,
                                                lifetimeKind, lifetimeArtifact, options, out pdi);
            if (hr >= 0)
            {
                packageDependencyId = Marshal.PtrToStringUni(pdi);
            }
            if (pdi != IntPtr.Zero)
            {
                HeapFree(pdi);
            }
            return hr;
        }

        private static DateTime FiletimeToDateTime(FILETIME fileTime)
        {
            long hFT2 = (((long) fileTime.dwHighDateTime) << 32) | ((uint) fileTime.dwLowDateTime);
            return DateTime.FromFileTimeUtc(hFT2);
        }

        private static FILETIME DateTimeToFiletime(DateTime time)
        {
            FILETIME ft;
            long hFT1 = time.ToFileTimeUtc();
            ft.dwLowDateTime = (int) (hFT1 & 0xFFFFFFFF);
            ft.dwHighDateTime = (int) (hFT1 >> 32);
            return ft;
        }

        /// Define a package dependency. The criteria for a PackageDependency
        /// (package family name, minimum version, etc)
        /// may match multiple packages, but ensures Deployment won't remove
        /// a package if it's the only one satisfying the PackageDependency.
        ///
        /// @note A package matching a PackageDependency pin can still be removed
        ///       as long as there's another package that satisfies the PackageDependency.
        ///       For example, if Fwk-v1 is installed and a PackageDependency specifies
        ///       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
        ///       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
        ///       is removed Deployment won't remove Fwk-v2 because it's the only package
        ///       satisfying the PackageDependency. Thus Fwk-v1 and Fwk-v2 (and any other
        ///       package matching the PackageDependency) are 'loosely pinned'. Deployment
        ///       guarantees it won't remove a package if it would make a PackageDependency
        ///       unsatisfied.
        ///
        /// A PackageDependency specifies criteria (package family, minimum version, etc)
        /// and not a specific package. Deployment reserves the right to use a different
        /// package (e.g. higher version) to satisfy the PackageDependency if/when
        /// one becomes available.
        ///
        /// @param user the user scope of the package dependency. If NULL the caller's
        ///        user context is used. MUST be NULL if CreatePackageDependencyOptions_ScopeIsSystem
        ///        is specified
        /// @param lifetimeArtifact MUST be NULL if lifetimeKind=PackageDependencyLifetimeKind_Process
        /// @param packageDependencyId allocated via HeapAlloc; use HeapFree to deallocate
        ///
        /// @note TryCreatePackageDependency2() fails if the PackageDependency cannot be resolved to a specific
        ///       package. This package resolution check is skipped if
        ///       CreatePackageDependencyOptions_DoNotVerifyDependencyResolution is specified. This is useful
        ///       for installers running as user contexts other than the target user (e.g. installers
        ///       running as LocalSystem).
        /// @see TryCreatePackageDependency
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int TryCreatePackageDependency2(
            /*PSID*/ IntPtr user,
            string packageFamilyName,
            /*PACKAGE_VERSION*/ long minVersion,
            /*PackageDependencyProcessorArchitectures*/ int packageDependencyProcessorArchitectures,
            /*PackageDependencyLifetimeKind*/ int lifetimeKind,
            string lifetimeArtifact,
            /*CreatePackageDependencyOptions*/ int options,
            /*const FILETIME* */ ref FILETIME lifetimeExpiration,
            /*_Outptr_result_maybenull_ PWSTR* */ out IntPtr packageDependencyId);

        public static int TryCreate2(
            string packageFamilyName,
            long minVersion,
            /*PackageDependencyProcessorArchitectures*/ int packageDependencyProcessorArchitectures,
            /*PackageDependencyLifetimeKind*/ int lifetimeKind,
            string lifetimeArtifact,
            /*CreatePackageDependencyOptions*/ int options,
            /*const FILETIME* */ FILETIME lifetimeExpiration,
            /*_Outptr_result_maybenull_ PWSTR* */ out string packageDependencyId)
        {
            packageDependencyId = null;

            IntPtr pdi = IntPtr.Zero;
            int hr = TryCreatePackageDependency2(IntPtr.Zero, packageFamilyName, minVersion, packageDependencyProcessorArchitectures,
                                                 lifetimeKind, lifetimeArtifact, options, ref lifetimeExpiration, out pdi);
            if (hr >= 0)
            {
                packageDependencyId = Marshal.PtrToStringUni(pdi);
            }
            if (pdi != IntPtr.Zero)
            {
                HeapFree(pdi);
            }
            return hr;
        }

        // Undefine a package dependency. Removing a pin on a PackageDependency is typically done at uninstall-time.
        // This implicitly occurs if the package dependency's 'lifetime artifact' (specified via TryCreatePackageDependency)
        // is deleted. Packages that are not referenced by other packages and have no pins are elegible to be removed.
        //
        // @warn DeletePackageDependency() requires the caller have administrative privileges
        //       if the package dependency was pinned with CreatePackageDependencyOptions_ScopeIsSystem.
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int DeletePackageDependency(
            string packageDependencyId);

        public static int Delete(
            string packageDependencyId)
        {
            return DeletePackageDependency(packageDependencyId);
        }

        /// Resolve a previously-pinned PackageDependency to a specific package and
        /// add it to the invoking process' package graph. Once the dependency has
        /// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
        /// can find the binaries in the resolved package.
        ///
        /// Package resolution is specific to a user and can return different values
        /// for different users on a system.
        ///
        /// Each successful AddPackageDependency() adds the resolve packaged to the
        /// calling process' package graph, even if already present. There is no
        /// duplicate 'detection' or 'filtering' applied by the API (multiple
        /// references from a package is not harmful). Once resolution is complete
        /// the package dependency stays resolved for that user until the last reference across
        /// all processes for that user is removed via RemovePackageDependency (or
        /// process termination).
        ///
        /// AddPackageDependency() adds the resolved package to the caller's package graph,
        /// per the rank specified. A process' package graph is a list of packages sorted by
        /// rank in ascending order (-infinity...0...+infinity). If package(s) are present in the
        /// package graph with the same rank as the call to AddPackageDependency the resolved
        /// package is (by default) added after others of the same rank. To add a package
        /// before others o the same rank, specify AddPackageDependencyOptions_PrependIfRankCollision.
        ///
        /// Every AddPackageDependency can be balanced by a RemovePackageDependency
        /// to remove the entry from the package graph. If the process terminates all package
        /// references are removed, but any pins stay behind.
        ///
        /// AddPackageDependency adds the resolved package to the process' package
        /// graph, per the rank and options parameters. The process' package
        /// graph is used to search for DLLs (per Dynamic-Link Library Search Order),
        /// WinRT objects and other resources; the caller can now load DLLs, activate
        /// WinRT objects and use other resources from the framework package until
        /// RemovePackageDependency is called. The packageDependencyId parameter
        /// must match a package dependency defined for the calling user or the
        /// system (i.e. pinned with CreatePackageDependencyOptions_ScopeIsSystem) else
        /// an error is returned.
        ///
        /// @param packageDependencyContext valid until passed to RemovePackageDependency()
        /// @param packageFullName allocated via HeapAlloc; use HeapFree to deallocate
        /// @see AddPackageDependency2()
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int AddPackageDependency(
            string packageDependencyId,
            int rank,
            /*AddPackageDependencyOptions*/ int options,
            /*_Out_ PACKAGEDEPENDENCY_CONTEXT* */ out IntPtr packageDependencyContext,
            /*_Outptr_opt_result_maybenull_ PWSTR* */ out IntPtr packageFullName);

        public static int Add(
            string packageDependencyId,
            int rank,
            /*AddPackageDependencyOptions*/ int options,
            /*_Out_ PACKAGEDEPENDENCY_CONTEXT* */ out IntPtr packageDependencyContext,
            out string packageFullName)
        {
            packageDependencyContext = IntPtr.Zero;
            packageFullName = null;

            IntPtr pdc = IntPtr.Zero;
            IntPtr pfn = IntPtr.Zero;
            int hr = AddPackageDependency(packageDependencyId, rank, options, out pdc, out pfn);
            if (hr >= 0)
            {
                packageDependencyContext = pdc;
                packageFullName = Marshal.PtrToStringUni(pfn);
            }
            if (pfn != IntPtr.Zero)
            {
                HeapFree(pfn);
            }
            return hr;
        }

        /// Resolve a previously-pinned PackageDependency to a specific package and
        /// add it to the invoking process' package graph. Once the dependency has
        /// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
        /// can find the binaries in the resolved package.
        ///
        /// Package resolution is specific to a user and can return different values
        /// for different users on a system.
        ///
        /// Each successful AddPackageDependency2() adds the resolve packaged to the
        /// calling process' package graph, even if already present. There is no
        /// duplicate 'detection' or 'filtering' applied by the API (multiple
        /// references from a package is not harmful). Once resolution is complete
        /// the package dependency stays resolved for that user until the last reference across
        /// all processes for that user is removed via RemovePackageDependency (or
        /// process termination).
        ///
        /// AddPackageDependency2() adds the resolved package to the caller's package graph,
        /// per the rank specified. A process' package graph is a list of packages sorted by
        /// rank in ascending order (-infinity...0...+infinity). If package(s) are present in the
        /// package graph with the same rank as the call to AddPackageDependency2 the resolved
        /// package is (by default) added after others of the same rank. To add a package
        /// before others o the same rank, specify AddPackageDependencyOptions2_PrependIfRankCollision.
        ///
        /// Every AddPackageDependency2 can be balanced by a RemovePackageDependency
        /// to remove the entry from the package graph. If the process terminates all package
        /// references are removed, but any pins stay behind.
        ///
        /// AddPackageDependency2 adds the resolved package to the process' package
        /// graph, per the rank and options parameters. The process' package
        /// graph is used to search for DLLs (per Dynamic-Link Library Search Order),
        /// WinRT objects and other resources; the caller can now load DLLs, activate
        /// WinRT objects and use other resources from the framework package until
        /// RemovePackageDependency is called. The packageDependencyId parameter
        /// must match a package dependency defined for the calling user or the
        /// system (i.e. pinned with CreatePackageDependencyOptions_ScopeIsSystem) else
        /// an error is returned.
        ///
        /// @param packageDependencyContext valid until passed to RemovePackageDependency()
        /// @param packageFullName allocated via HeapAlloc; use HeapFree to deallocate
        /// @see AddPackageDependency()
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int AddPackageDependency2(
            string packageDependencyId,
            int rank,
            /*AddPackageDependencyOptions2*/ int options,
            /*_Out_ PACKAGEDEPENDENCY_CONTEXT* */ out IntPtr packageDependencyContext,
            /*_Outptr_opt_result_maybenull_ PWSTR* */ out IntPtr packageFullName);

        public static int Add2(
            string packageDependencyId,
            int rank,
            /*AddPackageDependencyOptions2*/ int options,
            /*_Out_ PACKAGEDEPENDENCY_CONTEXT* */ out IntPtr packageDependencyContext,
            out string packageFullName)
        {
            packageDependencyContext = IntPtr.Zero;
            packageFullName = null;

            IntPtr pdc = IntPtr.Zero;
            IntPtr pfn = IntPtr.Zero;
            int hr = AddPackageDependency2(packageDependencyId, rank, options, out pdc, out pfn);
            if (hr >= 0)
            {
                packageDependencyContext = pdc;
                packageFullName = Marshal.PtrToStringUni(pfn);
            }
            if (pfn != IntPtr.Zero)
            {
                HeapFree(pfn);
            }
            return hr;
        }

        // Remove a resolved PackageDependency from the current process' package graph
        // (i.e. undo AddPackageDependency). Used at runtime (i.e. the moral equivalent
        // of Windows' RemoveDllDirectory()).
        //
        // @note This does not unload loaded resources (DLLs etc). After removing
        //        a package dependency any files loaded from the package can continue
        //        to be used; future file resolution will fail to see the removed
        //        package dependency.
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int RemovePackageDependency(
            /*PACKAGEDEPENDENCY_CONTEXT*/ IntPtr packageDependencyContext);

        public static int Remove(
            IntPtr packageDependencyContext)
        {
            return RemovePackageDependency(packageDependencyContext);
        }

        /// Return the package full name that would be used if the
        /// PackageDependency were to be resolved. Does not add the
        /// package to the process graph.
        ///
        /// @param packageFullName allocated via HeapAlloc; use HeapFree to deallocate.
        ///                        If the package dependency cannot be resolved the function
        ///                        succeeds but packageFullName is NULL.
        /// @see GetResolvedPackageFullNameForPackageDependency2
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int GetResolvedPackageFullNameForPackageDependency(
            string packageDependencyId,
            /*_Outptr_result_maybenull_ PWSTR* */ out IntPtr packageFullName);

        public static int GetResolvedPackageFullName(
            string packageDependencyId,
            out string packageFullName)
        {
            packageFullName = null;

            IntPtr pfn = IntPtr.Zero;
            int hr = GetResolvedPackageFullNameForPackageDependency(packageDependencyId, out pfn);
            if (hr >= 0)
            {
                packageFullName = Marshal.PtrToStringUni(pfn);
            }
            if (pfn != IntPtr.Zero)
            {
                HeapFree(pfn);
            }
            return hr;
        }

        /// Return the package full name that would be used if the
        /// PackageDependency were to be resolved. Does not add the
        /// package to the process graph.
        ///
        /// @param packageFullName allocated via HeapAlloc; use HeapFree to deallocate.
        /// @return E_INVALIDARG if packageDependencyId is not a valid package dependency.
        /// @see GetResolvedPackageFullNameForPackageDependency
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int GetResolvedPackageFullNameForPackageDependency2(
            string packageDependencyId,
            /*_Outptr_result_maybenull_ PWSTR* */ out IntPtr packageFullName);

        public static int GetResolvedPackageFullName2(
            string packageDependencyId,
            out string packageFullName)
        {
            packageFullName = null;

            IntPtr pfn = IntPtr.Zero;
            int hr = GetResolvedPackageFullNameForPackageDependency(packageDependencyId, out pfn);
            if (hr >= 0)
            {
                packageFullName = Marshal.PtrToStringUni(pfn);
            }
            if (pfn != IntPtr.Zero)
            {
                HeapFree(pfn);
            }
            return hr;
        }

        // Return the package dependency for the context.
        //
        // @param packageDependencyId allocated via HeapAlloc; use HeapFree to deallocate.
        //                            If the package dependency context cannot be resolved
        //                            the function succeeds but packageDependencyId is nullptr.
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int GetIdForPackageDependencyContext(
            /*PACKAGEDEPENDENCY_CONTEXT*/ IntPtr packageDependencyContext,
            /*_Outptr_result_maybenull_ PWSTR* */ out IntPtr packageDependencyId);

        public static int GetIdForContext(
            /*PACKAGEDEPENDENCY_CONTEXT*/ IntPtr packageDependencyContext,
            /*_Outptr_result_maybenull_ PWSTR* */ out string packageDependencyId)
        {
            packageDependencyId = null;

            IntPtr pdi = IntPtr.Zero;
            int hr = GetIdForPackageDependencyContext(packageDependencyContext, out pdi);
            if (hr >= 0)
            {
                packageDependencyId = Marshal.PtrToStringUni(pdi);
            }
            if (pdi != IntPtr.Zero)
            {
                HeapFree(pdi);
            }
            return hr;
        }

        /// Retrieve package dependencies.
        /// @param packageDependencyIds allocated via HeapAlloc; use HeapFree to deallocate
        ///
        /// @see FindPackageDependencyCriteria
        /// @see TryCreatePackageDependency2
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int FindPackageDependency(
            /*const FindPackageDependencyCriteria* */ ref FindPackageDependencyCriteria findPackageDependencyCriteria,
            /*_Out_ UINT32* */ out /*ref*/ uint packageDependencyIdsCount,
            /*_Outptr_result_buffer_maybenull_(*packageDependencyIdsCount) PWSTR** */ out IntPtr packageDependencyIds);

        public static int Find(
            FindPackageDependencyCriteria findPackageDependencyCriteria,
            out uint packageDependencyIdsCount,
            out string[] packageDependencyIds)
        {
            packageDependencyIdsCount = 0;
            packageDependencyIds = null;

            IntPtr pdis = IntPtr.Zero;
            int hr = FindPackageDependency(ref findPackageDependencyCriteria, out packageDependencyIdsCount, out pdis);
            if (hr >= 0)
            {
                if (packageDependencyIdsCount > 0)
                {
                    string[] ids = new string[packageDependencyIdsCount];
                    int ptrSize = IntPtr.Size;
                    for (uint index=0; index < packageDependencyIdsCount; ++index)
                    {
                        IntPtr stringPtr = Marshal.ReadIntPtr(pdis, (int)(index * ptrSize));
                        ids[index] = Marshal.PtrToStringUni(stringPtr);
                    }
                    packageDependencyIds = ids;
                }
                else
                {
                    packageDependencyIds = null;
                }
            }
            if (pdis != IntPtr.Zero)
            {
                HeapFree(pdis);
            }
            return hr;
        }

        /// Retrieve information about a package dependency.
        ///
        /// @param user allocated via HeapAlloc; use HeapFree to deallocate
        /// @param packageFamilyName allocated via HeapAlloc; use HeapFree to deallocate
        /// @param lifetimeArtifact allocated via HeapAlloc; use HeapFree to deallocate
        /// @param lifetimeExpiration if specified, the value is zero if expiration date is not set.
        /// @note Admin privilege is required the package dependency was created with CreatePackageDependencyOptions_ScopeIsSystem or user is not NULL and not the current user.
        /// @see FindPackageDependency
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int GetPackageDependencyInformation(
            /*PCWSTR*/ string packageDependencyId,
            /*_Outptr_opt_result_maybenull_ PSID* */ out IntPtr user,
            /*_Outptr_opt_result_maybenull_ PWSTR* */ out IntPtr packageFamilyName,
            /*_Out_opt_ PACKAGE_VERSION* */ out ulong minVersion,
            /*_Out_opt_ PackageDependencyProcessorArchitectures* */ out PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
            /*_Out_opt_ PackageDependencyLifetimeKind* */ out PackageDependencyLifetimeKind lifetimeKind,
            /*_Outptr_opt_result_maybenull_ PWSTR* */ out IntPtr lifetimeArtifact,
            /*_Out_opt_ CreatePackageDependencyOptions* */ out int options,
            /*_Out_opt_ FILETIME* */ out FILETIME lifetimeExpiration);

        public static int GetInfo(
            string packageDependencyId,
            out string packageFamilyName,
            out ulong minVersion,
            out PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
            out PackageDependencyLifetimeKind lifetimeKind,
            out string lifetimeArtifact,
            out int options,
            out DateTime lifetimeExpiration)
        {
            packageFamilyName = null;
            minVersion = 0;
            packageDependencyProcessorArchitectures = 0;
            lifetimeKind = 0;
            lifetimeArtifact = null;
            options = 0;
            lifetimeExpiration = DateTime.MinValue;

            IntPtr u = IntPtr.Zero;
            IntPtr pfn = IntPtr.Zero;
            IntPtr la = IntPtr.Zero;
            FILETIME le;
            int hr = GetPackageDependencyInformation(packageDependencyId, out u, out pfn, out minVersion,
                                                     out packageDependencyProcessorArchitectures,
                                                     out lifetimeKind, out la, out options, out le);
            if (hr >= 0)
            {
                packageFamilyName = Marshal.PtrToStringUni(pfn);
                if (la != IntPtr.Zero)
                {
                    lifetimeArtifact = Marshal.PtrToStringUni(la);
                }
                if ((le.dwHighDateTime != 0) || (le.dwLowDateTime != 0))
                {
                    lifetimeExpiration = FiletimeToDateTime(le);
                }
            }
            if (pfn != IntPtr.Zero)
            {
                HeapFree(pfn);
            }
            if (la != IntPtr.Zero)
            {
                HeapFree(la);
            }
            return hr;
        }

        /// Retrieve the list of processes using a package dependency.
        ///
        /// @param user the user scope of the package dependency. If NULL the caller's
        ///        user context is used. MUST be NULL if scopeIsSystem=TRUE.
        /// @param processIdsCount allocated via HeapAlloc; use HeapFree to deallocate
        /// @param processIds allocated via HeapAlloc; use HeapFree to deallocate
        /// @note Admin privilege is required if scopeIsSystem=TRUE or user is not NULL and not the current user.
        /// @see FindPackageDependency
        [DllImport("kernelbase.dll", ExactSpelling=true, CharSet=CharSet.Unicode)]
        private static extern int GetProcessesUsingPackageDependency(
            /*PCWSTR*/ string packageDependencyId,
            /*PSID*/ IntPtr user,
            /*BOOL*/ bool scopeIsSystem,
            /*_Out_ UINT32* */ out uint processIdsCount,
            /*_Outptr_result_buffer_maybenull_(*processIdsCount) DWORD** */ out IntPtr processIds);

        public static int GetProcesses(
            string packageDependencyId,
            bool scopeIsSystem,
            out uint processIdsCount,
            out uint[] processIds)
        {
            processIdsCount = 0;
            processIds = null;

            IntPtr pis = IntPtr.Zero;
            int hr = GetProcessesUsingPackageDependency(packageDependencyId, IntPtr.Zero, scopeIsSystem, out processIdsCount, out pis);
            if (hr >= 0)
            {
                if (processIdsCount > 0)
                {
                    uint[] pids = new uint[processIdsCount];
                    int pidSize = sizeof(uint);
                    for (uint index=0; index < processIdsCount; ++index)
                    {
                        pids[index] = (uint)Marshal.ReadInt32(pis, (int)(index * pidSize));
                    }
                    processIds = pids;
                }
                else
                {
                    processIds = null;
                }
            }
            if (pis != IntPtr.Zero)
            {
                HeapFree(pis);
            }
            return hr;
        }
    }

    public class PackageGraph
    {
        // Returns the package graph's current revision ID.
        [DllImport("kernelbase.dll")]
        private static extern uint GetPackageGraphRevisionId();

        public static uint RevisionId
        {
            get
            {
                return GetPackageGraphRevisionId();
            }
        }
    }
}
"@
