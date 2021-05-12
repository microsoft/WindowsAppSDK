Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    return $CollectionUri.Split("//")[1].Split(".")[0]
}