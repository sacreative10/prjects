// this file holds the declaration of the Pipe class
#pragma once
#include "renderer.h"
#include "bird.h"

class Pipe{
    public:
        float top;
        float bottom;
        float x;
        float width;
        float speed = 2;
        Pipe(float x);
        void update(Bird &bird, bool &reset);
        void draw(sf::RenderWindow &window);
        // check if the bird has collided with the pipe
        bool checkCollision(Bird &bird);
};
