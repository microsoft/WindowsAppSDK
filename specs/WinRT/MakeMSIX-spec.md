# MakeMSIX API in Windows App SDK
- [1. Background](#1-background)
- [2. Examples](#2-examples)
    - [2.1. Packing a package](#21-packing-a-package)
    - [2.2. Unbundling and unpacking a package to change information](#22-unbundling-and-unpacking-a-package-to-change-information)
    - [2.3. Helper methods for examples](#23-helper-methods-for-examples) 
- [3. API Details](#3-API-details)
- [4. Appendix](#4-Appendix)
- [5. Existing interfaces and options](#5-existing-interfaces-and-options)
  - [5.1. Makeappx](#51-makeappx)
    - [5.1.1. pack](#511-pack)
    - [5.1.2. bundle](#512-bundle)
    - [5.1.3. unpack](#513-unpack)
    - [5.1.4. unbundle](#514-unbundle)
  - [5.2. Makemsix](#52-makemsix)
    - [5.2.1. pack](#521-pack)
    - [5.2.2. bundle](#522-bundle)
    - [5.2.3. unpack](#523-unpack)
    - [5.2.4. unbundle](#524-unbundle)
  - [5.3. MSIXMgr](#53-msixmgr)
    - [5.3.1. unpack](#531-unpack)
- [6. Summary of existing options in relation to proposed API](#6-summary-of-existing-options-in-relation-to-proposed-API)

# 1. Background

The MakeMSIX API allows developers to create app packages for distribution. 
The API provides a WinRT interface that supports:
1. Creation of msix packages and msixbundle bundle packages,
2. Unpacking and unbundling of packages
3. Creation of vhd\vdx\cim images for Azure App Attach. 
4. Creation of Kozani packages.

Creation of Kozani packages is a new feature that has not existed in other msix packaging tools. The
other features in this spec have previously been available in command line tools discussed in the
appendix.

Kozani packages are msix packages that have been optimized for size by removing unnecessary
resources. All existing tools that work with msix packages are compatible with Kozani packages.
Kozani packages can be created manually without this API by modifying the files, manifest, and
resource index of an existing package using existing APIs.

# 2. Examples

## 2.1. Packing a package

```c#
static async Task CreatePackagesFromFolderExample()
{
    // Scenario: A developer is creating their own app. A build tool wants to create every type of distributable package for them.

    // Initial Conditions: The build has already produced a directory that contains the exact layout of each individual package
    // that it wants to bundle.
    // Each folder has an appxmanifest.xml in the root directory.

    // A full non-relative path to those layout folder is needed, as below.
    // Layout directories are inside this root, for example: packageLayoutRootPath\\ContosoApp1_2023.302.1739.686_x64__8wekyb3d8bbwe.
    string packageLayoutRootPath = "D:\\test\\ContosoApp1\\BuildOutput\\PackageLayouts";
    // The build tool packages each folder and puts the resulting packages at this location
    string packageOutputRootDirectoryPath = "D:\\test\\ContosoApp1\\BuildOutput\\packagedOutput\\";
    // The build tool wants to create the full bundle at this location
    string bundleOutputFilePath = "D:\\test\\ContosoApp1\\BuildOutput\\Package\\bundleOutput.msixbundle";
    // The build tool wants to create the kozani package at this location
    string kozaniPackageOutputFilePath = "D:\\test\\ContosoApp1\\BuildOutput\\Package\\kozaniPackagedOutput.msixbundle";
    // The build tool wants to create the app attach image at this location
    string appAttachImageFilePath = "D:\\xample\\ContosoApp1\\BuildOutput\\Package\\appAttachOutput.vhdx";
    // The certificate to sign the package is at
    string developerCertPfxFile = "D:\\test\\ContosoApp1\\developerCert.pfx";

    // Step 1. Create the full bundle.
    // Iterate through package layout folders and pack each one.
    DirectoryInfo packageLayoutRootDirectory = new DirectoryInfo(packageLayoutRootPath);
    var packTasks = packageLayoutRootDirectory.EnumerateDirectories()
                .Select(async directory =>
                {
                    PackageInformation packageInfo = await MakeMSIXManager.GetPackageInformation(directory.FullName);

                    var createPackageOptions = new CreatePackageOptions();
                    createPackageOptions.OverwriteOutputFileIfExists = true;
                    string packageOutputFilePath = packageOutputRootDirectoryPath + "\\" + packageInfo.Identity.FullName + ".appx";

                    await MakeMSIXManager.CreatePackage(directory.FullName, packageOutputFilePath, createPackageOptions);
                    return packageOutputFilePath;
                })
                .ToArray();
    await Task.WhenAll(packTasks);

    // Confirm the directory did contain package layouts.
    if (packTasks.Length == 0)
    {
        throw new Exception("No packages found at path: " + packageLayoutRootPath);
    }

    PackageInformation packageInfo = await MakeMSIXManager.GetPackageInformation(packTasks[0].Result);

    // Bundle all the packages together.
    CreateBundleOptions createbundleOptions = new CreateBundleOptions()
    {
        OverwriteOutputFileIfExists = true,
        FlatBundle = true,
        Version = packageInfo.Identity.Version,
    };

    await MakeMSIXManager.CreateBundle(packageOutputRootDirectoryPath, bundleOutputFilePath, createbundleOptions);

    // Sign the bundle
    await Example_SignPackage(developerCertPfxFile, bundleOutputFilePath);

    // Step 2. Create the kozani package from the bundle created in Step 1.
    // Append "Kozani" to the package name, and trim non-english languages from the package.
    string newPackageName = packageInfo.Identity.Name + "Kozani";
    CreateKozaniPackageOptions createKozaniPackageOptions = new CreateKozaniPackageOptions()
    {
        OverwriteOutputFileIfExists = true,
        RemoveExtensions = true,
        Name = newPackageName,
    };
    createKozaniPackageOptions.Languages.Append("en-US");
    await MakeMSIXManager.CreateKozaniPackage(bundleOutputFilePath, kozaniPackageOutputFilePath, createKozaniPackageOptions);

    // Step 3. Create app attach vhd from the bundle created in Step 1.
    CreateMountableImageOptions mountableImageOptions = new CreateMountableImageOptions
    {
        OverwriteOutputFileIfExists = true
    };

    List<string> packagesToAddToImage = new List<string>
    {
        bundleOutputFilePath
    };

    await MakeMSIXManager.CreateMountableImage(packagesToAddToImage, appAttachImageFilePath, mountableImageOptions);
    return;
}
```

## 2.2. Unbundling and unpacking a package to change information

```c#
static async Task ChangeVersionOfAllPackagesInBundle()
{
    // Scenario: A developer is writing code to update the version of all packages in a bundle.

    // Sample arguments.
    var bundleFilePath = new FileInfo("D:\\test\\ContosoApp1\\BuildOutput\\Package\\bundleOutput.msixbundle");
    var outputDirRoot = new FileInfo("D:\\test\\ContosoApp1\\BuildOutput\\newVersion");
    // Staging directories for the files while unpacking and repacking.
    string outputDirForBundle = outputDirRoot + "\\bundle";
    string outputDirRootForPackages = outputDirRoot + "\\unpackedPackages";
    string outputDirForPackedPackages = outputDirRoot + "\\packedPackages";

    Windows.ApplicationModel.PackageVersion newVersion = new Windows.ApplicationModel.PackageVersion(1, 0, 0, 0);

    // Unbundle the bundle to a folder. After the operation the folder will contain the
    // bundled packages as appx\msix packages, as well as the bundle metadata.
    var extractBundleOptions = new ExtractBundleOptions();
    extractBundleOptions.OverwriteOutputFilesIfExists = true;
    await MakeMSIXManager.ExtractBundle(bundleFilePath.FullName, outputDirForBundle, extractBundleOptions);

    // Iterate through the bundled packages and unpack and repack each one with the changed version.
    DirectoryInfo outputBundleDirInfo = new DirectoryInfo(outputDirForBundle);
    var extractTasks = outputBundleDirInfo.EnumerateFiles().Where(file =>
                {
                    // Ignore bundle footprint and metadata files in the folder.
                    return (String.Compare(file.Extension, ".appx", comparisonType: StringComparison.OrdinalIgnoreCase) == 0) ||
                            (String.Compare(file.Extension, ".msix", comparisonType: StringComparison.OrdinalIgnoreCase) == 0);
                })
                .Select(async file =>
                {
                    // Name the output folder for the unpacked package as the file name of the package
                    string outputDirForPackage = outputDirRootForPackages + "\\" + file.Name;

                    var extractPackageOptions = new ExtractPackageOptions();
                    extractPackageOptions.OverwriteOutputFilesIfExists = true;
                    await MakeMSIXManager.ExtractPackage(file.FullName, outputDirForPackage, extractPackageOptions);

                    string outputPackagePath = outputDirForPackedPackages + "\\" + file.Name;

                    // Change the version when re-packing
                    var createPackageOptions = new CreatePackageOptions();
                    createPackageOptions.OverwriteOutputFileIfExists = true;
                    createPackageOptions.Version = newVersion;
                    await MakeMSIXManager.CreatePackage(outputDirForPackage, outputPackagePath, createPackageOptions);
                    return;
                })
                .ToArray();
    await Task.WhenAll(extractTasks);

    string outputPathForBundle = outputDirRoot + "\\" + bundleFilePath.Name;
    // Re-bundle with the new version
    var createBundleOptions = new CreateBundleOptions();
    createBundleOptions.OverwriteOutputFileIfExists = true;
    createBundleOptions.Version = newVersion;
    await MakeMSIXManager.CreateBundle(outputDirForPackedPackages, outputPathForBundle, createBundleOptions);
    
    return;
}
```

## 2.3. Helper methods for examples

Windows has existing non-WinRT APIs for signing packages available in the CryptoAPI
https://learn.microsoft.com/en-us/windows/win32/seccrypto/using-cryptography
For completeness purposes some helper methods to instead find and call signtool.exe
from the Windows SDK are included here.
```c#
/// <summary>
/// Create a process and synchronously wait for it to exit.
/// </summary>
/// <param name="fileName">FileName argument for Process.StartInfo</param>
/// <param name="commandLine">Arguments for Process.StartInfo</param>
/// <returns>Exit code of the process.</returns>
static async Task<int> CreateProcessAndWaitForExitCodeAsync(string fileName, string arguments)
{
    Process process = new Process();
    process.StartInfo.FileName = fileName;
    process.StartInfo.Arguments = arguments;
    process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
    if (!process.Start())
    {
        throw new Exception("Child process failed to start");
    }
    await process.WaitForExitAsync();
    return process.ExitCode;
}

static string GetPlatformSDKPath()
{
    using (RegistryKey? sdkKey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\WOW6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0"))
    {
        string? installPath;
        string? productVersion;
        if ((sdkKey == null) ||
            (sdkKey.GetValueKind("InstallationFolder") != RegistryValueKind.String) ||
            (sdkKey.GetValueKind("ProductVersion") != RegistryValueKind.String) ||
            string.IsNullOrEmpty(installPath = sdkKey.GetValue("InstallationFolder") as string) ||
            string.IsNullOrEmpty(productVersion = sdkKey.GetValue("ProductVersion") as string))
        {
            throw new InvalidOperationException();
        }

        // The install path of the platform sdk in the filesystem always uses version format x.x.x.x
        // even though the version string in the registry may be stored as x.x if the full version is
        // x.x.0.0 
        int versionPartsFound = productVersion.Count(c => c == '.') + 1;
        int versionPartsRequired = 4;
        int versionDigitsToAdd = versionPartsRequired - versionPartsFound;
        for (int i = 0; i < versionDigitsToAdd; i++)
        {
            productVersion += ".0";
        }
        string processorArchitecture = "";
        switch (System.Runtime.InteropServices.RuntimeInformation.OSArchitecture)
        {
            case System.Runtime.InteropServices.Architecture.X64:
                processorArchitecture = "x64";
                break;
            case System.Runtime.InteropServices.Architecture.Arm:
                processorArchitecture = "arm";
                break;
            case System.Runtime.InteropServices.Architecture.Arm64:
                processorArchitecture = "arm64";
                break;
            case System.Runtime.InteropServices.Architecture.X86:
                processorArchitecture = "x86";
                break;
            default:
                throw new Exception("Unknown Windows SDK architecture");
        }

        string platformSDKExecutablePath = Path.Combine(installPath, "bin", productVersion, processorArchitecture);
        return platformSDKExecutablePath;
    }

    throw new Exception("Windows SDK Path not found in registry");
}

static async Task Example_SignPackage(string pfxFile, string packageFile)
{
    string signToolPath = Path.Combine(GetPlatformSDKPath(), "signtool.exe");
    string signToolArguments = "sign /fd SHA256 /f " + pfxFile + " " + packageFile;
    int exitCode = await CreateProcessAndWaitForExitCodeAsync(signToolPath, signToolArguments);
    if (exitCode != 0)
    {
        throw new Exception("Signtool failed with argumemnts: " + signToolArguments);
    }
    return;
}
```

# 3. API Details

```c#
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Microsoft.Kozani.MakeMSIX
{
    [contractversion(1)]
    apicontract MakeMSIXContract{};

    /// Options for creating a package
    [contract(MakeMSIXContract, 1)]
    runtimeclass CreatePackageOptions
    {
        /// Created by callers to pass options into CreatePackage()
        CreatePackageOptions();

        /// Optional replacement package name.
        /// If field is empty, value from AppxManifest.xml is unchanged.
        String Name;

        /// Optional replacement package publisher.
        /// If field is empty, value from AppxManifest.xml is unchanged.
        String Publisher;

        /// Optional replacement package version
        /// If version is 0, value from AppxManifest.xml is unchanged.
        Windows.ApplicationModel.PackageVersion Version;
        
        /// Overwrite output file if it already exists.
        /// Defaults to true.
        Boolean OverwriteOutputFileIfExists;

        /// Validates elements of the package during creation.
        /// Defaults to false.
        Boolean ValidateFiles;
    };

    /// Options for creating a Kozani package
    [contract(MakeMSIXContract, 1)]
    runtimeclass CreateKozaniPackageOptions
    {
        /// Created by callers to pass options into CreateKozaniPackage()
        CreateKozaniPackageOptions();

        /// Remove extensions from the manifest.
        /// Defaults to false.
        Boolean RemoveExtensions;

        /// Optional replacement package name.
        /// If field is empty, value from AppxManifest.xml is unchanged.
        String Name;

        /// Optional replacement package publisher.
        /// If field is empty, value from AppxManifest.xml is unchanged.
        String Publisher;

        /// Optional replacement package version
        /// If version is 0, value from AppxManifest.xml is unchanged.
        Windows.ApplicationModel.PackageVersion Version;

        /// Languages supported by the output package
        /// If field is empty, all languages from the original package are maintained.
        Windows.Foundation.Collections.IVector<String> Languages{ get; };

        /// ScaleFactors supported by the output package
        /// If field is empty, all scale factors from the original package are maintained.
        Windows.Foundation.Collections.IVector<UInt32> ScaleFactors{ get; };

        /// DirectX feature levels supported by the output package
        /// If field is empty, all DirectX feature levels from the original package are maintained.
        Windows.Foundation.Collections.IVector<String> DXFeatureLevels{ get; };

        /// Overwrite output file if it already exists.
        /// Defaults to true.
        Boolean OverwriteOutputFileIfExists;

        /// Validates elements of the package during creation.
        /// Defaults to false.
        Boolean ValidateFiles;
    };

    /// Options for creating a bundle
    [contract(MakeMSIXContract, 1)]
    runtimeclass CreateBundleOptions
    {
        /// Created by callers to pass options into CreateBundle()
        CreateBundleOptions();

        /// Create as a flat bundle. Package locations will be stored as external path references
        /// to files outside the msixbundle file. 
        /// Defaults to false.
        Boolean FlatBundle;

        /// Optional. Sets the version in the AppxBundleManifest.xml
        /// If version is 0, the version is created based on the current time.
        Windows.ApplicationModel.PackageVersion Version;

        /// Overwrite output file if it already exists.
        /// Defaults to true.
        Boolean OverwriteOutputFileIfExists;
    };

    /// Options for unpacking a package
    [contract(MakeMSIXContract, 1)]
    runtimeclass ExtractPackageOptions
    {
        /// Created by callers to pass options into ExtractPackage()
        ExtractPackageOptions();

        /// If true, the operation will overwrite existing files in the output path
        /// when unpacking.
        /// If false, the operation will fail if a file already exists.
        Boolean OverwriteOutputFilesIfExists;
    };

    /// Options for unpacking a package
    [contract(MakeMSIXContract, 1)]
    runtimeclass ExtractBundleOptions
    {
        /// Created by callers to pass options into ExtractBundle()
        ExtractBundleOptions();
        
        /// If true, the operation will overwrite existing files in the output path
        /// when unpacking.
        /// If false, the operation will fail if a file already exists.
        Boolean OverwriteOutputFilesIfExists;
    };

    /// Options for creating a mountable image
    [contract(MakeMSIXContract, 1)]
    runtimeclass CreateMountableImageOptions
    {
        /// Created by callers to pass options into CreateMountableImage()
        CreateMountableImageOptions();
        
        /// Root directory path for packages inside the image.
        /// Defaults to "WindowsApps"
        String PackageRootDirectoryInImage;

        /// Overwrite output file if it already exists.
        /// Defaults to true.
        Boolean OverwriteOutputFileIfExists;
    };

	/// Identity of a package
    runtimeclass PackageIdentity
    {
        /// Name of the package
        String Name{ get; };
        
        /// Publisher of the package
        String Publisher{ get; };

        /// PublisherId of the package
        String PublisherId{ get; };

        /// Version of the package
        Windows.ApplicationModel.PackageVersion Version{ get; };
        
        /// Architecture of the package
        Windows.System.ProcessorArchitecture Architecture{ get; };
        
        /// ResourceId of the package
        String ResourceId{ get; };

        /// FamilyName of the package
        String FamilyName{ get; };
 
        /// FullName of the package.
        String FullName{ get; };
    }

	/// Information about the contents of a package
    runtimeclass PackageInformation
    {
		/// Identity of the package
        PackageIdentity Identity{ get; };

        /// Languages supported by the package
        Windows.Foundation.Collections.IVectorView<String> Languages{ get; };

        /// ScaleFactors supported by the package
        Windows.Foundation.Collections.IVectorView<UInt32> ScaleFactors{ get; };

        /// DirectX feature levels supported by the package
        Windows.Foundation.Collections.IVectorView<String> DXFeatureLevels{ get; };
    }

    /// Static methods for creating and unpacking packages.
    [contract(MakeMSIXContract, 1)]
    runtimeclass MakeMSIXManager
    {
        /// Creates packages from the inputPath as specified by the createPackageOptions.
        /// Output path for the full packaged file.
        static Windows.Foundation.IAsyncAction CreatePackage(
            String inputPath,
            String outputFileName,
            CreatePackageOptions createPackageOptions);

        /// Creates bundles from the inputPath as specified by the createBundleOptions.
        /// Output path for the full bundled file.
        static Windows.Foundation.IAsyncAction CreateBundle(
            String inputPath,
            String outputFileName,
            CreateBundleOptions createBundleOptions);

        /// Unpacks a package at inputFileName as specified by the extractPackageOptions.
        /// The output folder to unpack the package into.
        static Windows.Foundation.IAsyncAction ExtractPackage(
            String inputFileName, 
            String outputPath, 
            ExtractPackageOptions extractPackageOptions);

        /// Unbundles a package at inputFileName as specified by the extractBundleOptions.
        /// The output folder to unpack the bundle package into.
        static Windows.Foundation.IAsyncAction ExtractBundle(
            String inputFileName,
            String outputPath,
            ExtractBundleOptions extractBundleOptions);

        /// Creates a Kozani package from an existing package.
        /// inputFileName can be an appx, appxbundle, msix, or msixbundle
        /// Output path for the kozani packaged file.
        /// Format must match input file. If inputFileName is an msix, then outputFileName must be an msix.
        /// If inputFileName is an msixbundle, then outputFileName must be an msixbundle.
        static Windows.Foundation.IAsyncAction CreateKozaniPackage(
            String inputFileName,
            String outputFileName,
            CreateKozaniPackageOptions createKozaniPackageOptions);

        /// Creates a mountable image that contains the packages at inputFileNames.
        /// Valid file extensions for outputFileName are vhd, vhdx, and CIM.
        /// Can be used for Azure App Attach.
        static Windows.Foundation.IAsyncAction CreateMountableImage(
            Windows.Foundation.Collections.IVector<String> inputFileNames,
            String outputFileName,
            CreateMountableImageOptions createMountableImageOptions);

        /// Gets information about the contents of a package 
        static Windows.Foundation.IAsyncOperation<PackageInformation> GetPackageInformation(String packageFileName);
    };
}
```

# 4. Appendix

# 5. Existing interfaces and options

The existing tools are:
- [Makeappx.exe](https://learn.microsoft.com/en-us/windows/win32/appxpkg/make-appx-package--makeappx-exe-)
    - Shipped in Windows' Platform SDK.
    - Exposes pack, unpack, bundle, unbundle, encrypt, decrypt and content group mapping.
    - Makeappx defines and uses its own file formats for encryption key files and content group
      mapping to allow creation of packages with different payloads from the same folder.

- [Makemsix.exe](https://github.com/Microsoft/msix-packaging) 
    - Available via the msix-packaging project.
    - Exposes pack, unpack, unbundle, and bundle* commands
        - (*Bundle command only supports creation of
          [flat bundles](https://learn.microsoft.com/en-us/windows/msix/package/flat-bundles). Flat
          bundles are bundles where package locations are stored as external path references rather
          than being stored inside the msixbundle file itself. Flat bundles are referred to as
          sparse bundles in the makeappx documentation).
    
- [Msixmgr.exe](https://github.com/Microsoft/msix-packaging) 
    - Available via the msix-packaging project and
      [direct download from learn.microsoft.com](https://learn.microsoft.com/en-us/azure/virtual-desktop/app-attach-msixmgr).
    - Exposes "unpack" command to convert msix packages to vhd, vhdx, cim image files.

None of the existing tools provide a programmatic interface for all aspects of packaging.

- Makeappx.exe provides the only complete implementation of packaging and bundling but requires
process creation and does not return any specific errors from process exit. It also does not support
any of the Azure app attach scenarios.

- Makemsix.exe is a cross-platform implementation of packaging, but does not support a complete set of
bundling features. The functionality is exposed as a command line as well as flat dll exports.

- Msixmgr.exe is mostly for specific Azure app attach packaging scenarios not covered by the other
tools. To use it programmatically would require either process creation or building the
msix-packaging github project and linking the static lib it produces into a project.

## 5.1. Makeappx

### 5.1.1. Pack
Usage:
------
    MakeAppx pack [options] /d <content directory> /p <output package name>
    MakeAppx pack [options] /f <mapping file> /p <output package name>
    MakeAppx pack [options] /m <app package manifest> /f <mapping file> /p <output package name>
    MakeAppx pack [options] /r /m <app package manifest> /f <mapping file> /p <output package name>
    MakeAppx pack [options] /d <content directory> /ep <encrypted output package name> /kf <key file>
    MakeAppx pack [options] /d <content directory> /ep <encrypted output package name> /kt

Options:
--------
    /h, /hashAlgorithm: Specifies a hash algorithm to use for creating the
        block map. Valid algorithm IDs are SHA256, SHA384, and SHA512. The
        default is SHA256.
    /nv, /noValidation: Skips validation that ensures the package will be
        installable on Windows. The validation include: existence of files
        referenced in manifest, ContentGroupMap correctness, and additional
        manifest validation on Protocols and FileTypeAssociation. By default,
        all semantic validation is performed.
    /nfv, /noFileValidation: Skips validation that ensures that the files used
        to create the package (from a folder through /d or layout file through
        /l) exist and are accessible. By default, all files must exist and not
        be read locked. If a file is inaccessible, it will not be added to the
        package.
    /nc, /noCompress: Prevents MakeAppx from compressing files in the package.
        By default, files in the package are compressed based on detected file
        type.
    /m: Specifies the path to an input app manifest which will be used as the
        basis for generating the output app package or resource package's
        manifest. When you use this option, you must also use /f and include a
        [ResourceMetadata] section in the mapping file to specify the resource
        dimensions to be included in the generated manifest.
    /r: Builds a resource package. You must use the /m option with this.
    /kf: Use this option to encrypt or decrypt the package or bundle using a
        key file. This option cannot be combined with /kt.
    /kt: Use this option to encrypt or decrypt the package or bundle using the
        global test key. This option cannot be combined with /kf.
    /cgm: The input content group map (CGM) file path used to create a
        stream-able package. Providing a content group map through this option
        will disable the check that all files in the content group map exist in
        the package.
    /pri, /makepriExeFullPath: You can use /pri to override the default
        MakePri.exe path with the custom fullpath from which makeappx.exe will
        launch the tool from when needed.
    /mp: Specifies the path to a main package in the same package family as the
        resource package being built.  You should provide this when encrypting
        a resource package or when the resource package contains a content
        group map.
    /pb, /publisherBridging: Use this option to add publisher bridging entries
        to the package or bundle.  Publisher bridging is useful when the new
        issued cert subject name changed but the old publisher name is still
        desired to maintain package identity continuity.
    /np, /noParallel: Use this option to disable parallel execution of this
        command.
    /ml, /memoryLimit: Specify maximum memory in bytes that MakeAppx should
        consume while executing in parallel. By default, this value is set to
        half of total physical memory.
    /o, /overwrite: Forces the output to overwrite any existing files with the
        same name. By default, the user is asked whether to overwrite existing
        files with the same name. You can't use this option with /no.
    /no, /noOverwrite: Prevents the output from overwriting any existing files
        with the same name. By default, the user is asked whether to overwrite
        existing files with the same name. You can't use this option with /o.
    /v, /verbose: Enables verbose output of messages to the console.
    /?, /help: Displays this help text.

### 5.1.2. Bundle

Usage:
------
    MakeAppx bundle [options] /d <content directory> /p <output bundle name>
    MakeAppx bundle [options] /f <mapping file> /p <output bundle name>
    MakeAppx bundle [options] /d <content directory> /ep <encrypted output bundle name> /kf MyKeyFile.txt
    MakeAppx bundle [options] /f <mapping file> /ep <encrypted output bundle name> /kt

Options:
--------
    /bv: Specifies the version number of the bundle being created. The version
        must be in dotted-quad notation of four integers
        <Major>.<Minor>.<Build>.<Revision> ranging from 0 to 65535 each. If the
        /bv option is not specified or is set to 0.0.0.0, the bundle is created
        using the current date-time formatted as the version:
        <Year>.<Month-Day>.<Hour-Minute>.<Second-Millisecond>.
    /mo: Generates a bundle manifest only, instead of a full bundle. Input
        files must all be package manifests in XML format if this option is
        specified.
    /fb: Generates a fully [sparse bundle](https://learn.microsoft.com/en-us/windows/msix/package/flat-bundles) 
        where all packages are references to packages that exist outside of 
        the bundle file
    /pri, /makepriExeFullPath: You can use /pri to override the default
        MakePri.exe path with the custom fullpath from which makeappx.exe will
        launch the tool from when needed.
    /kf: Use this option to encrypt or decrypt the package or bundle using a
        key file. This option cannot be combined with /kt.
    /kt: Use this option to encrypt or decrypt the package or bundle using the
        global test key. This option cannot be combined with /kf.
    /o, /overwrite: Forces the output to overwrite any existing files with the
        same name. By default, the user is asked whether to overwrite existing
        files with the same name. You can't use this option with /no.
    /no, /noOverwrite: Prevents the output from overwriting any existing files
        with the same name. By default, the user is asked whether to overwrite
        existing files with the same name. You can't use this option with /o.
    /v, /verbose: Enables verbose output of messages to the console.
    /?, /help: Displays this help text.

### 6.1.3. Unpack
Usage:
------
    MakeAppx unpack [options] /p <input package name> /d <output directory>
    MakeAppx unpack [options] /ep <encrypted input package name> /d <output directory> /kf <key file>
    MakeAppx unpack [options] /ep <encrypted input package name> /d <output directory> /kt

Options:
--------
    /pfn: Unpacks all files to a subdirectory under the specified output path,
        named after the package full name.
    /nv, /noValidation: Skips validation that ensures the package will be
        installable on Windows. The validation include: existence of files
        referenced in manifest, ContentGroupMap correctness, and additional
        manifest validation on Protocols and FileTypeAssociation. By default,
        all semantic validation is performed.
    /kf: Use this option to encrypt or decrypt the package or bundle using a
        key file. This option cannot be combined with /kt.
    /kt: Use this option to encrypt or decrypt the package or bundle using the
        global test key. This option cannot be combined with /kf.
    /nd: Skips decryption when unpacking an encrypted package or bundle.
    /o, /overwrite: Forces the output to overwrite any existing files with the
        same name. By default, the user is asked whether to overwrite existing
        files with the same name. You can't use this option with /no.
    /no, /noOverwrite: Prevents the output from overwriting any existing files
        with the same name. By default, the user is asked whether to overwrite
        existing files with the same name. You can't use this option with /o.
    /v, /verbose: Enables verbose output of messages to the console.
    /?, /help: Displays this help text.

### 6.1.4. Unbundle

Usage:
------
    MakeAppx unbundle [options] /p <input bundle name> /d <output directory>
    MakeAppx unbundle [options] /ep <encrypted input bundle name> /d <output directory> /kf <key file>
    MakeAppx unbundle [options] /ep <encrypted input bundle name> /d <output directory> /kt

Options:
--------
    /pfn: Unpacks all files to a subdirectory under the specified output path,
        named after the package full name.
    /kf: Use this option to encrypt or decrypt the package or bundle using a
        key file. This option cannot be combined with /kt.
    /kt: Use this option to encrypt or decrypt the package or bundle using the
        global test key. This option cannot be combined with /kf.
    /nd: Skips decryption when unpacking an encrypted package or bundle.
    /o, /overwrite: Forces the output to overwrite any existing files with the
        same name. By default, the user is asked whether to overwrite existing
        files with the same name. You can't use this option with /no.
    /no, /noOverwrite: Prevents the output from overwriting any existing files
        with the same name. By default, the user is asked whether to overwrite
        existing files with the same name. You can't use this option with /o.
    /v, /verbose: Enables verbose output of messages to the console.
    /?, /help: Displays this help text.

## 5.2. MakeMsix

MakeMSIX is generally a subset of MakeAppx's functionality. It lacks support for encryption, content
groups, mapping files, and bundle support is limited to only allowing creation of flat bundles
(bundles where the appxbundle file itself only references but does not contain the main and resource
appxpackages)

It does add the ability to optionally unpack all packages inside the bundle in one command using the
-pfn-flat option, as in: makemsix.exe unbundle -p <bundle> -d <directory> -pfn-flat

There is, however, no good option for reversing this command when recreating the packages and
bundle. Callers need to call makemsix pack on each individual package folder and then follow it with
a makemsix bundle call to generate a flat bundle.

### 5.2.1. Pack
Usage:
---------------
    makemsix.exe pack -d <directory> -p <package> [options]

Options:
---------------
    -d <directory> {Required}
        Input directory path.
    -p <package> {Required}
        Output package file path.
    -? [Flag]
        Displays this help text.

### 6.2.2. Bundle
Usage:
---------------
    makemsix.exe bundle -p <outputBundle> [options]

Options:
---------------
    -d <inputDirectory>
        Input directory path.
    -p <outputBundle> {Required}
        Output bundle file path.
    -f <mappingFile>
        Mapping file path.
    -bv <version>
        Specifies the version number of the bundle being created. The version must be in dotted - quad 
        notation of four integers <Major>.<Minor>.<Build>.<Revision> ranging from 0 to 65535 each. If 
        the -bv option is not specified or is set to 0.0.0.0, the bundle is created using the current 
        date - time formatted as the version: <Year>.<Month - Day>.<Hour - Minute>.<Second - Millisecond>.
    -mo [Flag]
        Generates a bundle manifest only, instead of a full bundle. Input files must all be package 
        manifests in XML format if this option is specified.
    -fb [Flag]
        Generates a fully sparse bundle where all packages are references to packages that exist 
        outside of the bundle file.
    -o [Flag]
        Forces the output to overwrite any existing files with the same name.By default, the user is 
        asked whether to overwrite existing files with the same name.You can't use this option with -no.
    -no [Flag]
        Prevents the output from overwriting any existing files with the same name. By default, the 
        user is asked whether to overwrite existing files with the same name.You can't use this option 
        with -o.
    -v [Flag]
        Enables verbose output of messages to the console.
    -? [Flag]
        Displays this help text.

### 6.2.3. Unpack
Usage:
---------------
    makemsix.exe unpack -p <package> -d <directory> [options]

Options:
---------------
    -p <package> {Required}
        Input package file path.
    -d <directory> {Required}
        Output directory path.
    -pfn [Flag]
        Unpacks all files to a subdirectory under the output path, named after the package full name.
    -ac [Flag]
        Allows any certificate. By default the signature origin must be known.
    -ss [Flag]
        Skips enforcement of signed packages. By default packages must be signed.
    -pfn-flat [Flag]
        Same behavior as -pfn for packages.
    -? [Flag]
        Displays this help text.

### 6.2.4. Unbundle

Usage:
---------------
    makemsix.exe unbundle -p <bundle> -d <directory> [options]

Options:
---------------
    -p <bundle> {Required}
        Input bundle file path.
    -d <directory> {Required}
        Output directory path.
    -pfn [Flag]
        Unpacks all files to a subdirectory under the output path, named after the package full name.
    -ac [Flag]
        Allows any certificate. By default the signature origin must be known.
    -ss [Flag]
        Skips enforcement of signed packages. By default packages must be signed.
    -sl [Flag]
        Skips matching packages with the language of the system. By default unpacked resources 
        packages will match the system languages.
    -sp [Flag]
        Skips matching packages with of the same system. By default unpacked application packages 
        will only match the platform.
    -extract-all [Flag]
        Extracts all packages from the bundle.
    -pfn-flat [Flag]
        Unpacks bundle's files to a subdirectory under the specified output path, named after the 
        package full name. Unpacks packages to subdirectories also under the specified output path, 
        named after the package full name. By default unpacked packages will be nested inside the bundle folder.
    -? [Flag]
        Displays this help text.

## 5.3. MSIXMgr

### 5.3.1. Unpack

Usage:
---------------
msixmgr.exe -Unpack -packagePath <path to package> -destination <output folder> [-applyacls]
[-create] [-vhdSize <size in MB>] [-filetype <CIM | VHD | VHDX>] [-rootDirectory <rootDirectory>]

Options:
---------------
    -Unpack: Unpack a package (.appx, .msix, .appxbundle, .msixbundle) and extract its contents to a folder.
    -applyACLs: optional parameter that applies ACLs to the resulting package folder(s) and 
    their parent folder
    -create: optional parameter that creates a new image with the specified -filetype and 
    unpacks the packages to that image
    -destination: the directory to place the resulting package folder(s) in
    -fileType: the type of file to unpack packages to. Valid file types include {VHD, VHDX, CIM}. 
    This is a required parameter when unpacking to CIM files
    -packagePath: the path to the package to unpack OR the path to a directory containing 
    multiple packages to unpack
    -rootDirectory: root directory on an image to unpack packages to. Required parameter 
    for unpacking to new and existing CIM files
    -validateSignature: optional parameter that validates a package's signature file before 
    unpacking the package. This will require that the package's certificate is installed on the machine.
    -vhdSize: the desired size of the VHD or VHDX file in MB. Must be between 5 and 2040000 MB. 
    Use only for VHD or VHDX files

# 6. Summary of existing options in relation to proposed API

# 6.1 Pack and Bundle
Existing tools all treat pack and bundle as separate commands. Though they are similar, each command
does have some options that are irrelevant to the other command. Options that are relevant to
bundling but not packaging are the Bundle Version, which nearly all callers will specify (the
alternative is the tool setting the version based on a timestamp), and allowing creation of flat
bundles. Options that are relevant for packaging but not bundling are hash algorithm, and creation
of streamable packages and resource packages.

In the long term it's likely that these differences in the information and flags required to support
creating a bundle and creating a package will only continue to grow.

# 6.2 Unpack and Unbundle

Existing tools have generally chosen to have unpack and unbundle as separate commands.

In cases where the API is being used programattically to do something like extract all packages and
update every manifest with a different version number, developers will have to handle the
differences between bundles and packages when recreating the package so the benefit of merging
unpack and unbundle seems small.

MSIXMgr defines an unpack command which has different usage from the unpack command of other tools.
The msixmgr unpack command merges creation of an image file and adding packages to that image file
into one command. Since the tool is specifically for creating Azure App Attach images developers are
unlikely to ever need to further interact with the resulting files inside the Azure App Attach
image. For the purposes of this API the unpack command of MSIXMgr seems more similar to a package
conversion like CreateKozaniPackage and so has been renamed to CreateMountableImage rather than
trying to fit all options that are only relevant for "unpacking" to a mountable image into the
unpack command.

The msixmgr unpack command line supports adding all packages in a folder to an image at once. The
CIM file format it supports always expands to fit those apps, but msixmgr does not currently support
expandable vhdx files. This means that the caller needs to know up front the size of all unpacked
packages when creating vhds, which will be difficult to know without either unpacking them first or
reading each package's block map to get file sizes. This API proposes getting rid of that
requirement and having the API implementation itself determine the size of all packages being added
in order to create an image of the correct size. This behavior is more consistent with other types
of package creation and eliminates the API differences between CIM files and VHD\VHDX files.

Callers may find it strange to need to first pack their directory to an msix or msixbundle, and then
create the vhdx from the package, rather than just creating the vhdx directly from the directory.
However, signing is not integrated into any of these tools, and is a separate step that is done
after packaging is complete. The Appx SIP knows how to sign packages, but not vhdx and other mounted
directories. The result is that creating a vhdx with an appx signature file (appxsignature.p7x)
requires first creating the package, then signing it, then creating the vhdx. Allowing creation of a
cim, vhd, or vhdx file directly from a directory seems likely to cause confusion for developers who
may not realize that they won't be able to sign the package in the image.

This API always applies ACLs for the package to the folder, and never validates the signature so
those options in msixmgr have not been exposed. If signature validation of a package (checking that
the root cert of a package is trusted on the current machine) is an important API for callers it can
be done as a separate operation from creation of an image file. This keeps signature concerns
completely outside the scope of this API.
