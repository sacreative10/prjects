#include "include/wall.h"


Wall::Wall(sf::Vector2f start, sf::Vector2f end)
{
    this->start = start;
    this->end = end;
}

void Wall::draw(sf::RenderWindow &window)
{
    // draw a line
    sf::Vertex line[] =
    {
        sf::Vertex(start, sf::Color::White),
        sf::Vertex(end, sf::Color::White)
    };
    window.draw(line, 2, sf::Lines);
}