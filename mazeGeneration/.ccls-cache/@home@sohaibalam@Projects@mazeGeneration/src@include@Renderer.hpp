#pragma once
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAZE_CELL_SIZE 40
#define MAZE_WIDTH (WINDOW_WIDTH / MAZE_CELL_SIZE)
#define MAZE_HEIGHT (WINDOW_HEIGHT / MAZE_CELL_SIZE)

// sfml renderer class
class Renderer : public sf::RenderWindow
{
  public:
    Renderer(int width, int height, std::string title);
    ~Renderer();
};