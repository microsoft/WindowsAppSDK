@echo off

powershell -ExecutionPolicy Unrestricted -NoLogo -NoProfile %~dpn0.ps1 %*
