robocopy %HELIX_CORRELATION_PAYLOAD% . /s

::This script file is what runs on the helix machine to start our tests.
te BaseUnitTests.dll /unicodeOutput:false /enableWttLogging /screenCaptureOnError /reportLoadingIssue
set _helixExitCode=%ERRORLEVEL%

dir
dir WexLogFileOutput
copy /y WexLogFileOutput\*.jpg %HELIX_WORKITEM_UPLOAD_ROOT%

type te.wtl

powershell -ExecutionPolicy Bypass .\ConvertWttLogToXUnit.ps1 te.wtl testResults.xml %testnameprefix% %helixworkitem%
type testResults.xml

::Ensure the exit code for running our tests is the exit code reported back to AzDO
exit %_helixExitCode%