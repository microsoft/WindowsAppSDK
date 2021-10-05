# Param: CollectionUri must be in the form below
# https://microsoft.visualstudio.com[/]*
function ExtractOrgFromAzureDevOpsCollectionUri([string]$CollectionUri)
{
    $CollectionUri = $CollectionUri.TrimEnd('/')
    $Split1 = $CollectionUri.Split(".")
    if ($Split1.Length -ne 3)
    {
        Write-Host "##vso[task.complete result=Failed;]Format Error"
        Exit 1
    }
    if ($split1[1] -ne "visualstudio")
    {
        Write-Host "##vso[task.complete result=Failed;]Format Error"
        Exit 1
    }
    if ($split1[2].Substring(0,3) -ne "com")
    {
        Write-Host "##vso[task.complete result=Failed;]Format Error"
        Exit 1
    }
    $temp1 = $Split1[0]
    $result = $temp1.Substring(8)
    return $result
}

# Param: buildRepositoryUri must be in the form below
# https://microsoft.visualstudio.com/xxx/_git/xxx[/]
function ConvertToMaestroFriendlyAzureDevOpUri([string]$buildRepositoryUri)
{
    $buildRepositoryUri = $buildRepositoryUri.TrimEnd('/')
    if (IsGitHubRepo($buildRepositoryUri))
    {
        Write-Host "URI is github"
        return $buildRepositoryUri
    }
    if (IsMaestroFriendlyAzureDevOpUri($buildRepositoryUri))
    {
        Write-Host "URI is already Maestro friendly"
        return $buildRepositoryUri
    }
    $devOpsAccount = ExtractOrgFromAzureDevOpsCollectionUri $buildRepositoryUri
    $buildRepositoryUriSplit = $buildRepositoryUri.Split("/")
    if ($buildRepositoryUriSplit.Length -ne 6)
    {
        Write-Host "##vso[task.complete result=Failed;]Format Error"
        Exit 1
    }

    $repository = "https://dev.azure.com/" + $devOpsAccount + "/" + $buildRepositoryUriSplit[3] + "/" + $buildRepositoryUriSplit[4] + "/" + $buildRepositoryUriSplit[5]
    return $repository
}

function IsGitHubRepo([string]$buildRepositoryUri)
{
    $githubUrls = @("https://github.com", "https://wwww.github.com")
    for ($i = 0; $i -le ($githubUrls.length); $i += 1)
    {
        if ($buildRepositoryUri.length -ge $githubUrls[$i].length)
        {
            if($buildRepositoryUri.Substring(0, $githubUrls[$i].length) -eq $githubUrls[$i])
            {
                return $true
            }
        }
    }
    return $false
}

function IsMaestroFriendlyAzureDevOpUri([string]$buildRepositoryUri)
{
    $azdoUri = "https://dev.azure.com"
    if ($buildRepositoryUri.length -ge $azdoUri.length)
    {
        if($buildRepositoryUri.Substring(0, $azdoUri.length) -eq $azdoUri)
        {
            return $true
        }
    }
    return $false
}