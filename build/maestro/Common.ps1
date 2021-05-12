Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $test = "https://microsoft.visualstudio.com/"
    $Split1 = $test.Split(".")
    Write-Host "S1 " $Split1[0]
    $temp1 = $Split1[1]
    $Split2 = $temp1.Substring(8) 
    Write-Host "S2 " $Split2
    return $Split2
}