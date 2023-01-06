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

if ($Name -NotMatch "^[A-Za-z0-9_]+$")
{
    Write-Output "ERROR: -Name must match the pattern [A-Za-z0-9_]+"
    Exit 1
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
    if ($ext -eq '.vcxproj')
    {
        $projectguid = "<ProjectGuid>{00000000-0000-0000-0000-000000000000}</ProjectGuid>"
        $newguid = $(New-Guid).Guid
        $newprojectguid = "<ProjectGuid>{$($newguid)}</ProjectGuid>"
        $content = $content -Replace $projectguid, $newprojectguid
    }

    $content
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
        $templates += $t
    }

    $templates
}

function List-ProjectTemplates
{
    $templates = Get-ProjectTemplates
    $templates | Sort-Object -Property Template | Format-Table Template,Type,Language,Target,Content -AutoSize | Out-Default
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
    $sourcedir = Join-Path $(Get-ProjectTemplatePath) $id
    $files = Get-ChildItem $sourcedir
    $count = 0
    ForEach ($f in $files)
    {
        $source = $f.FullName

        # Change placemarkers in file content and filenames to the project name
        # NOTE: The placemarker "Purojekuto Tenpuret" is Japanese for "Project Template" :-)
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
