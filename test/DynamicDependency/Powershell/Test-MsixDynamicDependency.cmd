@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\Test-MsixDynamicDependency.Tests.ps1 %*

exit /b %ERRORLEVEL%
