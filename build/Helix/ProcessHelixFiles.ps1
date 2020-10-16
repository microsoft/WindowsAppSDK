Param(
    [string]$AccessToken = $env:SYSTEM_ACCESSTOKEN,
    [string]$HelixAccessToken = $env:HelixAccessToken,
    [string]$CollectionUri = $env:SYSTEM_COLLECTIONURI,
    [string]$TeamProject = $env:SYSTEM_TEAMPROJECT,
    [string]$BuildUri = $env:BUILD_BUILDURI,
    [string]$OutputFolder = "HelixOutput"
)

$helixLinkFile = "$OutputFolder\LinksToHelixTestFiles.html"
$visualTreeVerificationFolder = "$OutputFolder\UpdatedVisualTreeVerificationFiles"

$accessTokenParam = ""
if($HelixAccessToken)
{
    Write-Host "!!!!helix access token is present!!!!"
    $accessTokenParam = "?access_token=$HelixAccessToken"
}

function Generate-File-Links
{
    Param ([Array[]]$files,[string]$sectionName)
    if($files.Count -gt 0)
    {
        Out-File -FilePath $helixLinkFile -Append -InputObject "<div class=$sectionName>"
        Out-File -FilePath $helixLinkFile -Append -InputObject "<h4>$sectionName</h4>"
        Out-File -FilePath $helixLinkFile -Append -InputObject "<ul>"
        foreach($file in $files)
        {
            Out-File -FilePath $helixLinkFile -Append -InputObject "<li><a href=$($file.Link)>$($file.Name)</a></li>"
        }
        Out-File -FilePath $helixLinkFile -Append -InputObject "</ul>"
        Out-File -FilePath $helixLinkFile -Append -InputObject "</div>"
    }
}

#Create output directory
New-Item $OutputFolder -ItemType Directory

$azureDevOpsRestApiHeaders = @{
    "Accept"="application/json"
    "Authorization"="Basic $([System.Convert]::ToBase64String([System.Text.ASCIIEncoding]::ASCII.GetBytes(":$AccessToken")))"
}

. "$PSScriptRoot/AzurePipelinesHelperScripts.ps1"

$queryUri = GetQueryTestRunsUri -CollectionUri $CollectionUri -TeamProject $TeamProject -BuildUri $BuildUri -IncludeRunDetails
Write-Host "queryUri = $queryUri"

$testRuns = Invoke-RestMethod -Uri $queryUri -Method Get -Headers $azureDevOpsRestApiHeaders
$webClient = New-Object System.Net.WebClient
[System.Collections.Generic.List[string]]$workItems = @()

foreach ($testRun in $testRuns.value)
{
    $testResults = Invoke-RestMethod -Uri "$($testRun.url)/results?api-version=5.1" -Method Get -Headers $azureDevOpsRestApiHeaders
    foreach ($testResult in $testResults.value)
    {
        if ($testResult.comment -ne $null)
        {
            $info = ConvertFrom-Json $testResult.comment
            $helixJobId = $info.HelixJobId
            $helixWorkItemName = $info.HelixWorkItemName
            $workItem = $Configuration + "_" + $Platform + "_" + $helixJobId + "_" + $helixWorkItemName
            if (-not $workItems.Contains($workItem))
            {
                $workItems.Add($workItem)
                $filesQueryUri = "https://helix.dot.net/api/2019-06-17/jobs/$helixJobId/workitems/$helixWorkItemName/files$accessTokenParam"
                Write-Host "files query uri = $filesQueryUri"
                $files = Invoke-RestMethod -Uri $filesQueryUri -Method Get
                $screenShots = $files | where { $_.Name.EndsWith(".jpg") }
                Write-Host "screenshots = $screenShots"
                $dumps = $files | where { $_.Name.EndsWith(".dmp") }
                $logs = $files | where { $_.Name.EndsWith(".log") }
                $visualTreeVerificationFiles = $files | where { $_.Name.EndsWith(".xml") -And (-Not $_.Name.Contains('testResults')) }
                $pgcFiles = $files | where { $_.Name.EndsWith(".pgc") }
                
                foreach($file in $files)
                {
                    # We don't upload dump files since they are too large.
                    # We don't upload the _subresults.json since they usually not useful for investigating test failures.
                    if(!$file.Name.EndsWith(".dmp") -and !$file.Name.EndsWith("_subresults.json"))
                    {
                        $destination = "$OutputFolder\$($file.Name)"
                        Write-Host "Copying $($file.Name) to $destination"
                        try
                        {
                            $webClient.DownloadFile($file.Link, $destination)
                        }
                        catch
                        {
                            Log-Error "Failed to download $($file.Name): $($_.Exception.Message)"
                        }
                    }
                }
            }
        }
    }
}

if(Test-Path $visualTreeVerificationFolder)
{
    $verificationFiles = Get-ChildItem $visualTreeVerificationFolder
    $prefixList = @()

    foreach($file in $verificationFiles)
    {
        Write-Host "Copying $($file.Name) to $visualTreeVerificationFolder"
        Move-Item $file.FullName "$visualTreeVerificationFolder\$($file.Name)" -Force
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