@echo off
echo Creating GNU project!
pushd %~dp0\..\..\
call dependencies\premake\premake5.exe gmake2
popd
pause