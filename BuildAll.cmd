@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\BuildAll.ps1 %*

exit /b %ERRORLEVEL%