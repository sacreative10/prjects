#include "include/mazeCell.hpp"

MazeCell::Mazecell::Mazecell(int x, int y)
{
    this->x = x;
    this->y = y;
    this->visited = false;
    this->walls.resize(4);
    for (int i = 0; i < 4; i++)
    {
        this->walls[i] = true;
    }
}

void MazeCell::Mazecell::drawCell(Renderer &renderer)
{
    float x_ = this->x * MAZE_CELL_SIZE;
    float y_ = this->y * MAZE_CELL_SIZE;
    // see if walls are there if so draw them
    if (this->walls[0])
    {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x_, y_)), sf::Vertex(sf::Vector2f(x_ + MAZE_CELL_SIZE, y_))};
        renderer.draw(line, 2, sf::Lines);
    }
    if (this->walls[1])
    {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x_ + MAZE_CELL_SIZE, y_)),
                             sf::Vertex(sf::Vector2f(x_ + MAZE_CELL_SIZE, y_ + MAZE_CELL_SIZE))};
        renderer.draw(line, 2, sf::Lines);
    }
    if (this->walls[2])
    {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x_ + MAZE_CELL_SIZE, y_ + MAZE_CELL_SIZE)),
                             sf::Vertex(sf::Vector2f(x_, y_ + MAZE_CELL_SIZE))};
        renderer.draw(line, 2, sf::Lines);
    }
    if (this->walls[3])
    {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x_, y_ + MAZE_CELL_SIZE)), sf::Vertex(sf::Vector2f(x_, y_))};
        renderer.draw(line, 2, sf::Lines);
    }
    if (this->visited)
    {
        // if visited draw a red square
        sf::RectangleShape square(sf::Vector2f(MAZE_CELL_SIZE, MAZE_CELL_SIZE));
        square.setFillColor(sf::Color::Red);
        square.setPosition(x_, y_);
        renderer.draw(square);
    }
}

MazeCell::Mazecell *MazeCell::Mazecell::getValidNeighbor(std::vector<std::vector<Mazecell>> &maze)
{
    std::vector<Mazecell *> validNeighbours;
    // check if there are any valid neighbours
    if (this->x > 0 && !maze[this->x - 1][this->y].visited)
    {
        validNeighbours.push_back(&maze[this->x - 1][this->y]);
    }
    if (this->y > 0 && !maze[this->x][this->y - 1].visited)
    {
        validNeighbours.push_back(&maze[this->x][this->y - 1]);
    }
    if (this->x < MAZE_WIDTH - 1 && !maze[this->x + 1][this->y].visited)
    {
        validNeighbours.push_back(&maze[this->x + 1][this->y]);
    }
    if (this->y < MAZE_HEIGHT - 1 && !maze[this->x][this->y + 1].visited)
    {
        validNeighbours.push_back(&maze[this->x][this->y + 1]);
    }
    // if there are no valid neighbours return null
    if (validNeighbours.size() == 0)
    {
        return nullptr;
    }
    // otherwise return a random valid neighbour
    srand(time(NULL)); 
    int randomIndex = rand() % validNeighbours.size();
    return validNeighbours[randomIndex];
}

void MazeCell::Mazecell::removeWallWith(Mazecell *cell)
{
    if (cell->x == this->x && cell->y == this->y - 1)
    {
        this->walls[0] = false;
        cell->walls[2] = false;
    }
    else if (cell->x == this->x && cell->y == this->y + 1)
    {
        this->walls[2] = false;
        cell->walls[0] = false;
    }
    else if (cell->x == this->x - 1 && cell->y == this->y)
    {
        this->walls[1] = false;
        cell->walls[3] = false;
    }
    else if (cell->x == this->x + 1 && cell->y == this->y)
    {
        this->walls[3] = false;
        cell->walls[1] = false;
    }
}
