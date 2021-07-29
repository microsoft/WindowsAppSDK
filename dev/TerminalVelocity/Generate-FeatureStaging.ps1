# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.

<#
.SYNOPSIS
    Generate Feature-checks from a Feature definition file.

.DESCRIPTION
    Create Feature-check functions to enable select code disablement based on build criteria.

.PARAMETER Path
    Source file containing feature definitions per FeatureStagingSchema.xsd.

.PARAMETER Branding
    The target Channel for Feature checks.

.PARAMETER BranchOverride
    TBD do we need this???

.PARAMETER Output
    File to create (default=stdout).

.PARAMETER Language
    Programming language to generate.

.PARAMETER Namespace
    Namespace for language symbols (Optional if -Language=C++). Multiple namespaces
    can be specified with "." or "::" separator and converted if necessary,
    e.g. "-Namespace Foo.Bar" and "-Namespace Foo::Bar" produce the same end result in all languages.

.EXAMPLE
    Generate-FeatureStaging Kittens.xml -Branding Preview -Output Kittens.h
#>

[CmdletBinding()]
Param(
    [Parameter(Position=0, Mandatory=$True)]
    [ValidateScript({ Test-Path $_ })]
    [string]$Path,

    [ValidateSet("Experimental", "Preview", "Release", "WindowsInbox")]
    [string]$Branding = "Experimental",

    [string]$BranchOverride = $Null,

    [string]$Output,

    [ValidateSet("C++", "C#")]
    [string]$Language = "C++",

    [string]$Namespace
)

Enum Stage
{
    AlwaysDisabled;
    AlwaysEnabled;
}

Function ConvertTo-FeatureStage([string]$stage)
{
    Switch($stage)
    {
        "AlwaysEnabled" { [Stage]::AlwaysEnabled; return }
        "AlwaysDisabled" { [Stage]::AlwaysDisabled; return }
    }
    Throw "Invalid feature stage $stage"
}

Class Feature
{
    [string]$Name
    [Stage]$Stage
    [System.Collections.Generic.Dictionary[string, Stage]]$BranchTokenStages
    [System.Collections.Generic.Dictionary[string, Stage]]$BrandingTokenStages
    [bool]$DisabledReleaseToken

    Feature([System.Xml.XmlElement]$entry)
    {
        $this.Name = $entry.name
        $this.Stage = ConvertTo-FeatureStage $entry.stage
        $this.BranchTokenStages = [System.Collections.Generic.Dictionary[string, Stage]]::new()
        $this.BrandingTokenStages = [System.Collections.Generic.Dictionary[string, Stage]]::new()
        $this.DisabledReleaseToken = $Null -Ne $entry.alwaysDisabledReleaseTokens

        ForEach ($b in $entry.alwaysDisabledBranchTokens.branchToken)
        {
            $this.BranchTokenStages[$b] = [Stage]::AlwaysDisabled
        }

        # AlwaysEnabled branches win over AlwaysDisabled branches
        ForEach ($b in $entry.alwaysEnabledBranchTokens.branchToken)
        {
            $this.BranchTokenStages[$b] = [Stage]::AlwaysEnabled
        }

        ForEach ($b in $entry.alwaysDisabledBrandingTokens.brandingToken)
        {
            $this.BrandingTokenStages[$b] = [Stage]::AlwaysDisabled
        }

        # AlwaysEnabled brandings win over AlwaysDisabled brandings
        ForEach ($b in $entry.alwaysEnabledBrandingTokens.brandingToken)
        {
            $this.BrandingTokenStages[$b] = [Stage]::AlwaysEnabled
        }
    }

    [string] PreprocessorName()
    {
        return "WINDOWSAPPSDK_$($this.Name.ToUpper())_ENABLED"
    }
}

class FeatureComparer : System.Collections.Generic.IComparer[Feature]
{
    [int] Compare([Feature]$a, [Feature]$b)
    {
        if ($a.Name -lt $b.Name)
        {
            return -1
        }
        elseif ($a.Name -gt $b.Name)
        {
            return 1
        }
        else
        {
            return 0
        }
    }
}

Function Resolve-FinalFeatureStage
{
    Param(
        [Feature]$Feature,
        [string]$Branch,
        [string]$Branding
    )

    # RELEASE=DISABLED wins all checks
    # Then, branch match by most-specific branch
    # Then, branding type (if no overriding branch match)

    if ($Branding -Eq "Release" -And $Feature.DisabledReleaseToken)
    {
        [Stage]::AlwaysDisabled
        return
    }

    if (-Not [String]::IsNullOrEmpty($Branch))
    {
        $lastMatchLen = 0
        $branchStage = $Null
        ForEach ($branchToken in $Feature.BranchTokenStages.Keys)
        {
            # Match the longest branch token -- it should be the most specific
            if ($Branch -Like $branchToken -And $branchToken.Length -Gt $lastMatchLen)
            {
                $lastMatchLen = $branchToken.Length
                $branchStage = $Feature.BranchTokenStages[$branchToken]
            }
        }
        if ($Null -Ne $branchStage)
        {
            $branchStage
            return
        }
    }

    $BrandingStage = $Feature.BrandingTokenStages[$Branding]
    if ($Null -Ne $BrandingStage)
    {
        $BrandingStage
        return
    }

    $Feature.Stage
}

