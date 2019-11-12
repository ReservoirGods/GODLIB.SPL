:: Resrvoir Gods GODLIB.SPL builder
::
:: Build all samples using fastbuild
::
:: We create a common base drive (X:) to allow fastbuild cache to be shared between projects

@echo off

for /D %%i in (*) do (
	if exist "%%i\FAST\OUT" (
		rmdir /S /Q "%%i\FAST\OUT"
	)
	if exist "%%i\OUT" (
		rmdir /S /Q "%%i\OUT"
	)	
)

