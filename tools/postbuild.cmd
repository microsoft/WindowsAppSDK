@echo off

REM Step 1: Rename the .nupkg file to .zip
ren "C:\Users\xianghong\Documents\WindowsAppSDK\BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.nupkg" "Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip"

REM Step 2: Clear content in the target directory
rd /s /q "C:\Users\xianghong\Documents\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1"
md "C:\Users\xianghong\Documents\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1"

REM Step 3: Extract contents of the .zip file into the target directory
powershell -command "Expand-Archive -Path 'C:\Users\xianghong\Documents\WindowsAppSDK\BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1.zip' -DestinationPath 'C:\ado\WindowsAppSDKAggregator\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.1.1.1.1' -Force"

echo Done
