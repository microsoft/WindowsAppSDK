@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\Test-PackageDependency.ps1 %*

exit /b %ERRORLEVEL%
