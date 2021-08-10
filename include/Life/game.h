#ifndef GAME_H
#define GAME_H

#include <string>
#include "Life/utils.h"
namespace Life
{
    class Game
    {
    public:
        Game(Utils utilities);
        virtual ~Game();

    public:
        bool isLoaded{false};

    protected:

    private:
        std::string saveFileName;
    };

}

#endif // GAME_H
