#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

class Player : public Entity
{
private:
    //Variables

    //Initializers
    void initVariables();

    void playAnimations(const float& dt);

public:
    Player(float x, float y, sf::Texture* textureSheet);
    virtual ~Player();
    virtual void update(const float& dt);


};

#endif
