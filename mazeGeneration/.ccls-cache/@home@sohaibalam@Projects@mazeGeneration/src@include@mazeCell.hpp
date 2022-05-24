#pragma once
#include "Renderer.hpp"

#include <vector>
namespace MazeCell
{
struct Mazecell
{
    int x;
    int y;
    bool visited;
    std::vector<bool> walls;
    Mazecell(int x, int y);
    void drawCell(Renderer &renderer);
    Mazecell *getValidNeighbor(std::vector<std::vector<Mazecell>> &maze);
    void removeWallWith(Mazecell *cell);
};
} // namespace MazeCell
