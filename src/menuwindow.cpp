#include "menuwindow.h"

float calcTitleBuffer(int charsize)
{
    return 20.f + (10.f * ((charsize-30.f)/45.f));
}

Menuwindow::Menuwindow( sf::Vector2u windowSize, tgui::Gui *gui, bool isVisible )
{
    const int TITLE_CHAR_SIZE = 120;

    sf::Vector2f screenCenter{windowSize.x / 2.f, windowSize.y / 2.f};

    if( !menuFont.loadFromFile( "resources/ITCKRIST.TTF" ) )
    {
        std::cout << "Menu font not loaded!!" << std::endl;
    }
    titleText.setFont( menuFont );
    titleText.setString( "Life" );
    titleText.setCharacterSize(TITLE_CHAR_SIZE);
    titleText.setFillColor( sf::Color2::Lightsteelblue_1 );
    titleText.setPosition( sf::Vector2f(
                               screenCenter.x - titleText.getGlobalBounds().width / 2.f,
                               screenCenter.y - (BB_HEIGHT / 2.f + titleText.getGlobalBounds().height + calcTitleBuffer(TITLE_CHAR_SIZE)) ) );
    // -------------------------
    screen.setSize( sf::Vector2f( windowSize.x, windowSize.y ) );
    screen.setFillColor( sf::Color( 80, 80, 80, 100 ) );
    screen.setPosition( sf::Vector2f( 0.f, 0.f ) );
    // -------------------------
//    buttonBoard.setSize( sf::Vector2f( BB_WIDTH, BB_HEIGHT ) );
//    buttonBoard.setFillColor( sf::Color2::Skyblue_4 );
//    buttonBoard.setOrigin( sf::Vector2f( BB_WIDTH / 2.f, BB_HEIGHT / 2.f ) );
//    buttonBoard.setPosition( screenCenter );
    // -------------------------
    menuGroup = tgui::Group::create();
    menuGroup->loadWidgetsFromFile("resources/mainmenu.txt");
    gui->add(menuGroup);
    tgui::Font::setGlobalFont(tgui::Font("resources/ITCKRIST.TTF"));

    tgui::Panel::Ptr panel = gui->get<tgui::Panel>("ButtonPanel");
    panel->setPosition(screenCenter.x - (BB_WIDTH/2),screenCenter.y - (BB_HEIGHT/2));
    menuGroup->setVisible(isVisible);
}

Menuwindow::~Menuwindow()
{
    //dtor
}

void Menuwindow::generateFrame()
{

}

void Menuwindow::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw( screen, states );
    target.draw( titleText );
    target.draw( buttonBoard, states );
}

