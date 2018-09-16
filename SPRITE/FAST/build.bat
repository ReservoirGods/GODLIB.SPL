@echo off
for %%a in ("%~dp0\..") do set "project=%%~nxa"
..\..\onebuild.bat %project% %*