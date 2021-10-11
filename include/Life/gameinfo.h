#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <string>
#include <SFML/Window.hpp>

namespace Life
{
    class GameInfo
    {
    public:
        GameInfo();
        virtual ~GameInfo();
        void setName( std::string name );
        void setFilename( std::string filename );
        void setDimensions( sf::Vector2u dimensions );
        // -------------
        std::string getName();
        std::string getFilename();
        sf::Vector2u getDimensions();
        uint64_t getMapSize();

    private:
        std::string _name;
        std::string _filename;
        sf::Vector2u _dimensions;
    };

}

#endif // GAMEINFO_H
