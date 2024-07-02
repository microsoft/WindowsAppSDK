# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Generate Feature-checks from a Feature definition file.

.DESCRIPTION
    Create Feature-check functions to enable select code disablement based on build criteria.

.PARAMETER Path
    Source file containing feature definitions per TerminalVelocityFeatures.xsd.

.PARAMETER Channel
    The target channel for Feature checks (default=Experimental).

.PARAMETER Output
    File to create (default=stdout).

.PARAMETER Language
    Programming language to generate (default=C++).

.PARAMETER Namespace
    Namespace for language symbols (Optional if -Language=C++). Multiple namespaces
    can be specified with "." or "::" separator and converted if necessary,
    e.g. "-Namespace Foo.Bar" and "-Namespace Foo::Bar" produce the same end result in all languages.

.EXAMPLE
    Generate-TerminalVelocityFeatures Kittens.xml -Channel Preview -Output Kittens.h
#>

[CmdletBinding()]
Param(
    [Parameter(Position=0, Mandatory=$True)]
    [ValidateScript({ Test-Path $_ })]
    [string]$Path,

    [ValidateSet("Experimental", "Preview", "Stable", "WindowsInbox")]
    [string]$Channel = "Experimental",

    [string]$Output,

    [ValidateSet("C++", "C#")]
    [string]$Language = "C++",

    [string]$Namespace
)

Set-StrictMode -Version 3.0

# Make sure Channel has the exact spelling even if the parameter had different case
foreach ($c in "Experimental", "Preview", "Stable", "WindowsInbox")
{
    if ($Channel -ieq $c)
    {
        $Channel = $c
    }
}

# Namespace is optional for C++
if ([String]::IsNullOrEmpty($Namespace))
{
    if ($Language -ne "C++")
    {
        Write-Output "Invalid parameter -Namespace is rquired, aborting..."
        Exit 1
    }
}

Enum State
{
    AlwaysDisabled;
    AlwaysEnabled;
}

Function ConvertTo-FeatureState([string]$state)
{
    Switch($state)
    {
        "AlwaysEnabled" { [State]::AlwaysEnabled; return }
        "AlwaysDisabled" { [State]::AlwaysDisabled; return }
    }
    Throw "Invalid feature state $state"
}

