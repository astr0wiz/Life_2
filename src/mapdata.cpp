#include "mapdata.h"

Mapdata::Mapdata( int rows, int cols )
{
    if( !cellTexture.loadFromFile( "resources/dot.png" ) )
    {
        std::cout << "** !! Texture not loaded !! **" << std::endl;
    }
    else
    {
        currentState = 1;
        mapsize.x = cols;
        mapsize.y = rows;
        unsigned int w = cellTexture.getSize().x;
        unsigned int h = cellTexture.getSize().y;
        cellTexture.setSmooth( true );

        for( int r = 0; r < rows; r++ )
        {
            for( int c = 0; c < cols; c++ )
            {
                cell lifecell;
                lifecell.state[0] = 0;
                lifecell.state[1] = 0;
                lifecell.dot.setTexture( cellTexture );
                lifecell.dot.setOrigin( sf::Vector2f( w / 2.f, h / 2.f ) );
                lifecell.dot.move( sf::Vector2f( c * w + ( w * 1.5f ), r * h + ( h * 1.5f ) + Menubar::MENUBAR_HEIGHT ) );
                lifecell.dot.setColor( statusColors[UNKNOWN] );
                lifecell.opacity = 0;
                celldata.push_back( lifecell );
            }
        }
    }
}

Mapdata::~Mapdata()
{
    celldata.clear();
}

uint8_t Mapdata::getNeighborCount( int row, int col, uint8_t stateNow )
{
    uint8_t ncount = 0;
    // Upper row
    int newrow = row == 0 ? mapsize.y - 1 : row - 1;
    // Left col
    int newcol = col == 0 ? mapsize.x - 1 : col - 1;
    for( int r = 0; r < 3; r++ )
    {
        for( int c = 0; c < 3; c++ )
        {
            if( !( ( ( r + newrow ) % mapsize.y == row ) && ( ( c + newcol ) % mapsize.x == col ) ) )
            {
                ncount += celldata[( ( r + newrow ) % mapsize.y ) * mapsize.x + ( ( c + newcol ) % mapsize.x )].state[stateNow];
            }
        }
    }
    return ncount;
}

void Mapdata::generateNextState( uint8_t nextState )
{
    for( int r = 0; r < mapsize.y; r++ )
    {
        for( int c = 0; c < mapsize.x; c++ )
        {
            uint8_t neighbors = getNeighborCount( r, c, currentState );
            cell* d = &celldata[r * mapsize.x + c];
            if( d->state[currentState] == DeadCell )
            {
                d->state[nextState] = neighbors == 3 ? LiveCell : DeadCell;
            }
            else
            {
                d->state[nextState] = neighbors == 3 || neighbors == 2 ? LiveCell : DeadCell;
            }
        }
    }
}

uint8_t Mapdata::calculateNextState()
{
    return ( currentState + 1 ) % 2;
}

void Mapdata::generateFrame()
{
    float fadeInterval = 255.f / ( float )transitionFrameCount;

    if( frameNumber == 0 )
    {
        currentState = calculateNextState();
        generateNextState( calculateNextState() );
    }
    uint8_t nextState = calculateNextState();

    for( int r = 0; r < mapsize.y; r++ )
    {
        for( int c = 0; c < mapsize.x; c++ )
        {
            cell* d = &celldata[r * mapsize.x + c];
            sf::Color dotcolor = d->dot.getColor();
            if( d->state[currentState] != d->state[nextState] )
            {
                if( d->state[nextState] == DeadCell )
                {
                    dotcolor = statusColors[DYING];
                    d->opacity =  255 - ( uint8_t )( ( frameNumber + 1 ) * fadeInterval );
                }
                else
                {
                    dotcolor = statusColors[BIRTHING];
                    d->opacity = ( uint8_t )( ( frameNumber + 1 ) * fadeInterval );
                }
            }
            else
            {
                dotcolor = statusColors[LIVE];
            }
            dotcolor.a = d->opacity;
            d->dot.setColor( dotcolor );
        }
    }
    frameNumber = ++frameNumber % transitionFrameCount;
}

void Mapdata::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    for( int r = 0; r < mapsize.y; r++ )
    {
        for( int c = 0; c < mapsize.x; c++ )
        {
            cell d = celldata[r * mapsize.x + c];
            target.draw( d.dot, states );
        }
    }
}

void Mapdata::setCellOn( cell* c )
{
    c->state[0] = 1;
    c->opacity = 255;
}

void Mapdata::simpleTest01()
{
    // oscillator
    int r = 0;
    int c = 20;
    cell* d = &celldata[r * mapsize.x + c];
    setCellOn( d );
    r = 1;
    d = &celldata[r * mapsize.x + c];
    setCellOn( d );
    r = 2;
    d = &celldata[r * mapsize.x + c];
    setCellOn( d );
}

void Mapdata::dumpSimpleTest01()
{
    int r = 0;
    int c = 1;
    std::cout << "========= Dump 01 ==========" << std::endl;
    cell d = celldata[r * mapsize.x + c];
    std::cout << "-> [" << c << "," << r << "] s0:" << +d.state[0] << " s1:" << +d.state[1] << std::endl;
    r = 1;
    d = celldata[r * mapsize.x + c];
    std::cout << "-> [" << c << "," << r << "] s0:" << +d.state[0] << " s1:" << +d.state[1] << std::endl;
    r = 2;
    d = celldata[r * mapsize.x + c];
    std::cout << "-> [" << c << "," << r << "] s0:" << +d.state[0] << " s1:" << +d.state[1] << std::endl;
}

void Mapdata::simpleTest02()
{
    int r = 0;
    int c = 1;
    cell* d = &celldata[r * mapsize.x + c];
    setCellOn( d );
    r = 1;
    c = 2;
    d = &celldata[r * mapsize.x + c];
    setCellOn( d );
    r = 2;
    c = 0;
    d = &celldata[r * mapsize.x + c];
    setCellOn( d );
    c = 1;
    d = &celldata[r * mapsize.x + c];
    setCellOn( d );
    c = 2;
    d = &celldata[r * mapsize.x + c];
    setCellOn( d );
}
