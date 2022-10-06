function GetCheckpointHash {
    param (
        [string]$CheckpointName
    )

    return (Get-FileHash -InputStream ([System.IO.MemoryStream]::New([System.Text.Encoding]::ASCII.GetBytes($CheckpointName))) -Algorithm MD5).Hash
}

function ReadBuildInfoFile {
    $BuildInfoPath = (Join-Path $env:Build_SourcesDirectory 'LocalBuildInformation.json')
    if (Test-Path ($BuildInfoPath) -PathType Leaf) {
        $global:Build_Info = Get-Content -Path $BuildInfoPath -raw | ConvertFrom-Json
    } else {
        $global:Build_Info = @{Checkpoint="none"}
    }
    
}

function WriteBuildInfoFile {
    Set-Content -Value (ConvertTo-Json $global:Build_Info -depth 32) (Join-Path $env:Build_SourcesDirectory 'LocalBuildInformation.json')
}

function ShowCheckpoint {
    $CheckpointName = $global:Build_Info.Checkpoint
    if ($CheckpointName -eq "none") {
        Write-Host @"

**************************************************
No current checkpoint
**************************************************

"@ -ForegroundColor CYAN        
    } else {
        $CheckpointHash = GetCheckpointHash($CheckpointName)
        Write-Host @"

**************************************************
Build Checkpoint: $CheckpointHash
$CheckpointName
**************************************************

"@ -ForegroundColor CYAN
    }
}

function Checkpoint {
    param (
        [string]$CheckpointName
    )
    $CheckpointHash = GetCheckpointHash($CheckpointName)

    if ($env:Build_Resume -eq $true) {
        if (($global:Build_Info.Checkpoint -eq $CheckpointName) -or ($global:Build_Info.Checkpoint -eq $CheckpointHash)) {
            $env:Build_Resume = $false
            return $true
        } else {
            return $false
        }
    } else {
        if ([string]::IsNullOrWhiteSpace($CheckpointName)) {
            $global:Build_Info.Checkpoint = "none"
        } else {
            $global:Build_Info.Checkpoint = $CheckpointName
            ShowCheckpoint
        }

        WriteBuildInfoFile
        return $true
    }
}

ReadBuildInfoFile
