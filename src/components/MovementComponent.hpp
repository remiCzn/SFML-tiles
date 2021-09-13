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

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MovementComponent
{
private:
    sf::Sprite* sprite;

    sf::Vector2f velocity;

    float maxVelocity;
    float acceleration;
    float deceleration;
    
public:
    MovementComponent(
        sf::Sprite* sprite,
        float maxVelocity, 
        float acceleration, 
        float decceleration
    );
    virtual ~MovementComponent();

    void move(const float dir_x, const float dir_y, const float dt);
    void update(const float& dt);

    const sf::Vector2f & getVelocity() const;
};

#endif