Class Feature
{
    [string]$Name
    [State]$State
    [int]$Id
    [System.Collections.Generic.Dictionary[string, State]]$ChannelTokenStates
    [bool]$DisabledReleaseToken

    Feature([System.Xml.XmlElement]$entry)
    {
        $this.Name = $entry.name
        $this.State = ConvertTo-FeatureState $entry.state

        # TODO: Remove the temp workaround of downgrading to StrictModel 1.0 once b#52128443 is fixed. 
        Set-StrictMode -Version 1.0
        $this.Id = $entry.id
        $this.ChannelTokenStates = [System.Collections.Generic.Dictionary[string, State]]::new()
        $this.DisabledReleaseToken = $Null -Ne $entry.alwaysDisabledReleaseTokens

        ForEach ($b in $entry.alwaysDisabledChannelTokens.channelToken)
        {
            $this.ChannelTokenStates[$b] = [State]::AlwaysDisabled
        }

        # AlwaysEnabled channels win over AlwaysDisabled channels
        ForEach ($b in $entry.alwaysEnabledChannelTokens.channelToken)
        {
            $this.ChannelTokenStates[$b] = [State]::AlwaysEnabled
        }
        Set-StrictMode -Version 3.0
    }

    [string] PreprocessorName([string]$namespace)
    {
        if ([String]::IsNullOrEmpty($namespace))
        {
            return "WINDOWSAPPRUNTIME_$($this.Name.ToUpper())_ENABLED"
        }
        else
        {
            $ns = $namespace.replace(".", "_").replace("::", "_")
            return "WINDOWSAPPRUNTIME_$($ns.ToUpper())_$($this.Name.ToUpper())_ENABLED"
        }
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

Function Resolve-FinalFeatureState
{
    Param(
        [Feature]$Feature,
        [string]$Channel
    )

    # RELEASE=DISABLED wins all checks
    # Then, channel type

    if ($Channel -Eq "Stable" -And $Feature.DisabledReleaseToken)
    {
        [State]::AlwaysDisabled
        return
    }

    $ChannelState = $Feature.ChannelTokenStates[$Channel]
    if ($Null -Ne $ChannelState)
    {
        $ChannelState
        return
    }

    $Feature.State
}

$ErrorActionPreference = "Stop"
$xml = [xml](Get-Content $Path -EA:Stop)
$xml.Schemas.Add('http://microsoft.com/windowsappsdk/TerminalVelocity/20210729/TerminalVelocityFeatures.xsd', (Resolve-Path (Join-Path $PSScriptRoot "TerminalVelocityFeatures.xsd")).Path) | Out-Null
$xml.Validate($null)

$featureComparer = [FeatureComparer]::new()
$features = [System.Collections.Generic.List[Feature]]::new(16)

ForEach ($entry in $xml.features.feature)
{
    $features.Add([Feature]::new($entry))
}

$features.Sort($featureComparer)

$featureFinalStates = [System.Collections.Generic.Dictionary[string, State]]::new(16)

ForEach ($feature in $features)
{
    $featureFinalStates[$feature.Name] = Resolve-FinalFeatureState -Feature $feature -Channel $Channel
}

### CODE GENERATION
function Output_Header($comment_line_prefix="//")
{
@"
$comment_line_prefix Copyright (c) Microsoft Corporation and Contributors.
$comment_line_prefix Licensed under the MIT License.

$comment_line_prefix THIS FILE IS AUTOMATICALLY GENERATED; DO NOT EDIT IT

$comment_line_prefix INPUT FILE: $Path
$comment_line_prefix OPTIONS: -Channel $Channel -Language $Language$(if (-not ([String]::IsNullOrEmpty($Namespace))) { " -Namespace $Namespace" }) -Path $Path$(if (-not ([String]::IsNullOrEmpty($Output))) { " -Output $Output" })


"@
}

### CODE GENERATION - C++
function Generate_CPP()
{
    $content = Output_Header

    $content += @"
#if defined(__midlrt)
namespace features
{

"@
    ForEach ($feature in $features)
    {
        $state = $featureFinalStates[$feature.Name]

        $content += @"
    feature_name $($feature.Name) = { $(if ($state -eq [State]::AlwaysDisabled) { "AlwaysDisabled" } else {"DisabledByDefault" }), FALSE };

"@
    }
    $content += @"
}
#endif // defined(__midlrt)


"@

    $content += "// Feature constants`r`n"
    ForEach ($feature in $features)
    {
        $state = $featureFinalStates[$feature.Name]

        $content += @"
#define $($feature.PreprocessorName($Namespace)) $(if ($state -eq [State]::AlwaysEnabled) { "1" } else { "0" })

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

__pragma(detect_mismatch("ODR_violation_$($feature.PreprocessorName($Namespace))_mismatch", "$($feature.State)"))
struct $($feature.Name)
{
    static constexpr bool IsEnabled() { return $($feature.PreprocessorName($Namespace)) == 1; }
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
        $state = $featureFinalStates[$feature.Name]

        if ($state -eq [State]::AlwaysEnabled)
        {
            $content += "#Define $($feature.PreprocessorName($Namespace))`r`n"
        }
        else
        {
            $content += "//DISABLED: $($feature.PreprocessorName($Namespace))`r`n"
        }
    }

    $content += @"

namespace $($Namespace.replace("::", "."))
{

"@

    ForEach ($feature in $features)
    {
        $content += @"

public static class $($feature.Name)
{
#if $($feature.PreprocessorName($Namespace))
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
if ($Language -ieq "C++")
{
    $generate = Generate_CPP
}
elseif ($Language -ieq "C#")
{
    $generate = Generate_CS
}
if ([String]::IsNullOrEmpty($Output))
{
    $generate
}
else
{
    Out-File -Encoding UTF8 -FilePath $Output -InputObject $generate
}
