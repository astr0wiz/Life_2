#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "pubsub.h"
#include "gamebar.h"
#include "Assets/resourcemanager.h"
#include "Scenes/menuscene.h"
#include <TGUI/TGUI.hpp>
#include "Life/utils.h"

namespace Life
{
    static constexpr char gameTitle[] = "Life 0.2";

    class GameWindow : public EventPublisher
    {
    public:
        GameWindow( std::shared_ptr<Assets::ResourceManager> resourceManager );
        virtual ~GameWindow();
        void setupBaseWindow();
        void setupTgui();
        void setupGameBar( std::shared_ptr<Assets::ResourceManager> resourceManager );
        void setupBackground();
        void setupScenes( std::shared_ptr<Assets::ResourceManager> resourceManager );
        sf::Vector2f getBaseWindowSize()
        {
            return baseWinSize;
        }
        void run();
        void AddScene(std::shared_ptr<Scenes::Scene> scene);

    public:
        tgui::GuiSFML gui;

    protected:

    private:
        sf::RenderWindow window;
        sf::RectangleShape backdrop;
        sf::Vector2f baseWinSize{0., 0.};
        std::shared_ptr<Gamebar> gamebar;
        std::shared_ptr<Assets::ResourceManager> resourceMgr;
        std::map<std::string, std::shared_ptr<Scenes::Scene>> scenes;
    };
}
#endif // GAMEWINDOW_H
