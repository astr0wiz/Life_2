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
#include "constants.h"
#include "mainlogger.h"
#include <sstream>
#include <SFML/Window.hpp>

namespace Life
{
    class Utils
    {
    public:
        Utils();
        virtual ~Utils();
        std::string getExePath();
        std::string getNextSaveFileName( std::string baseName );
        std::string getResourceDirectory();
        std::string getResourcePath(std::string resourceName);
        std::string getSaveGameDirectory();
        std::string getSaveGamePath(std::string saveGameName);
        std::string getKeyNameFromCode(sf::Keyboard::Key key);

    private:
        std::string getValueFromIni( std::string section, const char* key );
        void setValueToIni( std::string section, std::string key, std::string value );
        void saveIniFile();

    private:
        CSimpleIniA ini;
        bool iniFileLoaded{true};
        bool setCachedDirectory( std::string path, const char* iniTag );
        std::filesystem::path currentDirectory;
    };

}

#endif // UTILS_H
