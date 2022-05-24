// this file is the implementation file for the object class
// Language: cpp

#include "Object.h"

//@brief: this is the constructor for the object class
//@param: position - the position of the object
Object::Object(sf::Vector2f position)
{
    // this is the constructor for the object class
    // it takes in the position of the object
    this->position = position;
}

//@brief: this is the destructor for the object class
Object::~Object()
{
    // this is the destructor for the object class
    delete this;
}

//@brief: this method is used to draw the object
//@param: renderer - the renderer
//@param: gameState - the game state
void Object::draw(Renderer *renderer)
{
    // this method is used to draw the object
    // it takes in the renderer and the game state
    renderer->getWindow()->draw(*this);
}

//@brief: this method is used to update the object
//@param: gameState - the game state
void Object::update(GameState *gameState)
{
    // this method is used to update the object
    // it takes in the game state
}


//@brief: this method is used to get the position of the object
//@return: the position of the object
sf::Vector2f Object::getPosition()
{
    // this method is used to get the position of the object
    // it returns the position of the object
    return position;
}

//@brief: this method is used to set the position of the object
//@param: position - the position of the object
void Object::setPosition(sf::Vector2f position)
{
    // this method is used to set the position of the object
    // it takes in the position of the object
    this->position = position;
}

//@brief: this method is used to draw the object
//@param: target - the target
//@param: states - the states
void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // this method is used to draw the object
    // it takes in the target and the states
    target.draw(*this);
}