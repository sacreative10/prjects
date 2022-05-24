#include "include/Maze.hpp"

Maze::maze::maze(int x, int y, GenerationType generationType)
{
    this->m_GenerationType = generationType;
    for (int i = 0; i < x; i++)
    {
        std::vector<MazeCell::Mazecell> row;
        for (int j = 0; j < y; j++)
        {
            MazeCell::Mazecell mazecell(i, j);
            row.push_back(mazecell);
        }
        this->m_maze.push_back(row);
    }
}

void Maze::maze::update()
{
    this->currentCell->visited = true;
    switch (this->m_GenerationType)
    {
    case GenerationType::DepthFirstBacktracker:
        this->DepthFirstBacktracker();
        break;
    }
}

void Maze::maze::draw(Renderer &renderer)
{
    for (int i = 0; i < this->m_maze.size(); i++)
    {
        for (int j = 0; j < this->m_maze[i].size(); j++)
        {
            this->m_maze[i][j].drawCell(renderer);
        }
    }
}

void Maze::maze::DepthFirstBacktracker()
{
	MazeCell::Mazecell *nextCell = this->currentCell->getValidNeighbor(this->m_maze);
	if (nextCell != nullptr)
	{
		nextCell->visited = true;
        // add to stack
        this->stack.push_back(this->currentCell);
		this->currentCell->removeWallWith(nextCell);
		this->currentCell = nextCell;
	} else if (this->stack.size() > 0)
	{
		this->currentCell = this->stack.back();
		this->stack.pop_back();
	}
}


Maze::maze Maze::generateMaze(int width, int height, GenerationType generationType)
{
    Maze::maze maze(width, height, generationType);
    return maze;
}