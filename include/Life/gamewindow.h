#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "gamebar.h"
#include "Assets/resourcemanager.h"
#include "Scenes/menuscene.h"
#include <TGUI/TGUI.hpp>
#include "Life/utils.h"
#include "Life/game.h"
#include "Life/gameinfo.h"
#include "mainlogger.h"

namespace Life
{
    static constexpr char gameTitle[] = "Life 0.2";

    class GameWindow
    {
    public:
        GameWindow( std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utilities );
        virtual ~GameWindow();
        void setupBaseWindow();
        void setupTgui();
        void setupGameBar( std::shared_ptr<Assets::ResourceManager> resourceManager );
        void setupBackground();
        void setupScenes( std::shared_ptr<Assets::ResourceManager> resourceManager,std::shared_ptr<Life::Utils> utils );
        sf::Vector2f getBaseWindowSize()
        {
            return baseWinSize;
        }
        void run();
        void addScene(std::shared_ptr<Scenes::Scene> scene);
        void notifyEvent( sf::Event* what, std::shared_ptr<Scenes::Scene> subToSkip = 0 );
        void menuAction(COMMON::GameActions action, GameInfo gameInfo);
        void quitGame();
    public:
        tgui::GuiSFML gui;
        bool notifyEnabled{true};
        std::unique_ptr<Game> game;

    protected:

    private:
        sf::RenderWindow window;
        sf::RectangleShape backdrop;
        sf::Vector2f baseWinSize{0., 0.};
        std::shared_ptr<Gamebar> gamebar;
        std::shared_ptr<Assets::ResourceManager> resourceMgr;
        std::map<std::string, std::shared_ptr<Scenes::Scene>> scenes;
        std::shared_ptr<Life::Utils> utils;
    };
}
#endif // GAMEWINDOW_H
