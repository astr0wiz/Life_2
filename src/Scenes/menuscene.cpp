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

    void MenuScene::init( sf::Vector2f windowSize, tgui::GuiSFML* gui, std::shared_ptr<Assets::ResourceManager> resourceManager)
    {
        const int TITLE_CHAR_SIZE = 120;

        resources = resourceManager;
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
        menuGroup->loadWidgetsFromFile( resources->getResourcePath("mainmenu.txt") );
        gui->add( menuGroup );
        // -------------------------
        tgui::Font::setGlobalFont( tgui::Font( resources->getResourcePath("fonts/ITCKRIST.TTF") ) );
        tgui::Panel::Ptr panel = gui->get<tgui::Panel>( "ButtonPanel" );
        panel->setPosition( screenCenter.x - ( BB_WIDTH / 2 ), screenCenter.y - ( BB_HEIGHT / 2 ) );
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
        if(!isHidden)
        {
            target.draw(screen,states);
            target.draw(titleText);
        }
    }

}
