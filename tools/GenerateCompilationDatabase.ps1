# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Generates a compilation database (compile_commands.json) from MSBuild binlog files.

.DESCRIPTION
    This script processes MSBuild binary log files (.binlog) to extract compilation commands
    and generates a compilation database in JSON format (compile_commands.json). It uses the
    ms2cc tool to convert the filtered log into the desired format.

.PARAMETER Ms2ccVersion
    Specifies the version of ms2cc to download and use. Default is "1.3.0".

.PARAMETER DownloadMs2cc
    If set, it allows the script to download the specified version of ms2cc if it is not found
    in the expected location.

.PARAMETER Ms2ccPath
    Specifies a custom path to the ms2cc executable. If not provided, the script will download
    ms2cc to a default location.

.PARAMETER Update
    If set, the script will update an existing compile_commands.json file by merging new entries
    with existing ones instead of overwriting it.

.EXAMPLE
    .\GenerateCompilationDatabase.ps1 -Ms2ccVersion "1.3.0" -DownloadMs2cc -Update

    Generates or updates the compilation database using ms2cc version 1.3.0, downloading it if necessary.
#>

Param(
    [switch]$DownloadMs2cc,
    [string]$Ms2ccExePath,
    [string]$Ms2ccUrl = "https://github.com/freddiehaddad/ms2cc/releases/download/v1.3.0/ms2cc-1.3.0.zip",
    [switch]$Update
)

if (-Not $Ms2ccExePath -and -Not $DownloadMs2cc)
{
    Write-Error "ms2cc.exe not found at $ms2ccExe. Please provide a valid path using -Ms2ccExePath or allow downloading with -DownloadMs2cc."
    exit 1
}

$binlogFileBase = Join-Path (Split-Path $PSScriptRoot -parent) "BuildOutput\Binlogs"
$binlogFiles = Get-ChildItem -Path $binlogFileBase -Filter *.binlog -Recurse | Select-Object -ExpandProperty FullName

Write-Host "Binlog files found:"
$binlogFiles | ForEach-Object { Write-Host "    $_" }

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -prerelease -requires Microsoft.Component.MSBuild -property InstallationPath
Write-Verbose "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
Write-Verbose "msBuildPath: $msBuildPath"

$temp = Join-Path (Split-Path $PSScriptRoot -parent) "temp"

Write-Verbose "Using temporary path: $temp"

if (-not (Test-Path -Path $temp -PathType Container))
{
    Write-Verbose "Creating temporary directory: $temp"
    New-Item -ItemType Directory -Path $temp | Out-Null
}

if (Test-Path "$temp\temp-filtered.log")
{
    Write-Verbose "Removing existing filtered log: $temp\temp-filtered.log"
    Remove-Item "$temp\temp-filtered.log" -Force
}

if (Test-Path "$temp\temp-filtered2.log")
{
    Write-Verbose "Removing existing filtered log: $temp\temp-filtered2.log"
    Remove-Item "$temp\temp-filtered2.log" -Force
}

$tempFilteredLog = Join-Path $temp "temp-filtered.log"

foreach ($binlogFile in $binlogFiles)
{
    if (-Not (Test-Path $binlogFile))
    {
        Write-Error "Binlog file not found: $binlogFile"
        exit 1
    }

    $tempLog = Join-Path $temp "temp.log"

    & $msBuildPath $binlogFile /v:normal /noconlog /flp:logfile=$tempLog

    Select-String -Path $tempLog -Pattern "Target ""ClCompile"" in file","Cl.exe"  |
        ForEach-Object { $_.Line } |
        Where-Object { $_ -notmatch "Tracker.exe" } |
        Out-File -FilePath $tempFilteredLog -Append -Encoding utf8

    Remove-Item $tempLog -Force

    Write-Verbose "Processed binlog file: $binlogFile"
}

Write-Verbose "Filtered log file generated at: $tempFilteredLog"

$contextPath = ""

# For each line in temp-filtered.log, if it is a "Target " line, extract the project directory and save in the contextPath variable
# if it is a "Cl.exe" line, prepend the contextPath to every source file in that line only if it is
# a relative path, then output the modified line to temp-filtered-2.log
# For example, in the line:
# Target "ClCompile" in file "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.CppCommon.targets" from project "C:\WindowsAppSDK\dev\Detours\Detours.vcxproj" (target "_ClCompile" depends on it):
# Context here would be: "C:\WindowsAppSDK\dev\Detours"
# The source files are the arguments that ends with .cpp, .c, or .h
# They can have spaces in them. If so, they are enclosed in quotes.

$tempFiltered2Log = Join-Path $temp "temp-filtered2.log"
$lines = Get-Content $tempFilteredLog

Write-Verbose "Processing filtered log to adjust file paths..."

