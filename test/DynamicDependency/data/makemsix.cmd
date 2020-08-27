@ECHO OFF
SETLOCAL

SET ProjectDir=%1
SET OutDir=%2
SET TargetDir=%3
SET TargetFileName=%4
SET TargetName=%5

SET OutDirMsix=%OutDir%\msix

ECHO rd %OutDirMsix% /s /q
rd %OutDirMsix% /s /q

ECHO md %OutDirMsix%
md %OutDirMsix%

ECHO copy %ProjectDir%appxmanifest.template %OutDirMsix%\appxmanifest.xml
copy %ProjectDir%appxmanifest.template %OutDirMsix%\appxmanifest.xml

ECHO copy %ProjectDir%logo.png %OutDirMsix%\logo.png
copy %ProjectDir%logo.png %OutDirMsix%\logo.png

ECHO copy %TargetDir%\%TargetFileName% %OutDirMsix%\%TargetFileName%
copy %TargetDir%\%TargetFileName% %OutDirMsix%\%TargetFileName%

ECHO makeappx.exe pack /v /h SHA256 /d %OutDirMsix% /p %OutDir%%TargetName%.msix
makeappx.exe pack /v /h SHA256 /d %OutDirMsix% /p %OutDir%%TargetName%.msix

:TheEnd
ENDLOCAL

ECHO /B 0
