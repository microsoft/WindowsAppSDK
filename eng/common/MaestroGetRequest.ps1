[CmdLetBinding()]
Param(
    [string]$url,
    [string]$token,
    [string]$api,
    [string]$queryParameters
)

$headers = @{
    Authorization="Bearer $token"
}

$contentType = 'application/json'
$api = $api + '?api-version=2020-02-20' + $queryParameters
$fullUri = $url + $api

Write-Host $fullUri

$response = Invoke-WebRequest -Method 'GET' -Uri $fullUri -Headers $headers -ContentType $contentType
Write-Host $response

if ($Response.statuscode -lt '200')
{
  Write-Host $Response.statuscode
  Write-Host "##vso[task.complete result=Failed;]DONE"
}
if ($Response.statuscode -ge '300')
{
  Write-Host $Response.statuscode
  Write-Host "##vso[task.complete result=Failed;]DONE"
}


return $response