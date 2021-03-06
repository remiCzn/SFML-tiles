#include "PauseMenu.hpp"

PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font *font)
{
    this->font = font;

    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.f,
            static_cast<float>(window.getSize().y) - 100.f));

    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
        30.f);

    this->pauseText.setFont(*font);
    this->pauseText.setFillColor(sf::Color(255, 255, 255, 200));
    this->pauseText.setCharacterSize(60);
    this->pauseText.setString("PAUSE");
    this->pauseText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 40.f);
}

PauseMenu::~PauseMenu()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void PauseMenu::update(const sf::Vector2i &mousePoseWindow)
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        it->second->update(mousePoseWindow);
    }
}

void PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);

    for (auto &i : this->buttons)
    {
        i.second->render(&target);
    }
    target.draw(this->pauseText);
}

std::map<std::string, gui::Button *> &PauseMenu::getButtons()
{
    return this->buttons;
}

const bool PauseMenu::isButtonPressed(std::string key)
{
    return this->buttons[key]->isClicked();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{

    float width = 250.f;
    float height = 65.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new gui::Button(
        x, y, width, height,
        text, this->font, 50);
}