#include "Life/gamewindow.h"

namespace Life
{
    GameWindow::GameWindow( std::shared_ptr<Assets::ResourceManager> resourceManager )
    {
        setupBaseWindow();
        setupTgui();
        setupGameBar( resourceManager );
        setupBackground();
        setupScenes( resourceManager );
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
        gamebar = std::make_shared<Gamebar>( resourceManager->getMainFont() );
        std::cout << "Updating gamebar size and title" << std::endl;
        gamebar->updateSizeAndTitle( baseWinSize.x, gameTitle );
    }

    void GameWindow::setupScenes( std::shared_ptr<Assets::ResourceManager> resourceManager )
    {
        scenes.insert(std::make_pair<std::string,std::shared_ptr<Scenes::Scene>>( "Menu", std::make_shared<Scenes::MenuScene>()));
        scenes["Menu"]->init( baseWinSize, &gui, resourceManager );
    }

    void GameWindow::setupTgui()
    {
        gui.setTarget( window );
    }



    void GameWindow::run()
    {
        std::cout << "Running..." << std::endl;

        scenes["Menu"]->show();

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
                if(scenes["Menu"]->isVisible())
                {
                    gui.handleEvent( event );
                }
            }


            window.clear( sf::Color2::Rich_Black );

            window.draw( *gamebar );
            for (const auto& [key,scene]:scenes)
            {
                window.draw(*scene);
            }
            gui.draw();
            window.display();
        }
    }
}
