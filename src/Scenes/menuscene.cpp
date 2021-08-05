#include "Scenes/menuscene.h"

namespace Scenes
{
    MenuScene::MenuScene()
    {
        //ctor
    }

    MenuScene::~MenuScene()
    {
        //dtor
    }

    float calcTitleBuffer(int charsize)
    {
        return 20.f + (10.f * ((charsize-30.f)/45.f));
    }

    void MenuScene::init( tgui::GuiSFML* gui, sf::Vector2f windowSize )
    {
        const int TITLE_CHAR_SIZE = 120;

        sf::Vector2f screenCenter{windowSize.x / 2.f, windowSize.y / 2.f};

        if( !menuFont.loadFromFile( "resources/ITCKRIST.TTF" ) )
        {
            std::cout << "Menu font not loaded!!" << std::endl;
        }
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
        menuGroup->loadWidgetsFromFile( "resources/mainmenu.txt" );
        gui->add( menuGroup );
        // -------------------------
        tgui::Font::setGlobalFont( tgui::Font( "resources/ITCKRIST.TTF" ) );
        tgui::Panel::Ptr panel = gui->get<tgui::Panel>( "ButtonPanel" );
        panel->setPosition( screenCenter.x - ( BB_WIDTH / 2 ), screenCenter.y - ( BB_HEIGHT / 2 ) );
        menuGroup->setVisible( !isHidden );
    }

    void MenuScene::show()
    {
        isHidden = false;
    }

    void MenuScene::hide()
    {
        isHidden = true;
    }

    void MenuScene::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {

    }

}
