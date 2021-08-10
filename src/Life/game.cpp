#include "game.h"

namespace Life
{
    Game::Game(Utils utilities)
    {
        saveFileName= utilities.getNextSaveFileName("LifeSaveGame");
    }

    Game::~Game()
    {
        //dtor
    }

}
