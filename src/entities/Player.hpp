#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

enum Direction {
    DOWN,
    LEFT,
    RIGHT,
    UP
};

class Player : public Entity
{
private:
    //Variables
    bool attacking;
    float attack_cooldown;

    short direction;

    //Initializers
    void initVariables();

    void playAnimations(const float& dt);

public:
    Player(float x, float y, sf::Texture* textureSheet);
    virtual ~Player();

    void update(const float& dt);
    void render(sf::RenderTarget& target, bool debugMode);

    void updateAttack(const float& dt);
    void updateAnimation(const float& dt);
};

#endif
