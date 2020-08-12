@ECHO OFF
SETLOCAL

SET SolutionDir=%1
SET ProjectDir=%2
SET OutDir=%3
SET TargetDir=%4
SET TargetFileName=%5
SET TargetName=%6

SET OutDirMsix=%OutDir%msix\
SET OutMsix=%OutDir%%TargetName%.msix

ECHO rd %OutDirMsix% /s /q
rd %OutDirMsix% /s /q

ECHO md %OutDirMsix%
md %OutDirMsix%

ECHO copy %ProjectDir%appxmanifest.template %OutDirMsix%appxmanifest.xml
copy %ProjectDir%appxmanifest.template %OutDirMsix%appxmanifest.xml

IF NOT EXIST %ProjectDir%logo.png GOTO SkipLogo
ECHO copy %ProjectDir%logo.png %OutDirMsix%logo.png
copy %ProjectDir%logo.png %OutDirMsix%logo.png
:SkipLogo

IF NOT EXIST %ProjectDir%Assets GOTO SkipAssets
ECHO MD %OutDirMsix%Assets
MD %OutDirMsix%Assets
ECHO copy %ProjectDir%Assets\* %OutDirMsix%Assets\*
copy %ProjectDir%Assets\* %OutDirMsix%Assets\*
:SkipAssets

ECHO copy %TargetDir%%TargetFileName% %OutDirMsix%%TargetFileName%
copy %TargetDir%%TargetFileName% %OutDirMsix%%TargetFileName%

ECHO makeappx.exe pack /v /h SHA256 /d %OutDirMsix% /p %OutMsix%
makeappx.exe pack /v /o /h SHA256 /d %OutDirMsix% /p %OutMsix%

REM REM This would be
REM REM See https://osgwiki.com/wiki/Package_ES_Appx_Bundle#Code_sign_Appx_Bundle for details re SignCert
REM SET SignCert=136020001
REM SET SignPublisher=CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US
REM SET SignFile=%OutMsix%
REM SimpleSign.exe -i:%SignFile% -c:%SignCert% -s:"%SignPublisher%"
ECHO signtool.exe sign /a /v /fd SHA256 /f %ProjectDir%build\MSTest.pfx %OutMsix%
signtool.exe sign /a /v /fd SHA256 /f %SolutionDir%build\MSTest.pfx %OutMsix%

:TheEnd
ENDLOCAL

EXIT /B 0
