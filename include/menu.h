#ifndef MENU_H
#define MENU_H
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Colors.h"


class Menu: public sf::Drawable
{
    public:
        Menu(sf::Vector2u windowSize);
        virtual ~Menu();

    protected:

    private:
        sf::RectangleShape screen;
    private:
        void generateFrame();
};

#endif // MENU_H
