#include "./gui.hpp"

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, 
    float gridSize, const sf::Texture* texture_sheet,
    sf::Font& font, std::string text)
    : keyTimeMax(1.f), keytime(0.f)
{
    this->gridSize = gridSize;
    this->active = false;
    this->hidden = false;
    float offset = 100.f;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x + offset,y);
    this->bounds.setFillColor(sf::Color(50,50,50,100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));

    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x + offset, y);

    if(this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width) {
        this->sheet.setTextureRect(sf::IntRect(0,0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
    }
    if(this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height) {
        this->sheet.setTextureRect(sf::IntRect(0,0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
    }

    this->selector.setPosition(x + offset,y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

    this->textureRect.width = static_cast<int>(gridSize);
    this->textureRect.height = static_cast<int>(gridSize);

    this->hide_btn = new gui::Button(
        x, y, 50.f, 50.f,
        text, &font, 30,
        sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0),
        sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
        sf::Color(70,70,70,120), sf::Color(200,200,200,100), sf::Color(20,20,20,25), 0
    );
}

gui::TextureSelector::~TextureSelector(){
    delete this->hide_btn;
}

const bool& gui::TextureSelector::getActive() const {
    return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const {
    return this->textureRect;
}
const bool gui::TextureSelector::getKeytime() {
    if(this->keytime >= this->keyTimeMax)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

void gui::TextureSelector::updateKeytime(const float& dt) {
    if(this->keytime < this->keyTimeMax)
        this->keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt) {
    this->updateKeytime(dt);
    this->hide_btn->update(mousePosWindow);
    
    if(this->hide_btn->isClicked() && this->getKeytime())
    {
        this->hidden = !this->hidden;
    }

    if(!this->hidden)
    {
        if(this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
            this->active = true;
        else 
            this->active = false;

        if(this->active) {
            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

            this->selector.setPosition(
                this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
            );

            this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget& target) {
    if(!this->hidden) {
        target.draw(this->bounds);
        target.draw(this->sheet);

        if(this->active)
            target.draw(this->selector);
    }

    this->hide_btn->render(&target);
}