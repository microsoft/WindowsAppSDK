Param(
    [string]$Ms2ccVersion = "1.3.0"
)

$binlogFileBase = Split-Path $PSScriptRoot -parent
$binlogFile0 = Join-Path $binlogFileBase "BuildOutput\Binlogs\MrtCore.x64.Release.binlog"
$binlogFile1 = Join-Path $binlogFileBase "BuildOutput\Binlogs\WindowsAppRuntime.x64.Release.binlog"

$binlogFiles = @($binlogFile0, $binlogFile1)

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -prerelease -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
write-host "msBuildPath: $msBuildPath"

Remove-Item "temp-filtered.log" -ErrorAction SilentlyContinue

foreach ($binlogFile in $binlogFiles) {
    if (-Not (Test-Path $binlogFile)) {
        Write-Error "Binlog file not found: $binlogFile"
        exit 1
    }

    & $msBuildPath $binlogFile /v:normal /noconlog /flp:logfile=temp.log

    Select-String -Path "temp.log" -Pattern "Cl.exe" |
        ForEach-Object { $_.Line } |
        Where-Object { $_ -notmatch "Tracker.exe" } |
        Out-File -FilePath "temp-filtered.log" -Append -Encoding utf8

    Remove-Item "temp.log"
}

Write-Host "Filtered log file generated at: $(Get-Location)\temp-filtered.log"

$ms2ccPath = Join-Path $PSScriptRoot "ms2cc"
$ms2ccExe = Join-Path $ms2ccPath "ms2cc.exe"

if (-Not (Test-Path $ms2ccExe)) {
    Write-Host "Downloading ms2cc..."
    $ms2ccUrl = "https://github.com/freddiehaddad/ms2cc/releases/download/v$Ms2ccVersion/ms2cc-$Ms2ccVersion.zip"
    $zipPath = Join-Path $PSScriptRoot "ms2cc-$Ms2ccVersion.zip"

    try {
        Invoke-WebRequest -Uri $ms2ccUrl -OutFile $zipPath -UseBasicParsing
        Write-Host "Downloaded ms2cc to: $zipPath"

        if (-Not (Test-Path $ms2ccPath)) {
            New-Item -ItemType Directory -Path $ms2ccPath -Force | Out-Null
        }

        Expand-Archive -Path $zipPath -DestinationPath $ms2ccPath -Force
        Write-Host "Extracted ms2cc to: $ms2ccPath"

        Remove-Item $zipPath -Force
        Write-Host "Cleaned up zip file"

        if (Test-Path $ms2ccExe) {
            Write-Host "ms2cc successfully downloaded and extracted"
        } else {
            Write-Error "Failed to extract ms2cc.exe"
            exit 1
        }
    }
    catch {
        Write-Error "Failed to download or extract ms2cc: $_"
        exit 1
    }
} else {
    Write-Host "ms2cc already exists at: $ms2ccExe"
}

& $ms2ccExe -i "temp-filtered.log" -d (Split-Path $PSScriptRoot -parent) -p

Remove-Item "temp-filtered.log"
