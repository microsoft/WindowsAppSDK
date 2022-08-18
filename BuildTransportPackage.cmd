@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\BuildTransportPackage.ps1 %*

exit /b %ERRORLEVEL%