#ifndef PLAYER_GUI_H
#define PLAYER_GUI_H

#include "../entities/Player.hpp"
#include "../headers/headers.hpp"
#include "./progressBar/progressBar.hpp"

class PlayerGUI
{
private:
    Player *player;
    sf::Font font;
    float hpBarMaxWidth;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;
    sf::Text hpBarValue;

    progressBar hpBar;

    void initFont();

public:
    PlayerGUI(Player *player);
    virtual ~PlayerGUI();

    void updateHPBar();
    void update(const float &dt);

    void renderHPBar(sf::RenderTarget &target);
    void render(sf::RenderTarget &target);
};

#endif