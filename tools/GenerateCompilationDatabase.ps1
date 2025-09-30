$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -prerelease -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
write-host "msBuildPath: $msBuildPath"

$binlogFile = Split-Path $PSScriptRoot -parent
$binlogFile = Join-Path $binlogFile "BuildOutput\Binlogs\WindowsAppRuntime.x64.Release.binlog"

if (-Not (Test-Path $binlogFile)) {
    Write-Error "Binlog file not found: $binlogFile"
    exit 1
}

& $msBuildPath $binlogFile /v:normal /noconlog /flp:logfile=test.log

Write-Host "Log file generated at: $(Get-Location)\test.log"

Select-String -Path "test.log" -Pattern "Cl.exe" |
    ForEach-Object { $_.Line } |
    Where-Object { $_ -notmatch "Tracker.exe" } |
    Set-Content -Path "test-filtered.log"

Write-Host "Filtered log file generated at: $(Get-Location)\test-filtered.log"

Remove-Item "test.log"

& ms2cc -i "test-filtered.log" -d (Split-Path $PSScriptRoot -parent) -p

Remove-Item "test-filtered.log"
