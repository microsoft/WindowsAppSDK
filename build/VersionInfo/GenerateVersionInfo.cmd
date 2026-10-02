@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\GenerateVersionInfo.ps1 %*

exit /b %ERRORLEVEL%
