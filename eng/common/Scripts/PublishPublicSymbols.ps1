Param(
    [string] $RequestName,
    [boolean] $PublishToSymWeb = $true,
    [boolean] $PublishToMSDL = $true,
    [switch] $preProductionEnviroment
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$ProjectName = 'WindowsAppSDK'

$endPoint = "https://symbolrequestprod.trafficmanager.net/projects/$ProjectName/requests"
$resourceUrl = "api://30471ccf-0966-45b9-a979-065dbedb24c1"
if ($preProductionEnviroment)
{
  Write-Host "Using Preproduction Enviroment"
  $endPoint = "https://symbolrequestppe.trafficmanager.net/projects/$ProjectName/requests"
  $resourceUrl = "api://2748228d-54c2-4c34-a8ed-c4ae31661b39"
}

# See this page for info
Write-Host "See this page for more info:"
Write-Host "https://www.osgwiki.com/wiki/Symbols_Publishing_Pipeline_to_SymWeb_and_MSDL"

# Get the access token for the API
$token = (Get-AzAccessToken -ResourceUrl $resourceUrl).Token

# Register the request name
Write-Host "Registering request name"
$jsonData = @{
  requestName = "$RequestName"
  organizationName = "microsoft"
}
$jsonBody = $jsonData | ConvertTo-Json
Write-Host $jsonBody
Invoke-RestMethod -Method POST -Uri $endPoint -Headers @{ Authorization = "Bearer $token" } -ContentType "application/json" -Body $jsonBody

# Publish to public and internal server
Write-Host
Write-Host "Publishing to symbol server"
$jsonData = @{
    publishToInternalServer = $PublishToSymWeb
    publishToPublicServer = $PublishToMSDL
}
$jsonBody = $jsonData | ConvertTo-Json
Write-Host $jsonBody
Invoke-RestMethod -Method POST -Uri "$endPoint/$RequestName" -Headers @{ Authorization = "Bearer $token" } -ContentType "application/json" -Body $jsonBody

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

$publishToSymWebSucceeded = (-not $PublishToSymWeb)
$publishToMSDLSucceeded = (-not $PublishToMSDL)

$callCount = 1
$timeBetweenAPICalls = 20
$maxCallCount = 20
while (-not $publishToSymWebSucceeded -or -not $publishToMSDLSucceeded)
{
  Write-Host "Publishing result is pending"
  Start-Sleep -Seconds $timeBetweenAPICalls
  $result = Invoke-RestMethod -Method GET -Uri "$endPoint/$RequestName" -Headers @{ Authorization = "Bearer $token" } -ContentType "application/json"
  $callCount += 1

  Write-Host "MSDL Publishing Server Status: " $result.publishToPublicServerStatus
  Write-Host "MSDL Publishing Server Result: " $result.publishToPublicServerResult
  Write-Host "SymWeb Publishing Server Status: " $result.publishToInternalServerStatus
  Write-Host "SymWeb Publishing Server Result: " $result.publishToInternalServerResult

  if ($result.publishToPublicServerResult -eq 1)
  {
    Write-Host "MSDL Publishing result has Succeeded"
    $publishToMSDLSucceeded = $true
  }
  if ($result.publishToInternalServerResult -eq 1)
  {
    Write-Host "SymWeb Publishing result has Succeeded"
    $publishToSymWebSucceeded = $true
  }

  if ($result.publishToInternalServerResult -eq 2)
  {
    Write-Host "SymWeb Publishing result did not succeed"
    exit 1
  }
  if ($result.publishToInternalServerResult -eq 2)
  {
    Write-Host "MSDL Publishing result did not succeed"
    exit 1
  }
  if ($callCount -eq $maxCallCount)
  {
    Write-Host "Timeout reached"
    exit 1
  }
}
