#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
sf::Vector2f VecMult(sf::Vector2f vec, float scalar);
float DegreesToRadians(float degrees);
sf::Vector2f VectorfromAngle(float angle);
float distance(sf::Vector2f a, sf::Vector2f b);