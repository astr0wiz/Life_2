#ifndef MAPDATA_H
#define MAPDATA_H
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include "menubar.h"


struct cell
{
public:
    uint8_t state[2];
    sf::Sprite dot;
    uint8_t opacity;
};

class Mapdata : public sf::Drawable
{
public:
    Mapdata( int rows, int cols );
    ~Mapdata();
    void generateFrame();
    void generateNextState(uint8_t nextState);
    uint8_t calculateNextState();
    void simpleTest01();
    void simpleTest02();
public:
    enum Statuses
    {
        LIVE,
        DYING,
        BIRTHING,
        UNKNOWN,
        STATUS_COUNT
    };
    uint8_t currentState;
private:
    static constexpr uint8_t transitionFrameCount = 10;
    static constexpr uint8_t DeadCell = 0;
    static constexpr uint8_t LiveCell = 1;
    uint8_t frameNumber{0};
    sf::Vector2u mapsize{0,0};
    sf::Texture cellTexture;
    std::vector<cell> celldata;
    sf::Color statusColors[STATUS_COUNT] =
    {
        sf::Color2::Sapgreen, // Well
        sf::Color2::Indian_Red, // Dying
        sf::Color2::Deepskyblue, // Birthing
        sf::Color( 23, 97, 50, 0 )  // ??
    };
private:
    void setCellOn(cell *c);
    void dumpSimpleTest01();
    uint8_t getNeighborCount(int row, int col, uint8_t stateNow);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MAPDATA_H
