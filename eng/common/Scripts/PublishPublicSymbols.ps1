Param(
    [string] $RequestName
)

$ProjectName = 'WindowsAppSDK'

# See this page for info
Write-Host "See this page for more info:"
Write-Host "https://www.osgwiki.com/wiki/Symbols_Publishing_Pipeline_to_SymWeb_and_MSDL"

# Get the access token for the API
$token = (Get-AzAccessToken -ResourceUrl api://30471ccf-0966-45b9-a979-065dbedb24c1).Token

# Register the request name
Write-Host "Registering request name"
$jsonData = @{
  requestName = "$RequestName"
  organizationName = "microsoft"
}
$jsonBody = $jsonData | ConvertTo-Json
Write-Host $jsonBody
Invoke-RestMethod -Method POST -Uri https://symbolrequestprod.trafficmanager.net/projects/$ProjectName/requests -Headers @{ Authorization = "Bearer $token" } -ContentType "application/json" -Body $jsonBody

# Publish to public and internal server
Write-Host
Write-Host "Publishing to symbol server"
$jsonData = @{
    publishToInternalServer = "true"
    publishToPublicServer = "true"
}
$jsonBody = $jsonData | ConvertTo-Json
Write-Host $jsonBody
Invoke-RestMethod -Method POST -Uri https://symbolrequestprod.trafficmanager.net/projects/$ProjectName/requests/$RequestName -Headers @{ Authorization = "Bearer $token" } -ContentType "application/json" -Body $jsonBody

# Print publishing status information
Write-Host
Write-Host "Check status of symbol publishing here:"

Write-Host
Write-Host "PublishingStatus Key"
Write-Host "0: NotRequested; The request has not been requested to publish."
Write-Host "1: Submitted; The request is submitted to be published"
Write-Host "2: Processing; The request is still being processed"
Write-Host "3: Completed; The request has been completed processing. It can be failed or successful. Check PublishingResult to get more details"

Write-Host
Write-Host "PublishingResult Key"
Write-Host "0: Pending; The request has not completed or has not been requested."
Write-Host "1: Succeeded; The request has published successfully"
Write-Host "2: Failed; The request has failed to publish"
Write-Host "3: Cancelled; The request was cancelled."

# Check status of publishing request
Write-Host
Write-Host "Publishing Status:"
$publishToPublicServerResult = 0
$callCount = 1
$timeBetweenAPICalls = 20
$maxCallCount = 20
while ($publishToPublicServerResult -eq 0)
{
  Write-Host "Publishing result is pending"
  Start-Sleep -Seconds $timeBetweenAPICalls
  $result = Invoke-RestMethod -Method GET -Uri https://symbolrequestprod.trafficmanager.net/projects/$ProjectName/requests/$RequestName -Headers @{ Authorization = "Bearer $token" } -ContentType "application/json"
  $callCount += 1
  if ($result.publishToPublicServerStatus -eq 0)
  {
    Write-Host "Publishing Status is not showing as submitted"
    exit 1
  }
  $publishToPublicServerResult = $result.publishToPublicServerResult
  if ($publishToPublicServerResult -eq 1)
  {
    Write-Host "Publishing result has Succeeded"
    exit 0
  }
  if ($publishToPublicServerResult -eq 2)
  {
    Write-Host "Publishing result has Failed"
    exit 1
  }
  if ($publishToPublicServerResult -eq 3)
  {
    Write-Host "Publishing result has been Canceled"
    exit 1
  }
  if ($callCount -eq $maxCallCount)
  {
    Write-Host "Timeout reached"
    exit 1
  }
}
