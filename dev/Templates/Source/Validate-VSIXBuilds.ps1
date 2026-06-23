$msbuild = "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
$projects = @(
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/SingleProjectPackagedApp/WinUI.Desktop.Cs.SingleProjectPackagedApp.csproj",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/NavigationApp/WinUI.Desktop.Cs.NavigationApp.csproj",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/MvvmApp/WinUI.Desktop.Cs.MvvmApp.csproj",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/TabViewApp/WinUI.Desktop.Cs.TabViewApp.csproj",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/ClassLibrary/WinUI.Desktop.Cs.ClassLibrary.csproj",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/UnitTestApp/WinUI.Desktop.Cs.UnitTestApp.csproj",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/PackagedApp/WinUI.Desktop.Cs.PackagedApp.csproj"
)
$agents = @(
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/SingleProjectPackagedApp/AGENTS.md",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/NavigationApp/AGENTS.md",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/MvvmApp/AGENTS.md",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/TabViewApp/AGENTS.md",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/ClassLibrary/AGENTS.md",
    "dev/Templates/Source/ProjectTemplates/Desktop/CSharp/UnitTestApp/AGENTS.md"
)

$results = @()
$overallPass = $true
$firstFailure = ""

foreach ($proj in $projects) {
    Write-Host "Building $proj using Visual Studio MSBuild..."
    $output = & $msbuild $proj /t:Build /p:Configuration=Release /v:minimal /nologo 2>&1
    $exitCode = $LASTEXITCODE
    $vssdkMatch = $false
    foreach($line in $output) {
        if ($line -like "*VSSDK1016*") {
            $vssdkMatch = $true
            break
        }
    }
    
    $results += [PSCustomObject]@{
        Project = Split-Path $proj -Leaf
        ExitCode = $exitCode
        VSSDK1016 = $vssdkMatch
    }
    
    if ($exitCode -ne 0 -and $overallPass) {
        $overallPass = $false
        $firstFailure = "Build failed for $(Split-Path $proj -Leaf) with exit code $exitCode"
    }
    if ($vssdkMatch -and $overallPass) {
        $overallPass = $false
        $firstFailure = "VSSDK1016 found in $(Split-Path $proj -Leaf)"
    }
}

foreach ($agentsFile in $agents) {
    if (-not (Test-Path $agentsFile)) {
        if ($overallPass) {
            $overallPass = $false
            $firstFailure = "AGENTS.md not found: $agentsFile"
        }
        Write-Host "AGENTS.md missing: $agentsFile"
    }
}

$results | Format-Table
if ($overallPass) {
    Write-Host "OVERALL VERDICT: PASS"
} else {
    Write-Host "OVERALL VERDICT: FAIL"
    Write-Host "First Failure: $firstFailure"
}