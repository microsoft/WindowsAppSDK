@echo off
SETLOCAL

IF /I "%1" == "-help" GOTO Help
IF /I "%1" == "--help" GOTO Help

powershell %~dpn0.ps1 %*
GOTO TheEnd

:Help
powershell -c Get-Help %~dpn0.ps1 -full

:TheEnd
ENDLOCAL
