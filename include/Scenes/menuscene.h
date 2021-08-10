#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scenes/scene.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "Assets/Colors.h"

namespace Scenes
{
    class MenuScene : public Scene
    {
    public:
        MenuScene();
        virtual ~MenuScene();
        void show();
        void hide();
        void init( sf::Vector2f windowSize, tgui::GuiSFML* gui, std::shared_ptr<Assets::ResourceManager> resourceManager);
        bool isVisible();
    public:
        tgui::Group::Ptr menuGroup;

    private:
        static constexpr float BB_WIDTH = 400.f;
        static constexpr float BB_HEIGHT = 600.f;
        sf::Font menuFont;
        sf::RectangleShape screen;
        sf::Text titleText;
        //tgui::Panel::Ptr panel;

    private:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    };

}

#endif // MENUSCENE_H
