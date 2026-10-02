@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\AddProject.ps1 %*

exit /b %ERRORLEVEL%
