@echo off

set debugBuildOptions = "-Od -Oi"
set releaseBuildOptions = "-Ox -Zo"

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl %releaseBuildOptions% -W4 -fp:fast -MTd -nologo -EHsc -Z7 -Gm- -GR- -EHa- ..\source\launch.cpp /link -incremental:no -opt:ref
popd

