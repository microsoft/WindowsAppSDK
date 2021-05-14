[CmdLetBinding()]
Param(
    [string]$url,
    [string]$token,
    [string]$api,
    [string]$queryParameters,
    [string]$jsonBodyPath
)

$headers = @{
    Authorization="Bearer $token"
}

$body = ''
if (-not [string]::IsNullOrEmpty($jsonBodyPath))
{
  $body = Get-Content -Raw -Path $jsonBodyPath
}

$contentType = 'application/json'
$api = $api + '?api-version=2020-02-20' + $queryParameters
$fullUri = $url + $api

Write-Host $fullUri

$Response = Invoke-WebRequest -Method 'POST' -Uri $fullUri -Headers $headers -Body $body -ContentType $contentType
Write-Host $Response

if ($Response.statuscode -ne '201')
{
  Write-Host $Response.statuscode
  Write-Host "##vso[task.complete result=Failed;]DONE"
}
