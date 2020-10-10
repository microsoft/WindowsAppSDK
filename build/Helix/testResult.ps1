Param(
    [Parameter(Mandatory = $true)]
    [string]$Configuration,

    [Parameter(Mandatory = $true)]
    [string]$Platform
)

$AccessToken = $env:SYSTEM_ACCESSTOKEN
$HelixAccessToken = $env:HelixApiAccessToken

$azureDevOpsRestApiHeaders = @{
    "Accept"="application/json"
    "Authorization"="Basic $([System.Convert]::ToBase64String([System.Text.ASCIIEncoding]::ASCII.GetBytes(":$AccessToken")))"
}

$BuildUri = $env:BUILD_BUILDURI
echo $BuildUri

$url = "https://dev.azure.com/microsoft/LiftedIXP/_apis/test/runs?buildUri=$BuildUri"
echo $url

$testRuns = Invoke-RestMethod -Uri $url -Method Get -Headers $azureDevOpsRestApiHeaders

[System.Collections.Generic.List[string]]$workItems = @()

foreach ($testRun in $testRuns.value)
{
    $testRunResultsUri = "$($testRun.url)/results?api-version=5.0"
    $testResults = Invoke-RestMethod -Uri "$($testRun.url)/results?api-version=5.1" -Method Get -Headers $azureDevOpsRestApiHeaders
    foreach ($testResult in $testResults.value)
    {
        $info = ConvertFrom-Json $testResult.comment
        $helixJobId = $info.HelixJobId
        $helixWorkItemName = $info.HelixWorkItemName
        $workItem = $Configuration + "_" + $Platform + "_" + $helixJobId + "_" + $helixWorkItemName
        if (-not $workItems.Contains($workItem))
        {
            $workItems.Add($workItem)
            #Helix API version 2019-06-17 as per this documentation: https://helix.dot.net/swagger/ui/index#!
            $filesQueryUri = "https://helix.dot.net/api/2019-06-17/jobs/$helixJobId/workitems/$helixWorkItemName/files?access_token=$HelixAccessToken"
            $files = Invoke-RestMethod -Uri $filesQueryUri -Method Get
            echo $files.Count
            if($files.Count -gt 0)
            {
                foreach($file in $files)
                {
                    if ($file.Name.EndsWith(".jpg"))
                    {
                        $screenshotUrl = $file.Link + "?access_token=$HelixAccessToken"
                        $screenName = $workItem + "_" + $file.Name
                        echo $screenshotUrl
                        $output = "$PSScriptRoot\$screenName"
                        echo $output
                        Invoke-WebRequest -Uri $screenshotUrl -OutFile $output
                    }
                }
            }
        }
    }
}