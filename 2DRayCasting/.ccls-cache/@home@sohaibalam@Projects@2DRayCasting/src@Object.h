#pragma once
// this file is the header file for the Object class
// Language: cpp

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "renderer.h"

// all the object class is a class that is used to store the information about the objects in the game
// it stores the position
// it also has a method to draw the object
// it has a method to update the object

class Object : public sf::Drawable
{
  public:
    // this is the constructor for the object class
    // it takes in the position of the object
    Object(sf::Vector2f position);
    // this is the destructor for the object class
    ~Object();
    // this method is used to draw the object
    // it takes in the renderer and the game state
    void draw(Renderer *renderer);
    // this method is used to update the object
    // it takes in the game state
    void update(GameState *gameState);
    // this method is used to get the position of the object
    // it returns the position of the object
    sf::Vector2f getPosition();
    // this method is used to set the position of the object
    // it takes in the position of the object
    void setPosition(sf::Vector2f position);

  private:
    // this is the position of the object
    sf::Vector2f position;
    void virtual draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};
