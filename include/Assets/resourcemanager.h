#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <SFML/Graphics/Font.hpp>


namespace Assets
{
    class ResourceManager
    {
    public:
        ResourceManager();
        ~ResourceManager();
        bool setResourceDirectory( std::string path );
        sf::Font &getMainFont();
        void setMainFont( std::string fontName );

    protected:

    private:
        bool isMainFontLoaded{false};
        std::string resourcesDirectory;
        std::string mainFontName;
        sf::Font mainFont;
    };
}
#endif // RESOURCEMANAGER_H
