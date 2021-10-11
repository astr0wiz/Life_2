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

    void Game::setInfo( GameInfo gameInfo )
    {
        info = gameInfo;
        map.reserve( info.getMapSize() );
    }

    void Game::setAllDead()
    {
        for(unsigned int i = 0; i < map.size(); i++)
        {
            map[i] = 0;
        }
    }

}
