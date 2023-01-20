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
# NOTE: The placemarker phrases "Tokucho", "Purojekuto Tenpuret" and "Metadeta" are Japanese for "Feature", "Project Template" and "metadata" :-)

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
    Write-Host "ERROR: Specify -Add or -List (mutually exclusive)" -ForegroundColor Red -BackgroundColor Black
    Exit 1
}
elseif (($List -eq $false) -and ($Add -eq $false))
{
    Write-Host "ERROR: Specify a command (-Add or -List)" -ForegroundColor Red -BackgroundColor Black
    Exit 1
}

if ($Add -eq $true)
{
    if ([string]::IsNullOrEmpty($Template))
    {
        Write-Host "ERROR: -Add requires -Template parameter" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }

    if ([string]::IsNullOrEmpty($Name))
    {
        Write-Host "ERROR: -Add requires -Name parameter" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }

    if ([string]::IsNullOrEmpty($Feature))
    {
        Write-Host "ERROR: -Add requires -Feature parameter" -ForegroundColor Red -BackgroundColor Black
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

function Get-Abbreviation
{
    param(
        [string]$s
    )

    $s = $s -cReplace "[^A-Za-z]+", "."
    $s = $s -cReplace "[^A-Z.]", ""

    $s
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
    elseif ($target -eq 'exe')
    {
        'EXE'
    }
    elseif ($target -eq 'exe+dll')
    {
        'EXE+DLL'
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

    # Standard macro substitutions (all files)
    $content = $content.Replace("{MACRO-UUID-0001}", "{$($global:macro_uuid_0001)}")
    $content = $content.Replace("{MACRO-UUID-0002}", "{$($global:macro_uuid_0002)}")

    # Filetype-specific substitutions
    $featurenamespace = $Feature -Replace "[^A-Za-z0-9_]", "::"
    $featuredotnamespace = $Feature -Replace "[^A-Za-z0-9_]", "."
    $featuresymbol = $Feature -Replace "[^A-Za-z0-9_]", "_"
    $namenofeature = $Name.Replace($Feature, "")

    $featureAbbreviation = Get-Abbreviation $Feature
    $content = Get-Substitution $content 'TokuchoAbbreviation' $featureAbbreviation

    $nameAbbreviation = Get-Abbreviation $Name
    $content = Get-Substitution $content 'PurojekutoTenpuretAbbreviation' $nameAbbreviation

    $namenofeature = $Name.Replace($Feature, "")
    $namenofeatureAbbreviation = Get-Abbreviation $namenofeature
    $content = Get-Substitution $content 'PurojekutoTenpuretNoFeaturePrefixAbbreviation' $namenofeatureAbbreviation
    $content = Get-Substitution $content 'PurojekutoTenpuretNoFeaturePrefix' $namenofeature

    $ext = [System.IO.Path]::GetExtension($filename)
    if (($ext -eq '.h') -Or ($ext -eq '.cpp'))
    {
        if ($Name -match "^[AEIOUaeiou]")
        {
            $before = " a PurojekutoTenpuret"
            $after = " an PurojekutoTenpuret"
            $content = $content.Replace($before, $after)
        }
        if ($namenofeature -match "^[AEIOUaeiou]")
        {
            $before = " a PurojekutoTenpuretNoFeaturePrefix"
            $after = " an PurojekutoTenpuretNoFeaturePrefix"
            $content = $content.Replace($before, $after)
        }

        $content = Get-Substitution $content 'TokuchoNamespace' $featurenamespace
        $content = Get-Substitution $content 'TokuchoDotNamespace' $featuredotnamespace
        $content = Get-Substitution $content 'TokuchoSymbol' $featuresymbol

        $content = Get-Substitution $content 'PurojekutoTenpuretNoFeaturePrefix' $namenofeature

        $content = $content.Replace($Feature, $featurenamespace)

        $newguid = $(New-Guid).Guid
        $libid = "LIBID-00000000-0000-0000-0000-000000000000"
        $newlibid = "$($newguid)"
        $content = $content.Replace($libid, $newlibid)

        $newguid = $(New-Guid).Guid
        $clsiduuid = "CLSID-UUID-00000000-0000-0000-0000-000000000000"
        $newclsid_uuid = "$($newguid)"
        $content = $content.Replace($clsiduuid, $newclsid_uuid)
        $clsidguid = "CLSID-GUID-0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }"
        $fields = $newguid -Split '-'
        $newclsid_guid = "0x$($fields[0]), 0x$($fields[1]), 0x$($fields[2]), { 0x$($fields[3].Substring(0,2)), 0x$($fields[3].Substring(2,2)), 0x$($fields[4].Substring(0,2)), 0x$($fields[4].Substring(2,2)), 0x$($fields[4].Substring(4,2)), 0x$($fields[4].Substring(6,2)), 0x$($fields[4].Substring(8,2)), 0x$($fields[4].Substring(10,2)) }"
        $content = $content.Replace($clsidguid, $newclsid_guid)

        $newguid = $(New-Guid).Guid
        $provider_guid = "PROVIDER-{00000000-0000-0000-0000-000000000000}"
        $newprovider_guid = "$($newguid)"
        $content = $content.Replace($provider_guid, $newprovider_guid)
        $provider_value = "PROVIDER-(0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)"
        $fields = $newguid -Split '-'
        $newprovider_value = "(0x$($fields[0]), 0x$($fields[1]), 0x$($fields[2]), 0x$($fields[3].Substring(0,2)), 0x$($fields[3].Substring(2,2)), 0x$($fields[4].Substring(0,2)), 0x$($fields[4].Substring(2,2)), 0x$($fields[4].Substring(4,2)), 0x$($fields[4].Substring(6,2)), 0x$($fields[4].Substring(8,2)), 0x$($fields[4].Substring(10,2)))"
        $content = $content.Replace($provider_value, $newprovider_value)
    }
    elseif ($ext -eq '.idl')
    {
        if ($Name -match "^[AEIOUaeiou]")
        {
            $before = " a PurojekutoTenpuret"
            $after = " an PurojekutoTenpuret"
            $content = $content.Replace($before, $after)
        }
        if ($namenofeature -match "^[AEIOUaeiou]")
        {
            $before = " a PurojekutoTenpuretNoFeaturePrefix"
            $after = " an PurojekutoTenpuretNoFeaturePrefix"
            $content = $content.Replace($before, $after)
        }

        $content = Get-Substitution $content 'TokuchoNamespace' $featurenamespace
        $content = Get-Substitution $content 'TokuchoSymbol' $featuresymbol

        $content = Get-Substitution $content 'PurojekutoTenpuretNoFeaturePrefix' $namenofeature

        $newguid = $(New-Guid).Guid
        $uuid = "[uuid(00000000-0000-0000-0000-000000000000)]"
        $newuuid = "[uuid($($newguid))]"
        $content = $content.Replace($uuid, $newuuid)

        $interface = "interface PurojekutoTenpuretInterface : IUnknown"
        $newinterface = "interface I$($Name.Replace('Interface','')) : IUnknown"
        $content = $content.Replace($interface, $newinterface)

        $nameProxyStub = "PurojekutoTenpuretNoProxyStubSuffix"
        $nameminusProxyStub = $Name.Replace("ProxyStub", "")
        $content = $content.Replace($nameProxyStub, $nameminusProxyStub)

        $nameProxyStub = "PUROJEKUTOTENPURETNOPROXYSTUBSUFFIX"
        $nameminusProxyStub = $Name.Replace("ProxyStub", "").ToUpperInvariant()
        $content = $content.Replace($nameProxyStub, $nameminusProxyStub)
    }
    elseif (($ext -eq '.vcxproj') -Or ($ext -eq '.filters'))
    {
        $content = $content.Replace('PurojekutoTenpuretNoProxyStubSuffix', $Name.Replace('ProxyStub', ''))

        $newguid = $(New-Guid).Guid
        $projectguid = "<ProjectGuid>{00000000-0000-0000-0000-000000000000}</ProjectGuid>"
        $newprojectguid = "<ProjectGuid>{$($newguid)}</ProjectGuid>"
        $content = $content.Replace($projectguid, $newprojectguid)

        $interfaceproject = "PurojekutoTenpuretInterface"
        $newinterfaceproject = "$($Name.Replace('ProxyStub', ''))Interface"
        $content = $content.Replace($interfaceproject, $newinterfaceproject)
    }

    $content
}

function Get-Substitution
{
    param(
        [string]$s,
        [string]$from,
        [string]$to
    )

    $s = $s.Replace($from, $to)
    $s = $s.Replace($from.ToUpperInvariant(), $to.ToUpperInvariant())
    $s = $s.Replace($from.ToLowerInvariant(), $to.ToLowerInvariant())
    $s
}

function Get-ProjectTemplateOutputFileName
{
    param(
        [string]$filename
    )

    $featureAbbreviation = Get-Abbreviation $Feature
    $nameAbbreviation = Get-Abbreviation $Name

    $namenofeature = $Name.Replace($Feature, "")
    $namenofeatureAbbreviation = Get-Abbreviation $namenofeature

    $outfn = $filename
    $outfn = Get-Substitution $outfn 'TokuchoAbbreviation' $featureAbbreviation
    $outfn = Get-Substitution $outfn 'Tokucho' $feature
    $outfn = Get-Substitution $outfn 'PurojekutoTenpuretAbbreviation' $nameAbbreviation
    $outfn = Get-Substitution $outfn 'PurojekutoTenpuretNoFeaturePrefixAbbreviation' $namenofeatureAbbreviation
    $outfn = Get-Substitution $outfn 'PurojekutoTenpuretNoFeaturePrefix' $namenofeature
    $outfn = Get-Substitution $outfn 'PurojekutoTenpuretNoProxyStubSuffix' $Name.Replace('ProxyStub', '')
    $outfn = Get-Substitution $outfn 'PurojekutoTenpuret' $Name
    $outfn
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
        Write-Host "ERROR: Metadata missing ($filename)" -ForegroundColor Red -BackgroundColor Black
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

function New-Constants
{
    # Macro: {MACRO-UUID-000n}
    $global:macro_uuid_0001 = $(New-Guid).Guid
    $global:macro_uuid_0002 = $(New-Guid).Guid
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
        Write-Host "ERROR: -Add requires -Template" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }
    $templates = Get-ProjectTemplates
    $t = $templates | Where-Object { $_.Template -eq $Template }
    if ($t -eq $null)
    {
        Write-Host "ERROR: Template $Template not found. Use -List to list the available templates" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }
    $id = $t.Template
    if ([string]::IsNullOrEmpty($Name))
    {
        Write-Host "ERROR: -Add requires -Name" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }
    $sourcedir = Join-Path $(Get-ProjectTemplatePath) $id
    $sourcemetadatafilename = Join-Path $sourcedir "PurojekutoTenpuret.Metadeta"
    $sourcemetadata = Get-Content $sourcemetadatafilename -EA:Stop -Raw | ConvertFrom-Json
    if ($Name -NotMatch $sourcemetadata.Name.AllowedRegex)
    {
        Write-Host "ERROR: -Name doesn't match template's required pattern `"$($sourcemetadata.Name.AllowedRegex)`"" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }

    Write-Host "Creating project $Name from template $Template"

    $null = New-Constants

    $root = Get-ProjectRoot
    $targetsubdir = $t.Type.ToLowerInvariant()
    if (-not([string]::IsNullOrEmpty($Feature)))
    {
        $targetsubdir = Join-Path $targetsubdir $Feature
    }
    $targetsubdir = Join-Path $targetsubdir $Name
    $targetdir = Join-Path $root $targetsubdir
    if (Test-Path -Path $targetdir)
    {
        Write-Host "ERROR: Target directory exists ($targetdir). Remove to proceed" -ForegroundColor Red -BackgroundColor Black
        Exit 1
    }
    Write-Host "Creating $targetdir"
    $null = New-Item $targetdir -ItemType Directory

    Write-Host "Creating project files..."
    $files = Get-ChildItem $sourcedir -Exclude 'PurojekutoTenpuret.Metadeta' -Recurse
    $count = 0
    ForEach ($f in $files)
    {
        $source = $f.FullName

        $pathname = $f.FullName.Substring($sourcedir.Length + 1)
        $outfn = Get-ProjectTemplateOutputFileName $pathname
        $target = Join-Path $targetdir $outfn

        if ($f.PSIsContainer)
        {
            Write-Host "Creating $outfn"
            $null = New-Item $target -ItemType Directory
        }
        else
        {
            # Change placemarkers in the file content
            $in = Get-Content -Path $source -Encoding utf8 -Raw
            $out = $(Get-UpdatedContent $source $in)
            $out = Get-Substitution $out 'Tokucho' $Feature
            $out = Get-Substitution $out 'PurojekutoTenpuret' $Name
            $out = $out.TrimEnd()

            Write-Host "Transforming $f to $outfn"
            $null = Set-Content $target -Value $out -Encoding utf8

            $count++
        }
    }
    Write-Host "$count files copied to new project $targetdir"
    Write-Host "Coding time!"
}

if ($List -eq $true)
{
    $null = List-ProjectTemplates
}
if ($Add -eq $true)
{
    $null = Add-Project
}
