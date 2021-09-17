#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scenes/scene.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "Assets/Colors.h"
#include <iostream>

namespace Scenes
{
    enum class MenuButtons
    {
        Continue,
        Load,
        Save,
        Edit,
        Random,
        Credits,
        Quit
    };
    enum class RollDirections
    {
        Up,
        Down
    };
    class MenuScene : public Scene
    {
    public:
        MenuScene();
        virtual ~MenuScene();
        void show();
        void hide();
        void init( sf::Vector2f windowSize, tgui::GuiSFML* gui, std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utilities, std::function<void(COMMON::GameActions)> gameAction);
        bool isVisible();
        void updateEvent( void* who, sf::Event* what = 0 );
    public:
        tgui::Group::Ptr menuGroup;

    private:
        static constexpr float BB_WIDTH = 400.f;
        static constexpr float BB_HEIGHT = 600.f;
        sf::Font menuFont;
        sf::RectangleShape screen;
        sf::Text titleText;
        std::map<Scenes::MenuButtons,tgui::Button::Ptr> buttons;

    private:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
        void processButtonClick(MenuButtons selection);
        void rollButtonSelection(RollDirections direction);
    };

}

#endif // MENUSCENE_H
