rem @echo off

setlocal

CALL :buildIt BOX %*
CALL :buildIt CLI %*
CALL :buildIt COOKIJAR %*
CALL :buildIt JAGPAD %*
CALL :buildIt JOY %*
CALL :buildIt MOUSE %*
CALL :buildIt PICSHOW %*
CALL :buildIt SCREEN %*
CALL :buildIt SCRNSWAP %*
CALL :buildIt SPRITE %*

endlocal

exit /B 0

:buildIt

pushd "%~1\FAST" 
shift
for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b
call build.bat %ALL_BUT_FIRST%
popd

exit /B 0