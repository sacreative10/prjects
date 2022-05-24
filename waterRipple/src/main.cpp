#include <SFML/Graphics.hpp>

// define some constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "2D Water Ripple"

// quick handy function to swap the two buffers
void swap(std::vector<std::vector<float>> &a,
	  std::vector<std::vector<float>> &b) {
	std::vector<std::vector<float>> temp = a;
	a = b;
	b = temp;
}

std::vector<std::vector<float>> Buffer1;  // buffer for the current frame
std::vector<std::vector<float>> Buffer2;  // buffer for the next frame
float damping = 0.95;			  // damping factor

int main() {
	// create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
				WINDOW_TITLE);
	window.setFramerateLimit(120);
	// initialization of buffers go here
	Buffer1.resize(WINDOW_WIDTH, std::vector<float>(WINDOW_HEIGHT, 0.0f));
	Buffer2.resize(WINDOW_WIDTH, std::vector<float>(WINDOW_HEIGHT, 0.0f));
	// further initialization goes here
	sf::Uint8 *pixels = new sf::Uint8[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
	sf::Texture texture;
	if (!texture.create(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		return EXIT_FAILURE;
	}
	sf::Sprite sprite;
	// gameloop
	while (window.isOpen()) {
		// event handling
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Buffer2[event.mouseButton.x][event.mouseButton.y] = 255.0f;
			}
		}
		// computations for all pixels other than the borders
		for (int x = 1; x < WINDOW_WIDTH - 1; x++) {
			for (int y = 1; y < WINDOW_HEIGHT - 1; y++) {
				Buffer1[x][y] =
				    (Buffer2[x - 1][y] + Buffer2[x + 1][y] +
				     Buffer2[x][y - 1] + Buffer2[x][y + 1]) /
					2.0f -
				    Buffer1[x][y];
				Buffer1[x][y] *= damping;
				// update the pixel values
				pixels[(y * WINDOW_WIDTH + x) * 4] =
				    static_cast<sf::Uint8>(Buffer1[x][y] * 255);
				pixels[(y * WINDOW_WIDTH + x) * 4 + 1] =
				    static_cast<sf::Uint8>(Buffer1[x][y] * 255);
				pixels[(y * WINDOW_WIDTH + x) * 4 + 2] =
				    static_cast<sf::Uint8>(Buffer1[x][y] * 255);
				pixels[(y * WINDOW_WIDTH + x) * 4 + 3] = 255;
			}
		}
		// update the texture
		texture.update(pixels);
		// draw the texture
		sprite.setTexture(texture);
		window.clear();
		window.draw(sprite);
		window.display();
		// swap the buffers
		swap(Buffer1, Buffer2);
	}
}

