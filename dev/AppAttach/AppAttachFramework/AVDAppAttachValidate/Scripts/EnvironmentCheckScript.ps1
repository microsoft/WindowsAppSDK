param(
        [Parameter(Mandatory=$false)]
        [string] $powershellIsRunningAsAdmin,

        [Parameter(Mandatory=$false)]
        [string] $powershellIsNotRunningAsAdmin
    )
try{
    
    if(-not ($powershellIsRunningAsAdmin -and $powershellIsNotRunningAsAdmin)){
        throw "Mandatory parameters are missing in the script"
    }

    # Check if Powershell has admin priviledges
    if(-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))
    {
        Write-Output $powershellIsNotRunningAsAdmin
    }
    else
    {
        Write-Output $powershellIsRunningAsAdmin
    }
}
catch {
    Write-Error "Error Occurred:"
    Write-Error $_
}