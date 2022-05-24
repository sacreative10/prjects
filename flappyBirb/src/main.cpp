#include "include/renderer.h"
#include "include/bird.h"
#include "include/Pipe.h"

#include <vector>
bool reset = false;
bool bird_reset = false;
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Flappy Bird");
    window.setFramerateLimit(60);
    Bird bird(25, 0);
    std::vector<Pipe> pipes;   
    pipes.push_back(Pipe(WIDTH));
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        bird.jump();
                    }
                    break;
            }
        
        }
        if(reset || bird_reset)
        {
            bird.y = HEIGHT/2;
            bird.velocity = 0;
            pipes.clear();
            pipes.push_back(Pipe(WIDTH));
            reset = false;
        }
        // add pipes to the screen if the pipe is off the screen
        window.clear();
        for(auto &pipe : pipes)
        {
            pipe.draw(window);
            pipe.update(bird, reset);
            if(pipe.x < -20)
            {
                pipes.push_back(Pipe(WIDTH));
                pipes.erase(pipes.begin());
                
            }
        }
        bird.draw(window);
        window.display();
        bird_reset = bird.update();
        bird.think(pipes[0].x, pipes[0].top, pipes[0].bottom);
    }

    return 0;
}