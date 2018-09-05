:: Resrvoir Gods GODLIB.SPL builder
::
:: Build all samples using fastbuild
::
:: We create a common base drive (X:) to allow fastbuild cache to be shared between projects

@echo off

setlocal

pushd ..

set mypath=%cd%

subst X: %mypath%

pushd X:

cd GODLIB.SPL

CALL :buildIt BOX %*
CALL :buildIt CLI %*
CALL :buildIt COOKIJAR %*
CALL :buildIt JAGPAD %*
CALL :buildIt JOY %*
CALL :buildIt MOUSE %*
CALL :buildIt MUSIC %*
CALL :buildIt PICSHOW %*
CALL :buildIt SCREEN %*
CALL :buildIt SCRNSWAP %*
CALL :buildIt SPRITE %*

popd

subst X: /D

popd

endlocal

exit /B 0

:buildIt

pushd "%~1\FAST" 
shift
for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b
call build.bat %ALL_BUT_FIRST%
popd

exit /B 0