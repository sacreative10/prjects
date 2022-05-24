#include "include/ray.h"
#include "include/util.h"
#include <cmath>

Ray::Ray(sf::Vector2f position, float radian_direction)
{
    this->position = position;
    // convert radians to degrees, and into a vector
    this->direction = sf::Vector2f(cos(radian_direction), sin(radian_direction));
}

void Ray::draw(sf::RenderWindow &window)
{
    // draw a line
    sf::Vertex line[] = {sf::Vertex(position, sf::Color::White),
                         sf::Vertex(position + direction * 50, sf::Color::White)};
    window.draw(line, 2, sf::Lines);
}

std::optional<sf::Vector2f> Ray::intersect(Wall wall)
{
    // using line-by-line intersection
    const float x1 = wall.start.x;
    const float y1 = wall.start.y;
    const float x2 = wall.end.x;
    const float y2 = wall.end.y;

    const float x3 = position.x;
    const float y3 = position.y;
    const float x4 = position.x + direction.x;
    const float y4 = position.y + direction.y;

    const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0)
        return std::nullopt;
    else
    {
        const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
        if (t >= 0 && t <= 1 && u >= 0)
            return sf::Vector2f(x1 + t * (x2 - x1), y1 + t * (y2 - y1));
        else
            return std::nullopt;
    }
}

void Ray::setDir(sf::Vector2f dir)
{
    this->direction.x = dir.x - position.x;
    this->direction.y = dir.y - position.y;
    // normalize
    auto norm_dir = normalize(this->direction);
    this->direction.x = norm_dir.x;
    this->direction.y = norm_dir.y;
}