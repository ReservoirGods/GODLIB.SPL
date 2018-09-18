:: Resrvoir Gods GODLIB.SPL builder
::
:: Build all samples using fastbuild
::
:: We create a common base drive (X:) to allow fastbuild cache to be shared between projects

@echo off
::setlocal

::pushd ..
::set mypath=%cd%
::subst X: %mypath%
::pushd X:
::cd GODLIB.SPL

for /D %%i in (*) do (
	if exist "%%i\FAST" (
		pushd "%%i\FAST"
		call build.bat %*
		popd
	)
)

::popd
::subst X: /D
::popd

::endlocal
