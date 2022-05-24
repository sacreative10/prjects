// this file is the implementation of the Bird class
// the declaration of the Bird class is in src/include/bird.h

#include "include/bird.h"
#include "include/NeuralNetwork.h"
#include "include/renderer.h"

#include <iostream>

// remove static assert
#define NDEBUG

// initialize the Bird class with neural network
Bird::Bird(float x, float y) : brain({4, 4, 1})
{
    this->x = x;
    this->y = y;
}

void Bird::think(float pipe_x, float pipe_top, float pipe_bottom)
{
    std::vector<float> data = {y/HEIGHT, pipe_x / WIDTH, pipe_top / HEIGHT, pipe_bottom / HEIGHT};
    std::vector<RowVector *> inputs;
    std::vector<RowVector *> outputs;
    outputs.push_back(new RowVector(4));
    inputs.push_back(new RowVector(4));
    // input 1 is the bird's y position
    // inout 2 is the x location of the closest pipe
    // input 3 is the y location of the top of closest pipe
    // input 4 is the y location of the bottom of closest pipe
    // set the inputs
    for(int i = 0; i < 4; i++)
    {
        inputs[0]->coeffRef(1, i) = data[i];
    }
    // feed the neural network the inputs using the brain.train() function
    auto test = brain.train(inputs, outputs);
    // jump if the output is greater than 0.5
    std::cout << test[0] << std::endl;
}

bool Bird::update()
{

    if (this->y < 0 || this->y > HEIGHT)
    {
        return true;
    }
    this->velocity += 0.1;
    this->y += this->velocity;
    return false;
}

void Bird::draw(sf::RenderWindow &window)
{
    sf::CircleShape shape(16.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(this->x, this->y);
    window.draw(shape);
}

void Bird::jump()
{
    this->velocity = -2.5;
}
