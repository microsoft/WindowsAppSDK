Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $Split1 = $CollectionUri.Split("//")[1]
    Write-Host "S1 " $Split1
    $Split2 =  $Split1.Split(".")[0]
    return $Split2
}