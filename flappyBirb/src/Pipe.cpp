// this file holds the implementation of the Pipe class
// the declaration of the Pipe class is in src/include/Pipe.h

#include "include/Pipe.h"

Pipe::Pipe(float x)
{
    srand(time(NULL));
    this->x = x;
    this->top = rand() % (HEIGHT/2);
    this->bottom = rand() % (HEIGHT/2);
    this->width = 20;
}

void Pipe::draw(sf::RenderWindow &window){
    sf::RectangleShape topPipe(sf::Vector2f(this->width, this->top));
    sf::RectangleShape bottomPipe(sf::Vector2f(this->width, this->bottom));
    topPipe.setPosition(this->x, 0);
    bottomPipe.setPosition(this->x, HEIGHT - this->bottom);
    topPipe.setFillColor(sf::Color::Red);
    bottomPipe.setFillColor(sf::Color::Red);
    window.draw(topPipe);
    window.draw(bottomPipe);
}

bool Pipe::checkCollision(Bird &bird){
    if(bird.x + 16 > this->x && bird.x < this->x + this->width){
        if(bird.y < this->top || bird.y > HEIGHT - this->bottom){
            return true;
        }
    }
    return false;
}

void Pipe::update(Bird &bird, bool &reset){
    this->x -= this->speed;
    if(this->checkCollision(bird)){
        reset = true;
    }    
}