@echo off
SETLOCAL

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile %~dpn0.ps1 %*

ENDLOCAL
