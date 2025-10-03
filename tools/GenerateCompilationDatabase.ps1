Param(
    [string]$Ms2ccVersion = "1.3.0"
)

$binlogFileBase = Join-Path (Split-Path $PSScriptRoot -parent) "BuildOutput\Binlogs"

$binlogFiles = Get-ChildItem -Path $binlogFileBase -Filter *.binlog -Recurse | Select-Object -ExpandProperty FullName

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -prerelease -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
write-host "msBuildPath: $msBuildPath"

Remove-Item "temp-filtered.log" -ErrorAction SilentlyContinue
Remove-Item "temp-filtered2.log" -ErrorAction SilentlyContinue

# Target "ClCompile" in file "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.CppCommon.targets" from project "C:\WindowsAppSDK\dev\Detours\Detours.vcxproj" (target "_ClCompile" depends on it):
# Context here would be: "C:\WindowsAppSDK\dev\Detours"

foreach ($binlogFile in $binlogFiles) {
    if (-Not (Test-Path $binlogFile)) {
        Write-Error "Binlog file not found: $binlogFile"
        exit 1
    }

    & $msBuildPath $binlogFile /v:normal /noconlog /flp:logfile=temp.log

    Select-String -Path "temp.log" -Pattern "Target ""ClCompile"" in file","Cl.exe"  |
        ForEach-Object { $_.Line } |
        Where-Object { $_ -notmatch "Tracker.exe" } |
        Out-File -FilePath "temp-filtered.log" -Append -Encoding utf8

    Remove-Item "temp.log"
}

Write-Host "Filtered log file generated at: $(Get-Location)\temp-filtered.log"

$contextPath = ""

# for each line in temp-filtered.log, if it is a "Target " line, extract the project directory and save in the contextPath variable
# if it is a "Cl.exe" line, prepend the contextPath to every source file in that line only if it is
# a relative path, then output the modified line to temp-filtered-2.log
# The source files are the arguments that ends with .cpp, .c, or .h
# They can have spaces in them. If so, they are enclosed in quotes.

$lines = Get-Content "temp-filtered.log"

foreach ($line in $lines) {
    if ($line -match 'Target "ClCompile" in file "([^"]+)" from project "([^"]+)"') {
        $contextPath = Split-Path $matches[2] -parent
        Write-Host "Context path set to: $contextPath"
    } elseif ($line -match 'Cl\.exe (.+)$') {
        $clLine = $matches[1]
        $args = $clLine -split ' (?=(?:[^"]*"[^"]*")*[^"]*$)'

        $modifiedArgs = @()
        foreach ($arg in $args) {
            if ($arg -match '^(.*\.(cpp|c|h))$' -or $arg -match '^"(.*\.(cpp|c|h))"$') {
                $filePath = $arg.Trim('"')
                if (-Not ([System.IO.Path]::IsPathRooted($filePath))) {
                    $filePath = Join-Path $contextPath $filePath
                }
                if ($arg.StartsWith('"') -and $arg.EndsWith('"')) {
                    $modifiedArgs += '"' + $filePath + '"'
                } else {
                    $modifiedArgs += $filePath
                }
            } else {
                $modifiedArgs += $arg
            }
        }

        $modifiedLine = "Cl.exe " + ($modifiedArgs -join ' ')
        Add-Content -Path "temp-filtered2.log" -Value $modifiedLine
        # Write-Host "Processed Cl.exe line: $modifiedLine"
    }
}

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

& $ms2ccExe -i "temp-filtered2.log" -d (Split-Path $PSScriptRoot -parent) -p

Remove-Item "temp-filtered.log"
Remove-Item "temp-filtered2.log"
