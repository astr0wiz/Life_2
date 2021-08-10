#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <SFML/Graphics/Font.hpp>
#include "Life/utils.h"


namespace Assets
{
    class ResourceManager
    {
    public:
        ResourceManager();
        ~ResourceManager();
        sf::Font& getMainFont();
        void setMainFont( std::string fontName );
        void init( std::shared_ptr<Life::Utils> utilities );
        std::string getResourcePath(std::string resourceName);

    protected:

    private:
        bool isMainFontLoaded{false};
        std::string resourcesDirectory;
        std::string mainFontName;
        sf::Font mainFont;
        std::shared_ptr<Life::Utils> utils;
    };
}
#endif // RESOURCEMANAGER_H
