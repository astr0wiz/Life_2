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

    void MenuScene::init( sf::Vector2f windowSize, tgui::GuiSFML* gui, std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utilities, std::function<void( COMMON::GameActions, Life::GameInfo )> gameAction )
    {
        const int TITLE_CHAR_SIZE = 120;

        gameInfo.setName("");
        gameInfo.setFilename("");
        gameInfo.setDimensions({0,0});
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
        initMenu( gui, screenCenter );
        initGenericModal( gui, screenCenter );
        initNewMenuModal( gui, screenCenter );
    }

    void MenuScene::initMenu( tgui::GuiSFML* gui, sf::Vector2f screenCenter )
    {
        menuGroup = tgui::Group::create();
        menuGroup->loadWidgetsFromFile( resources->getResourcePath( "mainmenu.txt" ) );
        gui->add( menuGroup );
        // -------------------------
        tgui::Font::setGlobalFont( tgui::Font( resources->getResourcePath( "fonts/ITCKRIST.TTF" ) ) );
        tgui::Panel::Ptr panel = gui->get<tgui::Panel>( "ButtonPanel" );
        menuModalScreen = gui->get<tgui::Panel>( "ModalScreen" );
        panel->setPosition( screenCenter.x - ( BB_WIDTH / 2 ), screenCenter.y - ( BB_HEIGHT / 2 ) );
        menuModalScreen->setVisible( false );
        menuModalScreen->setPosition( screenCenter.x - ( BB_WIDTH / 2 ), screenCenter.y - ( BB_HEIGHT / 2 ) );
        buttons.insert( {Scenes::MenuButtons::Continue, gui->get<tgui::Button>( "ContinueButton" )} );
        buttons.insert( {Scenes::MenuButtons::New, gui->get<tgui::Button>( "NewButton" )} );
        buttons.insert( {Scenes::MenuButtons::Load, gui->get<tgui::Button>( "LoadButton" )} );
        buttons.insert( {Scenes::MenuButtons::Save, gui->get<tgui::Button>( "SaveButton" )} );
        buttons.insert( {Scenes::MenuButtons::Options, gui->get<tgui::Button>( "OptionsButton" )} );
        buttons.insert( {Scenes::MenuButtons::Quit, gui->get<tgui::Button>( "QuitButton" )} );
        buttons[Scenes::MenuButtons::Continue]->onPress( &MenuScene::continueAction, this );
        buttons[Scenes::MenuButtons::New]->onPress( &MenuScene::newAction, this );
        buttons[Scenes::MenuButtons::Load]->onPress( &MenuScene::loadAction, this );
        buttons[Scenes::MenuButtons::Save]->onPress( &MenuScene::saveAction, this );
        buttons[Scenes::MenuButtons::Options]->onPress( &MenuScene::optionsAction, this );
        buttons[Scenes::MenuButtons::Quit]->onPress( &MenuScene::quitAction, this );
    }

    void MenuScene::initGenericModal( tgui::GuiSFML* gui, sf::Vector2f screenCenter )
    {
        modalMenuGroup = tgui::Group::create();
        modalMenuGroup->loadWidgetsFromFile( resources->getResourcePath( "modalYesNo.txt" ) );
        gui->add( modalMenuGroup );
        modalPanel = gui->get<tgui::Panel>( "ModalPanel" );
        modalPanel->setPosition( screenCenter.x - ( MM_WIDTH / 2 ), screenCenter.y - ( MM_HEIGHT / 2 ) );
        modalPanel->setVisible( false );
        modalTitle = gui->get<tgui::Label>( "Title" );
        modalMessage = gui->get<tgui::Label>( "Message" );
        buttons.insert( {Scenes::MenuButtons::ModalYes, gui->get<tgui::Button>( "YesButton" )} );
        buttons.insert( {Scenes::MenuButtons::ModalNo, gui->get<tgui::Button>( "NoButton" )} );
        buttons.insert( {Scenes::MenuButtons::ModalOk, gui->get<tgui::Button>( "OkButton" )} );
    }

    void MenuScene::initNewMenuModal( tgui::GuiSFML* gui, sf::Vector2f screenCenter )
    {
        modalNewChoiceGroup = tgui::Group::create();
        modalNewChoiceGroup->loadWidgetsFromFile( resources->getResourcePath( "newChoices.txt" ));
        gui->add( modalNewChoiceGroup );
        newChoicesPanel = gui->get<tgui::Panel>( "MapChoicePanel" );
        newChoicesPanel->setPosition( screenCenter.x - ( NEWMODAL_WIDTH / 2 ), screenCenter.y - ( NEWMODAL_HEIGHT / 2 ) );
        newChoicesPanel->setVisible( false );
        newChoicesSmall = gui->get<tgui::RadioButton>( "MapChoiceSizeSmall" );
        newChoicesMedium = gui->get<tgui::RadioButton>( "MapChoiceSizeMedium" );
        newChoicesLarge = gui->get<tgui::RadioButton>( "MapChoiceSizeLarge" );
        buttons.insert( {Scenes::MenuButtons::NewOk, gui->get<tgui::Button>( "MapChoiceGoButton" )} );
        buttons.insert( {Scenes::MenuButtons::NewCancel, gui->get<tgui::Button>( "MapChoiceCancelButton" )} );
    }


    bool MenuScene::isLastGameAvailable()
    {
        return false;
    }

    void MenuScene::continueAction()
    {
        if( !isLastGameAvailable() )
        {
            menuModalScreen->setVisible( true );
            modalPanel->setVisible( true );
            modalTitle->setText( "No Currently Running Game" );
            modalMessage->setText( "There is no game to continue from.  You might try creating a New game." );
            buttons[Scenes::MenuButtons::ModalYes]->setVisible( false );
            buttons[Scenes::MenuButtons::ModalNo]->setVisible( false );
            buttons[Scenes::MenuButtons::ModalOk]->setVisible( true );
            buttons[Scenes::MenuButtons::ModalOk]->onPress( &MenuScene::closeModal, this );
        }
    }

    void MenuScene::newAction()
    {
        menuModalScreen->setVisible( true );
        newChoicesPanel->setVisible( true );
        buttons[Scenes::MenuButtons::NewOk]->onPress( &MenuScene::createNewMap, this );
        buttons[Scenes::MenuButtons::NewCancel]->onPress( &MenuScene::closeNewChoiceModal, this );
    }

    void MenuScene::createNewMap()
    {
        closeNewChoiceModal();
        if(newChoicesLarge->isChecked())
        {
            gameInfo.setDimensions({1000,1000});
        }
        else
        {
            if(newChoicesMedium->isChecked())
            {
                gameInfo.setDimensions({200,200});
            }
            else{
                gameInfo.setDimensions({50,50});
            }
        }
        gameInfo.setName("New Game");
        gameActionFunc( COMMON::GameActions::New, gameInfo );
    }

    void MenuScene::closeNewChoiceModal()
    {
        menuModalScreen->setVisible( false );
        newChoicesPanel->setVisible( false );
    }

    void MenuScene::loadAction()
    {
    }

    void MenuScene::saveAction()
    {
    }

    void MenuScene::optionsAction()
    {
    }

    void MenuScene::quitAction()
    {
        menuModalScreen->setVisible( true );
        modalPanel->setVisible( true );
        modalTitle->setText( "Confirm Quit" );
        modalMessage->setText( "Are you sure you want to quit?  You can still press 'No' and save your game." );
        buttons[Scenes::MenuButtons::ModalYes]->setVisible( true );
        buttons[Scenes::MenuButtons::ModalNo]->setVisible( true );
        buttons[Scenes::MenuButtons::ModalOk]->setVisible( false );
        buttons[Scenes::MenuButtons::ModalYes]->onPress( &MenuScene::quitGame, this );
        buttons[Scenes::MenuButtons::ModalNo]->onPress( &MenuScene::closeModal, this );
    }

    void MenuScene::closeModal()
    {
        menuModalScreen->setVisible( false );
        modalPanel->setVisible( false );
    }

    void MenuScene::quitGame()
    {
        closeModal();
        gameActionFunc( COMMON::GameActions::Quit, gameInfo );
    }

    void MenuScene::show()
    {
        isHidden = false;
        menuGroup->setVisible( true );
    }

    void MenuScene::hide()
    {
        isHidden = true;
        menuGroup->setVisible( false );
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
                os << "KEYPRESSED = ";
                if( modalPanel->isVisible() )
                {
                    os << "[Modal] ";
                    if( buttons[MenuButtons::ModalOk]->isVisible() )
                    {
                        if( what->key.code == sf::Keyboard::O )
                        {
                            closeModal();
                        }
                    }
                    else
                    {
                        switch( what->key.code )
                        {
                            case sf::Keyboard::Y:
                                quitGame();
                                break;
                            case sf::Keyboard::N:
                                closeModal();
                                break;
                        }
                    }
                }
                else
                {
                    os << "[-menu-]";
                    switch( what->key.code )
                    {
                        case sf::Keyboard::C:
                            buttons[MenuButtons::Continue]->setFocused( true );
                            continueAction();
                            break;
                        case sf::Keyboard::N:
                            buttons[MenuButtons::New]->setFocused( true );
                            break;
                        case sf::Keyboard::L:
                            buttons[MenuButtons::Load]->setFocused( true );
                            break;
                        case sf::Keyboard::S:
                            buttons[MenuButtons::Save]->setFocused( true );
                            break;
                        case sf::Keyboard::O:
                            buttons[MenuButtons::Options]->setFocused( true );
                            break;
                        case sf::Keyboard::Q:
                            buttons[MenuButtons::Quit]->setFocused( true );
                            quitAction();
                            break;
                        case sf::Keyboard::Enter:
                            break;
                    }
                }
                os << utils->getKeyNameFromCode( what->key.code );
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
        switch( selection )
        {
            case MenuButtons::Quit:
                // call gameActionFunc
                break;
        }
    }

}
