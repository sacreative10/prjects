// this file holds the renderer class implementation
// Author: S Alam
// Date: 02/4/2022

#include "Renderer.h"
///
//@brief: the constructor for the renderer class
//@param: width - the width of the window
//@param: height - the height of the window
//@param: title - the title of the window
//@return: none
Renderer::Renderer(int width, int height, std::string title)
{
    // create the window object
    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    // set the vertical sync enabled to true
    window->setVerticalSyncEnabled(true);
    // set the framerate limit to 60
    window->setFramerateLimit(60);
    // set the instance variable to this object
    instance = this;
}

//@brief: the destructor for the renderer class
//@param: none
//@return: none
Renderer::~Renderer()
{
    // delete the window object
    delete window;
}

//@brief: the render function for the renderer class, it takes in a vector of drawable objects
//@param: objects - a vector of drawable objects
//@return: none
void Renderer::render(std::vector<sf::Drawable *> objects)
{
    // clear the window
    window->clear();
    // loop through the objects vector
    for (int i = 0; i < objects.size(); i++)
    {
        // draw the object
        window->draw(*objects[i]);
    }
    // display the window
    window->display();
}

//@brief: handles the window events
//@param: none
//@return: none
void Renderer::handleEvents()
{
    // create an event object
    sf::Event event;
    // loop through the events
    while (window->pollEvent(event))
    {
        // handle the events
        handleInput(event);
    }
}

//@brief: handles the input
//@param: event - the event object
//@return: none
void Renderer::handleInput(sf::Event &event)
{
    // if the event is a close event
    if (event.type == sf::Event::Closed)
    {
        // close the window
        window->close();
    }
}

//@brief: the getInstance function for the renderer class
//@param: none
//@return: a pointer to the renderer object
Renderer *Renderer::getInstance()
{
    // return the instance variable
    return instance;
}

//@brief: the getWindow function for the renderer class
//@param: none
//@return: a pointer to the sfml window object
sf::RenderWindow *Renderer::getWindow()
{
    // return the window variable
    return window;
}