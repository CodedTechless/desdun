@echo off
echo Creating Visual Studio 2022 project!
pushd %~dp0\..\..\
call dependencies\premake\premake5.exe vs2022
popd
pause