// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Microsoft.Windows.ApplicationModel.DynamicDependency.BootstrapCS
{
    class AutoInitialize
    {
        [global::System.Runtime.InteropServices.DllImport("user32.dll", CharSet = global::System.Runtime.InteropServices.CharSet.Unicode, SetLastError = true)]
        private static extern int MessageBox(global::System.IntPtr hWnd, string lpText, string lpCaption, uint uType);

        [global::System.Runtime.CompilerServices.ModuleInitializer]
        internal static void AccessWindowsAppSDK()
        {
            uint majorMinorVersion = global::Microsoft.WindowsAppSDK.Release.MajorMinor;
            string versionTag = global::Microsoft.WindowsAppSDK.Release.VersionTag;
            var minVersion = new PackageVersion(global::Microsoft.WindowsAppSDK.Runtime.Version.UInt64);
            try
            {
                global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.Initialize(majorMinorVersion, versionTag, minVersion);
            }
            catch (global::System.Exception e)
            {
                if (global::System.Diagnostics.Debugger.IsAttached)
                {
                    global::System.Diagnostics.Debugger.Break();
                }
                else
                {
                    MessageBox(global::System.IntPtr.Zero, "You need to run the Windows App Runtime Installer and its MSIX components", "MddBootstrap", (uint)0x00000010L);
                }
                global::System.Environment.FailFast(e.Message);
            }
        }
    }
}
