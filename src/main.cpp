#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Assets/Colors.h"
#include "Assets/resourcemanager.h"
#include "Life/gamewindow.h"

using namespace std;

int row_max = 0;
int col_max = 0;
bool inMotion = false;
bool isMenuVisible = true;
sf::RenderWindow window;
sf::RectangleShape backdrop;
sf::Clock timer;

std::shared_ptr<Assets::ResourceManager> resourceManager{new Assets::ResourceManager};


void runGame();

int main()
{
    resourceManager->setResourceDirectory( "resources" );
    resourceManager->setMainFont( "ITCKRIST.TTF" );

    runGame();
    return 0;
}

void continueFromMenu()
{
    inMotion = true;
    timer.restart();
    isMenuVisible = false;
}

void runGame()
{
    Life::GameWindow gameWindow( resourceManager );
    gameWindow.run();
/* =====================================================================================
**    std::vector<sf::VideoMode> vmodes = sf::VideoMode::getFullscreenModes( );
**    sf::Vector2f baseWinSize{0., 0.};
**    if ( vmodes.size( ) > 0 )
**    {
**        window.create( vmodes[0], "Life 1.0", sf::Style::Fullscreen );
**        baseWinSize.x = vmodes[0].width;
**        baseWinSize.y = vmodes[0].height;
**    }
**    else
**    {
**        window.create( sf::VideoMode( 640, 480, sf::VideoMode::getDesktopMode().bitsPerPixel ), "Life 1.0", sf::Style::None );
**        baseWinSize.x = 640.;
**        baseWinSize.y = 480.;
**    }
**    ** =======================================================
**    ** Grid size uses window size minus a small buffer.
**    ** =======================================================
**    row_max = ( baseWinSize.y - Menubar::MENUBAR_HEIGHT ) * 16 - 2;
**    col_max = baseWinSize.x * 16 - 2;
**
**    tgui::Gui gui{window};
**    Mapdata map( row_max, col_max );
**    Menuwindow menu( window.getSize(), &gui, isMenuVisible );
**    backdrop.setSize( sf::Vector2f( baseWinSize.x, baseWinSize.y - Menubar::MENUBAR_HEIGHT ) );
**    backdrop.setPosition( sf::Vector2f( 0.f, Menubar::MENUBAR_HEIGHT ) );
**    backdrop.setFillColor( sf::Color2::Rich_Black );
**
**    ** =======================================================
**    ** Top menubar
**    ** =======================================================
**    Menubar menubar( baseWinSize.x );
**
**    ** =======================================================
**    ** Setup the menu buttons
**    ** =======================================================
**    tgui::Button::Ptr aButton = gui.get<tgui::Button>( "ContinueButton" );
**    aButton->onPress( &continueFromMenu );
**    aButton = gui.get<tgui::Button>( "QuitButton" );
**    aButton->onPress( [&] {window.close();} );
**
**    ** ----------------
**    ** Load test data
**    ** ----------------
**    map.simpleTest01();
**    map.simpleTest02();
**
**
**    window.setFramerateLimit( 60 );
**    timer.restart();
**    menubar.resetTimer();
**    while( window.isOpen() )
**    {
**        sf::Event event;
**        while( window.pollEvent( event ) )
**        {
**            if( event.type == sf::Event::Closed )
**            {
**                window.close();
**            }
**            if( event.type == sf::Event::KeyPressed )
**            {
**                switch( event.key.code )
**                {
**                    case sf::Keyboard::F1:
**                        inMotion = false;
**                        isMenuVisible = true;
**                        menu.menuGroup->setVisible( isMenuVisible );
**                        break;
**                    case sf::Keyboard::Space:
**                        std::cout << "Toggle inMotion.  BEFORE Value: " << inMotion ;
**                        if( inMotion )
**                        {
**                            inMotion = false;
**                        }
**                        else
**                        {
**                            inMotion = true;
**                            timer.restart();
**                        }
**                        std::cout << "  AFTER Value: " << inMotion << std::endl;
**                        break;
**                }
**            }
**            if( isMenuVisible )
**            {
**                gui.handleEvent( event );
**            }
**        }
**
**        window.clear( sf::Color2::Rich_Black );
**
**        if( inMotion )
**        {
**            map.generateFrame();
**            menubar.setElapsedTime( timer.restart() );
**        }
**        window.draw( backdrop );
**        window.draw( map );
**        window.draw( menubar );
**
**        if( isMenuVisible )
**        {
**            menu.generateFrame();
**            window.draw( menu );
**            gui.draw();
**        }
**
**        window.display();
**    }
========================================================================== */
}
