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
    Param (
        $testRun,
        [Parameter(Mandatory=$false)]
        [string]$token
    )

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
        # There may already be other test results reported in the pipeline from other non-Helix tests.
        # In this case, there won't be a comment on the test run, or the HelixJobId will be missing, so
        # we need to first check if they exist in order to prevent errors.

        if($singleTestResult.value.comment){
            $info = ConvertFrom-Json $singleTestResult.value.comment
            if ($info.HelixJobId) {
                $helixJobId = $info.HelixJobId

                $queryUrl = "https://helix.dot.net/api/2019-06-17/jobs/${helixJobId}"
                if ($token)
                {
                    $queryUrl += "?access_token=${token}"
                }

                $job = Invoke-RestMethodWithRetries $queryUrl
                return $job.Type
            }
        }

        # If we couldn't find the HelixJobType the test run is likely another non-Helix test, so we'll return unknown.
        return "UNKNOWN"
    }
}

function Append-HelixAccessTokenToUrl
{
    Param ([string]$url, [string]$token)
    if($url.Contains("?"))
    {
        $url = "$($url)&access_token=$($token)"
    }
    else
    {
        $url = "$($url)?access_token=$($token)"
    }
    return $url
}


# The Helix Rest api is sometimes unreliable. So we call these apis with retry logic. 
# Note: The Azure DevOps apis are stable and do not need to be called with this retry logic.
$helixApiRetries = 0
$helixApiRetriesMax = 10 

function Download-StringWithRetries
{
    Param ([string]$fileName, [string]$url)

    $result = ""
    $done = $false

    while(!($done))
    {
        try
        {
            Write-Host "Downloading $fileName"
            $result = (New-Object System.Net.WebClient).DownloadString($url)
            $done = $true
        }
        catch
        {
            Write-Host "Failed to download $fileName $($PSItem.Exception)"

            $helixApiRetries = $helixApiRetries + 1
            if($helixApiRetries -lt $helixApiRetriesMax)
            {
                Write-Host "Sleep and retry download of $fileName"
                Start-Sleep 60
            }
            else
            {
                throw "Failed to download $fileName"
            }
        }
    }

    return $result
}

function Invoke-RestMethodWithRetries
{
    Param ([string]$url)

    $result = @()
    $done = $false

    while(!($done))
    {
        try
        {
            $result = Invoke-RestMethod -Uri $url -Method Get
            $done = $true
        }
        catch
        {
            Write-Host "Failed to invoke Rest method $($PSItem.Exception)"

            $helixApiRetries = $helixApiRetries + 1
            if($helixApiRetries -lt $helixApiRetriesMax)
            {
                Write-Host "Sleep and retry invoke"
                Start-Sleep 60
            }
            else
            {
                throw "Failed to invoke Rest method"
            }
        }
    }

    return $result
}

function Download-FileWithRetries
{
    Param ([string]$fileurl, [string]$destination)

    $done = $false

    while(!($done))
    {
        try
        {
            Write-Host "Downloading $destination"
            $webClient.DownloadFile($fileurl, $destination)
            $done = $true
        }
        catch
        {
            Write-Host "Failed to download $destination $($PSItem.Exception)"

            $helixApiRetries = $helixApiRetries + 1
            if($helixApiRetries -lt $helixApiRetriesMax)
            {
                Write-Host "Sleep and retry download of $destination"
                Start-Sleep 60
            }
            else
            {
                throw "Failed to download $destination"
            }
        }
    }
}