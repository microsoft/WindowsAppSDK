Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $Split1 = $CollectionUri.Split(".")
    $temp1 = $Split1[0]
    $Split2 = $temp1.Substring(8)
    return $Split2
}