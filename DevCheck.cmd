@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\tools\DevCheck\DevCheck.ps1 %*

exit /b %ERRORLEVEL%