foreach ($line in $lines)
{
    if ($line -match 'Target "ClCompile" in file "([^"]+)" from project "([^"]+)"')
    {
        $contextPath = Split-Path $matches[2] -parent
        Write-Verbose "Context path set to: $contextPath"
    }
    elseif ($line -match 'Cl\.exe (.+)$')
    {
        $clLine = $matches[1]
        $clArgs = $clLine -split ' (?=(?:[^"]*"[^"]*")*[^"]*$)'

        $modifiedArgs = @()
        foreach ($arg in $clArgs)
        {
            if ($arg -match '^(.*\.(cpp|hpp|c|h))$' -or $arg -match '^"(.*\.(cpp|hpp|c|h))"$')
            {
                $filePath = $arg.Trim('"')
                if (-Not ([System.IO.Path]::IsPathRooted($filePath)))
                {
                    $filePath = Join-Path $contextPath $filePath
                }
                if ($arg.StartsWith('"') -and $arg.EndsWith('"'))
                {
                    $modifiedArgs += '"' + $filePath + '"'
                }
                else
                {
                    $modifiedArgs += $filePath
                }
            }
            elseif ($arg -match '^/Yu(.*)$')
            {
                $pchPath = $matches[1].Trim('"')
                if (-Not ([System.IO.Path]::IsPathRooted($pchPath)))
                {
                    $pchPath = Join-Path $contextPath $pchPath
                }
                $modifiedArgs += '/Yu"' + $pchPath + '"'
            }
            else
            {
                $modifiedArgs += $arg
            }
        }

        # Move the /I argument that matches the contextPath to be the first /I argument.
        # This is to ensure that the context include path is always first and clangd can find the headers
        # on the correct path. This is important because clangd tries to find headers in the order
        # of the include paths, but for the precompiled headers that are included with angular brackets
        # it comes from the context path. The /Yu argument has a absolute path but for
        # some reason clangd does not use that path to find the precompiled header that is included.
        $includeArgs = $modifiedArgs | Where-Object { $_ -like '/I*' }
        $otherArgs = $modifiedArgs | Where-Object { $_ -notlike '/I*' }
        # Find the /I argument that matches the contextPath ignoring case and the trailing slash
        $contextIncludeArg = $includeArgs | Where-Object { $_ -ieq ("/I$contextPath") -or $_ -ieq ("/I$contextPath\") } | Select-Object -First 1

        if ($contextIncludeArg)
        {
            Write-Host "Moving context include path to the front: $contextIncludeArg"
            $includeArgs = $includeArgs | Where-Object { $_ -ne $contextIncludeArg }
            $modifiedArgs = @($contextIncludeArg) + $includeArgs + $otherArgs
        }

        $modifiedLine = "Cl.exe " + ($modifiedArgs -join ' ')
        Add-Content -Path $tempFiltered2Log -Value $modifiedLine
    }
}

Write-Verbose "Adjusted file paths and generated: $tempFiltered2Log"

if ($Ms2ccExePath)
{
    if (-Not (Test-Path $Ms2ccExePath))
    {
        Write-Error "Provided ms2cc.exe path does not exist: $Ms2ccExePath"
        exit 1
    }
    Write-Host "Using provided ms2cc.exe path: $ms2ccExe"
}
elseif ($DownloadMs2cc)
{
    Write-Host "Downloading ms2cc..."
    $zipPath = Join-Path $temp "ms2cc.zip"
    $ms2ccPath = Join-Path $temp "ms2cc"
    $Ms2ccExePath = Join-Path $ms2ccPath "ms2cc.exe"

    try
    {
        Invoke-WebRequest -Uri $Ms2ccUrl -OutFile $zipPath -UseBasicParsing
        Write-Host "Downloaded ms2cc to: $zipPath"

        if (-Not (Test-Path $ms2ccPath))
        {
            New-Item -ItemType Directory -Path $ms2ccPath -Force | Out-Null
        }

        Expand-Archive -Path $zipPath -DestinationPath $ms2ccPath -Force
        Write-Verbose "Extracted ms2cc to: $ms2ccPath"

        Remove-Item $zipPath -Force
        Write-Verbose "Cleaned up zip file"

        if (Test-Path $ms2ccExePath)
        {
            Write-Host "ms2cc successfully downloaded and extracted"
        }
        else
        {
            Write-Error "Failed to extract ms2cc.exe"
            exit 1
        }
    }
    catch
    {
        Write-Error "Failed to download or extract ms2cc: $_"
        exit 1
    }
}

$backupPath = $null

# If the -Update flag is provided, we want to update an existing compile_commands.json
# instead of overwriting it.
if ($Update)
{
    # Save the old compile_commands.json if it exists in a new file
    $compileCommandsPath = Join-Path (Split-Path $PSScriptRoot -parent) "compile_commands.json"
    if (Test-Path $compileCommandsPath)
    {
        $backupPath = Join-Path $temp "compile_commands_old.json"
        Copy-Item -Path $compileCommandsPath -Destination $backupPath
        Write-Host "Backed up existing compile_commands.json to: $backupPath"
    }
    else
    {
        Write-Host "No existing compile_commands.json found to back up."
    }
}

& $Ms2ccExePath -i $tempFiltered2Log -d (Split-Path $PSScriptRoot -parent) -p

if ($Update -and (Test-Path $backupPath))
{
    # Merge the old and new compile_commands.json files
    $newCommands = Get-Content -Raw -Path (Join-Path (Split-Path $PSScriptRoot -parent) "compile_commands.json") | ConvertFrom-Json
    $oldCommands = Get-Content -Raw -Path $backupPath | ConvertFrom-Json

    # What defines the uniqueness of a command is the combination of "file" and "directory"
    # We want to merge the old and new commands, preferring the new ones in case of duplicates
    $mergedCommands = @{}
    foreach ($cmd in $oldCommands + $newCommands)
    {
        $key = "$($cmd.file)|$($cmd.directory)"
        $mergedCommands[$key] = $cmd
    }
    $mergedCommands.Values | ConvertTo-Json -Depth 10 | Set-Content -Path (Join-Path (Split-Path $PSScriptRoot -parent) "compile_commands.json") -Encoding utf8
    Write-Host "Merged old and new compile_commands.json files."
}

Remove-Item $temp -Recurse -Force
Write-Verbose "Temporary files cleaned up."
Write-Host "Compilation database generated at: $(Split-Path $PSScriptRoot -parent)\compile_commands.json"
