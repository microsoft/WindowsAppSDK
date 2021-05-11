Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    return $CollectionUri.Substring(22, $CollectionUri.length - 23)
}