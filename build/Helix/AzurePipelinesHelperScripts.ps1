function GetAzureDevOpsBaseUri
{
    Param(
        [string]$CollectionUri,
        [string]$TeamProject
    )

    return $CollectionUri + $TeamProject
}

function GetQueryTestRunsUri
{
    Param(
        [string]$CollectionUri,
        [string]$TeamProject,
        [string]$BuildUri,
        [switch]$IncludeRunDetails
    )

    if ($IncludeRunDetails)
    {
        $includeRunDetailsParameter = "&includeRunDetails=true"
    }
    else
    {
        $includeRunDetailsParameter = ""
    }

    $baseUri = GetAzureDevOpsBaseUri -CollectionUri $CollectionUri -TeamProject $TeamProject
    $queryUri = "$baseUri/_apis/test/runs?buildUri=$BuildUri$includeRunDetailsParameter&api-version=5.0"
    return $queryUri
}

function Get-HelixJobTypeFromTestRun
{
    Param ($testRun)

    $testRunSingleResultUri = "$($testRun.url)/results?`$top=1&`$skip=0&api-version=5.1"
    $singleTestResult = Invoke-RestMethod -Uri $testRunSingleResultUri -Method Get -Headers $azureDevOpsRestApiHeaders
    $count = $singleTestResult.value.Length
    if($count -eq 0)
    {
        # If the count is 0, then results have not yet been reported for this run.
        # We only care about completed runs with results, so it is ok to just return 'UNKNOWN' for this run.
        return "UNKNOWN"
    }
    else
    {
        $info = ConvertFrom-Json $singleTestResult.value.comment
        $helixJobId = $info.HelixJobId
        $job = Invoke-RestMethod -Uri "https://helix.dot.net/api/2019-06-17/jobs/${helixJobId}?access_token=${HelixAccessToken}" -Method Get
        return $job.Type
    }
}