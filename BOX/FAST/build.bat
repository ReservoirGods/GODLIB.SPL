@echo off
for %%a in ("%~dp0\..") do set "project=%%~nxa"
..\..\..\TOOLS.RG\FASTBUILD\Windows-x64-v0.96-RG\FBuild.exe sln %project%-Debug %*