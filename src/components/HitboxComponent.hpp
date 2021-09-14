#ifndef HITBOX_COMP_H
#define HITBOX_COMP_H

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class HitboxComponent
{
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    float offsetX;
    float offsetY;

public:
    HitboxComponent(sf::Sprite &sprite, float offset_X, float offset_Y, float width, float height);
    virtual ~HitboxComponent();

    bool checkIntersect(const sf::FloatRect &frect);

    void update();
    void render(sf::RenderTarget &target);
};

#endif