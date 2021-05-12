Write-Host "Hello from Common.ps1"

# Pram: CollectionUri must be in the form below
# https://dev.azure.com/fabrikamfiber/
function GetOrgNameFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $test = "https://microsoft.visualstudio.com/"
    $Split1 = $test.Split("//")
    Write-Host "S1 " $Split1[1]
    $temp1 = $Split1[1]
    $Split2 = $temp1.Split(".")
    Write-Host "S2 " $Split2[0]


    $Inputstring ="Sonali Bhatt is Database Administrator"
    $CharArray =$InputString.Split(" ")
    $String1= $CharArray[0]
    $String2= $CharArray[4] 
    write-host $String1
    write-host $String2
    return $Split2[0]
}