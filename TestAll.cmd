@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\TestAll.ps1 %*

exit /b %ERRORLEVEL%