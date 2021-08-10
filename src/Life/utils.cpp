#include "utils.h"

namespace Life
{
    Utils::Utils()
    {
        char pBuf[PATH_MAX];
        int bytes = readlink( "/proc/self/exe", pBuf, PATH_MAX );
        if( bytes >= 0 )
        {
            pBuf[bytes] = '\0';
        }
        else
        {
            std::cout << "EPIC FAIL!!!  Cannot get current directory!" << std::endl;
        }
        std::filesystem::path p{std::string( pBuf,  bytes > 0  ? bytes : 0 )};
        currentDirectory =  p.parent_path();
        iniFileLoaded = true;
        std::filesystem::path currDir = currentDirectory;
        currDir  /= "Life.ini";
        std::cout << "INI file is here: " << currDir << std::endl;
        SI_Error rc = ini.LoadFile( currDir.c_str() );
        if ( rc < 0 )
        {
            std::cout << "Ini file not found.  Creating new file." << std::endl;
            const std::string initialFile = "[General]\nVersion = 0.2\n";
            rc = ini.LoadData( initialFile );
            if ( rc < 0 )
            {
                std::cout << "Epic Error!!!  Cannot load initial values!" << std::endl;
                iniFileLoaded = false;
            }
            else
            {
                saveIniFile();
            }
        };
    }

    Utils::~Utils()
    {
    }

    void Utils::saveIniFile()
    {
        if( iniFileLoaded )
        {
            std::string path = ".";
            std::string resourcesDirectory;
            struct stat info;
            if( stat( path.c_str(), &info ) != 0 )
            {
                std::cout << "ERROR!  Cannot access game directory '" << path << "'" << std::endl;
            }
            else if( !( info.st_mode & S_IFDIR ) )
            {
                std::cout << "ERROR!  " << path << " is not a directory" << std::endl;
            }
            else
            {
                std::filesystem::path currDir = currentDirectory;
                currDir  /= "Life.ini";
                ini.SaveFile( currDir.c_str() );
            }
        }
    }

    std::string Utils::getValueFromIni( std::string section, std::string key )
    {
        if( iniFileLoaded )
        {
            return ini.GetValue( section.c_str(), key.c_str(), "" );
        }
        return "";
    }

    void Utils::setValueToIni( std::string section, std::string key, std::string value )
    {
        if( iniFileLoaded )
        {
            ini.SetValue( section.c_str(), key.c_str(), value.c_str() );
        }
    }

    std::string Utils::getNextSaveFileName( std::string baseName )
    {
        return "";
    }

    std::string Utils::getResourceDirectory( )
    {
        std::string rdir = getValueFromIni( "File", "resourcedir" );
        if ( rdir == "" )
        {
            if( setResourceDirectory( "resources" ) )
            {
                rdir = getValueFromIni( "File", "resourcedir" );
            }
        }
        std::filesystem::path currDir = currentDirectory;
        currDir  /= rdir;
        return currDir;
    }

    bool Utils::setResourceDirectory( std::string path )
    {
        std::filesystem::path currDir = currentDirectory;
        currDir  /= path;
        struct stat info;
        if( stat( currDir.c_str(), &info ) != 0 )
        {
            std::cout << "ERROR!  Cannot access resource directory '" << currDir << "'" << std::endl;
            return false;
        }
        else if( !( info.st_mode & S_IFDIR ) )
        {
            std::cout << "ERROR!  " << currDir << " is not a directory" << std::endl;
            return false;
        }
        setValueToIni( "File", "resourcedir", path );
        saveIniFile();
        return true;
    }

    std::string Utils::getResourcePath( std::string resourceName )
    {
        std::filesystem::path rdir{getResourceDirectory()};
        return rdir /= resourceName;
    }

}
