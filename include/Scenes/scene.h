#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

namespace Scenes
{
    class Scene : public sf::Drawable
    {
    public:
        Scene(){}
        virtual ~Scene() {}
        virtual void show(){};
        virtual void hide(){};

    protected:
        bool isHidden{true};

    private:
        virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const{};
    };

}

#endif // SCENE_H
