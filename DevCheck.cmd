@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\DevCheck.ps1 %*

exit /b %ERRORLEVEL%