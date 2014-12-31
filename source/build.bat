@echo off

REM errors.txt is where the output errors from the compiler get stored
REM so that cim can ream them later
REM
REM DEBUG BUILD  -Od -Oi
REM RELEASE BUILD -Ox

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl -MT -nologo -Ox -EHsc -Z7 ..\source\launch.cpp
rem for outputing errors to a file 2> CompilationErrors.txt
popd
