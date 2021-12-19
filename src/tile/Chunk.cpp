#include "Chunk.hpp"
#include "../resource/algo/Noise.hpp"
#include "../resource/algo/test/run.hpp"

void Chunk::clear()
{
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        for (size_t y = 0; y < this->chunkWidthGrid; y++)
        {
            for (size_t z = 0; z < this->chunk[x][y].size(); z++)
            {
                delete this->chunk[x][y][z];
                this->chunk[x][y][z] = new Tile();
            }
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
        this->chunk.push_back(std::vector<std::vector<Tile *>>());
        this->chunk[x].resize(this->chunkWidthGrid);
        for (size_t y = 0; y < this->chunkWidthGrid; y++)
        {
            this->chunk[x].push_back(std::vector<Tile *>());
        }
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
            for (auto &z : y)
            {

                if (z->getType() == TileTypes::DOODAD)
                {
                    this->deferredRenderStack.push(z);
                }
                else
                {
                    z->render(target);
                }
                if (z->getCollision() && debugMode)
                {
                    this->collisionBox.setPosition(z->getPosition());
                    target.draw(this->collisionBox);
                }
            }
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
            if (!this->chunk[x][y].empty())
            {
                for (size_t z = 0; z < this->chunk[x][y].size(); z++)
                {
                    Json::Value value = this->chunk[x][y][z]->getAsJson();
                    value["x"] = x;
                    value["y"] = y;
                    value["z"] = z;
                    root["tiles"].append(value);
                }
            }
        }
    }

    return root;
}

void Chunk::loadFromJson(Json::Value chunk)
{
    this->chunk.resize(this->chunkWidthGrid, std::vector<std::vector<Tile *>>());
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        this->chunk[x].resize(this->chunkWidthGrid, std::vector<Tile *>());
    }

    for (unsigned int i = 0; i < chunk["tiles"].size(); i++)
    {
        Json::Value tile = chunk["tiles"][i];
        this->chunk[tile["x"].asInt()][tile["y"].asInt()].push_back(
            new Tile(tile["x"].asInt() * this->gridSizeF + this->offsetX,
                     tile["y"].asInt() * this->gridSizeF + this->offsetY,
                     this->gridSizeF,
                     this->tileSheet,
                     sf::IntRect(tile["trX"].asInt(), tile["trY"].asInt(), this->gridSizeU, this->gridSizeU),
                     tile["collision"].asBool(),
                     tile["type"].asInt()));
    }
}

void Chunk::addTile(const unsigned x, const unsigned y, const sf::IntRect &texture_rect, bool collision, short type)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0 && this->chunk[x][y].size() <= this->layers)
    {
        this->chunk[x][y].push_back(
            new Tile((x * gridSizeF) + this->offsetX, (y * this->gridSizeF) + this->offsetY, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
    }
}

void Chunk::removeTile(const unsigned x, const unsigned y)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0 && this->chunk[x][y].size() > 0)
    {
        delete this->chunk[x][y][this->chunk[x][y].size() - 1];
        this->chunk[x][y].pop_back();
    }
}

const std::vector<Tile *> Chunk::getTileStack(const unsigned x, const unsigned y)
{
    if (x >= 0 && x < chunkWidthGrid && y >= 0 && y < chunkWidthGrid)
    {
        return this->chunk[x][y];
    }
    return std::vector<Tile *>();
}

void Chunk::generate(float scale, float threshold)
{
    for (unsigned int x = 0; x < this->chunkWidthGrid; x++)
    {
        for (unsigned int y = 0; y < this->chunkWidthGrid; y++)
        {
            if (Noise::generate(x + (int)(this->offsetX / this->gridSizeF), y + (int)(this->offsetY / this->gridSizeF)) > threshold)
            {
                this->chunk[x][y].push_back(
                    new Tile((x * this->gridSizeF) + this->offsetX, (y * this->gridSizeF) + this->offsetY, this->gridSizeF, this->tileSheet, sf::IntRect(0, 2 * gridSizeU, gridSizeU, gridSizeU), true, TileTypes::DEFAULT));
            }
        }
    }
}