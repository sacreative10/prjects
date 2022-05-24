// this file holds the declaration of the wall data structure
#pragma once
#include <SFML/Graphics.hpp>
struct Wall
{
    Wall(sf::Vector2f start, sf::Vector2f end);
   void draw(sf::RenderWindow &window);
    sf::Vector2f start;
    sf::Vector2f end;
};