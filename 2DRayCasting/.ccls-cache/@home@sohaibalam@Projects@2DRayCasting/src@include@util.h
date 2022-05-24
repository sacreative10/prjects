// header guard
#ifndef UTIL_H
#define UTIL_H
#include <SFML/Graphics.hpp>
#include <cmath>
// multiply a sf::Vector2f and scalar
sf::Vector2f operator*(const sf::Vector2f &v, float s)
{
    return sf::Vector2f(v.x * s, v.y * s);
}

// quake3 inverse square root function
float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;           // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // what the fuck?
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y)); // 1st iteration
    // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

// normalize a sf::Vector2f
sf::Vector2f normalize(const sf::Vector2f &v)
{
    return v * Q_rsqrt(v.x * v.x + v.y * v.y);
}

// distance between two sf::Vector2f
float distance(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return Q_rsqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}
// closing header guard
#endif 