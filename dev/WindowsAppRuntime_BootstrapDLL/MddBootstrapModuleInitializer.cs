using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Microsoft.Windows.ApplicationModel.DynamicDependency;
using Microsoft.WindowsAppSDK;

//Driver Code
class MddBootstrapInitializerCS
{
    [ModuleInitializer]
    internal static void AccessWindowsAppSDK()
    {

        // Initialize access to Windows App SDK
        uint majorMinorVersion = Release.MajorMinor;
        string versionTag = Release.VersionTag;

        ushort Major = Microsoft.WindowsAppSDK.Runtime.Version.Major;
        ushort Minor = Microsoft.WindowsAppSDK.Runtime.Version.Minor;
        ushort Build = Microsoft.WindowsAppSDK.Runtime.Version.Build;
        ushort Revision = Microsoft.WindowsAppSDK.Runtime.Version.Revision;
        
   
        var minVersion = new PackageVersion(Revision, Build, Minor, Major);
        try
        {
            Bootstrap.Initialize(majorMinorVersion, versionTag,minVersion);
        }
        catch (Exception e)
        {
            Environment.FailFast(e.Message);
        }
    }
}
