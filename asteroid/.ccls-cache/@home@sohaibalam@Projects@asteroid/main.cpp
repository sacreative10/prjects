#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#define WIDTH 800
#define HEIGHT 600

void WrapCoordinates(float ix, float iy, float& ox, float& oy)
{
    ox = ix;
    oy = iy;
    if (ix < 0)
        ox += WIDTH;
    if (ix > WIDTH)
        ox -= WIDTH;
    if (iy < 0)
        oy += HEIGHT;
    if (iy > HEIGHT )
        oy -= HEIGHT;
}

void goodwrap(float x, float y)
{
    WrapCoordinates(x, y, x, y);
}

class Asteroid : public sf::Drawable
{
public:
    Asteroid(const sf::Vector2f& position, const sf::Vector2f& velocity, const float radius)
        : m_position(position)
        , m_velocity(velocity)
        , m_radius(radius)
    {
        m_shape.setRadius(radius);
        m_shape.setOrigin(radius, radius);
        m_shape.setPosition(position);
        m_shape.setFillColor(sf::Color::White);
    }
    void Update()
    {
        m_shape.setPosition(m_position);
    }
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            goodwrap(m_position.x, m_position.y);
            target.draw(m_shape, states);
        }
    sf::CircleShape m_shape;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_radius;
};


struct Spaceobject 
{
    float x, y;
    float dx, dy;

    int Size;
};


std::vector<Spaceobject> asteroids;


int main(int, char**) {
    std::cout << "Hello, world!\n";
    asteroids.push_back({20, 20, 8, -6, (int)64});
    // delta time
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time deltaTime = clock.restart();

        window.clear();

        for(auto& a : asteroids)
        {
            a.x += a.dx * deltaTime.asSeconds();
            a.y += a.dy * deltaTime.asSeconds();
            WrapCoordinates(a.x, a.y, a.x, a.y);
            for(int x = 0; x < a.Size; x++)
            {
                for(int y = 0; y < a.Size; y++)
                {
                    float fx, fy;
                    WrapCoordinates(a.x + x, a.y + y, fx, fy);
                    Asteroid asteroid(sf::Vector2f(fx, fy), sf::Vector2f(0, 0), (float)a.Size / 2);
                    asteroid.Update();
                    window.draw(asteroid);
                }
            }
        }
        window.display();
    }
}
