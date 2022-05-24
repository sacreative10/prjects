#include <math.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define WIDTH 800
#define HEIGHT 600


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "LorenzSystem");
	sf::Event event;
	window.setFramerateLimit(60);
	float dt = 0.01f;
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
	float sigma = 10.0f;
	float beta = 8.0f / 3.0f;
	float rho = 28.0f;
	std::vector<sf::Vertex> vertices;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		std::cout << "here" << std::endl;
		float dx = sigma * (y - x);
		float dy = x * (rho - z) - y;
		float dz = x * y - beta * z;
		x += dx * dt;
		y += dy * dt;
		z += dz * dt;
		std::cout << x << " " << y << " " << z << std::endl;
		vertices.push_back(sf::Vertex(sf::Vector2f(5 * x + WIDTH/2, 5 * y + HEIGHT/2)));
		window.clear();
		window.draw(vertices.data(), vertices.size(), sf::LineStrip);
		window.display();
	}

	return 0;
}
