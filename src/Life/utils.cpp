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
                logger.Log( "EPIC FAIL!!!  Cannot get current directory!" );
            }
            std::filesystem::path p{std::string( pBuf,  bytes > 0  ? bytes : 0 )};
            currentDirectory =  p.parent_path();
        }
        return currentDirectory;
    }

    std::string Utils::getKeyNameFromCode( sf::Keyboard::Key key )
    {
        switch( key )
        {
            case sf::Keyboard::Key::A:
                return "A";
                break;
            case sf::Keyboard::Key::B:
                return "B";
                break;
            case sf::Keyboard::Key::C:
                return "C";
                break;
            case sf::Keyboard::Key::D:
                return "D";
                break;
            case sf::Keyboard::Key::E:
                return "E";
                break;
            case sf::Keyboard::Key::F:
                return "F";
                break;
            case sf::Keyboard::Key::G:
                return "G";
                break;
            case sf::Keyboard::Key::H:
                return "H";
                break;
            case sf::Keyboard::Key::I:
                return "I";
                break;
            case sf::Keyboard::Key::J:
                return "J";
                break;
            case sf::Keyboard::Key::K:
                return "K";
                break;
            case sf::Keyboard::Key::L:
                return "L";
                break;
            case sf::Keyboard::Key::M:
                return "M";
                break;
            case sf::Keyboard::Key::N:
                return "N";
                break;
            case sf::Keyboard::Key::O:
                return "O";
                break;
            case sf::Keyboard::Key::P:
                return "P";
                break;
            case sf::Keyboard::Key::Q:
                return "Q";
                break;
            case sf::Keyboard::Key::R:
                return "R";
                break;
            case sf::Keyboard::Key::S:
                return "S";
                break;
            case sf::Keyboard::Key::T:
                return "T";
                break;
            case sf::Keyboard::Key::U:
                return "U";
                break;
            case sf::Keyboard::Key::V:
                return "V";
                break;
            case sf::Keyboard::Key::W:
                return "W";
                break;
            case sf::Keyboard::Key::X:
                return "X";
                break;
            case sf::Keyboard::Key::Y:
                return "Y";
                break;
            case sf::Keyboard::Key::Z:
                return "Z";
                break;
            case sf::Keyboard::Key::Num0:
                return "Num0";
                break;
            case sf::Keyboard::Key::Num1:
                return "Num1";
                break;
            case sf::Keyboard::Key::Num2:
                return "Num2";
                break;
            case sf::Keyboard::Key::Num3:
                return "Num3";
                break;
            case sf::Keyboard::Key::Num4:
                return "Num4";
                break;
            case sf::Keyboard::Key::Num5:
                return "Num5";
                break;
            case sf::Keyboard::Key::Num6:
                return "Num6";
                break;
            case sf::Keyboard::Key::Num7:
                return "Num7";
                break;
            case sf::Keyboard::Key::Num8:
                return "Num8";
                break;
            case sf::Keyboard::Key::Num9:
                return "Num9";
                break;
            case sf::Keyboard::Key::Escape:
                return "Escape";
                break;
            case sf::Keyboard::Key::LControl:
                return "LControl";
                break;
            case sf::Keyboard::Key::LShift:
                return "LShift";
                break;
            case sf::Keyboard::Key::LAlt:
                return "LAlt";
                break;
            case sf::Keyboard::Key::LSystem:
                return "LSystem";
                break;
            case sf::Keyboard::Key::RControl:
                return "RControl";
                break;
            case sf::Keyboard::Key::RShift:
                return "RShift";
                break;
            case sf::Keyboard::Key::RAlt:
                return "RAlt";
                break;
            case sf::Keyboard::Key::RSystem:
                return "RSystem";
                break;
            case sf::Keyboard::Key::Menu:
                return "Menu";
                break;
            case sf::Keyboard::Key::LBracket:
                return "LBracket";
                break;
            case sf::Keyboard::Key::RBracket:
                return "RBracket";
                break;
            case sf::Keyboard::Key::Semicolon:
                return "Semicolon";
                break;
            case sf::Keyboard::Key::Comma:
                return "Comma";
                break;
            case sf::Keyboard::Key::Period:
                return "Period";
                break;
            case sf::Keyboard::Key::Quote:
                return "Quote";
                break;
            case sf::Keyboard::Key::Slash:
                return "Slash";
                break;
            case sf::Keyboard::Key::Backslash:
                return "Backslash";
                break;
            case sf::Keyboard::Key::Tilde:
                return "Tilde";
                break;
            case sf::Keyboard::Key::Equal:
                return "Equal";
                break;
            case sf::Keyboard::Key::Hyphen:
                return "Hyphen";
                break;
            case sf::Keyboard::Key::Space:
                return "Space";
                break;
            case sf::Keyboard::Key::Enter:
                return "Enter";
                break;
            case sf::Keyboard::Key::Backspace:
                return "Backspace";
                break;
            case sf::Keyboard::Key::Tab:
                return "Tab";
                break;
            case sf::Keyboard::Key::PageUp:
                return "PageUp";
                break;
            case sf::Keyboard::Key::PageDown:
                return "PageDown";
                break;
            case sf::Keyboard::Key::End:
                return "End";
                break;
            case sf::Keyboard::Key::Home:
                return "Home";
                break;
            case sf::Keyboard::Key::Insert:
                return "Insert";
                break;
            case sf::Keyboard::Key::Delete:
                return "Delete";
                break;
            case sf::Keyboard::Key::Add:
                return "Add";
                break;
            case sf::Keyboard::Key::Subtract:
                return "Subtract";
                break;
            case sf::Keyboard::Key::Multiply:
                return "Multiply";
                break;
            case sf::Keyboard::Key::Divide:
                return "Divide";
                break;
            case sf::Keyboard::Key::Left:
                return "Left";
                break;
            case sf::Keyboard::Key::Right:
                return "Right";
                break;
            case sf::Keyboard::Key::Up:
                return "Up";
                break;
            case sf::Keyboard::Key::Down:
                return "Down";
                break;
            case sf::Keyboard::Key::Numpad0:
                return "Numpad0";
                break;
            case sf::Keyboard::Key::Numpad1:
                return "Numpad1";
                break;
            case sf::Keyboard::Key::Numpad2:
                return "Numpad2";
                break;
            case sf::Keyboard::Key::Numpad3:
                return "Numpad3";
                break;
            case sf::Keyboard::Key::Numpad4:
                return "Numpad4";
                break;
            case sf::Keyboard::Key::Numpad5:
                return "Numpad5";
                break;
            case sf::Keyboard::Key::Numpad6:
                return "Numpad6";
                break;
            case sf::Keyboard::Key::Numpad7:
                return "Numpad7";
                break;
            case sf::Keyboard::Key::Numpad8:
                return "Numpad8";
                break;
            case sf::Keyboard::Key::Numpad9:
                return "Numpad9";
                break;
            case sf::Keyboard::Key::F1:
                return "F1";
                break;
            case sf::Keyboard::Key::F2:
                return "F2";
                break;
            case sf::Keyboard::Key::F3:
                return "F3";
                break;
            case sf::Keyboard::Key::F4:
                return "F4";
                break;
            case sf::Keyboard::Key::F5:
                return "F5";
                break;
            case sf::Keyboard::Key::F6:
                return "F6";
                break;
            case sf::Keyboard::Key::F7:
                return "F7";
                break;
            case sf::Keyboard::Key::F8:
                return "F8";
                break;
            case sf::Keyboard::Key::F9:
                return "F9";
                break;
            case sf::Keyboard::Key::F10:
                return "F10";
                break;
            case sf::Keyboard::Key::F11:
                return "F11";
                break;
            case sf::Keyboard::Key::F12:
                return "F12";
                break;
            case sf::Keyboard::Key::F13:
                return "F13";
                break;
            case sf::Keyboard::Key::F14:
                return "F14";
                break;
            case sf::Keyboard::Key::F15:
                return "F15";
                break;
            case sf::Keyboard::Key::Pause:
                return "Pause";
                break;
            default:
                return "UNKNOWN";
                break;
        }
    }
}
