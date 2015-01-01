@echo off

REM errors.txt is where the output errors from the compiler get stored
REM so that cim can ream them later
REM

set debugBuildOptions = "-Od -Oi"
set releaseBuildOptions = "-Ox -Zo"

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl %debugBuildOptions% -MT -nologo -EHsc -Z7 ..\source\launch.cpp
rem for outputing errors to a file 2> CompilationErrors.txt
popd
