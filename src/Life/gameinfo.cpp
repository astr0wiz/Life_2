#include "gameinfo.h"

namespace Life
{
    GameInfo::GameInfo()
    {
        //ctor
    }

    GameInfo::~GameInfo()
    {
        //dtor
    }

    void GameInfo::setName( std::string name )
    {
        _name = name;
    }

    void GameInfo::setFilename( std::string filename )
    {
        _filename = filename;
    }

    void GameInfo::setDimensions( sf::Vector2u dimensions )
    {
        _dimensions = dimensions;
    }

// -------------

    std::string GameInfo::getName()
    {
        return _name;
    }

    std::string GameInfo::getFilename()
    {
        return _filename;
    }

    sf::Vector2u GameInfo::getDimensions()
    {
        return _dimensions;
    }

}

