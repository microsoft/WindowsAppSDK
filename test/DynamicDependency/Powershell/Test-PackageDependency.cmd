@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\Test-PackageDependency.Tests.ps1 %*

exit /b %ERRORLEVEL%
