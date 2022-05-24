#include "include/object.h"
#include <cmath>
#include <limits>

Object::Object(sf::Vector2f position, sf::Vector2f direction)
{
    this->position = position;
    this->direction = direction;
    for (int i = 0; i < 360; i += 10)
    {
        // push back a ray, direction in radians
        Ray ray(position, i * M_PI / 180);
        rays.push_back(ray);
    }
}

void Object::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle(10);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(10, 10);
    circle.setPosition(position);
    window.draw(circle);
}

void Object::updatePos(sf::Vector2f position)
{
    this->position = position;
    for (auto &ray : rays)
    {
        ray.position = position;
    }
}

void Object::raycast(std::vector<Wall> &wall, sf::RenderWindow &window)
{
    for (auto &ray : rays)
    {
        std::optional<sf::Vector2f> closest = std::nullopt;
        // for each ray, cast it to the walls
        for (auto &wall_ : wall)
        {
            auto record = std::numeric_limits<float>::infinity();
            auto point = ray.intersect(wall_);
            if (point)
            {
                auto distance_ = distance(position, point.value());
                if (distance_ < record)
                {
                    record = distance_;
                    closest = point;
                }
            }
        }
        if (closest)
        {
            sf::Vertex line[] = {sf::Vertex(position, sf::Color::White), sf::Vertex(closest.value(), sf::Color::White)};
            window.draw(line, 2, sf::Lines);
        }
    }
}