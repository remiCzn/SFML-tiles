#include "Chunk.hpp"
#include "../resource/algo/Noise.hpp"
#include "../resource/algo/test/run.hpp"

void Chunk::clear()
{
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        for (size_t y = 0; y < this->chunkWidthGrid; y++)
        {
            delete this->chunk[x][y];
            this->chunk[x][y] = nullptr;
        }
    }
}

Chunk::Chunk(float gridSize, sf::Texture &tilesheet, sf::RectangleShape &collisionBox, int offsetX, int offsetY)
    : tileSheet(tilesheet), offsetX(offsetX), offsetY(offsetY)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);

    this->chunkWidthGrid = 16;
    this->chunkWidthF = this->chunkWidthGrid * this->gridSizeF;
    this->layers = 1;

    this->chunk.resize(this->chunkWidthGrid);
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        this->chunk.push_back(std::vector<Tile *>());
        this->chunk[x].resize(this->chunkWidthGrid);
    }
    this->collisionBox = collisionBox;

    this->chunkBox.setSize(sf::Vector2f(
        this->chunkWidthF, this->chunkWidthF
    ));
    this->chunkBox.setPosition(static_cast<float>(offsetX), static_cast<float>(offsetY));
    this->chunkBox.setOutlineThickness(1.f);
    this->chunkBox.setOutlineColor(sf::Color::White);
    this->chunkBox.setFillColor(sf::Color::Transparent);
}

Chunk::~Chunk()
{
    this->clear();
}

void Chunk::update()
{
}

void Chunk::render(sf::RenderTarget &target, bool debugMode)
{
    for (auto &x : this->chunk)
    {
        for (auto &y : x)
        {
            if (y != nullptr) {
                y->render(target);
                
                if (y->getCollision() && debugMode)
                {
                    this->collisionBox.setPosition(y->getPosition());
                    target.draw(this->collisionBox);
                }
            }
            //TODO: Optimize Rendering, because with 16 chunk (+ collision Box) -> 16fps
        }
    }
    if (debugMode)
    {
        target.draw(chunkBox);
    }
}

void Chunk::renderDeferred(sf::RenderTarget &target)
{
    while (!this->deferredRenderStack.empty())
    {
        deferredRenderStack.top()->render(target);
        deferredRenderStack.pop();
    }
}

Json::Value Chunk::getAsJson()
{
    Json::Value root = Json::Value();
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        for (size_t y = 0; y < this->chunkWidthGrid; y++)
        {
            if (this->chunk[x][y] != nullptr)
            {
                Json::Value value = this->chunk[x][y]->getAsJson();
                value["x"] = x;
                value["y"] = y;
                root["tiles"].append(value);
            }
        }
    }

    return root;
}

void Chunk::loadFromJson(Json::Value chunk)
{
    this->chunk.resize(this->chunkWidthGrid, std::vector<Tile *>());
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        this->chunk[x].resize(this->chunkWidthGrid);
    }

    for (unsigned int i = 0; i < chunk["tiles"].size(); i++)
    {
        Json::Value tile = chunk["tiles"][i];
        this->chunk[tile["x"].asInt()][tile["y"].asInt()] = 
            TileRegistry::Instance()->CreateTile(TileType::STONE, tile["x"].asInt() + static_cast<int>(this->offsetX / gridSizeF), tile["y"].asInt() + static_cast<int>(this->offsetY / gridSizeF));
            /*new Tile(tile["x"].asInt() * this->gridSizeF + this->offsetX,
                     tile["y"].asInt() * this->gridSizeF + this->offsetY,
                     this->gridSizeF,
                     this->tileSheet,
                     sf::IntRect(tile["trX"].asInt(), tile["trY"].asInt(), this->gridSizeU, this->gridSizeU),
                     tile["collision"].asBool(),
                     tile["type"].asInt())*/
    }
}

void Chunk::addTile(const unsigned x, const unsigned y, const sf::IntRect &texture_rect, bool collision, short type)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0)
    {
        this->chunk[x][y] =
            TileRegistry::Instance()->CreateTile(TileType::STONE, x + static_cast<int>(this->offsetX / this->gridSizeF), y + static_cast<int>(this->offsetY / this->gridSizeF));
    }
}

void Chunk::addTile(const unsigned x, const unsigned y, TileType type)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0)
    {
        this->chunk[x][y] =
            TileRegistry::Instance()->CreateTile(type, x + static_cast<int>(this->offsetX / gridSizeF), y + static_cast<int>(this->offsetY / gridSizeF));
    }
}

void Chunk::removeTile(const unsigned x, const unsigned y)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0 && this->chunk[x][y] != nullptr)
    {
        delete this->chunk[x][y];
        this->chunk[x][y] = nullptr;
    }
}

const Tile* Chunk::getTile(const unsigned x, const unsigned y)
{
    if (x >= 0 && x < chunkWidthGrid && y >= 0 && y < chunkWidthGrid)
    {
        return this->chunk[x][y];
    }
    return nullptr;
}

void Chunk::generate(float scale, float threshold)
{
    for (unsigned int x = 0; x < this->chunkWidthGrid; x++)
    {
        for (unsigned int y = 0; y < this->chunkWidthGrid; y++)
        {
            float value = Noise::generate(x + (int)(this->offsetX / this->gridSizeF), y + (int)(this->offsetY / this->gridSizeF));
            if (value > threshold + 0.1) {
                this->chunk[x][y] =
                    TileRegistry::Instance()->CreateTile(TileType::STONE, x + static_cast<int>(this->offsetX / gridSizeF), y + static_cast<int>(this->offsetY / gridSizeF));
            }
            else if (value > threshold)
            {
                this->chunk[x][y] =
                    //new Tile((x * this->gridSizeF) + this->offsetX, (y * this->gridSizeF) + this->offsetY, this->gridSizeF, this->tileSheet, sf::IntRect(0, 0, gridSizeU, gridSizeU), true, TileTypes::DEFAULT)
                    TileRegistry::Instance()->CreateTile(TileType::DIRT, x + static_cast<int>(this->offsetX / gridSizeF), y + static_cast<int>(this->offsetY / gridSizeF));
            }
        }
    }
}