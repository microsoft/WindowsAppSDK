$ProgressPreference = "SilentlyContinue"

$arch = $env:_BuildArch;
$buildFavor = "$($env:_BuildArch)$($env:_BuildType)"
$binRoot = $env:BinRoot

$outputDir = Join-Path (Join-Path $binRoot $buildFavor) "TestDependencies"
$outputPath = Join-Path $outputDir "dotnet-windowsdesktop-runtime-installer.exe"

if(!(Test-Path $outputDir))
{
    New-Item -ItemType Directory -Path $outputDir | Out-Null
}

# Find direct download links at https://dotnet.microsoft.com/download/dotnet/5.0
$downloadurlx86 = "https://download.visualstudio.microsoft.com/download/pr/a8dcbda1-8720-453c-9ec6-5a9d90935643/28754321a8b966f1ce837e6f59035b48/windowsdesktop-runtime-5.0.3-win-x86.exe"
$downloadurlx64 = "https://download.visualstudio.microsoft.com/download/pr/c6541c87-42f2-4c5d-b6db-2df0dade5e00/13e89a5fec3ddb224cd93dd18b0761ff/windowsdesktop-runtime-5.0.3-win-x64.exe"

if($arch -eq "x86")
{
    $downloadurl = $downloadurlx86
}
elseif($arch -eq "amd64")
{
    $downloadurl = $downloadurlx64
}
else
{
    Write-Host "dotnet Desktop runtime not available for arch $arch"
    return
}


if(!(Test-Path $outputPath))
{
    Write-Host "Downloading $downloadurl to $outputPath"
    Invoke-WebRequest $downloadurl -OutFile $outputPath
}