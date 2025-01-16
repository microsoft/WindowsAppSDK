REM execute this script from the root directory of WindowAppSDK repository

@echo off

copy "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.nupkg" "..\WindowsAppSDKAggregator\localpackages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.nupkg"

REM if exist, delete "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip"
if exist "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip" (
    del "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip"
)

REM Step 1: duplicate a .zip file from .nupkg
copy "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.nupkg" "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip"

REM Step 2: Clear content in the target directory
rd /s /q "..\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1"
md "..\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1"

REM Step 3: Extract contents of the .zip file into the target directory
powershell -command "Expand-Archive -Path 'BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip' -DestinationPath '..\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1' -Force"

echo Done