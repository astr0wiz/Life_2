#ifndef GAME_H
#define GAME_H

#include <string>
#include "Life/utils.h"
#include <SFML/Window.hpp>
namespace Life
{
    class Game
    {
    public:
        Game();
        virtual ~Game();

    public:
        bool isLoaded{false};
        void setDimensions(sf::Vector2u dimensions);

    protected:

    private:
        std::string saveFileName;
        std::string description;
        sf::Vector2u mapDimensions;
    };

}

#endif // GAME_H
