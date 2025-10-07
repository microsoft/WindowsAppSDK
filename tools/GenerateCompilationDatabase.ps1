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
    [string]$Ms2ccVersion = "1.3.0",
    [switch]$DownloadMs2cc,
    [string]$Ms2ccPath,
    [switch]$Update
)

$binlogFileBase = Join-Path (Split-Path $PSScriptRoot -parent) "BuildOutput\Binlogs"
$binlogFiles = Get-ChildItem -Path $binlogFileBase -Filter *.binlog -Recurse | Select-Object -ExpandProperty FullName

Write-Host "Binlog files found:"
$binlogFiles | ForEach-Object { Write-Host "    $_" }

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -prerelease -requires Microsoft.Component.MSBuild -property InstallationPath
Write-Host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
Write-Host "msBuildPath: $msBuildPath"

Remove-Item "temp-filtered.log" -ErrorAction SilentlyContinue
Remove-Item "temp-filtered2.log" -ErrorAction SilentlyContinue

foreach ($binlogFile in $binlogFiles)
{
    if (-Not (Test-Path $binlogFile))
    {
        Write-Error "Binlog file not found: $binlogFile"
        exit 1
    }

    & $msBuildPath $binlogFile /v:normal /noconlog /flp:logfile=temp.log

    Select-String -Path "temp.log" -Pattern "Target ""ClCompile"" in file","Cl.exe"  |
        ForEach-Object { $_.Line } |
        Where-Object { $_ -notmatch "Tracker.exe" } |
        Out-File -FilePath "temp-filtered.log" -Append -Encoding utf8

    Remove-Item "temp.log"

    Write-Host "Processed binlog file: $binlogFile"
}

Write-Host "Filtered log file generated at: $(Get-Location)\temp-filtered.log"

$contextPath = ""

# For each line in temp-filtered.log, if it is a "Target " line, extract the project directory and save in the contextPath variable
# if it is a "Cl.exe" line, prepend the contextPath to every source file in that line only if it is
# a relative path, then output the modified line to temp-filtered-2.log
# For example, in the line:
# Target "ClCompile" in file "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.CppCommon.targets" from project "C:\WindowsAppSDK\dev\Detours\Detours.vcxproj" (target "_ClCompile" depends on it):
# Context here would be: "C:\WindowsAppSDK\dev\Detours"
# The source files are the arguments that ends with .cpp, .c, or .h
# They can have spaces in them. If so, they are enclosed in quotes.

$lines = Get-Content "temp-filtered.log"

Write-Host "Processing filtered log to adjust file paths..."

foreach ($line in $lines)
{
    if ($line -match 'Target "ClCompile" in file "([^"]+)" from project "([^"]+)"')
    {
        $contextPath = Split-Path $matches[2] -parent
        Write-Host "Context path set to: $contextPath"
    }
    elseif ($line -match 'Cl\.exe (.+)$')
    {
        $clLine = $matches[1]
        $clArgs = $clLine -split ' (?=(?:[^"]*"[^"]*")*[^"]*$)'

        $modifiedArgs = @()
        foreach ($arg in $clArgs)
        {
            if ($arg -match '^(.*\.(cpp|hpp|c|h))$' -or $arg -match '^"(.*\.(cpp|c|h))"$')
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
            else
            {
                $modifiedArgs += $arg
            }
        }

        $modifiedLine = "Cl.exe " + ($modifiedArgs -join ' ')
        Add-Content -Path "temp-filtered2.log" -Value $modifiedLine
    }
}

Write-Host "Adjusted file paths and generated: $(Get-Location)\temp-filtered2.log"

$ms2ccPath = Join-Path $PSScriptRoot "ms2cc"
$ms2ccExe = Join-Path $ms2ccPath "ms2cc.exe"

if (-Not (Test-Path $ms2ccExe))
{
    Write-Host "Downloading ms2cc..."
    $ms2ccUrl = "https://github.com/freddiehaddad/ms2cc/releases/download/v$Ms2ccVersion/ms2cc-$Ms2ccVersion.zip"
    $zipPath = Join-Path $PSScriptRoot "ms2cc-$Ms2ccVersion.zip"

    try
    {
        Invoke-WebRequest -Uri $ms2ccUrl -OutFile $zipPath -UseBasicParsing
        Write-Host "Downloaded ms2cc to: $zipPath"

        if (-Not (Test-Path $ms2ccPath))
        {
            New-Item -ItemType Directory -Path $ms2ccPath -Force | Out-Null
        }

        Expand-Archive -Path $zipPath -DestinationPath $ms2ccPath -Force
        Write-Host "Extracted ms2cc to: $ms2ccPath"

        Remove-Item $zipPath -Force
        Write-Host "Cleaned up zip file"

        if (Test-Path $ms2ccExe)
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
else
{
    Write-Host "ms2cc already exists at: $ms2ccExe"
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
        $backupPath = Join-Path (Split-Path $PSScriptRoot -parent) "compile_commands_old.json"
        Copy-Item -Path $compileCommandsPath -Destination $backupPath
        Write-Host "Backed up existing compile_commands.json to: $backupPath"
    }
    else
    {
        Write-Host "No existing compile_commands.json found to back up."
    }
}

& $ms2ccExe -i "temp-filtered2.log" -d (Split-Path $PSScriptRoot -parent) -p

Remove-Item "temp-filtered.log"
Remove-Item "temp-filtered2.log"
Write-Host "Temporary files cleaned up."

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

    Remove-Item $backupPath -Force
}

Write-Host "Compilation database generated at: $(Split-Path $PSScriptRoot -parent)\compile_commands.json"
