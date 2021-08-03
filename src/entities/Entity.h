#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:
    /* data */
protected:
     sf::RectangleShape shape;
     float moveSpeed;
public:
    Entity(/* args */);
    virtual ~Entity();

    virtual void move(const float& dt, const float x, const float y);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);
};

#endif