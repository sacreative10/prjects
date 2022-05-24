// this file holds the definition of the object class, which is controlled by the player using the mouse.
// the object has rays that are cast from the object to the walls.
// the rays are cast in a circle around the object.
// Language: cpp
#include "ray.h"
#include <SFML/Graphics.hpp>
#include "util.h"
#include <vector>

class Object
{
  public:
    Object(sf::Vector2f position, sf::Vector2f direction);
    void draw(sf::RenderWindow &window);
    void updatePos(sf::Vector2f position);
    void raycast(std::vector<Wall> &wall, sf::RenderWindow &window);
    std::vector<Ray> rays;
    sf::Vector2f position;
    sf::Vector2f direction;
};