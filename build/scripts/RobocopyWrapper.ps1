param (
    [string]$source = "", 
    [string]$dest = "",
    [string]$options = "/E /XC /XN /XO /NJH /NJS /NDL /NP /NFL"
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$robocopyCmd = "robocopy $source $dest $options"

Invoke-Expression $robocopyCmd

if ($LASTEXITCODE -eq 0) 
{
    Write-Host "Robocopy operation completed successfully."
} 
elseif ($LASTEXITCODE -lt 4) 
{
    $LASTEXITCODE = 0
    Write-Host "Robocopy operation completed with some files copied."
} 
else 
{
    Write-Host "Copy operation encountered errors."
}

exit $LASTEXITCODE
