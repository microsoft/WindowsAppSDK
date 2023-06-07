param(
        [Parameter(Mandatory=$false)]
        [string] $accessToken,

        [Parameter(Mandatory=$false)]
        [string] $emailId,

        [Parameter(Mandatory=$false)]
        [string] $resourceGroupName,

        [Parameter(Mandatory=$false)]
        [string] $subscriptionId,

        [Parameter(Mandatory=$false)]
        [string] $storageAccountName,

        [Parameter(Mandatory=$false)]
        [string] $fileshareName,

        [Parameter(Mandatory=$false)]
        [string] $packageName,

        [Parameter(Mandatory=$false)]
        [string] $fileExistsInFileShare,

        [Parameter(Mandatory=$false)]
        [string] $fileDoesNotExistInFileShare
    )

try{
    if(-not ($accessToken -and $emailId -and $resourceGroupName -and $subscriptionId -and $storageAccountName -and $fileshareName -and $packageName -and $fileExistsInFileShare -and $fileDoesNotExistInFileShare)){
        throw "Mandatory parameters are missing in the script"
    }

    # Check and install dependent modules
    if(-not ((Get-PackageProvider).Name -contains "Nuget")){
        Install-PackageProvider -Name NuGet -MinimumVersion 2.8.5.201 -Force
    }
    if(-not (Get-Module Az.Accounts -ListAvailable)){
        Install-Module Az.Accounts -Force -AllowClobber
    }
    if(-not (Get-Module Az.Storage -ListAvailable)){
        Install-Module Az.Storage -Force -AllowClobber
    }
    if(-not (Get-Module Az.DesktopVirtualization -ListAvailable)){
        Install-Module Az.DesktopVirtualization -Force -AllowClobber
    }

    # Clear existing azure context
    Clear-AzContext -Force

    # Connect to relevant azure account and set subscription id
    Connect-AzAccount -AccessToken $accessToken -AccountId $emailId
    Set-AzContext -SubscriptionId $subscriptionId

    # Get list of files available in file share
    $key = (Get-AzStorageAccountKey -ResourceGroupName $resourceGroupName -Name $storageAccountName)[0].Value
    $context = New-AzStorageContext -StorageAccountName $storageAccountName -StorageAccountKey $key
    $files = (Get-AzStorageFile -ShareName $fileshareName -Context $context).Name

    # Compare against output file name
    if($packageName -in $files){
        Write-Output $fileExistsInFileShare
    }
    else{
        Write-Output $fileDoesNotExistInFileShare
    }
}

catch {
    Write-Error "Error Occurred:"
    Write-Error $_
}
