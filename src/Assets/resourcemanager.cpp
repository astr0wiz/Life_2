#include "Assets/resourcemanager.h"

namespace Assets
{
    ResourceManager::ResourceManager() {}

    ResourceManager::~ResourceManager() {}

    bool ResourceManager::setResourceDirectory( std::string path )
    {
        struct stat info;
        if( stat( path.c_str(), &info ) != 0 )
        {
            std::cout << "ERROR!  Cannot access resource directory '" << path << std::endl;
            return false;
        }
        else if( info.st_mode & S_IFDIR )
        {
            resourcesDirectory = path;
        }
        else
        {
            std::cout << "ERROR!  " << path << " is not a directory" << std::endl;
            return false;
        }
        return true;
    }

    void ResourceManager::setMainFont( std::string fontName )
    {
        // Would like to have an array of fonts with some way to determine
        // the fonts from each other.
        std::cout << "Setting main font to " << fontName <<std::endl;
        mainFontName = fontName;
    }

    sf::Font& ResourceManager::getMainFont()
    {
        std::cout << "isMainFontLoaded? " << (isMainFontLoaded ? "true" : "false") << std::endl;
        if( !isMainFontLoaded )
        {
            std::cout << "Getting font from " << resourcesDirectory << "/fonts/" << mainFontName << std::endl;
            if( !mainFont.loadFromFile( resourcesDirectory + "/fonts/" + mainFontName ) )
            {
                std::cout << "ERROR!  Main font not loaded!!" << std::endl;
            }
            else
            {
                isMainFontLoaded = true;
            }
        }
        return mainFont;
    }
}
