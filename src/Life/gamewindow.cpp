#include "gamewindow.h"

namespace Life
{
    GameWindow::GameWindow( std::shared_ptr<Assets::ResourceManager> resourceManager )
    {
        setupBaseWindow();
        setupGameBar( resourceManager );
        setupBackground();
        setupMenuing();
    }

    GameWindow::~GameWindow()
    {
        //dtor
    }

    void GameWindow::setupBaseWindow()
    {
        std::cout << "Setting up base window" << std::endl;
        std::vector<sf::VideoMode> vmodes = sf::VideoMode::getFullscreenModes( );
        if ( vmodes.size( ) > 0 )
        {
            window.create( vmodes[0], gameTitle, sf::Style::Fullscreen );
            baseWinSize.x = vmodes[0].width;
            baseWinSize.y = vmodes[0].height;
        }
        else
        {
            window.create( sf::VideoMode( 640, 480, sf::VideoMode::getDesktopMode().bitsPerPixel ), "Life 1.0", sf::Style::None );
            baseWinSize.x = 640.;
            baseWinSize.y = 480.;
        }
    }

    void GameWindow::setupBackground()
    {
        std::cout << "Setting up background" << std::endl;
        backdrop.setSize( sf::Vector2f( baseWinSize.x, baseWinSize.y ) );
        backdrop.setPosition( sf::Vector2f( 0.f, 0.f ) );
        backdrop.setFillColor( sf::Color2::Rich_Black );
    }

    void GameWindow::setupGameBar( std::shared_ptr<Assets::ResourceManager> resourceManager )
    {
        std::cout << "Setting up gamebar" << std::endl;
        gamebar = std::make_shared<Gamebar>(resourceManager->getMainFont());
        std::cout << "Updating gamebar size and title" << std::endl;
        gamebar->updateSizeAndTitle( baseWinSize.x, gameTitle );
    }

    void GameWindow::setupMenuing()
    {
        gui.setTarget(window);
        scenes.emplace("Menu",Scenes::MenuScene());
    }

    void GameWindow::run()
    {
        std::cout << "Running..." << std::endl;
        while( window.isOpen() )
        {
            sf::Event event;
            while( window.pollEvent( event ) )
            {
                if( event.type == sf::Event::Closed )
                {
                    window.close();
                }
                if( event.type == sf::Event::KeyPressed )
                {
                    switch( event.key.code )
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    }
                }
            }

            window.clear( sf::Color2::Rich_Black );

            window.draw( *gamebar );
            window.display();
        }
    }
}
