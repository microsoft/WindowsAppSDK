[CmdLetBinding()]
Param(
    [string]$Uri,
    [string]$token
)

$headers = @{
    Authorization="Bearer $token"
}

$Body = @{
    'name' = 'test3'
    'classification' = 'test3'
    'api-version' = '2020-02-20'
} | ConvertTo-Json

Write-Host $Uri

$Response = Invoke-WebRequest -Method 'POST' -Uri $Uri -Headers $headers -Body $Body
Write-Host $Response.statuscode

if ($Response.statuscode -ne '201')
{
  Write-Host "##vso[task.complete result=Failed;]DONE"
}