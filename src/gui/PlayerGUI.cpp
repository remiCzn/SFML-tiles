#include "PlayerGUI.hpp"

PlayerGUI::PlayerGUI(Player *player)
{
    this->player = player;
    this->initFont();
    this->initHPBar();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::initFont()
{
    this->font.loadFromFile("fonts/FreeSans.ttf");
}

void PlayerGUI::initHPBar()
{
    float width = 300.f;
    float height = 50.f;
    float x = 10.f;
    float y = 10.f;

    this->hpBarMaxWidth = width;

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->hpBarBack.setOutlineColor(sf::Color::White);
    this->hpBarBack.setOutlineThickness(1.f);
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
    this->hpBarInner.setOutlineColor(sf::Color::White);
    this->hpBarInner.setOutlineThickness(1.f);
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());

    this->hpBarValue.setFont(this->font);
    this->hpBarValue.setCharacterSize(18);
    this->hpBarValue.setString("100%");
    this->hpBarValue.setPosition(x + width / 2.f - this->hpBarValue.getGlobalBounds().width / 2.f, y + height / 2.f - this->hpBarValue.getGlobalBounds().height / 2.f);
}

void PlayerGUI::update(const float &dt)
{
    this->updateHPBar();
}

void PlayerGUI::updateHPBar()
{
    float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);
    this->hpBarValue.setString(std::to_string(static_cast<int>(percent * 100)).append("%"));
    this->hpBarInner.setSize(
        sf::Vector2f(
            static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
            this->hpBarInner.getSize().y));
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    this->renderHPBar(target);
}

void PlayerGUI::renderHPBar(sf::RenderTarget &target)
{
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
    target.draw(this->hpBarValue);
}