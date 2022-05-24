#include <math.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>

// some global parameters
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const float DA = 1;  // diffusion rate of A
const float DB = 0.5;  // diffusion rate of B
const float f = 0.03;	  // feed rate
const float k = 0.06;	  // kill rate

// data structure to hold the cells for simulation
struct Cell {
	float A;
	float B;
};




std::vector<std::vector<Cell>> currentMomentGrid;
std::vector<std::vector<Cell>> nextMomentGrid;

void initialiseGrids(int width, int height,
		     std::vector<std::vector<Cell>> &currentMomentGrid,
		     std::vector<std::vector<Cell>> &nextMomentGrid) {
	currentMomentGrid.resize(width);
	nextMomentGrid.resize(width);
	for (int i = 0; i < width; i++) {
		currentMomentGrid[i].resize(height);
		nextMomentGrid[i].resize(height);
		for (int j = 0; j < height; j++) {
			currentMomentGrid[i][j].A = 1;
			currentMomentGrid[i][j].B = 0;

			nextMomentGrid[i][j].A = 1;
			nextMomentGrid[i][j].B = 0;
		}
	}
	for (int i = ((WINDOW_WIDTH / 2) - 50); i < ((WINDOW_WIDTH / 2) + 50);
	     i++) {
		for (int j = ((WINDOW_HEIGHT / 2) - 50);
		     j < ((WINDOW_HEIGHT / 2) + 50); j++) {
			currentMomentGrid[i][j].B = 1;
		}
	}
}


// swapping the grids every frame
void swap(std::vector<std::vector<Cell>> &currentMomentGrid, std::vector<std::vector<Cell>> &nextMomentGrid) {
	std::vector<std::vector<Cell>> temp = currentMomentGrid;
	currentMomentGrid = nextMomentGrid;
	nextMomentGrid = temp;
}

// finally the laplacian functions
// Though I am always looking for a better way to do this
float laplacianA(int i, int j,
		 std::vector<std::vector<Cell>> &currentMomentGrid) {
	float laplacian = 0;
	// main cell
	laplacian += currentMomentGrid[i][j].A * -1;
	// adjacent cells
	laplacian += currentMomentGrid[i - 1][j].A * 0.2;
	laplacian += currentMomentGrid[i + 1][j].A * 0.2;
	laplacian += currentMomentGrid[i][j - 1].A * 0.2;
	laplacian += currentMomentGrid[i][j + 1].A * 0.2;
	// diagonal cells
	laplacian += currentMomentGrid[i - 1][j - 1].A * 0.05;
	laplacian += currentMomentGrid[i + 1][j - 1].A * 0.05;
	laplacian += currentMomentGrid[i - 1][j + 1].A * 0.05;
	laplacian += currentMomentGrid[i + 1][j + 1].A * 0.05;
	return laplacian;
}

float laplacianB(int i, int j,
		 std::vector<std::vector<Cell>> &currentMomentGrid) {
	float laplacian = 0;
	// main cell
	laplacian += currentMomentGrid[i][j].B * -1;
	// adjacent cells
	laplacian += currentMomentGrid[i - 1][j].B * 0.2;
	laplacian += currentMomentGrid[i + 1][j].B * 0.2;
	laplacian += currentMomentGrid[i][j - 1].B * 0.2;
	laplacian += currentMomentGrid[i][j + 1].B * 0.2;
	// diagonal cells
	laplacian += currentMomentGrid[i - 1][j - 1].B * 0.05;
	laplacian += currentMomentGrid[i + 1][j - 1].B * 0.05;
	laplacian += currentMomentGrid[i - 1][j + 1].B * 0.05;
	laplacian += currentMomentGrid[i + 1][j + 1].B * 0.05;
	return laplacian;
}

void computeUpdate(std::vector<std::vector<Cell>> &currentMomentGrid,
		   std::vector<std::vector<Cell>> &nextMomentGrid) {
	for (int i = 1; i < WINDOW_WIDTH - 1; i++) {
		for (int j = 1; j < WINDOW_HEIGHT - 1; j++) {
			float A0 = currentMomentGrid[i][j].A;
			float B0 = currentMomentGrid[i][j].B;
			float A1 =
			    A0 + (DA * laplacianA(i, j, currentMomentGrid) -
				  (A0 * B0 * B0) + (f * (1 - A0))) *
				     1.0;
			float B1 =
			    B0 + (DB * laplacianB(i, j, currentMomentGrid) +
				  (A0 * B0 * B0) - ((k + f) * B0)) *
				     1.0;
			nextMomentGrid[i][j].A = A1;
			nextMomentGrid[i][j].B = B1;
		}
	}
}

int main() {
	sf::RenderWindow window(
	    sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
	    "Reaction Diffusion Algorithm - Gray-Scott Model");
	window.setFramerateLimit(2000);
	initialiseGrids(WINDOW_WIDTH, WINDOW_HEIGHT, currentMomentGrid,
			nextMomentGrid);
	sf::Uint8 *pixels = new sf::Uint8[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
	sf::Texture texture;
	sf::Sprite sprite;
	if (!texture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		std::cout << "Error creating texture" << std::endl;
		return -1;
	}

	// the way to show the grids is to
	// 1. compute the next moment
	// 2. display the next moment
	// 3. swap the grids
	// 4. repeat
	// run every frame
	while (window.isOpen()) {
		sf::Clock clock;
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		// compute the grids
		std::thread computeThread(computeUpdate,
					  std::ref(currentMomentGrid),
					  std::ref(nextMomentGrid));
		// render the grids
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				int pix = (i + j * WINDOW_WIDTH) * 4;
				float a = currentMomentGrid[i][j].A;
				float b =  currentMomentGrid[i][j].B;
				float c = ((a - b) * 255);
				pixels[pix] = currentMomentGrid[i][j].A * 255;
				pixels[pix + 1] = currentMomentGrid[i][j].B * 255;
				pixels[pix + 2] = currentMomentGrid[i][j].B * 255;
				pixels[pix + 3] = currentMomentGrid[i][j].A * 255;
				//	pixels[pix] =
				//	    floor(currentMomentGrid[i][j].A *
				//255); 	pixels[pix + 1] = 0; 	pixels[pix + 2] =
				//	    floor(currentMomentGrid[i][j].B *
				//255); 	pixels[pix + 3] = 255;
			}
		}
		texture.update(pixels);
		sprite.setTexture(texture);
		window.draw(sprite);
		computeThread.join();
		// swap the grids
		swap(currentMomentGrid, nextMomentGrid);
		window.display();
	}
}
