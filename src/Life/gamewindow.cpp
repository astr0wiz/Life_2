#include "Life/gamewindow.h"

namespace Life
{
    GameWindow::GameWindow( std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utilities )
    {
        //actionFunc = &Life::GameWindow::menuAction;
        setupBaseWindow();
        setupTgui();
        setupGameBar( resourceManager );
        setupBackground();
        setupScenes( resourceManager, utilities );
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

    void GameWindow::setupScenes( std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utils )
    {
        scenes.insert( std::make_pair<std::string, std::shared_ptr<Scenes::Scene>>( "Menu", std::make_shared<Scenes::MenuScene>() ) );
        scenes["Menu"]->init( baseWinSize, &gui, resourceManager, utils, std::bind(&GameWindow::menuAction, this, std::placeholders::_1) );
        /*
        ===========================================================================================================================
        ===========================================================================================================================
        Here is the problem:

        I want the MenuScene to call "quits" back to GameWindow if Quit is selected.

        Possible solution:  Don't use MenuScene.  Just create a modal-like function which returns the selection (just like a damn
        modal window!!!).  Then, the processing for each option is done in GameWindow.

        Great.

        So, it's not a Scene.  WHat is it then?
        ===========================================================================================================================
        ===========================================================================================================================
        */
        //this->subscribe(&scenes["Menu"]);
    }

    void GameWindow::menuAction( COMMON::GameActions action )
    {
        if( action == COMMON::GameActions::Quit )
        {
            quitGame();
        }
    }

    void GameWindow::setupTgui()
    {
        gui.setTarget( window );
    }

    void GameWindow::quitGame()
    {
        window.close();
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
                            quitGame();
                            break;
                    }
                    notifyEvent( &event );
                }
                if( scenes["Menu"]->isVisible() )
                {
                    gui.handleEvent( event );
                }

            }


            window.clear( sf::Color2::Rich_Black );

            window.draw( *gamebar );
            for ( const auto& [key, scene] : scenes )
            {
                window.draw( *scene );
            }
            gui.draw();
            window.display();
        }
    }

    void GameWindow::notifyEvent( sf::Event* what, std::shared_ptr<Scenes::Scene> subToSkip )
    {
        if( notifyEnabled )
        {
            for( auto p = scenes.begin(); p != scenes.end(); p++ )
            {
                if( p->second != subToSkip )
                {
                    p->second->updateEvent( this, what );
                }
            }
        }
        notifyEnabled = true;
    }

}
