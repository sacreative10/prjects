#include "include/utilities.h"

//* @brief Multiplies a vector by a scalar
//* @param vec The vector to be multiplied
//* @param scalar The scalar to multiply the vector by
//* @return The resulting vector
sf::Vector2f VecMult(sf::Vector2f vec, float scalar)
{
    return sf::Vector2f(vec.x * scalar, vec.y * scalar);
};

//* @brief Converts degrees to radians
//* @param degrees The degrees to be converted
//* @return The resulting radians
float DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180);
};

//* @brief Converts radians to degrees
//* @param radians The radians to be converted
//* @return The resulting degrees in a vector
sf::Vector2f VectorfromAngle(float angle)
{
    return sf::Vector2f(cos(angle), sin(angle));
};

//* @brief Calculates the distance between two points
//* @param a The first point
//* @param b The second point
//* @return The distance between the two points
float distance(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
};