#ifndef MOVE_COMPO_H
#define MOVE_COMPO_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <math.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum movement_states {
    IDLE_DOWN = 0,
    IDLE_LEFT,
    IDLE_RIGHT,
    IDLE_UP,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class MovementComponent
{
private:
    sf::Sprite* sprite;

    sf::Vector2f velocity;

    float maxVelocity;
    float acceleration;
    float deceleration;

    short state;
    
public:
    MovementComponent(
        sf::Sprite* sprite,
        float maxVelocity, 
        float acceleration, 
        float decceleration
    );
    virtual ~MovementComponent();

    const short getState() const;

    const float& getMaxVelocity() const;

    void move(const float dir_x, const float dir_y, const float dt);
    void update(const float& dt);

    const sf::Vector2f & getVelocity() const;
};

#endif