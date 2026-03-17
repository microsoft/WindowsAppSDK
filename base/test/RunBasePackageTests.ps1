# RunBasePackageTests.ps1
# Builds all Base package test configurations and verifies results.
# Can be run from any directory — automatically finds repo root.
param(
    [string]$MsBuildPath
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Continue'
$script:PassCount = 0
$script:FailCount = 0

# Find repo root (walk up from script location looking for .git)
$scriptDir = $PSScriptRoot
$repoRoot = $scriptDir
while ($repoRoot -and !(Test-Path (Join-Path $repoRoot ".git"))) {
    $repoRoot = Split-Path $repoRoot -Parent
}
if (!$repoRoot -or !(Test-Path (Join-Path $repoRoot ".git"))) {
    Write-Host "ERROR: Could not find repo root from $scriptDir" -ForegroundColor Red
    exit 1
}
Write-Host "Repo root: $repoRoot"
Push-Location $repoRoot

# Auto-detect MSBuild if not specified
if (!$MsBuildPath) {
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $vsPath = & $vswhere -latest -requires Microsoft.Component.MSBuild -property installationPath 2>$null
        if ($vsPath) {
            $MsBuildPath = Join-Path $vsPath "MSBuild\Current\Bin\MSBuild.exe"
        }
    }
    if (!$MsBuildPath -or !(Test-Path $MsBuildPath)) {
        Write-Host "ERROR: Could not find MSBuild. Pass -MsBuildPath explicitly." -ForegroundColor Red
        Pop-Location
        exit 1
    }
    Write-Host "MSBuild: $MsBuildPath"
}

function Test-BuildSuccess {
    param([string]$Name, [string]$BuildCmd, [scriptblock]$Verify)

    Write-Host "`n========== $Name ==========" -ForegroundColor Cyan
    Write-Host "Building..."

    $output = Invoke-Expression $BuildCmd 2>&1 | Out-String
    $exitCode = $LASTEXITCODE

    if ($exitCode -ne 0) {
        Write-Host "FAIL: Build failed (exit code $exitCode)" -ForegroundColor Red
        Write-Host $output | Select-Object -Last 10
        $script:FailCount++
        return
    }

    # Run verification
    $result = & $Verify
    if ($result) {
        Write-Host "PASS" -ForegroundColor Green
        $script:PassCount++
    } else {
        $script:FailCount++
    }
}

function Test-BuildError {
    param([string]$Name, [string]$BuildCmd, [string]$ExpectedError)

    Write-Host "`n========== $Name (expect error) ==========" -ForegroundColor Cyan
    Write-Host "Building (expecting failure)..."

    $output = Invoke-Expression $BuildCmd 2>&1 | Out-String
    $exitCode = $LASTEXITCODE

    if ($exitCode -eq 0) {
        Write-Host "FAIL: Build succeeded but should have failed" -ForegroundColor Red
        $script:FailCount++
        return
    }

    if ($output -match [regex]::Escape($ExpectedError)) {
        Write-Host "PASS: Got expected error" -ForegroundColor Green
        $script:PassCount++
    } else {
        Write-Host "FAIL: Build failed but with wrong error" -ForegroundColor Red
        Write-Host "Expected: $ExpectedError" -ForegroundColor Yellow
        # Show error lines
        $output -split "`n" | Where-Object { $_ -match "error" } | Select-Object -First 5 | ForEach-Object { Write-Host "  $_" }
        $script:FailCount++
    }
}

function Test-NoDlls {
    param([string]$Dir, [string[]]$AllowedDlls = @())

    $dlls = @(Get-ChildItem "$Dir\*.dll" -ErrorAction SilentlyContinue | ForEach-Object { $_.Name })
    $unexpected = @($dlls | Where-Object { $_ -notin $AllowedDlls })

    if ($unexpected.Count -gt 0) {
        Write-Host "FAIL: Unexpected DLLs found:" -ForegroundColor Red
        $unexpected | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
        return $false
    }
    Write-Host "  DLLs: $($dlls.Count) (all expected)"
    return $true
}

