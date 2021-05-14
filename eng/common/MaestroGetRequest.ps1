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

$Response = Invoke-WebRequest -Method 'GET' -Uri $fullUri -Headers $headers -ContentType $contentType
Write-Host $Response

if ($Response.statuscode -ne '201')
{
  Write-Host $Response.statuscode
  Write-Host "##vso[task.complete result=Failed;]DONE"
}
