#include "PlayerGUI.hpp"

PlayerGUI::PlayerGUI(Player *player)
    : hpBar(10.f, 10.f, 300.f, ProgressBarType::LARGE, this->font, sf::Color(50, 50, 50, 200), sf::Color(250, 20, 20, 200)),
      levelBar(10.f, 65.f, 400.f, ProgressBarType::THICK, this->font, sf::Color(50, 50, 50, 200), sf::Color(20, 20, 250, 200))
{
    this->player = player;
    this->initFont();
    this->hpBar.setProgressBarMode(ProgressBarMode::ABSOLUTE);
    this->levelBar.setProgressBarMode(ProgressBarMode::FRAC);
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::initFont()
{
    this->font.loadFromFile("src/fonts/FreeSans.ttf");
}

void PlayerGUI::update(const float &dt)
{
    this->hpBar.update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax);
    this->levelBar.update(2, 3);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->hpBar.render(target);
    this->levelBar.render(target);
}