#include <iostream>
#include "./helpers.h"
#include "./converter.h"

int main(int argc, char** argv)
{
    if(argc < 2 || argc > 3)
    {
        std::cout << "Usage: alt-cfg-converter [Input File] [?Output File]" << std::endl;
        return 0;
    }

    // Read file information
    auto file      = argv[1];
    auto name      = Helpers::GetFileName(file);
    auto extension = Helpers::GetFileExtension(file);
    auto content   = Helpers::ReadFile(file);
    std::cout << "Converting '" << file << "' (Type: " << extension << ")" << std::endl;

    // Determine file type
    std::string output;
    std::string outputType;
    if(extension == "json")
    {
        output     = Converter::JsonToCfg(content);
        outputType = "cfg";
    }
    else if(extension == "cfg")
    {
        output     = Converter::CfgToJson(content);
        outputType = "json";
    }

    if(output.empty())
    {
        std::cerr << "Failed to convert file" << std::endl;
        return 0;
    }

    // Write converted file to output
    std::string outputFile;
    if(argc == 3) outputFile = argv[2];
    else
        outputFile = name + "." + outputType;

    Helpers::WriteFile(outputFile, output);
    std::cout << "Wrote output to '" << outputFile << "'" << std::endl;
}
