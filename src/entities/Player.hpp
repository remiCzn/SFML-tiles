#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

enum Direction
{
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

    sf::RectangleShape rect;

    //Initializers
    void initVariables();

    void updateAnimation(const float& dt);
    void playAttackAnimation(std::string sprite_key, std::string hitbox_key, const float& dt);

public:
    Player(float x, float y, sf::Texture *textureSheet);
    virtual ~Player();

    void update(const float &dt);
    void render(sf::RenderTarget &target, bool debugMode);

    void updateAttack(const float &dt);

    AttributeComponent *getAttributeComponent();

    void loseHP(const int hp);
    void gainHP(const int hp);
    void gainExp(const int exp);
};

#endif
