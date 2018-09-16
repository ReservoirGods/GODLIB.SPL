setlocal
set proj=%1

shift
set params=%1
:loop
shift
if [%1]==[] goto afterloop
set params=%params% %1
goto loop
:afterloop

..\..\..\TOOLS.RG\FASTBUILD\Windows-x64-v0.96-RG\FBuild.exe -cache sln %proj%-Debug %params%
endlocal