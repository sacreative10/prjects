#include "renderer.h"

class Blackhole
{
  public:
    Blackhole(float x, float y);
    ~Blackhole();

    void draw();

    sf::Vector2f position; // Position of the blackhole
    float schwarzschildradius; // in m
private:
    float mass;
};
