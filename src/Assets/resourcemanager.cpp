#include "Assets/resourcemanager.h"

namespace Assets
{
    ResourceManager::ResourceManager() {}

    ResourceManager::~ResourceManager() {}

    void ResourceManager::init( std::shared_ptr<Life::Utils> utilities )
    {
        utils = utilities;
        resourcesDirectory = utils->getResourceDirectory();
    }

    void ResourceManager::setMainFont( std::string fontName )
    {
        // Would like to have an array of fonts with some way to determine
        // the fonts from each other.
        std::cout << "Setting main font to " << fontName << std::endl;
        mainFontName = fontName;
    }

    sf::Font& ResourceManager::getMainFont()
    {
        std::cout << "isMainFontLoaded? " << ( isMainFontLoaded ? "true" : "false" ) << std::endl;
        if( !isMainFontLoaded )
        {
            std::string mainFontPath=utils->getResourcePath("fonts/" + mainFontName);
            std::cout << "Getting font from " << mainFontPath << std::endl;
            if( !mainFont.loadFromFile( mainFontPath ) )
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

    std::string ResourceManager::getResourcePath(std::string resourceName)
    {
        return utils->getResourcePath(resourceName);
    }
}
