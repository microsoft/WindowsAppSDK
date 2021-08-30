// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System.Runtime.InteropServices;

namespace Microsoft.Windows.ApplicationModel.DynamicDependency
{
    // The version of an MSIX package. This is logically `Major.Minor.Build.Revision` and can be expressed as...
    // * individual `ushort` values (uint16)
    // * an unsigned `ulong` value (uint64)
    // * a dot-string notation ("major.minor.build.revision")
    public struct PackageVersion
    {
        public ushort Major;
        public ushort Minor;
        public ushort Build;
        public ushort Revision;

        // Create an instance with the value `major.0.0.0`.
        public PackageVersion(ushort major) :
            this(major, 0, 0, 0)
        {
        }

        // Create an instance with the value `major.minor.0.0`.
        public PackageVersion(ushort major, ushort minor) :
            this(major, minor, 0, 0)
        {
        }

        // Create an instance with the value `major.minor.build.0`.
        public PackageVersion(ushort major, ushort minor, ushort build) :
            this(major, minor, build, 0)
        {
        }

        // Create an instance with the value `major.minor.build.revision`.
        public PackageVersion(ushort major, ushort minor, ushort build, ushort revision)
        {
            Major = major;
            Minor = minor;
            Build = build;
            Revision = revision;
        }

        // Create an instance from a version as a uint64.
        public PackageVersion(ulong version) :
            this((ushort)(version >> 48), (ushort)(version >> 32), (ushort)(version >> 16), (ushort)version)
        {
        }

        // Return the version as a uint64.
        public ulong ToVersion()
        {
            return (((ulong)Major) << 48) | (((ulong)Minor) << 32) | (((ulong)Build) << 16) | ((ulong)Revision);
        }

        // Return the string as a formatted value "major.minor.build.revision".
        public override string ToString()
        {
            return $"{Major}.{Minor}.{Build}.{Revision}";
        }
    };

    internal static class NativeMethods
    {
        [DllImport("Microsoft.WindowsAppSDK.Bootstrap.dll", EntryPoint = "MddBootstrapInitialize", CharSet = CharSet.Unicode, ExactSpelling = true, PreserveSig = false)]
        internal static extern void MddBootstrapInitialize_Throw(uint majorMinorVersion, string versionTag, PackageVersion packageVersion);

        [DllImport("Microsoft.WindowsAppSDK.Bootstrap.dll", CharSet = CharSet.Unicode, ExactSpelling = true)]
        internal static extern int MddBootstrapInitialize(uint majorMinorVersion, string versionTag, PackageVersion packageVersion);

        [DllImport("Microsoft.WindowsAppSDK.Bootstrap.dll", ExactSpelling = true)]
        internal static extern void MddBootstrapShutdown();
    }

    // The Windows App SDK bootstrap initialization API.
    public class Bootstrap
    {
        /// Initialize the calling process to use Windows App SDK's framework package.
        ///
        /// Find a Windows App SDK framework package meeting the criteria and make it available
        /// for use by the current process. If multiple packages meet the criteria the best
        /// candidate is selected.
        ///
        /// This is equivalent to `Initialize(majorMinorVersion, null, new PackageVersion())`.
        ///
        /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
        /// @see Initialize(uint, string)
        /// @see Initialize(uint, string, PackageVersion)
        /// @see Shutdown()
        public static void Initialize(uint majorMinorVersion)
        {
            Initialize(majorMinorVersion, null);
        }

        /// Initialize the calling process to use Windows App SDK's framework package.
        ///
        /// Find a Windows App SDK framework package meeting the criteria and make it available
        /// for use by the current process. If multiple packages meet the criteria the best
        /// candidate is selected.
        ///
        /// This is equivalent to `Initialize(majorMinorVersion, versionTag, new PackageVersion())`.
        ///
        /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
        /// @param versionTag version tag (if any), e.g. "preview1".
        /// @see Initialize(uint)
        /// @see Initialize(uint, string, PackageVersion)
        /// @see Shutdown()
        public static void Initialize(uint majorMinorVersion, string versionTag)
        {
            Initialize(majorMinorVersion, versionTag, new PackageVersion());
        }

