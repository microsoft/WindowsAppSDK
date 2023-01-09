# Make a valid AppxManifest.xml from a templated file and variable substititon

<#
.SYNOPSIS
    Add a new project to the repository from the available project templates.

.DESCRIPTION
    Review the current environment and fix or warn if anything is amiss. This includes...

.PARAMETER List
    List the available project templates.

.PARAMETER Add
    Add a new project based on one of the available templates.

.PARAMETER Template
    The project template to use for the new project.

.PARAMETER Feature
    The project's parent feature.

.PARAMETER Name
    The project's name.

.EXAMPLE
    AddProject -List -Verbose
    AddProject -Add -Template dev.cpp.dll.winrt -Name EnvironmentManager
#>

# NOTE: Project Templates must be in a directory \tools\ProjectTemplates\<type>.<language>.<target>.<content>
#       For example, \tools\ProjectTemplates\dev.cpp.exe.console for a \dev C++ project creating a console-mode EXE
# NOTE: Project Templates have their name substituted for the placemarker.
# NOTE: Project Templates MUST have a metadata file named PurojekutoTenpuret.Metadeta.
# NOTE: The placemarker phrases "Purojekuto Tenpuret" and "Metadeta" are Japanese for "Project Template" and "metadata" :-)

[CmdletBinding(SupportsShouldProcess=$true)]
Param(
    [Switch]$List=$false,

    [Switch]$Add=$false,

    [String]$Template=$null,

    [String]$Name=$null,

    [String]$Feature=$null
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = 'Stop'

if (($List -eq $true) -and ($Add -eq $true))
{
    Write-Output "ERROR: Specify -Add or -List (mutually exclusive)"
    Exit 1
}
elseif (($List -eq $false) -and ($Add -eq $false))
{
    Write-Output "ERROR: Specify a command (-Add or -List)"
    Exit 1
}

if ($Add -eq $true)
{
    if ([string]::IsNullOrEmpty($Template))
    {
        Write-Output "ERROR: -Add requires -Template parameter"
        Exit 1
    }

    if ([string]::IsNullOrEmpty($Name))
    {
        Write-Output "ERROR: -Add requires -Name parameter"
        Exit 1
    }

    if ([string]::IsNullOrEmpty($Feature))
    {
        Write-Output "ERROR: -Add requires -Feature parameter"
        Exit 1
    }
}

function Get-ProjectRoot
{
    return $(Get-Item $PSScriptRoot).Parent.FullName
}

function Get-TempPath
{
    $root = Get-ProjectRoot
    $temp = Join-Path $root 'temp'
    if (-not(Test-Path -Path $temp -PathType Container))
    {
        Write-Host "Creating $temp..."
        New-Item -Path $temp -ItemType Directory -Force
    }
    return $temp
}

function Get-UserPath
{
    $root = Get-ProjectRoot
    $user = Join-Path $root '.user'
    if (-not(Test-Path -Path $user -PathType Container))
    {
        Write-Host "Creating $user..."
        $null = New-Item -Path $user -ItemType Directory -Force
    }
    return $user
}

function Get-ProjectTemplatePath
{
    $root = Get-ProjectRoot
    $tools = Join-Path $root 'tools'
    $templates = Join-Path $tools 'ProjectTemplates'
    return $templates
}

function Get-TemplateLanguage
{
    param(
        [string]$language
    )

    if ($language -eq 'cpp')
    {
        'C++'
    }
    elseif ($language -eq 'cs')
    {
        'C#'
    }
    else
    {
        $language
    }
}

function Get-TemplateTarget
{
    param(
        [string]$target
    )

    if ($target -eq 'dll')
    {
        'DLL'
    }
    elseif ($language -eq 'exe')
    {
        'EXE'
    }
    else
    {
        $target
    }
}

function Get-TemplateContent
{
    param(
        [string]$content
    )

    if ($content -eq 'winrt')
    {
        'WinRT'
    }
    else
    {
        $content
    }
}

function Get-UpdatedContent
{
    param(
        [string]$filename,
        [string]$content
    )

    $ext = [System.IO.Path]::GetExtension($filename)
    if ($ext -eq '.h')
    {
        $libid = "LIBID-00000000-0000-0000-0000-000000000000"
        $newguid = $(New-Guid).Guid
        $newlibid = "$($newguid)"
        $content = $content -Replace $libid, $newlibid

        $clsiduuid = "CLSID-UUID-00000000-0000-0000-0000-000000000000"
        $newguid = $(New-Guid).Guid
        $newclsiduuid = "$($newguid)"
        $content = $content -Replace $clsiduuid, $newclsiduuid
        $clsidguid = "CLSID-GUID-0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }"
        $fields = $newguid -Split '-'
        $newclsid_guid = "0x$($fields[0]), 0x$($fields[1]), 0x$($fields[2]), { 0x$($fields[3].Substring(0,2)), 0x$($fields[3].Substring(2,2)), 0x$($fields[4].Substring(0,2)), 0x$($fields[4].Substring(2,2)), 0x$($fields[4].Substring(4,2)), 0x$($fields[4].Substring(6,2)), 0x$($fields[4].Substring(8,2)), 0x$($fields[4].Substring(10,2)) }"
        $content = $content -Replace $clsidguid, $newclsidguid
    }
    elseif ($ext -eq '.idl')
    {
        $uuid = "[uuid(00000000-0000-0000-0000-000000000000)]"
        $newguid = $(New-Guid).Guid
        $newuuid = "[uuid($($newguid))]"
        $content = $content -Replace $uuid, $newuuid
    }
    elseif ($ext -eq '.vcxproj')
    {
        $projectguid = "<ProjectGuid>{00000000-0000-0000-0000-000000000000}</ProjectGuid>"
        $newguid = $(New-Guid).Guid
        $newprojectguid = "<ProjectGuid>{$($newguid)}</ProjectGuid>"
        $content = $content -Replace $projectguid, $newprojectguid
    }

    $content
}

function Get-ProjectTemplateMetadata
{
    param(
        [string]$path,
        [string]$id
    )

    $sourcedir = Join-Path $(Get-ProjectTemplatePath) $id
    $filename = Join-Path $sourcedir "PurojekutoTenpuret.Metadeta"
    if (-not(Test-Path -Path $filename -PathType Leaf))
    {
        Write-Host "ERROR: Metadata missing ($filename)"
        Exit 1
    }
    $metadata = Get-Content $filename -EA:Stop -Raw | ConvertFrom-Json

    $metadata
}

function Get-ProjectTemplates
{
    $template_path = $(Get-ProjectTemplatePath)
    $templates_dirs = $(Get-ChildItem -Path $template_path -Attributes Directory)
    $templates = @()
    ForEach ($pt in $templates_dirs)
    {
        $id = $pt.BaseName
        $fields = $id -Split "\."
        $t = [PSCustomObject]@{}
        $t | Add-Member -MemberType NoteProperty -Name 'Template' -Value $id
        $t | Add-Member -MemberType NoteProperty -Name 'Type' -Value $fields[0]
        $language = Get-TemplateLanguage $fields[1]
        $t | Add-Member -MemberType NoteProperty -Name 'Language' -Value $language
        $target = Get-TemplateTarget $fields[2]
        $t | Add-Member -MemberType NoteProperty -Name 'Target' -Value $target
        $content = Get-TemplateContent $fields[3]
        $t | Add-Member -MemberType NoteProperty -Name 'Content' -Value $content

        $metadata = Get-ProjectTemplateMetadata $template_path $id
        $t | Add-Member -MemberType NoteProperty -Name 'Description' -Value $metadata.Description
        $t | Add-Member -MemberType NoteProperty -Name 'Libraries' -Value $metadata.Libraries
        $t | Add-Member -MemberType NoteProperty -Name 'Name_AllowedRegex' -Value $metadata.Name.AllowedRegex

        $templates += $t
    }

    $templates
}

function List-ProjectTemplates
{
    $templates = Get-ProjectTemplates
    $templates | Sort-Object -Property Template | Format-Table Template,Type,Language,Target,Content,Description,Libraries -AutoSize | Out-Default
}

function Add-Project
{
    if ([string]::IsNullOrEmpty($Template))
    {
        Write-Host "ERROR: -Add requires -Template"
        Exit 1
    }
    $templates = Get-ProjectTemplates
    $t = $templates | Where-Object { $_.Template -eq $Template }
    if ($t -eq $null)
    {
        Write-Host "ERROR: Template $Template not found. Use -List to list the available templates"
        Exit 1
    }
    $id = $t.Template
    if ([string]::IsNullOrEmpty($Name))
    {
        Write-Host "ERROR: -Add requires -Name"
        Exit 1
    }
    $sourcedir = Join-Path $(Get-ProjectTemplatePath) $id
    $sourcemetadatafilename = Join-Path $sourcedir "PurojekutoTenpuret.Metadeta"
    $sourcemetadata = Get-Content $sourcemetadatafilename -EA:Stop -Raw | ConvertFrom-Json
    if ($Name -NotMatch $sourcemetadata.Name.AllowedRegex)
    {
        Write-Host "ERROR: -Name doesn't match template's required pattern `"$($sourcemetadata.Name.AllowedRegex)`""
        Exit 1
    }

    Write-Host "Creating project $Name from template $Template"

    $root = Get-ProjectRoot
    $targetdir = Join-Path $root $t.Type.ToLowerInvariant()
    if (-not([string]::IsNullOrEmpty($Feature)))
    {
        $targetdir = Join-Path $targetdir $Feature
    }
    $targetdir = Join-Path $targetdir $Name
    if (Test-Path -Path $targetdir)
    {
        Write-Host "ERROR: Target directory exists ($targetdir). Remove to proceed"
        Exit 1
    }
    Write-Host "Creating $targetdir"
    $null = New-Item $targetdir -ItemType Directory

    Write-Host "Creating project files..."
    $files = Get-ChildItem $sourcedir -Exclude 'PurojekutoTenpuret.Metadeta'
    $count = 0
    ForEach ($f in $files)
    {
        $source = $f.FullName

        # Change placemarkers in file content and filenames to the project name
        $in = Get-Content -Path $source -Encoding utf8 -Raw
        $out = $(Get-UpdatedContent $source $in)
        $out = $out -Replace 'PurojekutoTenpuret', $Name
        $out = $out -Replace 'PurojekutoTenpuret'.ToUpperInvariant(), $Name.ToUpperInvariant()
        $out = $out -Replace 'PurojekutoTenpuret'.ToLowerInvariant(), $Name.ToLowerInvariant()
        $out = $out.TrimEnd()

        $outfn = $f -Replace 'PurojekutoTenpuret', $Name
        $outfn = $outfn -Replace 'PurojekutoTenpuret'.ToUpperInvariant(), $Name.ToUpperInvariant()
        $outfn = $outfn -Replace 'PurojekutoTenpuret'.ToLowerInvariant(), $Name.ToLowerInvariant()
        $target = Join-Path $targetdir $outfn

        Write-Host "Transforming $f to $outfn"
        $null = Set-Content $target -Value $out -Encoding utf8

        $count++
    }
    Write-Output "$count files copied to new project $targetdir"
    Write-Output "Coding time!"
}

if ($List -eq $true)
{
    $null = List-ProjectTemplates
}
if ($Add -eq $true)
{
    $null = Add-Project
}
