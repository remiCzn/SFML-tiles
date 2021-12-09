#include "PlayerGUI.hpp"

PlayerGUI::PlayerGUI(Player *player) : hpBar(10.f, 10.f, 300.f, ProgressBarType::LARGE, this->font, sf::Color(50, 50, 50, 200), sf::Color(250, 20, 20, 200))
{
    this->player = player;
    this->initFont();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::initFont()
{
    this->font.loadFromFile("fonts/FreeSans.ttf");
}

void PlayerGUI::update(const float &dt)
{
    this->updateHPBar();
}

void PlayerGUI::updateHPBar()
{
    this->hpBar.update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hp);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->hpBar.render(target);
}