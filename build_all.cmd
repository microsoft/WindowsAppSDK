if not exist ".\.nuget" mkdir ".\.nuget"
if not exist ".\.nuget\nuget.exe" powershell -Command "Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile .\.nuget\nuget.exe"

call .nuget\nuget.exe restore WindowsAppRuntime.sln -configfile nuget.config

call :dobuild release x86
call :dobuild release arm
call :dobuild release arm64
call :dobuild release x64
call :dobuild debug x86
call :dobuild debug arm
call :dobuild debug arm64
call :dobuild debug x64
goto :eof

:dobuild
call msbuild /m /p:Configuration=%1,Platform=%2 WindowsAppRuntime.sln
goto :eof
