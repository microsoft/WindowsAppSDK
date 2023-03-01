# Make MSIX API in Windows App SDK

# Background

The Make MSIX api allows developers to create app packages for distribution. The api
provides similar functionality as multiple existing command line tools.

For more details see:

-   [The makeappx command line tool](https://learn.microsoft.com/en-us/windows/win32/appxpkg/make-appx-package--makeappx-exe-)
    Shipped as part of the Windows Development Kit.
    Exposes pack, unpack, bundle, and unbundle commands, as well as encryption support
    via a custom key-file list file, and mapping .

-   [The makemsix command line tool and dll](https://github.com/Microsoft/msix-packaging)
    Available through the github project.
    Exposes pack, unpack, unbundle, and bundle* commands (*Bundle command is not implemented).
    
-   [The msixmgr command line tool](https://github.com/Microsoft/msix-packaging and 
    https://learn.microsoft.com/en-us/azure/virtual-desktop/app-attach-msixmgr)
    Available through github and as a direct download from the learn.microsoft.com site.
    Exposes "unpack" command to convert msix packages to vhd, vhdx, cim image files.

## The problems today

None of the existing tools provide a good programmatic interface for all aspects of packaging.

The makeappx.exe built into windows provides the only complete implementation of packaging
and bundling but requires CreateProcess and does not return any specific errors from process exit.
It also does not support any of the azure app attach scenarios.

The makemsix tool is designed as a cross-platform implementation of packaging, but does not support
the bundle command. The functionality is exposed as a command line as well as flat dll exports.

The msixmgr tool is mostly for specific azure app attach packaging scenarios that are not covered by
the other tools. To use it programmatically would require either using CreateProcess or building
the msix-packaging github project and linking the static lib it produces into a project.

# Existing interfaces and options

## Makeappx

### Pack
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

### Bundle

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
    /fb: Generates a fully sparse bundle where all packages are references to
        packages that exist outside of the bundle file
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

### Unpack
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

### Unbundle

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

## MakeMsix

MakeMSIX is generally a subset of MakeAppx's functionality. It lacks support for
encryption, content groups, mapping files, and bundle support is limited to
only allowing creation of flat-bundles (bundles where the appxbundle file itself
only references but does not contain the main and resource appxpackages)

It does add the ability to optionally unpack all packages inside the bundle
in one command using the -pfn-flat option, as in:
makemsix.exe unbundle -p <bundle> -d <directory> -pfn-flat

There is, however, no good option for reversing this command when recreating the
packages and bundle. Callers need to call makemsix pack on each individual
package folder and then follow it with a makemsix bundle call to generate a
flat bundle.

### Pack
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

### Bundle
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
        Specifies the version number of the bundle being created. The version must be in dotted - quad notation of four integers <Major>.<Minor>.<Build>.<Revision> ranging from 0 to 65535 each. If the -bv option is not specified or is set to 0.0.0.0, the bundle is created using the current date - time formatted as the version: <Year>.<Month - Day>.<Hour - Minute>.<Second - Millisecond>.
    -mo [Flag]
        Generates a bundle manifest only, instead of a full bundle. Input files must all be package manifests in XML format if this option is specified.
    -fb [Flag]
        Generates a fully sparse bundle where all packages are references to packages that exist outside of the bundle file.
    -o [Flag]
        Forces the output to overwrite any existing files with the same name.By default, the user is asked whether to overwrite existing files with the same name.You can't use this option with -no.
    -no [Flag]
        Prevents the output from overwriting any existing files with the same name. By default, the user is asked whether to overwrite existing files with the same name.You can't use this option with -o.
    -v [Flag]
        Enables verbose output of messages to the console.
    -? [Flag]
        Displays this help text.

### Unpack
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

### Unbundle

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
        Skips matching packages with the language of the system. By default unpacked resources packages will match the system languages.
    -sp [Flag]
        Skips matching packages with of the same system. By default unpacked application packages will only match the platform.
    -extract-all [Flag]
        Extracts all packages from the bundle.
    -pfn-flat [Flag]
        Unpacks bundle's files to a subdirectory under the specified output path, named after the package full name. Unpacks packages to subdirectories also under the specified output path, named after the package full name. By default unpacked packages will be nested inside the bundle folder.
    -? [Flag]
        Displays this help text.

## MSIXMgr

### Unpack
msixmgr.exe -Unpack -packagePath <path to package> -destination <output folder> [-applyacls] [-create] [-vhdSize <size in MB>] [-filetype <CIM | VHD | VHDX>] [-rootDirectory <rootDirectory>]

-Unpack: Unpack a package (.appx, .msix, .appxbundle, .msixbundle) and extract its contents to a folder.
                -applyACLs: optional parameter that applies ACLs to the resulting package folder(s) and their parent folder
                -create: optional parameter that creates a new image with the specified -filetype and unpacks the packages to that image
                -destination: the directory to place the resulting package folder(s) in
                -fileType: the type of file to unpack packages to. Valid file types include {VHD, VHDX, CIM}. This is a required parameter when unpacking to CIM files
                -packagePath: the path to the package to unpack OR the path to a directory containing multiple packages to unpack
                -rootDirectory: root directory on an image to unpack packages to. Required parameter for unpacking to new and existing CIM files
                -validateSignature: optional parameter that validates a package's signature file before unpacking the package. This will require that the package's certificate is installed on the machine.
                -vhdSize: the desired size of the VHD or VHDX file in MB. Must be between 5 and 2040000 MB. Use only for VHD or VHDX files

# Summary of existing options

Existing options all treat pack and bundle as separate commands. Though they are similar, each command does have 
some options that are irrelevant to the other command. For bundling that means specifying the Bundle Version, which
nearly all callers will specify (the alternative is the tool setting the version based on a timestamp), and allowing
creation of sparse bundles. For packaging that means hash algorithm, and creation of streamable packages and resource
packages.

In the long term it's likely that these differences in the information and flags required to support creating a bundle
and creating a package will only continue to grow.

Unpack and Unbundle is a somewhat different story. If defined as an atomic operation where a package is unpacked to a folder,
it is less likely that differences will arise between unbundle and unpack. However, as seen with the existing makemsix tool,
as long as pack and bundle are separate operations it may not be especially useful for unbundle and unpack to be joined. Unpacking of
all bundled packages might save time if someone wanted to examine the manifest of a main package inside the bundle,
as might be an expected use case for a command line tool.
But in cases where the api is actually being used programattically, to do something like extract all packages and update
every manifest, say with a different version number, there is no avoiding use of filesystem apis to find each
unpacked package. In such a case merging the unbundle and unpack command into one api call saves very little complexity for
the caller, especially if pack and bundle have not also been merged to allow callers to use one call to package all subfolders
with appxmanifests and then bundle all of them together.

For these reasons pack, bundle, unpack, unbundle have been left as separate commands. 

MSIXMgr defines an unpack command which has fairly different usage from the makeappx unpack command.
The msixmgr unpack command mostly takes options that affect the phase of the operation that creates the vhdx\cim. 
With the set of options to describe the output it looks more like the "pack\bundle" commands of the other tools.
In an api that supports creation of the CIM, VHD, VHDX file as well as creation of msix and msixbundle files, callers may
find it strange at first to need to first pack their directory to an msix, and then create the vhdx from the msix, rather than just
creating the vhdx directly. However, signing is not integrated into any of these tools, and is a separate step that
is done after packaging is complete. The Appx SIP knows how to sign packages, but not vhdx and other mounted directories. The result
is that creating a vhdx with an appx signature file (appxsignature.p7x) requires first creating the package, then signing it, then
creating the vhdx.

The msixmgr command line supports adding all packages in a folder to an image at once, but does not currently support expandable vhdx files.
CIM files meanwhile are always expandable. This means that the caller needs to know up front the size of all unpacked packages only when
creating vhds. This api proposes adding support for dynamic vhds\vhdx files in order to ease that burden .

# Examples

## Packing a package

```cpp
    TEST_METHOD(TestPack)
    {
        winrt::init_apartment();

        // Create package from folder.
        std::wstring packageOutputFilePath{ L"E:\\test\\packagedOutput.msix" };
        try
        {
            PackOptions packOptions = PackOptions();
            packOptions.OverwriteFiles(true);
            packOptions.PackageFilePath(packageOutputFilePath);

            MakeMSIXManager::Pack(L"E:\\test\\unpackedPackageInput", packOptions).get();
        }
        catch (winrt::hresult_error const& ex)
        {
            OutputDebugString(ex.message().c_str());
            winrt::check_hresult(ex.code());
        }

        // Create kozani package from package.
        try
        {
            CreateKozaniPackageOptions kozaniPackOptions = CreateKozaniPackageOptions();
            kozaniPackOptions.OverwriteFiles(true);
            kozaniPackOptions.PackageFilePath(L"E:\\test\\kozaniPackagedOutput.msix");
            MakeMSIXManager::CreateKozaniPackage(packageOutputFilePath, kozaniPackOptions).get();
        }
        catch (winrt::hresult_error const& ex)
        {
            OutputDebugString(ex.message().c_str());
            winrt::check_hresult(ex.code());
        }

        // Create app attach vhd from package.
        try
        {
            std::wstring appAttachImageFilePath{ L"E:\\test\\appAttachOutput.vhdx" };
            CreateMountableImageOptions mountableImageOptions = CreateMountableImageOptions();
            mountableImageOptions.DynamicallyExpandable(true);
            mountableImageOptions.MaximumExpandableImageSizeMegabytes(100);
            MakeMSIXManager::CreateMountableImage(appAttachImageFilePath, mountableImageOptions).get();

            AddPackageToImageOptions addToImageOptions = AddPackageToImageOptions();
            addToImageOptions.PackageRootDirectoryInImage(L"WindowsApps");
            MakeMSIXManager::AddPackageToImage(packageOutputFilePath, appAttachImageFilePath, addToImageOptions).get();
        }
        catch (winrt::hresult_error const& ex)
        {
            OutputDebugString(ex.message().c_str());
            winrt::check_hresult(ex.code());
        }
    }
```

## Bundling a package

```cpp
    TEST_METHOD(TestBundle)
    {
        winrt::init_apartment();
        try
        {
            auto bundleOptions = BundleOptions();
            bundleOptions.OverwriteFiles(true);
            bundleOptions.BundleFilePath(L"E:\\test\\bundledOutput.msixbundle");
            bundleOptions.BundleVersion(winrt::Windows::ApplicationModel::PackageVersion(1, 1, 0, 0));

            MakeMSIXManager::Bundle(L"E:\\test\\unbundledPackageInput", bundleOptions).get();
        }
        catch (winrt::hresult_error const& ex)
        {
            OutputDebugString(ex.message().c_str());
            winrt::check_hresult(ex.code());
        }
    }
```

## Unpacking a package

```cpp
    TEST_METHOD(TestUnpack)
    {
        winrt::init_apartment();
        try
        {
            auto unpackOptions = UnpackOptions();
            unpackOptions.OverwriteFiles(true);
            unpackOptions.UnpackedPackageRootDirectory(L"E:\\test\\unpackedPackageOutput");

            MakeMSIXManager::Unpack(L"E:\\test\\package.msix", unpackOptions).get();
        }
        catch (winrt::hresult_error const& ex)
        {
            OutputDebugString(ex.message().c_str());
            winrt::check_hresult(ex.code());
        }
    }
```

## Unbundling a package

```cpp
    TEST_METHOD(TestUnbundle)
    {
        winrt::init_apartment();
        try
        {
            std::wstring outputDir{ L"E:\\test\\unpackedBundleOutput" };
            auto unbundleOptions = UnbundleOptions();
            unbundleOptions.OverwriteFiles(true);
            unbundleOptions.UnbundledPackageRootDirectory(outputDir);

            MakeMSIXManager::Unbundle(L"E:\\test\\bundle.msixbundle", unbundleOptions).get();

            // Iterate through packages and unpack each one.
            for (const auto& file : std::filesystem::directory_iterator(outputDir))
            {
                auto unpackOptions = UnpackOptions();
                unpackOptions.OverwriteFiles(true);
                std::filesystem::path outputDirForPackage{ outputDir };
                outputDirForPackage /= file.path().stem();
                unpackOptions.UnpackedPackageRootDirectory(outputDirForPackage.c_str());

                MakeMSIXManager::Unpack(file.path().c_str(), unpackOptions).get();
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            OutputDebugString(ex.message().c_str());
            winrt::check_hresult(ex.code());
        }
    }
```

# API Details

```c#
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Microsoft.Kozani.MakeMSIX
{
    [contractversion(1)]
    apicontract MakeMSIXContract{};

    /// Options for creating a package
    [contract(MakeMSIXContract, 1)]
    runtimeclass PackOptions
    {
        /// <summary>
        /// Created by callers to pass options into CreatePackage
        /// </summary>
        PackOptions();

        /// <summary>
        /// Output path for the full packaged file.
        /// </summary>
        String PackageFilePath{ get; set; };

        /// <summary>
        /// Overwrite PackageFilePath if it already exists.
        /// Defaults to true.
        /// </summary>
        Boolean OverwriteFiles{ get; set; };
        /// <summary>
        /// Validates elements of the package during creation.
        /// Defaults to false.
        /// </summary>
        Boolean ValidateFiles{ get; set; };
    };
    
    /// Options for creating a Kozani package
    [contract(MakeMSIXContract, 1)]
    runtimeclass CreateKozaniPackageOptions
    {
        /// <summary>
        /// 
        /// </summary>
        CreateKozaniPackageOptions();

        /// <summary>
        /// Output path for the full packaged file.
        /// Format must match input file. If packageFilePathToConvert is an appx or msix, then PackageFilePath must be an appx or msix.
        /// If packageFilePathToConvert is an appxbundle or msixbundle, then PackageFilePath must be an appxbundle or msixbundle.
        /// </summary>
        String PackageFilePath{ get; set; };

        /// <summary>
        /// Optional replacement package publisher.
        /// If not set, publisher from appxmanifest.xml is unchaged.
        /// </summary>
        String PackagePublisher{ get; set; };

        /// <summary>
        /// Optional replacement package name.
        /// If not set, name from appxmanifest.xml is unchaged.
        /// </summary>
        String PackageName{ get; set; };

        /// <summary>
        /// Overwrite PackageFilePath if it already exists.
        /// Defaults to true.
        /// </summary>
        Boolean OverwriteFiles{ get; set; };
        /// <summary>
        /// Validates elements of the package during creation.
        /// Defaults to false.
        /// </summary>
        Boolean ValidateFiles{ get; set; };
    };

    /// Options for creating a bundle
    [contract(MakeMSIXContract, 1)]
    runtimeclass BundleOptions
    {
        /// <summary>
        /// Created by callers to pass options into Bundle
        /// </summary>
        BundleOptions();

        /// <summary>
        /// Output path for the full bundled file.
        /// </summary>
        String BundleFilePath{ get; set; };

        /// <summary>
        /// Overwrite BundleFilePath if they already exist.
        /// Defaults to true.
        /// </summary>
        Boolean OverwriteFiles{ get; set; };

        /// <summary>
        /// Create as a flat bundle. Package locations will be stored as external path references
        /// rather than being stored inside the msixbundle file itself. 
        /// Defaults to false.
        /// </summary>
        Boolean FlatBundle{ get; set; };

        /// <summary>
        /// Optional. Sets the version in the AppxBundleManifest.xml
        /// If not set the version is created based on the current time.
        /// </summary>
        Windows.ApplicationModel.PackageVersion BundleVersion{ get; set; };
    };

    /// <summary>
    /// Options for unpacking a package
    /// </summary>
    [contract(MakeMSIXContract, 1)]
    runtimeclass UnpackOptions
    {
        /// <summary>
        /// Created by callers to pass options into UnpackPackage
        /// </summary>
        UnpackOptions();
    
        /// <summary>
        /// The output folder to unpack the package into.
        /// </summary>
        String UnpackedPackageRootDirectory{ get; set; };
        /// <summary>
        /// If true, the operation will overwrite existing files in the UnpackedPackageRootDirectory
        /// when unpacking.
        /// If false, the operation will fail if a file already exists.
        /// </summary>
        Boolean OverwriteFiles{ get; set; };
    };

    /// <summary>
    /// Options for unpacking a package
    /// </summary>
    [contract(MakeMSIXContract, 1)]
    runtimeclass UnbundleOptions
    {
        /// <summary>
        /// Created by callers to pass options into UnpackPackage
        /// </summary>
        UnbundleOptions();

        /// <summary>
        /// The output folder to unpack the bundle package into.
        /// </summary>
        String UnbundledPackageRootDirectory{ get; set; };
        /// <summary>
        /// If true, the operation will overwrite existing files in the UnbundledPackageRootDirectory
        /// when unpacking.
        /// If false, the operation will fail if a file already exists.
        /// </summary>
        Boolean OverwriteFiles{ get; set; };
    };
    
    /// <summary>
    /// 
    /// </summary>
    [contract(MakeMSIXContract, 1)]
    runtimeclass CreateMountableImageOptions
    {
        /// <summary>
        /// Created by callers to pass options into CreateMountableImage
        /// </summary>
        CreateMountableImageOptions();
        /// <summary>
        /// Fixed image size in GB. Valid for vhds and vhdx. CIM images automatically expand.
        /// Default is 0.
        /// </summary>
        UInt32 FixedImageSize{ get; set; };

        /// <summary>
        /// Make image file expandable. 
        /// Default is true
        /// </summary>
        Boolean DynamicallyExpandable{ get; set; };
        /// <summary>
        /// Fixed image size in GB. Valid for vhds and vhdx. CIM images have no limit.
        /// Default is 1.
        /// </summary>
        UInt32 MaximumExpandableImageSize{ get; set; };
    };

    /// <summary>
    /// 
    /// </summary>
    [contract(MakeMSIXContract, 1)]
    runtimeclass AddPackageToImageOptions
    {
        /// <summary>
        /// Created by callers to pass options into AddPackageToImage
        /// </summary>
        AddPackageToImageOptions();

        /// <summary>
        /// Root directory on an image to unpack packages to. 
        /// Required parameter for adding to CIM files. Optional for vhd\vhdx.
        /// </summary>
        String PackageRootDirectoryInImage{ get; set; };
    };

    /// <summary>
    /// Static methods for creating and unpacking packages.
    /// </summary>
    [contract(MakeMSIXContract, 1)]
    runtimeclass MakeMSIXManager
    {
        /// <summary>
        /// Creates packages from the directoryPathToPack as specified by the packOptions.
        /// </summary>
        static Windows.Foundation.IAsyncAction Pack(String directoryPathToPack, PackOptions packOptions);
        /// <summary>
        /// Creates bundles from the directoryPathToBundle as specified by the bundleOptions.
        /// </summary>
        static Windows.Foundation.IAsyncAction Bundle(String directoryPathToBundle, BundleOptions bundleOptions);
        /// <summary>
        /// Unpacks a package at packageFilePathToUnpack as specified by the unpackOptions.
        /// </summary>
        static Windows.Foundation.IAsyncAction Unpack(String packageFilePathToUnpack, UnpackOptions unpackOptions);
        /// <summary>
        /// Unbundles a package at bundleFilePathToUnbundle as specified by the unbundleOptions.
        /// </summary>
        static Windows.Foundation.IAsyncAction Unbundle(String bundleFilePathToUnbundle, 
            UnbundleOptions unbundleOptions);
        /// <summary>
        /// Creates a Kozani package from an existing package.
        /// packageFilePathToConvert can be an appx, appxbundle, msix, or msixbundle
        /// </summary>
        static Windows.Foundation.IAsyncAction CreateKozaniPackage(String packageFilePathToConvert,
            CreateKozaniPackageOptions createKozaniPackageOptions);
        

        /// <summary>
        /// Mount the image at imageFilePathToMount
        /// </summary>
        static Windows.Foundation.IAsyncAction Mount(String imageFilePathToMount, Boolean readOnly);

        /// <summary>
        /// Unmount the image that was mounted from imageFilePathToUnmount
        /// </summary>
        static Windows.Foundation.IAsyncAction Unmount(String imageFilePathToUnmount);

        /// <summary>
        /// Create mountable image at imageFilePath. Valid file extensions are vhd, vhdx, and CIM.
        /// </summary>
        static Windows.Foundation.IAsyncAction CreateMountableImage(String imageFilePath, 
            CreateMountableImageOptions createMountableImageOptions);

        /// <summary>
        /// Add the package at packageFilePath to the image at imageFilePath.
        /// </summary>
        static Windows.Foundation.IAsyncAction AddPackageToImage(String packageFilePath, String imageFilePath, 
            AddPackageToImageOptions addPackageToImageOptions);
    };
}


```

# Appendix
