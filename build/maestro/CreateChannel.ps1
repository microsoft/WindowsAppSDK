$Uri = '$(MaestroUri)'
$token = '$(MaestroToken)'
$headers = @{
    Authorization="Bearer $token"
}

$Body = @{
    id = '3'
    name = 'test3'
    classification = 'test3'
} | ConvertTo-Json

$Response = Invoke-WebRequest -Method Post -Uri $Uri -Headers $headers -Body $Body -Verbose
WriteHost $Response.statuscode

if ($Response.statuscode -ne '201')
{
  Write-Host "##vso[task.complete result=Failed;]DONE"
}