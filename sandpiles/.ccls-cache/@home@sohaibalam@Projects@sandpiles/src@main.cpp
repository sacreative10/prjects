#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define WIN_WIDTH 400
#define WIN_HEIGHT 400

std::vector<std::vector<int>> grid;

void topple(std::vector<std::vector<int>> &grid)
{
    std::vector<std::vector<int>> newGrid;
    newGrid.resize(grid.size());
    for (int i = 0; i < grid.size(); i++)
    {
        newGrid[i].resize(grid[i].size());
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] < 4)
            {
                newGrid[i][j] = grid[i][j];
            }
        }
    }
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            int sandAmount = grid[i][j];
            if (sandAmount >= 4)
            {
                newGrid[i][j] += (sandAmount - 4);
                newGrid[i + 1][j]++;
                newGrid[i - 1][j]++;
                newGrid[i][j + 1]++;
                newGrid[i][j - 1]++;
            }
        }
    }
    grid = newGrid;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Sandpile");
    window.setFramerateLimit(60);
    grid.resize(WIN_WIDTH);
    for (int i = 0; i < WIN_WIDTH; i++)
    {
        grid[i].resize(WIN_HEIGHT);
        for (int j = 0; j < WIN_HEIGHT; j++)
        {
            grid[i][j] = 0;
        }
    }
    grid[WIN_WIDTH / 2][WIN_HEIGHT / 2] = 100000;
    sf::Uint8 *pixels = new sf::Uint8[WIN_WIDTH * WIN_HEIGHT * 4];
    sf::Texture texture;
    texture.create(WIN_WIDTH, WIN_HEIGHT);
    sf::Sprite sprite;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        for (int i = 0; i < WIN_WIDTH; i++)
        {
            for (int j = 0; j < WIN_HEIGHT; j++)
            {
                int sandAmount = grid[i][j];
                sf::Color color = sf::Color(255, 255, 255);
                if (sandAmount == 0)
                {
                    color = sf::Color(0, 0, 0);
                }
                else if (sandAmount == 1)
                {
                    color = sf::Color(255, 0, 255);
                }
                else if (sandAmount == 2)
                {
                    color = sf::Color(0, 255, 255);
                }
                else if (sandAmount == 3)
                {
                    color = sf::Color(0, 255, 0);
                }
                pixels[(i + j * WIN_WIDTH) * 4] = color.r;
                pixels[(i + j * WIN_WIDTH) * 4 + 1] = color.g;
                pixels[(i + j * WIN_WIDTH) * 4 + 2] = color.b;
                pixels[(i + j * WIN_WIDTH) * 4 + 3] = color.a;
            }
        }
        texture.update(pixels);
        sprite.setTexture(texture);
        window.clear();
        window.draw(sprite);
        window.display();
        topple(grid);
    }
}