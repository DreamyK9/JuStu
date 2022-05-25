@echo off
set "cmd=%~1"
set "params=%~2"

if "%cmd%"=="" (
	echo "status" executes a command and prints its exit code to the console
	echo Usage: status ^<command^> "[command parameters]"
	echo.
	goto :eof
) else (
	start %cmd% "%params%"
	echo.   Command "%cmd%" exited with Exit Code %errorLevel%
	)
