@echo off

IF NOT EXIST build\ (
    mkdir build
)
pushd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
popd

IF NOT EXIST dist\ (
    mkdir dist
)
copy build\win64\Release\alt-cfg-converter.exe dist
::copy build\win64\Release\alt-cfg-converter.pdb dist
