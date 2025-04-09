# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

# This script overrides AssemblyInfo.cs, AssemblyInfo.ver, and AssemblyInfo.h in build/VersionInfo.
# The parameters ProductMajor and ProductMinor version will be used in the overwrite 
# for the ProductVersion field

# The AssemblyInfo.ver is to be used in an rc file to add VersionInfo to a dll.
# VERSIONINFO_FILENAME must be defined when used
# VERSIONINFO_FILEVERSION and VERSIONINFO_FILEVERSION_STRING is optional

# If VERSIONINFO_FILEVERSION and VERSIONINFO_FILEVERSION_STRING is not defined,
# the ProductMajor and ProductMinor will be used. 

[CmdLetBinding()]
Param(
    [ValidateRange(0, 65535)]
    [int]$ProductMajor,

    [ValidateRange(0, 64)]
    [int]$ProductMinor
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Don't output file with Bom
$utf8NoBomEncoding = New-Object System.Text.UTF8Encoding $False

$scriptFullPath =  (Split-Path -Parent $MyInvocation.MyCommand.Definition)
Write-Verbose "scriptFullPath: $scriptFullPath"

# Default values for CompanyName, ProductName, Copyright
$companyName = "Microsoft Corporation"
$productName = "Windows App SDK"
$copyright = "Copyright (c) Microsoft Corporation. All rights reserved."

# Generating AssemblyInfo.cs override
$assemblyInfoCs = @"
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

[assembly: AssemblyCompany("$companyName")]
[assembly: AssemblyProduct("$productName")]
[assembly: AssemblyCopyright("$copyright")]

[assembly: AssemblyVersion("$ProductMajor.$ProductMinor")]
[assembly: AssemblyFileVersion("$ProductMajor.$ProductMinor")]

[assembly: AssemblyMetadata("IsTrimmable", "True")]
"@

Write-Verbose $assemblyInfoCs
$assemblyInfoCsPath = "$scriptFullPath/AssemblyInfo.cs"
Write-Verbose "Writing $assemblyInfoCsPath..."
[System.IO.File]::WriteAllLines($assemblyInfoCsPath, $assemblyInfoCs, $utf8NoBomEncoding)

# Generating AssemblyInfo.ver override
$assemblyInfoVer = @"
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#define STR1(x) #x
#define DELIM STR1(.)
#define STR2(a,b)       STR1(a) DELIM STR1(b)

#ifndef WINDOWSAPPSDK_RELEASE_MAJOR
#define WINDOWSAPPSDK_RELEASE_MAJOR     $ProductMajor
#endif

#ifndef WINDOWSAPPSDK_RELEASE_MINOR
#define WINDOWSAPPSDK_RELEASE_MINOR     $ProductMinor
#endif

#define WINDOWSAPPSDK_PRODUCT_VERSION           WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR
#define WINDOWSAPPSDK_PRODUCT_VERSION_STRING    STR2(WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR)
#define WINDOWSAPPSDK_COMPANY_NAME              "$companyName"
#define WINDOWSAPPSDK_LEGAL_COPYRIGHT           "$copyright"
#define WINDOWSAPPSDK_PRODUCT_NAME              "$productName"

// Assign default values for things not assigned.

#ifndef VERSIONINFO_FILEVERSION
#define VERSIONINFO_FILEVERSION WINDOWSAPPSDK_PRODUCT_VERSION
#endif

#ifndef VERSIONINFO_FILEVERSION_STRING
#define VERSIONINFO_FILEVERSION_STRING  WINDOWSAPPSDK_PRODUCT_VERSION_STRING
#endif 

#ifndef VERSIONINFO_FILETYPE
#define VERSIONINFO_FILETYPE  VFT_DLL
#endif

#ifndef VERSIONINFO_FILEFLAGS
#ifdef _DEBUG
#define VERSIONINFO_FILEFLAGS VS_FF_DEBUG
#else
#define VERSIONINFO_FILEFLAGS 0
#endif
#endif

// Define the version info resource

VS_VERSION_INFO VERSIONINFO
 PRODUCTVERSION WINDOWSAPPSDK_PRODUCT_VERSION
 FILEVERSION VERSIONINFO_FILEVERSION
 FILETYPE VERSIONINFO_FILETYPE
 FILEFLAGSMASK 0x3fl;
 FILEFLAGS VERSIONINFO_FILEFLAGS 
 FILEOS VOS_NT_WINDOWS32

 BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "CompanyName", WINDOWSAPPSDK_COMPANY_NAME
            VALUE "FileDescription", VERSIONINFO_FILENAME
            VALUE "FileVersion", VERSIONINFO_FILEVERSION_STRING
            VALUE "InternalName", VERSIONINFO_FILENAME
            VALUE "LegalCopyright", WINDOWSAPPSDK_LEGAL_COPYRIGHT
            VALUE "OriginalFilename", VERSIONINFO_FILENAME
            VALUE "ProductName", WINDOWSAPPSDK_PRODUCT_NAME
            VALUE "ProductVersion", WINDOWSAPPSDK_PRODUCT_VERSION_STRING
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x409, 1200
    END
 END
"@

Write-Verbose $assemblyInfoVer
$assemblyInfoVerPath = "$scriptFullPath/AssemblyInfo.ver"
Write-Verbose "Writing $assemblyInfoVerPath..."
[System.IO.File]::WriteAllLines($assemblyInfoVerPath, $assemblyInfoVer, $utf8NoBomEncoding)

# Generating AssemblyInfo.h override
$assemblyInfoH = @"
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef WINDOWSAPPSDK_RELEASE_MAJOR
#define WINDOWSAPPSDK_RELEASE_MAJOR     $ProductMajor
#endif

#ifndef WINDOWSAPPSDK_RELEASE_MINOR
#define WINDOWSAPPSDK_RELEASE_MINOR     $ProductMinor
#endif
"@

Write-Verbose $assemblyInfoH
$assemblyInfoHPath = "$scriptFullPath/AssemblyInfo.h"
Write-Verbose "Writing $assemblyInfoHPath..."
[System.IO.File]::WriteAllLines($assemblyInfoHPath, $assemblyInfoH, $utf8NoBomEncoding)

