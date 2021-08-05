#include "menubar.h"


Menubar::Menubar( float menuwidth )
{
    if( !menuFont.loadFromFile( "resources/ITCKRIST.TTF" ) )
    {
        std::cout << "Menu font not loaded!!" << std::endl;
    }
    menubar.setSize( sf::Vector2f( menuwidth, MENUBAR_HEIGHT ) );
    menubar.setPosition( sf::Vector2f( 0.f, 0.f ) );
    menubar.setFillColor( sf::Color2::Dark_Gunmetal );

    title.setFont( menuFont );
    title.setCharacterSize( 18 );
    title.setPosition( MENUBAR_PADDING_LEFT, MENUBAR_PADDING_TOP );
    title.setString( "Life 0.1" );
    title.setFillColor( sf::Color2::Old_Silver );

    hints.setFont( menuFont );
    hints.setCharacterSize( 18 );
    hints.setString( "[Space]: Pause/Continue  F1: Toggle Menu" );
    hints.setPosition( ( menuwidth / 2.f ) - ( hints.getGlobalBounds().width / 2.f ), MENUBAR_PADDING_TOP );
    hints.setFillColor( sf::Color2::Old_Silver );

    playtime.setFont( menuFont );
    playtime.setCharacterSize( 18 );
    playtime.setFillColor( sf::Color2::Old_Silver );
    playtime.setString("Running time: 00:00:00");
    playtime.setPosition( menubar.getSize().x - (playtime.getGlobalBounds().width + MENUBAR_PADDING_LEFT), MENUBAR_PADDING_TOP );
}

Menubar::~Menubar()
{
    //dtor
}

void Menubar::resetTimer()
{
    totalPlaytime = sf::Time::Zero;
}

void Menubar::setElapsedTime( sf::Time elapsedTime )
{
    totalPlaytime += elapsedTime;
    float s = trunc(totalPlaytime.asSeconds());
    float h = floor( s / 3600. );
    float m = floor( (s - ( h * 3600. )) / 60. );
    s -= ( h * 3600. ) + ( m * 60. );
    std::ostringstream os;
    os << "Running time: ";
    os << std::setfill('0') << std::setw(2) << (int)h << ":";
    os << std::setfill('0') << std::setw(2) << (int)m << ":";
    os << std::setfill('0') << std::setw(2) << (int)s;
    playtime.setString( os.str() );
    os.flush();
}

void Menubar::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw( menubar, states );
    target.draw( title, states );
    target.draw( hints, states );
    target.draw( playtime, states );
}

