#include "include/Renderer.hpp"

Renderer::Renderer(int width, int height, std::string title) : sf::RenderWindow(sf::VideoMode(width, height), title)
{
    this->setFramerateLimit(60);
}

Renderer::~Renderer()
{
}