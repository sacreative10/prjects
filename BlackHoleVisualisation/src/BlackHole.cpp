#include "include/BlackHole.h"

Blackhole::Blackhole(float x, float y)
{
    position = sf::Vector2f(x, y);
    mass = 6.5; // mass of the black hole is 6.5e+26 k
    schwarzschildradius = (2 * (G * mass)) / (c * c);
}
