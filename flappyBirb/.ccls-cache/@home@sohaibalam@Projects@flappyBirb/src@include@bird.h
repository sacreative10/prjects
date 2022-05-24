#pragma once
#include "renderer.h"
#include "NeuralNetwork.h"
// This is the bird class for flappy bird.
class Bird
{
    public:
        float y;
        float x;
        float velocity;
        Bird(float x, float y);
        bool update();
        void draw(sf::RenderWindow &window);
        void jump();
        void think(float pipe_x, float pipe_top, float pipe_bottom);
        NeuralNetwork brain;
};
