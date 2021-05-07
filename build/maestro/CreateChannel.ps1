[CmdLetBinding()]
Param(
    [string]$Uri,
    [string]$token
)

$headers = @{
    Authorization="Bearer $token"
}

$Body = @{
    id = '3'
    name = 'test3'
    classification = 'test3'
} | ConvertTo-Json

Write-Host $Uri

$Response = Invoke-WebRequest -Method Post -Uri $Uri -Headers $headers -Body $Body -ContentType 'application/x-www-form-urlencoded'
Write-Host $Response.statuscode

if ($Response.statuscode -ne '201')
{
  Write-Host "##vso[task.complete result=Failed;]DONE"
}