function Test-HasBootstrapDlls {
    param([string]$Dir, [switch]$Managed)

    $dlls = Get-ChildItem "$Dir\*.dll" -ErrorAction SilentlyContinue | ForEach-Object { $_.Name }
    $hasNative = $dlls -contains "Microsoft.WindowsAppRuntime.Bootstrap.dll"
    $hasManaged = !$Managed -or ($dlls -contains "Microsoft.WindowsAppRuntime.Bootstrap.Net.dll")

    if (!$hasNative) {
        Write-Host "FAIL: Microsoft.WindowsAppRuntime.Bootstrap.dll not found" -ForegroundColor Red
        return $false
    }
    if ($Managed -and !$hasManaged) {
        Write-Host "FAIL: Microsoft.WindowsAppRuntime.Bootstrap.Net.dll not found" -ForegroundColor Red
        return $false
    }
    Write-Host "  Bootstrap DLLs present"
    return $true
}

# ============================================================
Write-Host "Base Package Test Suite" -ForegroundColor White
Write-Host "======================" -ForegroundColor White

$csProj = "base\test\BasePackageTest\CS\BasePackageTest.csproj"
$cppProj = "base\test\BasePackageTest\CPP\BasePackageTestCpp.vcxproj"

# Clean previous outputs
Write-Host "`nCleaning..."
cmd /c "rd /s /q base\test\BasePackageTest\CS\bin 2>nul"
cmd /c "rd /s /q base\test\BasePackageTest\CS\obj 2>nul"
cmd /c "rd /s /q base\test\BasePackageTest\CPP\out 2>nul"
cmd /c "rd /s /q base\test\BasePackageTest\CPP\obj 2>nul"

# Ensure C++ NuGet packages are restored
Write-Host "Restoring C++ NuGet packages..."
cmd /c "rd /s /q base\test\BasePackageTest\CPP\packages 2>nul"
cmd /c "rd /s /q Packages\microsoft.windowsappsdk.base 2>nul"
nuget restore base\test\BasePackageTest\CPP\packages.config -PackagesDirectory base\test\BasePackageTest\CPP\packages -ConfigFile base\test\BasePackageTest\CPP\nuget.config 2>&1 | Out-Null

# ============================================================
# C# Tests
# ============================================================
Write-Host "`n" -NoNewline
Write-Host "===== C# Tests =====" -ForegroundColor White

# Config 1: Ge_SC_Unpkg — no bootstrap DLLs
$csAllowed = @("BasePackageTest.dll", "Microsoft.Windows.SDK.NET.dll", "WinRT.Runtime.dll")
Test-BuildSuccess "C# 1: Ge_SC_Unpkg" `
    "dotnet build $csProj -c Ge_SC_Unpkg --no-incremental -v q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CS\bin\x64\Ge_SC_Unpkg\net8.0-windows10.0.26100.0\win-x64" -AllowedDlls $csAllowed }

# Config 2: RS5_FD_Unpkg — bootstrap DLLs present
dotnet restore $csProj -p:Configuration=RS5_FD_Unpkg 2>&1 | Out-Null
Test-BuildSuccess "C# 2: RS5_FD_Unpkg" `
    "dotnet build $csProj -c RS5_FD_Unpkg --no-incremental --no-restore -v q 2>&1" `
    { Test-HasBootstrapDlls "base\test\BasePackageTest\CS\bin\x64\RS5_FD_Unpkg\net8.0-windows10.0.17763.0\win-x64" -Managed }

# Config 3: Ge_FD_Unpkg_NoBoot — no bootstrap DLLs
dotnet restore $csProj -p:Configuration=Ge_FD_Unpkg_NoBoot 2>&1 | Out-Null
Test-BuildSuccess "C# 3: Ge_FD_Unpkg_NoBoot" `
    "dotnet build $csProj -c Ge_FD_Unpkg_NoBoot --no-incremental --no-restore -v q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CS\bin\x64\Ge_FD_Unpkg_NoBoot\net8.0-windows10.0.26100.0\win-x64" -AllowedDlls $csAllowed }

