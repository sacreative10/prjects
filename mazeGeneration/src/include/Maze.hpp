#include "Renderer.hpp"

#include "mazeCell.hpp"

#include <vector>

namespace Maze {
	enum class GenerationType{
		DepthFirstBacktracker,
	};
	struct maze{
		std::vector<std::vector<MazeCell::Mazecell>> m_maze;
		std::vector<MazeCell::Mazecell* > stack;
		GenerationType m_GenerationType;
		MazeCell::Mazecell *currentCell;
		maze(int width, int height, GenerationType generationType);
		void update();
		void draw(Renderer& renderer);
		void DepthFirstBacktracker();
	};
	maze generateMaze(int width, int height, GenerationType generationType);
} // namespace Maze