        /// Initialize the calling process to use Windows App SDK's framework package.
        ///
        /// Find a Windows App SDK framework package meeting the criteria and make it available
        /// for use by the current process. If multiple packages meet the criteria the best
        /// candidate is selected.
        ///
        /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
        /// @param versionTag version tag (if any), e.g. "preview1".
        /// @param minVersion the minimum version to use
        /// @see Initialize(uint)
        /// @see Initialize(uint, string)
        /// @see Shutdown()
        public static void Initialize(uint majorMinorVersion, string versionTag, PackageVersion minVersion)
        {
            NativeMethods.MddBootstrapInitialize_Throw(majorMinorVersion, versionTag, minVersion);
        }

        /// Initialize the calling process to use Windows App SDK's framework package.
        /// Failure returns false with the failure HRESULT in the hresult parameter.
        ///
        /// Find a Windows App SDK framework package meeting the criteria and make it available
        /// for use by the current process. If multiple packages meet the criteria the best
        /// candidate is selected.
        ///
        /// This is equivalent to `TryInitialize(majorMinorVersion, null, new PackageVersion(), hresult)`.
        ///
        /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
        /// @retval true if successful, otherwise false is returned.
        /// @see TryInitialize(uint, string, out int)
        /// @see TryInitialize(uint, string, PackageVersion, out int)
        /// @see Shutdown()
        public static bool TryInitialize(uint majorMinorVersion, out int hresult)
        {
            return TryInitialize(majorMinorVersion, null, out hresult);
        }

        /// Initialize the calling process to use Windows App SDK's framework package.
        /// Failure returns false with the failure HRESULT in the hresult parameter.
        ///
        /// Find a Windows App SDK framework package meeting the criteria and make it available
        /// for use by the current process. If multiple packages meet the criteria the best
        /// candidate is selected.
        ///
        /// This is equivalent to `TryInitialize(majorMinorVersion, versionTag, new PackageVersion(), hresult)`.
        ///
        /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
        /// @param versionTag version tag (if any), e.g. "preview1".
        /// @retval true if successful, otherwise false is returned.
        /// @see TryInitialize(uint, out int)
        /// @see TryInitialize(uint, string, PackageVersion, out int)
        /// @see Shutdown()
        public static bool TryInitialize(uint majorMinorVersion, string versionTag, out int hresult)
        {
            var minVersion = new PackageVersion();
            return TryInitialize(majorMinorVersion, versionTag, minVersion, out hresult);
        }

        /// Initialize the calling process to use Windows App SDK's framework package.
        /// Failure returns false with the failure HRESULT in the hresult parameter.
        ///
        /// Find a Windows App SDK framework package meeting the criteria and make it available
        /// for use by the current process. If multiple packages meet the criteria the best
        /// candidate is selected.
        ///
        /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
        /// @param versionTag version tag (if any), e.g. "preview1".
        /// @param minVersion the minimum version to use.
        /// @param hresult the error code if an error occurred.
        /// @retval true if successful, otherwise false is returned.
        /// @see TryInitialize(uint, out int)
        /// @see TryInitialize(uint, string, out int)
        /// @see Shutdown()
        public static bool TryInitialize(uint majorMinorVersion, string versionTag, PackageVersion minVersion, out int hresult)
        {
            hresult = NativeMethods.MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion);
            return hresult >= 0;
        }

        /// Undo the changes made by Initialize().
        ///
        /// @warning Packages made available via `Initialize()` and
        ///          the Dynamic Dependencies API should not be used after this call.
        /// @see Initialize(uint)
        /// @see Initialize(uint, string)
        /// @see Initialize(uint, string, PackageVersion)
        /// @see TryInitialize(uint, out int)
        /// @see TryInitialize(uint, string, out int)
        /// @see TryInitialize(uint, string, PackageVersion, out int)
        public static void Shutdown()
        {
            NativeMethods.MddBootstrapShutdown();
        }
    }
}
