#pragma once
#include "wall.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>

class Ray
{
  public:
    Ray(sf::Vector2f position, float radian_direction);
    void draw(sf::RenderWindow &window);
    std::optional<sf::Vector2f> intersect(Wall wall);
    void setDir(sf::Vector2f dir);
    sf::Vector2f position;
    sf::Vector2f direction;
};