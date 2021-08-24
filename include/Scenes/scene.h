#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "Assets/resourcemanager.h"

namespace Scenes
{
    class Scene : public sf::Drawable
    {
    public:
        Scene() {}
        virtual ~Scene() {}
        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void init( sf::Vector2f, tgui::GuiSFML*, std::shared_ptr<Assets::ResourceManager> ) = 0;
        virtual bool isVisible()
        {
            return !isHidden;
        }
        virtual void updateEvent( void* who, sf::Event* what = 0 ) = 0;

    protected:
        bool isHidden{true};
        std::shared_ptr<Assets::ResourceManager> resources;

    private:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const = 0;
    };

}

#endif // SCENE_H
