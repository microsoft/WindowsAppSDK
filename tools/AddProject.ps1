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

.PARAMETER Verbose
    Display detailed information

.EXAMPLE
    AddProject -List -Verbose
    AddProject -Add -Template dev.cpp.dll.winrt -Name EnvironmentManager
#>

Param(
    [Switch]$List=$false,

    [String]$Add=$false,

    [String]$Name=$null,

    [String]$Feature=$null,

    [Switch]$Verbose=$false
)

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

function Write-Verbose
{
    param(
        [Parameter(Mandatory=$true)]
        [string]$Message
    )

    if ($Verbose -eq $true)
    {
        Write-Host $Message
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

function Get-Language
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

function Get-Target
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

function Get-Content
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

function List-ProjectTemplates
{
    $template_path = $(Get-ProjectTemplatePath)
    $templates_dirs = $(Get-ChildItem -Path $template_path -Attributes Directory)
    $templates = @()
    ForEach ($pt in $templates_dirs)
    {
        $id = $pt.BaseName
        $fields = $id -Split "\."
        $template = [PSCustomObject]@{}
        $template | Add-Member -MemberType NoteProperty -Name 'Template' -Value $id
        $template | Add-Member -MemberType NoteProperty -Name 'Type' -Value $fields[0]
        $language = Get-Language $fields[1]
        $template | Add-Member -MemberType NoteProperty -Name 'Language' -Value $language
        $target = Get-Target $fields[2]
        $template | Add-Member -MemberType NoteProperty -Name 'Target' -Value $target
        $content = Get-Content $fields[3]
        $template | Add-Member -MemberType NoteProperty -Name 'Content' -Value $content
        $templates += $template
    }
    $templates | Sort-Object -Property Template | Format-Table Template,Type,Language,Target,Content -AutoSize | Out-Default
}

function Add-Project
{
}

if ($List -eq $true)
{
    $null = List-ProjectTemplates
}
if ($Add -eq $true)
{
    $null = Add-Project
}
