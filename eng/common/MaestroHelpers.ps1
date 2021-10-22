# Pram: CollectionUri must be in the form below
# https://microsoft.visualstudio.com/
function ExtractOrgFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $Split1 = $CollectionUri.Split(".")
    $temp1 = $Split1[0]
    $Split2 = $temp1.Substring(8)
    return $Split2
}

function ConvertToMaestroFriendlyUri([string]$buildRepositoryUri)
{
    $devOpsAccount = ExtractOrgFromAzureDevOpsCollectionUri $buildRepositoryUri
    $buildRepositoryUriSplit = $buildRepositoryUri.Split("/")
    $repository = "https://dev.azure.com/" + $devOpsAccount + "/" + $buildRepositoryUriSplit[3] + "/" + $buildRepositoryUriSplit[4] + "/" + $buildRepositoryUriSplit[5]
    return $repository
}

function IsGitHubRepo([string]$buildRepositoryUri)
{
    $githubUri = "https://github.com"
    if ($buildRepositoryUri.length -ge $githubUri.length)
    {
        if($buildRepositoryUri.Substring(0, $githubUri.length) -eq $githubUri)
        {
            return $true
        }
    }
    return $false
}