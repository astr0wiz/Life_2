#ifndef UTILS_H
#define UTILS_H
#define SI_CONVERT_GENERIC

#include "limits.h"
#include <unistd.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include "SimpleIni.h"
namespace Life
{
    class Utils
    {
    public:
        Utils();
        virtual ~Utils();
        std::string getNextSaveFileName( std::string baseName );
        std::string getResourceDirectory();
        std::string getResourcePath(std::string resourceName);

    private:
        std::string getValueFromIni( std::string section, std::string key );
        void setValueToIni( std::string section, std::string key, std::string value );
        void saveIniFile();

    private:
        CSimpleIniA ini;
        bool iniFileLoaded{true};
        bool setResourceDirectory( std::string path );
        std::filesystem::path currentDirectory;
    };

}

#endif // UTILS_H
