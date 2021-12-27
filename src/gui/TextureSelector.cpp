#include "./gui.hpp"

gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
                                      float gridSize,
                                      sf::Font &font, std::string text)
    : keyTimeMax(1.f), keytime(0.f)
{
    this->gridSize = gridSize;
    this->active = false;
    this->hidden = false;
    float offset = 60.f;

    this->scale = 2.f;

    this->bounds.setPosition(x + offset, y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    short index = 0;
    for (const auto e : TileTypeNs::All) {
        this->sheets.push_back(sf::Sprite());
        sf::Sprite& tile = this->sheets.back();
        tile.setTexture(*TileRegistry::Instance()->getTexture(e));
        tile.setTextureRect(sf::IntRect(0, 0, static_cast<int>(gridSize), static_cast<int>(gridSize)));
        tile.setPosition(x + offset + gridSize * this->scale * index, y);
        tile.scale(sf::Vector2f(scale, scale));

        index++;
    }

    index = 10;

    int cols = 4;
    int rows = (index/cols) + 1;

    this->bounds.setSize(sf::Vector2f(this->scale * cols * gridSize, this->scale * rows * gridSize));

    this->selector.setPosition(x + offset, y);
    this->selector.setSize(sf::Vector2f(gridSize * scale, gridSize * scale));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

    this->type = TileType::STONE;

    this->hide_btn = new gui::Button(
        0.f, 0.f, 60.f, 60.f,
        text, &font, 28,
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 120), sf::Color(200, 200, 200, 100), sf::Color(20, 20, 20, 25), 0);
}

gui::TextureSelector::~TextureSelector()
{
    delete this->hide_btn;
}

const bool &gui::TextureSelector::getActive() const
{
    return this->active;
}

const TileType& gui::TextureSelector::getType() const
{
    return this->type;
}

const bool gui::TextureSelector::getKeytime()
{
    if (this->keytime >= this->keyTimeMax)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

void gui::TextureSelector::updateKeytime(const float &dt)
{
    if (this->keytime < this->keyTimeMax)
        this->keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
    this->updateKeytime(dt);
    this->hide_btn->update(mousePosWindow);

    if (this->hide_btn->isClicked() && this->getKeytime())
    {
        this->hidden = !this->hidden;
    }

    if (!this->hidden)
    {
        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
            this->active = true;
        else
            this->active = false;

        if (this->active)
        {
            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize * scale);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize * scale);

            this->selector.setPosition(
                this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize * scale,
                this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize * scale
            );
            unsigned int typeNum = this->mousePosGrid.y * 4 + this->mousePosGrid.x;
            if (typeNum < (int)TileType::NONE) {
                this->type = static_cast<TileType>(typeNum);
            }
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
    if (!this->hidden)
    {
        target.draw(this->bounds);
        for (size_t i = 0; i < this->sheets.size(); i++) {
            target.draw(this->sheets.at(i));
        }

        if (this->active)
            target.draw(this->selector);
    }

    this->hide_btn->render(&target);
}