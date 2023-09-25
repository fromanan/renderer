#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <libloaderapi.h>

class File
{
public:
    static std::string ReadFile(const std::string& filepath)
    {
        const std::ifstream fileStream(filepath);
        if (!fileStream.is_open())
        {
            const std::string message { "Failed to open file '" + filepath + "'!" };
            throw std::exception(message.c_str());
        }
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        return buffer.str();
    }

    static std::string GetRootPath()
    {
        #ifdef OS_WINDOWS
        char filename[MAX_PATH + 1];
        GetModuleFileNameA(nullptr, filename, MAX_PATH);
        return GetDirectory(filename);
        #elif OS_LINUX
        return std::filesystem::canonical("/proc/self/exe");
        #else
        return std::string();
        #endif
    }

    static std::string GetDirectory(const std::string& filepath)
    {
        size_t lastSlashIndex = filepath.find_last_of('\\');
        if (lastSlashIndex != std::string::npos)
            return filepath.substr(0, lastSlashIndex);
        
        lastSlashIndex = filepath.find_last_of('/');
        if (lastSlashIndex != std::string::npos)
            return filepath.substr(0, lastSlashIndex);

        return { };
    }
};