# Config 4: RS5_FD_Unpkg_NoBoot — ERROR expected
dotnet restore $csProj -p:Configuration=RS5_FD_Unpkg_NoBoot 2>&1 | Out-Null
Test-BuildError "C# 4: RS5_FD_Unpkg_NoBoot" `
    "dotnet build $csProj -c RS5_FD_Unpkg_NoBoot --no-incremental --no-restore -v q 2>&1" `
    "The Windows App SDK Bootstrapper is required for framework-dependent unpackaged apps"

# Config 5: H19H1_SC_Pkg — no bootstrap DLLs
dotnet restore $csProj -p:Configuration=H19H1_SC_Pkg 2>&1 | Out-Null
Test-BuildSuccess "C# 5: H19H1_SC_Pkg" `
    "dotnet build $csProj -c H19H1_SC_Pkg --no-incremental --no-restore -v q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CS\bin\x64\H19H1_SC_Pkg\net8.0-windows10.0.18362.0\win-x64" -AllowedDlls $csAllowed }

# Config 6: RS5_SC_Pkg_URF — ERROR expected (Foundation required)
dotnet restore $csProj -p:Configuration=RS5_SC_Pkg_URF 2>&1 | Out-Null
Test-BuildError "C# 6: RS5_SC_Pkg_URF" `
    "dotnet build $csProj -c RS5_SC_Pkg_URF --no-incremental --no-restore -v q 2>&1" `
    "Undocked Reg-Free WinRT activation requires the Microsoft.WindowsAppSDK.Foundation package"

# Config 7: RS5_SC_Pkg_NoURF — ERROR expected (URF not optional)
dotnet restore $csProj -p:Configuration=RS5_SC_Pkg_NoURF 2>&1 | Out-Null
Test-BuildError "C# 7: RS5_SC_Pkg_NoURF" `
    "dotnet build $csProj -c RS5_SC_Pkg_NoURF --no-incremental --no-restore -v q 2>&1" `
    "Undocked Reg-Free WinRT activation is required for self-contained apps targeting Windows versions prior to 10.0.18362.0"

# Config 8: RS5_FD_Pkg — ERROR expected (DeploymentMgr requires Foundation)
dotnet restore $csProj -p:Configuration=RS5_FD_Pkg 2>&1 | Out-Null
Test-BuildError "C# 8: RS5_FD_Pkg" `
    "dotnet build $csProj -c RS5_FD_Pkg --no-incremental --no-restore -v q 2>&1" `
    "DeploymentManager initialization requires the Microsoft.WindowsAppSDK.Foundation package"

# Config 9: RS5_SC_Pkg_URF_Fdn — Foundation referenced, URF=true, no bootstrap DLLs
# Foundation adds extra DLLs but bootstrap should still be absent (SC=true)
dotnet restore $csProj -p:Configuration=RS5_SC_Pkg_URF_Fdn 2>&1 | Out-Null
Test-BuildSuccess "C# 9: RS5_SC_Pkg_URF_Fdn" `
    "dotnet build $csProj -c RS5_SC_Pkg_URF_Fdn --no-incremental --no-restore -v q 2>&1" `
    {
        $dir = "base\test\BasePackageTest\CS\bin\x64\RS5_SC_Pkg_URF_Fdn\net8.0-windows10.0.17763.0\win-x64"
        $dlls = @(Get-ChildItem "$dir\*.dll" -ErrorAction SilentlyContinue | ForEach-Object { $_.Name })
        $bootstrapDlls = @($dlls | Where-Object { $_ -match "Bootstrap" })
        if ($bootstrapDlls.Count -gt 0) {
            Write-Host "FAIL: Bootstrap DLLs found:" -ForegroundColor Red
            $bootstrapDlls | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
            return $false
        }
        Write-Host "  DLLs: $($dlls.Count) (no bootstrap, Foundation present)"
        return $true
    }

# ============================================================
# C++ Tests
# ============================================================
Write-Host "`n" -NoNewline
Write-Host "===== C++ Tests =====" -ForegroundColor White

