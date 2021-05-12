Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $Split1 = $CollectionUri.Split("//")
    Write-Host "S1 " $Split1[1]
    $temp1 = $Split1[1]
    $Split2 = $temp1.Split(".")
    Write-Host "S2 " $Split2[0]
    return $Split2[0]
}