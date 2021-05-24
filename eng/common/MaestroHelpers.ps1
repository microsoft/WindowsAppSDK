# Pram: CollectionUri must be in the form below
# https://microsoft.visualstudio.com/
function ExtractOrgFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $Split1 = $CollectionUri.Split(".")
    $temp1 = $Split1[0]
    $Split2 = $temp1.Substring(8)
    return $Split2
}