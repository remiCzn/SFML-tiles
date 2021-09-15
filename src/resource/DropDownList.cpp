#include "gui.hpp"

gui::DropDownList::DropDownList(
    float x, float y, float width, float height,
            sf::Font* font, std::string list[],
            unsigned nrOfElements, unsigned default_index
) : showList(false), keytimeMax(1.f), keytime(0.f)
{
    this->font = font;
    for(size_t i = 0; i < nrOfElements; i++)
    {
        this->list.push_back(
            new gui::Button(
                x, y + (i * height), width, height,
                list[i], this->font, 12,
                sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200),
                sf::Color(255,255,255,150), sf::Color(255,255,255,255), sf::Color(20,20,20,50)
            )
        );
    }
    this->activeElement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList()
{
    delete this->activeElement;
    for(size_t i = 0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }
}

const bool gui::DropDownList::getKeyTime()
{
    if(this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void gui::DropDownList::updateKeytime(const float& dt)
{
    if(this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
    this->updateKeytime(dt);
    this->activeElement->update(mousePos);

    if(this->activeElement->isPressed() && this->getKeyTime())
    {
        this->showList = !this->showList;
    }
    
    if(this->showList)
    {
        for(auto &i : this->list)
            i->update(mousePos);
    }
}

void gui::DropDownList::render(sf::RenderTarget* target)
{
    this->activeElement->render(target);

    if(this->showList)
    {
        for(auto &i : this->list)
        {
            i->render(target);
        }
    }
}