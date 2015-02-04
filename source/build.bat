@echo off

set debugBuildOptions = "-Od -Oi"
set releaseBuildOptions = "-Ox -Zo"

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl %releaseBuildOptions% -W4 -MT -nologo -EHsc -Z7 ..\source\launch.cpp
popd

