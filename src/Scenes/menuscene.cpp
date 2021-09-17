#include "Scenes/menuscene.h"

namespace Scenes
{
    MenuScene::MenuScene( )
    {
        //ctor
    }

    MenuScene::~MenuScene()
    {
        //dtor
    }

    float calcTitleBuffer( int charsize )
    {
        return 20.f + ( 10.f * ( ( charsize - 30.f ) / 45.f ) );
    }

    void MenuScene::init( sf::Vector2f windowSize, tgui::GuiSFML* gui, std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utilities, std::function<void(COMMON::GameActions)> gameAction )
    {
        const int TITLE_CHAR_SIZE = 120;

        resources = resourceManager;
        utils = utilities;
        gameActionFunc = gameAction;
        sf::Vector2f screenCenter{windowSize.x / 2.f, windowSize.y / 2.f};

        menuFont = resources->getMainFont();
        titleText.setFont( menuFont );
        titleText.setString( "Life" );
        titleText.setCharacterSize( TITLE_CHAR_SIZE );
        titleText.setFillColor( sf::Color2::Lightsteelblue_1 );
        titleText.setPosition( sf::Vector2f(
                                   screenCenter.x - titleText.getGlobalBounds().width / 2.f,
                                   screenCenter.y - ( BB_HEIGHT / 2.f + titleText.getGlobalBounds().height + calcTitleBuffer( TITLE_CHAR_SIZE ) ) ) );
        // -------------------------
        screen.setSize( sf::Vector2f( windowSize.x, windowSize.y ) );
        screen.setFillColor( sf::Color( 80, 80, 80, 100 ) );
        screen.setPosition( sf::Vector2f( 0.f, 0.f ) );
        // -------------------------
        menuGroup = tgui::Group::create();
        menuGroup->loadWidgetsFromFile( resources->getResourcePath( "mainmenu.txt" ) );
        gui->add( menuGroup );
        // -------------------------
        tgui::Font::setGlobalFont( tgui::Font( resources->getResourcePath( "fonts/ITCKRIST.TTF" ) ) );
        tgui::Panel::Ptr panel = gui->get<tgui::Panel>( "ButtonPanel" );
        panel->setPosition( screenCenter.x - ( BB_WIDTH / 2 ), screenCenter.y - ( BB_HEIGHT / 2 ) );
        buttons.insert( {Scenes::MenuButtons::Continue, gui->get<tgui::Button>( "ContinueButton" )} );
        buttons.insert( {Scenes::MenuButtons::Load, gui->get<tgui::Button>( "LoadButton" )} );
        buttons.insert( {Scenes::MenuButtons::Save, gui->get<tgui::Button>( "SaveButton" )} );
        buttons.insert( {Scenes::MenuButtons::Edit, gui->get<tgui::Button>( "EditButton" )} );
        buttons.insert( {Scenes::MenuButtons::Random, gui->get<tgui::Button>( "RandomButton" )} );
        buttons.insert( {Scenes::MenuButtons::Credits, gui->get<tgui::Button>( "CreditsButton" )} );
        buttons.insert( {Scenes::MenuButtons::Quit, gui->get<tgui::Button>( "QuitButton" )} );
    }

    void MenuScene::show()
    {
        isHidden = false;
        menuGroup->setVisible( !isHidden );
    }

    void MenuScene::hide()
    {
        isHidden = true;
        menuGroup->setVisible( !isHidden );
    }

    bool MenuScene::isVisible()
    {
        return !isHidden;
    }

