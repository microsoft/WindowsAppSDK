@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\tools\RunTests.ps1 %*

exit /b %ERRORLEVEL%
