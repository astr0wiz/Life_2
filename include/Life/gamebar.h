#ifndef GAMEBAR_H
#define GAMEBAR_H
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include "Assets/resourcemanager.h"

namespace Life
{
    class Gamebar: public sf::Drawable
    {
    public:
        Gamebar(sf::Font& gamebarFont);
        ~Gamebar();
        void updateSizeAndTitle( float menuwidth, std::string gameTitle );
        void setElapsedTime( sf::Time elapsedTime );
        void resetTimer();
        static constexpr int GAMEBAR_HEIGHT = 32;
        static constexpr int GAMEBAR_PADDING_LEFT = 8;
        static constexpr int GAMEBAR_PADDING_TOP = 4;
        static constexpr int GAMEBAR_FONT_SIZE = 16;

    private:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    private:
        sf::RectangleShape gamebar;
        sf::Font font;
        sf::Text title;
        sf::Text hints;
        sf::Text playtime;
        sf::Time totalPlaytime;
    };
}
#endif // Gamebar_H
