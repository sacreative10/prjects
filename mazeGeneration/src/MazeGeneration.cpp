#include "include/Maze.hpp"
#include "include/Renderer.hpp"
#include "include/mazeCell.hpp"

// std::async is a C++11 feature. include it
#include <future>

int main()
{
    // multithread the initialization of the maze
    auto maze_ = std::async(std::launch::async, Maze::generateMaze, WINDOW_WIDTH, WINDOW_HEIGHT, Maze::GenerationType::DepthFirstBacktracker);
    Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT, "Maze Generator");
    while (renderer.isOpen())
    {
        sf::Event event;
        while (renderer.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderer.close();
            }
        }
        renderer.clear();
        maze_.get().draw(renderer);
        renderer.display();
    }
}
