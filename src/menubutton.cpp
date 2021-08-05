#include "menubutton.h"

Menubutton::Menubutton( std::string caption, sf::Font font , sf::Rect<float> emplacement)
{
    buttonActiveColor = sf::Color2::Aliceblue;
    buttonDimColor = sf::Color2::Dimgray;
    buttonCaption.setFont(font);
    buttonCaption.setString(caption);
    buttonCaption.setCharacterSize(30);
    buttonBackground.setPosition(emplacement.top, emplacement.left);
    buttonBackground.setSize(sf::Vector2f(emplacement.width,emplacement.height));
    buttonBackground.setFillColor(sf::Color2::Cadetblue_4);
    // ----------------------------------------
}

Menubutton::~Menubutton()
{
    //dtor
}

void Menubutton::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw(buttonBackground,states);
    target.draw(buttonCaption,states);
}
