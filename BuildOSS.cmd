@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\BuildOSS.ps1 %*

exit /b %ERRORLEVEL%
