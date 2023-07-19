@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile -File %~dp0\eng\common\DevCheck.ps1 %*

exit /b %ERRORLEVEL%
