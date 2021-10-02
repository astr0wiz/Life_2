#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scenes/scene.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "Assets/Colors.h"
#include "Life/gameinfo.h"
#include <iostream>

namespace Scenes
{
    enum class MenuButtons
    {
        Continue,
        New,
        Load,
        Save,
        Options,
        Quit,
        ModalYes,
        ModalNo,
        ModalOk,
        NewOk,
        NewCancel
    };
    enum class RollDirections
    {
        Up,
        Down
    };
    class MenuScene : public Scene
    {
    public:
        MenuScene();
        virtual ~MenuScene();
        void show();
        void hide();
        void init( sf::Vector2f windowSize, tgui::GuiSFML* gui, std::shared_ptr<Assets::ResourceManager> resourceManager, std::shared_ptr<Life::Utils> utilities, std::function<void(COMMON::GameActions, Life::GameInfo)> gameAction);
        bool isVisible();
        void updateEvent( void* who, sf::Event* what = 0 );
    public:
        tgui::Group::Ptr menuGroup;
        tgui::Group::Ptr modalMenuGroup;
        tgui::Group::Ptr modalNewChoiceGroup;

    private:
        static constexpr float BB_WIDTH = 380.f;
        static constexpr float BB_HEIGHT = 560.f;
        static constexpr float MM_WIDTH = 500.f;
        static constexpr float MM_HEIGHT = 260.f;
        static constexpr float NEWMODAL_WIDTH = 500.f;
        static constexpr float NEWMODAL_HEIGHT = 480.f;
        sf::Font menuFont;
        sf::RectangleShape screen;
        sf::Text titleText;
        std::map<Scenes::MenuButtons,tgui::Button::Ptr> buttons;
        Life::GameInfo gameInfo;
        //------------Generic Modal------------
        tgui::Panel::Ptr menuModalScreen;
        tgui::Panel::Ptr modalPanel;
        tgui::Label::Ptr modalTitle;
        tgui::Label::Ptr modalMessage;
        //------------New Game Modal-----------
        tgui::Panel::Ptr newChoicesPanel;
        tgui::RadioButton::Ptr newChoicesSmall;
        tgui::RadioButton::Ptr newChoicesMedium;
        tgui::RadioButton::Ptr newChoicesLarge;
        tgui::RadioButtonGroup::Ptr newChoicesButtonGroup;


    private:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
        void initMenu(tgui::GuiSFML* gui, sf::Vector2f screenCenter);
        void initGenericModal(tgui::GuiSFML* gui, sf::Vector2f screenCenter);
        void initNewMenuModal(tgui::GuiSFML* gui, sf::Vector2f screenCenter);
        void processButtonClick(MenuButtons selection);
        bool isLastGameAvailable();
        // -------- Menu Actions ----------
        void continueAction();
        void newAction();
        void loadAction();
        void saveAction();
        void optionsAction();
        void quitAction();
        // ---------------------------------
        void quitGame();
        void closeModal();
        void closeNewChoiceModal();
        void createNewMap();
    };

}

#endif // MENUSCENE_H
