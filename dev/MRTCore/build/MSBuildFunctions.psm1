# Information about the MSBuild version we depend on and the install script for it.
# This script is designed so that only these two variables need to change if we have
# a new dependency on a specific version of MSBuild. If the cmd prompt used for init
# isn't the correct one, this will download MSBuild to the .buildtools directory. The
# version can be as precise as we need it to be (i.e. 16.8.0.45203), but we should
# be as flexible as we can
$MSBuildVer = "16.8"

$repoRoot = Split-Path -Parent $PSScriptRoot
$vsconfigPath = "$repoRoot\.vsconfig_buildtools"

# This URI corresponds to MSBuild 16.8. If this ever changes, change the MSBuildVer
# property above
$MSBuildInstallURI = "https://download.visualstudio.microsoft.com/download/pr/ecb3860e-5c66-4a3f-8acf-ef190d5f9a96/18162a4d36635d0958bf56654d4a03b211dcd8474b3a4036c8a0a0fb6a0eb053/vs_BuildTools.exe"
$MSBuildInstallParams = "--norestart --quiet --wait --force --installPath {0} --config $vsconfigPath"
$MSBuildUninstallParams = "uninstall --norestart --quiet --wait --force --installPath {0}"

function Download-MSBuild([string]$OutFile)
{
    Write-Host -NoNewline "Downloading $OutFile... "
    Invoke-WebRequest -Uri $MSBuildInstallURI -OutFile $OutFile
    Write-Host -ForegroundColor Green Done.
}

function LaunchSetupAndWait([string]$exePath, [string[]]$ArgumentList)
{
    Write-Host "$exePath $($ArgumentList -join ' ')"
    $c = Start-Process $exePath -Wait -PassThru -ArgumentList $ArgumentList
    $exitcode = $c.ExitCode

    # 3010 just means restart required, which isn't necessary
    $success = $exitCode -eq 0 -or $exitCode -eq 3010
    if ($success)
    {
        Write-Host -ForegroundColor Green Done.
    }
    else
    {
        Write-Host -ForegroundColor Red "Error $exitcode"
    }
    return ($success)
}

function Install-MSBuild([string]$installDir, [string]$vs_buildtools, [string]$logsDir)
{
    New-Item -Path $installDir -Force -ItemType 'Directory' | Out-Null
    $installed = LaunchSetupAndWait $vs_buildtools -ArgumentList "$([string]::Format($MSBuildInstallParams, $installDir))"
    if (!$installed)
    {
        Write-InstallError $logsDir
        exit 1
    }
}

function Modify-MSBuild([string]$installDir, [string]$vs_buildtools, [string]$logsDir)
{
    $modified = LaunchSetupAndWait $vs_buildtools -ArgumentList "modify $([string]::Format($MSBuildInstallParams, $installDir))"
    if (!$modified)
    {
        Write-InstallError $logsDir
        exit 1
    }
}

function Uninstall-MSBuild([string]$installDir, [string]$vs_buildtools, [string]$logsDir)
{
    $installed = LaunchSetupAndWait $vs_buildtools -ArgumentList "uninstall $([string]::Format($MSBuildUninstallParams, $installDir))"
    if (!$installed)
    {
        Write-InstallError $logsDir
        exit 1
    }
}

function Write-InstallError([string]$logsDir)
{
    # try to figure out what went wrong
    $latestClientLog = (Get-ChildItem $env:temp\dd_* | Sort-Object -Property LastWriteTime -Descending)[0]
    $log = (Get-Content $latestClientLog)
    $errorLines = ($log -like '*Error :*')
    if ($errorLines)
    {
        Write-Host $errorLines
    }
    
    $logLocation = $env:Temp
    if (-not [string]::IsNullOrEmpty($logsDir))
    {
        New-Item -Path $logsDir -Force -ItemType 'Directory' | Out-Null
        $logLocation = $logsDir
        Copy-Item -Path "$env:Temp\*" -Filter "dd_*" -Destination $logsDir
    }

    Write-Host "For more information see $logLocation\dd_*"
}

function Test-MSBuild([string]$msbuildExe)
{
    $msbuildVerInstalled = "n/a"
    if (Test-Path $msbuildExe)
    {
        $msbuildVerInstalled = .$msbuildExe "-version" "-noLogo"
        Write-Host "MSBuild.exe at $msbuildExe is version $msbuildVerInstalled"
    }
    return $msbuildVerInstalled.StartsWith($MSBuildVer)
}