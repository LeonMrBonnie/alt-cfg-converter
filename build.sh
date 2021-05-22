mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
cd ..

if [ ! -d "./dist" ]; then
    mkdir dist
fi

cp build/linux64/Release/json-to-alt-cfg.exe dist
#cp build/linux64/Release/json-to-alt-cfg.pdb dist