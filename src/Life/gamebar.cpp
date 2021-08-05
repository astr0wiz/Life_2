#include "Life/gamebar.h"

namespace Life
{
    Gamebar::Gamebar(sf::Font& gamebarFont)
    {
        std::cout << "NEW Gamebar" << std::endl;
        gamebar.setPosition( sf::Vector2f( 0.f, 0.f ) );
        gamebar.setFillColor( sf::Color2::Dark_Gunmetal );

        title.setFont( gamebarFont );
        title.setCharacterSize( GAMEBAR_FONT_SIZE );
        title.setFillColor( sf::Color2::Old_Silver );

        hints.setFont( gamebarFont );
        hints.setCharacterSize( GAMEBAR_FONT_SIZE );
        hints.setString( "[Space]: Pause/Continue  F1: Toggle Menu" );
        hints.setFillColor( sf::Color2::Old_Silver );

        playtime.setFont( gamebarFont );
        playtime.setCharacterSize( GAMEBAR_FONT_SIZE );
        playtime.setFillColor( sf::Color2::Old_Silver );
        playtime.setString( "Running time: 00:00:00" );
    }

    Gamebar::~Gamebar()
    {
        //dtor
    }

    void Gamebar::updateSizeAndTitle( float menuwidth, std::string gameTitle )
    {
        gamebar.setSize( sf::Vector2f( menuwidth, GAMEBAR_HEIGHT ) );
        title.setString( gameTitle );
        title.setPosition( GAMEBAR_PADDING_LEFT, GAMEBAR_PADDING_TOP );
        hints.setPosition( ( menuwidth / 2.f ) - ( hints.getGlobalBounds().width / 2.f ), GAMEBAR_PADDING_TOP );
        playtime.setPosition( gamebar.getSize().x - ( playtime.getGlobalBounds().width + GAMEBAR_PADDING_LEFT ), GAMEBAR_PADDING_TOP );
    }

    void Gamebar::resetTimer()
    {
        totalPlaytime = sf::Time::Zero;
    }

    void Gamebar::setElapsedTime( sf::Time elapsedTime )
    {
        totalPlaytime += elapsedTime;
        float s = trunc( totalPlaytime.asSeconds() );
        float h = floor( s / 3600. );
        float m = floor( ( s - ( h * 3600. ) ) / 60. );
        s -= ( h * 3600. ) + ( m * 60. );
        std::ostringstream os;
        os << "Running time: ";
        os << std::setfill( '0' ) << std::setw( 2 ) << ( int )h << ":";
        os << std::setfill( '0' ) << std::setw( 2 ) << ( int )m << ":";
        os << std::setfill( '0' ) << std::setw( 2 ) << ( int )s;
        playtime.setString( os.str() );
        os.flush();
    }

    void Gamebar::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        target.draw( gamebar, states );
        target.draw( title, states );
        target.draw( hints, states );
        target.draw( playtime, states );
    }

}
