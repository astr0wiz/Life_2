#include "game.h"

namespace Life
{
    Game::Game()
    {
//        saveFileName= utilities.getNextSaveFileName("LifeSaveGame");
//        description = "New Game";
//        mapDimensions = dimensions;
    }

    Game::~Game()
    {
        //dtor
    }

    void Game::setDimensions(sf::Vector2u dimensions)
    {
        mapDimensions = dimensions;
    }

}