    void MenuScene::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        if( !isHidden )
        {
            target.draw( screen, states );
            target.draw( titleText );
        }
    }

    void MenuScene::updateEvent( void* who, sf::Event* what )
    {
        std::ostringstream os;
        os << "updateEvent::";
        switch ( what->type )
        {
            case sf::Event::EventType::Closed:
                os << "CLOSED";
                break;
            case sf::Event::EventType::Resized:
                os << "RESIZED";
                break;
            case sf::Event::EventType::LostFocus:
                os << "LOSTFOCUS";
                break;
            case sf::Event::EventType::GainedFocus:
                os << "GAINEDFOCUS";
                break;
            case sf::Event::EventType::TextEntered:
                os << "TEXTENTERED";
                break;
            case sf::Event::EventType::KeyPressed:
                switch( what->key.code )
                {
                    case sf::Keyboard::C:
                        buttons[MenuButtons::Continue]->setFocused( true );
                        break;
                    case sf::Keyboard::L:
                        buttons[MenuButtons::Load]->setFocused( true );
                        break;
                    case sf::Keyboard::S:
                        buttons[MenuButtons::Save]->setFocused( true );
                        break;
                    case sf::Keyboard::E:
                        buttons[MenuButtons::Edit]->setFocused( true );
                        break;
                    case sf::Keyboard::R:
                        buttons[MenuButtons::Random]->setFocused( true );
                        break;
                    case sf::Keyboard::D:
                        buttons[MenuButtons::Credits]->setFocused( true );
                        break;
                    case sf::Keyboard::Q:
                        buttons[MenuButtons::Quit]->setFocused( true );
                        gameActionFunc(COMMON::GameActions::Quit);
                        break;
                    case sf::Keyboard::Down:
                        rollButtonSelection(RollDirections::Down);
                        break;
                    case sf::Keyboard::Up:
                        rollButtonSelection(RollDirections::Up);
                        break;
                    case sf::Keyboard::Enter:
                        break;
                }
                os << "KEYPRESSED = " << utils->getKeyNameFromCode( what->key.code );
                break;
            case sf::Event::EventType::KeyReleased:
                os << "KEYRELEASED";
                break;
            case sf::Event::EventType::MouseWheelMoved:
                os << "MOUSEWHEELMOVED";
                break;
            case sf::Event::EventType::MouseWheelScrolled:
                os << "MOUSEWHEELSCROLLED";
                break;
            case sf::Event::EventType::MouseButtonPressed:
                os << "MOUSEBUTTONPRESSED";
                break;
            case sf::Event::EventType::MouseButtonReleased:
                os << "MOUSEBUTTONRELEASED";
                break;
            case sf::Event::EventType::MouseMoved:
                os << "MOUSEMOVED";
                break;
            case sf::Event::EventType::MouseEntered:
                os << "MOUSEENTERED";
                break;
            case sf::Event::EventType::MouseLeft:
                os << "MOUSELEFT";
                break;
            case sf::Event::EventType::JoystickButtonPressed:
                os << "JOYSTICKBUTTONPRESSED";
                break;
            case sf::Event::EventType::JoystickButtonReleased:
                os << "JOYSTICKBUTTONRELEASED";
                break;
            case sf::Event::EventType::JoystickMoved:
                os << "JOYSTICKMOVED";
                break;
            case sf::Event::EventType::JoystickConnected:
                os << "JOYSTICKCONNECTED";
                break;
            case sf::Event::EventType::JoystickDisconnected:
                os << "JOYSTICKDISCONNECTED";
                break;
            case sf::Event::EventType::TouchBegan:
                os << "TOUCHBEGAN";
                break;
            case sf::Event::EventType::TouchMoved:
                os << "TOUCHMOVED";
                break;
            case sf::Event::EventType::TouchEnded:
                os << "TOUCHENDED";
                break;
            case sf::Event::EventType::SensorChanged:
                os << "SENSORCHANGED";
                break;
            case sf::Event::EventType::Count:
                os << "COUNT";
                break;
        }
        MainLogger::Instance().Log( os.str() );
    }

    void MenuScene::processButtonClick( MenuButtons selection )
    {
        buttons[selection]->setFocused( true );
        switch(selection)
        {
            case MenuButtons::Quit:
                // call gameActionFunc
                break;
        }
    }

    void MenuScene::rollButtonSelection( RollDirections direction )
    {
        for( auto const& [btnType, btn] : buttons )
        {
            if( btn->isFocused() )
            {
                if( direction == RollDirections::Down )
                {
                    switch( btnType )
                    {
                        case MenuButtons::Continue:
                            buttons[MenuButtons::Load]->setFocused( true );
                            break;
                        case MenuButtons::Load:
                            buttons[MenuButtons::Save]->setFocused( true );
                            break;
                        case MenuButtons::Save:
                            buttons[MenuButtons::Edit]->setFocused( true );
                            break;
                        case MenuButtons::Edit:
                            buttons[MenuButtons::Random]->setFocused( true );
                            break;
                        case MenuButtons::Random:
                            buttons[MenuButtons::Credits]->setFocused( true );
                            break;
                        case MenuButtons::Credits:
                            buttons[MenuButtons::Quit]->setFocused( true );
                            break;
                        case MenuButtons::Quit:
                            buttons[MenuButtons::Continue]->setFocused( true );
                            break;
                    }
                }
                else
                {
                    switch( btnType )
                    {
                        case MenuButtons::Continue:
                            buttons[MenuButtons::Quit]->setFocused( true );
                            break;
                        case MenuButtons::Load:
                            buttons[MenuButtons::Continue]->setFocused( true );
                            break;
                        case MenuButtons::Save:
                            buttons[MenuButtons::Load]->setFocused( true );
                            break;
                        case MenuButtons::Edit:
                            buttons[MenuButtons::Save]->setFocused( true );
                            break;
                        case MenuButtons::Random:
                            buttons[MenuButtons::Edit]->setFocused( true );
                            break;
                        case MenuButtons::Credits:
                            buttons[MenuButtons::Random]->setFocused( true );
                            break;
                        case MenuButtons::Quit:
                            buttons[MenuButtons::Credits]->setFocused( true );
                            break;
                    }
                }
                return;
            }
        }
        if( direction == RollDirections::Down )
        {
            buttons[MenuButtons::Continue]->setFocused( true );
        }
        else
        {
            buttons[MenuButtons::Quit]->setFocused( true );
        }
    }

}