$ErrorActionPreference = "Stop"
$x = [xml](Get-Content $Path -EA:Stop)
$x.Schemas.Add('http://microsoft.com/TilFeatureStaging-Schema.xsd', (Resolve-Path (Join-Path $PSScriptRoot "FeatureStagingSchema.xsd")).Path) | Out-Null
$x.Validate($null)

$featureComparer = [FeatureComparer]::new()
$features = [System.Collections.Generic.List[Feature]]::new(16)

ForEach ($entry in $x.featureStaging.feature)
{
    $features.Add([Feature]::new($entry))
}

$features.Sort($featureComparer)

$featureFinalStages = [System.Collections.Generic.Dictionary[string, Stage]]::new(16)

$branch = $BranchOverride
if ([String]::IsNullOrEmpty($branch))
{
    try
    {
        $branch = & git branch --show-current 2>$Null
    }
    catch
    {
        try
        {
            $branch = & git rev-parse --abbrev-ref HEAD 2>$Null
        }
        catch
        {
            Write-Host "Cannot determine current Git branch; skipping branch validation"
        }
    }
}

ForEach ($feature in $features)
{
    $featureFinalStages[$feature.Name] = Resolve-FinalFeatureStage -Feature $feature -Branch $branch -Branding $Branding
}

### CODE GENERATION
function Output_Header($comment_line_prefix="//")
{
@"
$comment_line_prefix Copyright (c) Microsoft Corporation. All rights reserved.
$comment_line_prefix Licensed under the MIT License. See LICENSE in the project root for license information.

$comment_line_prefix THIS FILE IS AUTOMATICALLY GENERATED; DO NOT EDIT IT

$comment_line_prefix INPUT FILE: $Path


"@
}

### CODE GENERATION - C++
function Generate_CPP()
{
    $content = Output_Header

    $content += "// Feature constants`r`n"
    ForEach ($feature in $features)
    {
        $stage = $featureFinalStages[$feature.Name]

        $content += @"
#define $($feature.PreprocessorName()) $(if ($stage -eq [Stage]::AlwaysEnabled) { "1" } else { "0" })

"@
    }

    $content += @"

#if defined(__cplusplus)

"@

    if (-not [String]::IsNullOrEmpty($Namespace))
    {
        $content += @"

namespace $($Namespace.replace(".", "::"))
{

"@
    }

    ForEach ($feature in $features)
    {
        $content += @"

__pragma(detect_mismatch("ODR_violation_$($feature.PreprocessorName())_mismatch", "$($feature.Stage)"))
struct $($feature.Name)
{
    static constexpr bool IsEnabled() { return $($feature.PreprocessorName()) == 1; }
};

"@
    }

    if (-not [String]::IsNullOrEmpty($Namespace))
    {
        $content += @"

} // namespace $Namespace

"@
    }

    $content += @"

#endif // defined(__cplusplus)

"@

    return $content
}

### CODE GENERATION - C#
function Generate_CS()
{
    $content = Output_Header

    $content += "// Feature constants`r`n"
    ForEach ($feature in $features)
    {
        $stage = $featureFinalStages[$feature.Name]

        if ($stage -eq [Stage]::AlwaysEnabled)
        {
            $content += "#Define $($feature.PreprocessorName())`r`n"
        }
        else
        {
            $content += "//DISABLED: $($feature.PreprocessorName())`r`n"
        }
    }

    if (-not [String]::IsNullOrEmpty($Namespace))
    {
        $content += @"

namespace $($Namespace.replace("::", "."))
{

"@
    }

    ForEach ($feature in $features)
    {
        $content += @"

public static class $($feature.Name)
{
#if $($feature.PreprocessorName())
    public const bool IsEnabled = true;
#else
    public const bool IsEnabled = false;
#endif
};

"@
    }

    if (-not [String]::IsNullOrEmpty($Namespace))
    {
        $content += @"

} // namespace $Namespace

"@
    }

    return $content
}

### CODE GENERATION - Language Selection
$generate = $Null
if ($Language -eq "C++")
{
    $generate = Generate_CPP
}
elseif ($Language -eq "C#")
{
    $generate = Generate_CS
}
$generate
if ([String]::IsNullOrEmpty($Output))
{
    $generate
}
else
{
    Out-File -Encoding UTF8 -FilePath $Output -InputObject $generate
}
