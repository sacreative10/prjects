#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
    float time = 0.0f;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fourier Series");
    // setup
    float radius = 100.f;
    sf::Vector2f circlePos = sf::Vector2f(200, 200);
    std::vector<float> pointsofWave; 

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float x = radius * cos(time);
        float y = radius * sin(time);
        pointsofWave.push_back(y);
        sf::CircleShape miniCircle(8);
        miniCircle.setFillColor(sf::Color::Red);
        miniCircle.setPosition(circlePos.x + x, circlePos.y + y);
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(circlePos.x, circlePos.y), sf::Color::Red),
            sf::Vertex(sf::Vector2f(circlePos.x + x + 8, circlePos.y + y + 8), sf::Color::Red)
        };
        window.clear();
        window.draw(line, 2, sf::Lines);
        window.draw(miniCircle);
        for(int i = 0; i < pointsofWave.size(); i++)
        {
            std::vector<sf::Vertex> line;
            line.push_back(sf::Vertex(sf::Vector2f(i, pointsofWave[i]), sf::Color::Red));
        }
        window.display();
        time += 0.001f;
    }
    return 0;
}
