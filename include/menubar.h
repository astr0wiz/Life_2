#ifndef MENUBAR_H
#define MENUBAR_H
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include <math.h>
#include <iostream>
#include <iomanip>


class Menubar: public sf::Drawable
{
public:
    Menubar(float menuwidth);
    ~Menubar();
    void setElapsedTime(sf::Time elapsedTime);
    void resetTimer();
    static constexpr int MENUBAR_HEIGHT = 32;
    static constexpr int MENUBAR_PADDING_LEFT = 8;
    static constexpr int MENUBAR_PADDING_TOP = 4;

private:
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
    sf::RectangleShape menubar;
    sf::Font menuFont;
    sf::Text title;
    sf::Text hints;
    sf::Text playtime;
    sf::Time totalPlaytime;
};

#endif // MENUBAR_H
