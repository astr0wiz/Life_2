#ifndef GAME_H
#define GAME_H

#include <string>
#include "Life/utils.h"
#include "Life/gameinfo.h"
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
        void setInfo(GameInfo gameInfo);
        void setAllDead();

    protected:

    private:
        std::string description;
        std::vector<uint32_t> map;
        GameInfo info;
    };

}

#endif // GAME_H
