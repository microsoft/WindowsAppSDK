REM execute this script from the root directory of WindowAppSDK repository

@echo off

REM Step 1: Rename the .nupkg file to .zip
ren "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.nupkg" "Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip"

REM Step 2: Clear content in the target directory
rd /s /q "..\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1"
md "..\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1"

REM Step 3: Extract contents of the .zip file into the target directory
powershell -command "Expand-Archive -Path 'BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip' -DestinationPath '..\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1' -Force"

echo Done