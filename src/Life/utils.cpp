#include "utils.h"

namespace Life
{
    Utils::Utils()
    {
        MainLogger& logger = MainLogger::Instance();
        std::ostringstream os;

        iniFileLoaded = true;
        std::filesystem::path currDir = getExePath();
        currDir  /= "Life.ini";
        os << "INI file is here: " << currDir;
        logger.Log( os.str() );
        SI_Error rc = ini.LoadFile( currDir.c_str() );
        if ( rc < 0 )
        {
            logger.Log( "Ini file not found.  Creating new file." );
            const std::string initialFile = "[General]\nVersion = 0.2\n";
            rc = ini.LoadData( initialFile );
            if ( rc < 0 )
            {
                logger.Log( "Epic Error!!!  Cannot load initial values!" );
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
            MainLogger& logger = MainLogger::Instance();
            std::ostringstream os;
            std::string path = ".";
            std::string resourcesDirectory;
            struct stat info;
            if( stat( path.c_str(), &info ) != 0 )
            {
                os << "ERROR!  Cannot access game directory '" << path << "'";
            }
            else if( !( info.st_mode & S_IFDIR ) )
            {
                os << "ERROR!  " << path << " is not a directory";
            }
            else
            {
                std::filesystem::path currDir = currentDirectory;
                currDir  /= "Life.ini";
                ini.SaveFile( currDir.c_str() );
            }
            if( os.tellp() > 0 )
            {
                logger.Log( os.str() );
            }
        }
    }

    std::string Utils::getValueFromIni( std::string section, const char* key )
    {
        if( iniFileLoaded )
        {
            return ini.GetValue( section.c_str(), key, "" );
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

//{========== Resource Directory ===================================

    std::string Utils::getResourceDirectory( )
    {
        std::string rdir = getValueFromIni( "File", COMMON::INITAG_RESOURCEDIR.data() );
        if ( rdir == "" )
        {
            if( setCachedDirectory( "resources", COMMON::INITAG_RESOURCEDIR.data() ) )
            {
                rdir = getValueFromIni( "File", COMMON::INITAG_RESOURCEDIR.data() );
            }
        }
        std::filesystem::path currDir = currentDirectory;
        currDir  /= rdir;
        return currDir;
    }

    std::string Utils::getResourcePath( std::string resourceName )
    {
        std::filesystem::path rdir{getResourceDirectory()};
        return rdir /= resourceName;
    }

//}


//{========== Save Games Directory =================================

    std::string Utils::getSaveGameDirectory()
    {
        std::string rdir = getValueFromIni( "File", COMMON::INITAG_SAVEGAMEDIR.data() );
        if ( rdir == "" )
        {
            if( setCachedDirectory( "saved", COMMON::INITAG_SAVEGAMEDIR.data() ) )
            {
                rdir = getValueFromIni( "File", COMMON::INITAG_SAVEGAMEDIR.data() );
            }
        }
        std::filesystem::path currDir = currentDirectory;
        currDir  /= rdir;
        return currDir;
    }

    std::string Utils::getSaveGamePath( std::string saveGameName )
    {
        std::filesystem::path rdir{getSaveGameDirectory()};
        return rdir /= saveGameName;
    }

//}

    bool Utils::setCachedDirectory( std::string path, const char* iniTag )
    {
        MainLogger& logger = MainLogger::Instance();
        std::ostringstream os;
        std::filesystem::path currDir = currentDirectory;
        currDir  /= path;
        struct stat info;
        if( stat( currDir.c_str(), &info ) != 0 )
        {
            os << "ERROR!  setCachedDirectory: Cannot access directory '" << currDir << "'";
            logger.Log( os.str() );
            return false;
        }
        else if( !( info.st_mode & S_IFDIR ) )
        {
            os << "ERROR!  setCachedDirectory: '" << currDir << "' is not a directory";
            logger.Log( os.str() );
            return false;
        }
        setValueToIni( "File", iniTag, path );
        saveIniFile();
        return true;
    }

    std::string Utils::getExePath()
    {
        if( currentDirectory.empty() )
        {
            MainLogger& logger = MainLogger::Instance();
            char pBuf[PATH_MAX];
            int bytes = readlink( "/proc/self/exe", pBuf, PATH_MAX );
            if( bytes >= 0 )
            {
                pBuf[bytes] = '\0';
            }
            else
            {
                logger.Log("EPIC FAIL!!!  Cannot get current directory!");
            }
            std::filesystem::path p{std::string( pBuf,  bytes > 0  ? bytes : 0 )};
            currentDirectory =  p.parent_path();
        }
        return currentDirectory;
    }

}
