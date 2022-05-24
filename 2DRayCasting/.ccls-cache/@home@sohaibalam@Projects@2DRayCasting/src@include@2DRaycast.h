#include "object.h"
#include "utilities.h"
#include "wall.h"

//* @brief Namespace for the raycasting system
namespace Raycast
{
sf::RenderWindow Init();
void Runtime(sf::RenderWindow &window);
Object initaliseObject(sf::Vector2f position);
std::vector<Wall> initaliseWalls();
void SystemUpdate(Object &object, std::vector<Wall> &walls, sf::RenderWindow &window);
} // namespace Raycast