$msbuild = "`"$MsBuildPath`""

# Config 1: Ge_SC_Unpkg — no DLLs
Test-BuildSuccess "C++ 1: Ge_SC_Unpkg" `
    "& $msbuild $cppProj /p:Configuration=Ge_SC_Unpkg /p:Platform=x64 /nr:false /v:q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CPP\out\Ge_SC_Unpkg\x64" }

# Config 2: RS5_FD_Unpkg — bootstrap DLL present
Test-BuildSuccess "C++ 2: RS5_FD_Unpkg" `
    "& $msbuild $cppProj /p:Configuration=RS5_FD_Unpkg /p:Platform=x64 /nr:false /v:q 2>&1" `
    { Test-HasBootstrapDlls "base\test\BasePackageTest\CPP\out\RS5_FD_Unpkg\x64" }

# Config 3: Ge_FD_Unpkg_NoBoot — no DLLs
Test-BuildSuccess "C++ 3: Ge_FD_Unpkg_NoBoot" `
    "& $msbuild $cppProj /p:Configuration=Ge_FD_Unpkg_NoBoot /p:Platform=x64 /nr:false /v:q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CPP\out\Ge_FD_Unpkg_NoBoot\x64" }

# Config 4: RS5_FD_Unpkg_NoBoot — ERROR expected
Test-BuildError "C++ 4: RS5_FD_Unpkg_NoBoot" `
    "& $msbuild $cppProj /p:Configuration=RS5_FD_Unpkg_NoBoot /p:Platform=x64 /nr:false /v:q 2>&1" `
    "The Windows App SDK Bootstrapper is required for framework-dependent unpackaged apps"

# Config 5: H19H1_SC_Pkg — no DLLs
Test-BuildSuccess "C++ 5: H19H1_SC_Pkg" `
    "& $msbuild $cppProj /p:Configuration=H19H1_SC_Pkg /p:Platform=x64 /nr:false /v:q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CPP\out\H19H1_SC_Pkg\x64" }

# Config 6: RS5_SC_Pkg_URF — ERROR expected (Foundation required)
Test-BuildError "C++ 6: RS5_SC_Pkg_URF" `
    "& $msbuild $cppProj /p:Configuration=RS5_SC_Pkg_URF /p:Platform=x64 /nr:false /v:q 2>&1" `
    "Undocked Reg-Free WinRT activation requires the Microsoft.WindowsAppSDK.Foundation package"

# Config 7: RS5_SC_Pkg_NoURF — ERROR expected (URF not optional)
Test-BuildError "C++ 7: RS5_SC_Pkg_NoURF" `
    "& $msbuild $cppProj /p:Configuration=RS5_SC_Pkg_NoURF /p:Platform=x64 /nr:false /v:q 2>&1" `
    "Undocked Reg-Free WinRT activation is required for self-contained apps targeting Windows versions prior to 10.0.18362.0"

# Config 8: RS5_FD_Pkg — ERROR expected (DeploymentMgr requires Foundation)
Test-BuildError "C++ 8: RS5_FD_Pkg" `
    "& $msbuild $cppProj /p:Configuration=RS5_FD_Pkg /p:Platform=x64 /nr:false /v:q 2>&1" `
    "DeploymentManager initialization requires the Microsoft.WindowsAppSDK.Foundation package"

# Config 9: RS5_SC_Pkg_URF_Fdn — Foundation simulated, URF=true, no DLLs
Test-BuildSuccess "C++ 9: RS5_SC_Pkg_URF_Fdn" `
    "& $msbuild $cppProj /p:Configuration=RS5_SC_Pkg_URF_Fdn /p:Platform=x64 /nr:false /v:q 2>&1" `
    { Test-NoDlls "base\test\BasePackageTest\CPP\out\RS5_SC_Pkg_URF_Fdn\x64" }

# ============================================================
# Summary
# ============================================================
Write-Host "`n======================" -ForegroundColor White
Write-Host "Results: $script:PassCount passed, $script:FailCount failed" -ForegroundColor $(if ($script:FailCount -eq 0) { "Green" } else { "Red" })
Write-Host "======================" -ForegroundColor White

Pop-Location
exit $script:FailCount
