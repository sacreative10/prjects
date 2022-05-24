#include "include/object.h"
#include "include/wall.h"
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // create a new renderer with anti-aliasing enabled
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, sf::ContextSettings(24));
    window.setFramerateLimit(60);
    // create a bunch of walls
    srand(time(NULL));
    std::vector<Wall> walls;
    // push back 8 walls in random positions
    for (int i = 0; i < 8; i++)
    {
        walls.push_back(Wall(sf::Vector2f(rand() % 800, rand() % 600), sf::Vector2f(rand() % 800, rand() % 600)));
    }
    Object object(sf::Vector2f(400, 300), sf::Vector2f(1, 0));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseMoved)
            {
                object.updatePos(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            }
        }
        window.clear();
        // draw the walls
        for (auto &wall : walls)
        {
            wall.draw(window);
        }
        window.display();
    }
    return 0;
}