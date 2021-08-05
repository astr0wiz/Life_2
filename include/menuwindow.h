#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>
#include <TGUI/TGUI.hpp>
#include "Colors.h"

class Menuwindow: public sf::Drawable
{
public:
    Menuwindow( sf::Vector2u windowSize, tgui::Gui *gui, bool isVisible );
    virtual ~Menuwindow();
    void generateFrame();
public:
    tgui::Group::Ptr menuGroup;
private:
    static constexpr float BB_WIDTH = 400.f;
    static constexpr float BB_HEIGHT = 600.f;
    sf::RectangleShape screen;
    sf::RectangleShape buttonBoard;
    sf::Font menuFont;
    sf::Text titleText;
private:
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
};

#endif // MENU_H
