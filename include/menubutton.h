#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Colors.h"


class Menubutton : public sf::Drawable
{
public:
    Menubutton( std::string caption, sf::Font font , sf::Rect<float> emplacement);
    ~Menubutton();

protected:

private:
    sf::Color buttonActiveColor;
    sf::Color buttonDimColor;
    sf::Font buttonFont;
    sf::Text buttonCaption;
    sf::RectangleShape buttonBackground;
private:
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

};

#endif // MENUBUTTON_H
