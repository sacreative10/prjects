#pragma once
// this class is a renderer for the game, it uses SFML to render to the screen
// it also handles the input for the game
// it is a singleton class
#include <SFML/Graphics.hpp>

// game state
#include "GameState.h"
// object
#include "Object.h"

// this is the class that handles the rendering of the raycasting game
class Renderer
{
  public:
    // this is the constructor for the renderer
    // it initializes the SFML window
    Renderer(int width, int height, std::string title);
    // this is the destructor for the renderer
    // it closes the SFML window
    ~Renderer();
    // this method is used to render the game
    // it takes in the game state and the objects to render
    void render(GameState *gameState, std::vector<Object *> objects);
    // this method is used to handle the input for the game
    // it is a procedure that takes in the game state and the input
    void handleInput(GameState *gameState, sf::Event event);
    // this method is used to get the SFML window
    // it returns the SFML window
    sf::RenderWindow *getWindow();

  private:
    // this is the SFML window
    sf::RenderWindow *window;
};