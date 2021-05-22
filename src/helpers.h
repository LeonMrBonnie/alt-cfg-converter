#pragma once
#include <fstream>
#include <string>
#include <sstream>

namespace Helpers
{
    static std::string ReadFile(std::string path)
    {
        // Open the file and check if it was opened successfully
        std::ifstream file(path);
        if(!file.good() || !file.is_open())
        {
            file.close();
            return std::string();
        }

        // Read the file
        std::stringstream buffer;
        buffer << file.rdbuf();

        file.close();
        return buffer.str();
    }
    static bool WriteFile(std::string path, std::string& content)
    {
        // Open the file and check if it was opened successfully
        std::ofstream file(path);
        if(!file.good() || !file.is_open())
        {
            file.close();
            return false;
        }

        // Write to the file
        file.write(content.c_str(), content.size());

        file.close();
        return true;
    }
    static std::string GetFileName(std::string file)
    {
        return file.substr(0, file.find_last_of("."));
    }
    static std::string GetFileExtension(std::string file)
    {
        return file.substr(file.find_last_of(".") + 1);
    }
}  // namespace Helpers
