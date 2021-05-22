# Alt Config Converter

A C++ commandline utility to convert alt-config files to JSON and JSON files to alt-config files.

## Usage

Compile the executable yourself using the instructions [down below](#build), or download the newest version from the `Releases`. <br>
Just run the compiled executable with one or two commandline arguments. <br>
The first argument is the path to the input file, the second argument is the path to the output file. <br>
The second argument is optional, if not provided it will place it right next to the input file with the extension of the output format.

`alt-cfg-converter [Input File] [?Output File]`

## Build

To build simply clone the repo, pull the submodules and run the `build.bat` or `build.sh` build script. <br>
The output executable can then be found in the `dist` directory.
