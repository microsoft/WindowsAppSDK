[CmdLetBinding()]
Param(
    [string]$Uri,
    [string]$token,
    [string]$JsonPath
)

$headers = @{
    Authorization="Bearer $token"
}

$body = Get-Content -Raw -Path $JsonPath

$contentType = 'application/x-www-form-urlencoded'
$api = '/api/builds?api-version=2020-02-20'
$fullUri = $Uri + $api

Write-Host $fullUri

$Response = Invoke-WebRequest -Method 'POST' -Uri $fullUri -Headers $headers -Body $body -ContentType $contentType
Write-Host $Response.statuscode

if ($Response.statuscode -ne '201')
{
  Write-Host $Response.statuscode
  Write-Host "##vso[task.complete result=Failed;]DONE"
}
