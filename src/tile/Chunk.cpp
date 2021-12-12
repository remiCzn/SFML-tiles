#include "Chunk.hpp"

void Chunk::clear()
{
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        for (size_t y = 0; y < this->chunkWidthGrid; y++)
        {
            for (size_t z = 0; z < this->layers; z++)
            {
                for (size_t k = 0; k < this->chunk[x][y][z].size(); k++)
                {
                    delete this->chunk[x][y][z][k];
                    this->chunk[x][y][z][k] = new Tile();
                }
            }
        }
    }
}

Chunk::Chunk(float gridSize, sf::Texture &tilesheet, sf::RectangleShape &collisionBox)
    : tileSheet(tilesheet)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);

    this->chunkWidthGrid = 16;
    this->chunkWidthF = this->chunkWidthGrid * this->gridSizeF;
    this->layers = 1;

    this->chunk.resize(this->chunkWidthGrid);
    for (size_t x = 0; x < this->chunkWidthGrid; x++)
    {
        this->chunk.push_back(std::vector<std::vector<std::vector<Tile *>>>());
        this->chunk[x].resize(this->chunkWidthGrid);
        for (size_t y = 0; y < this->chunkWidthGrid; y++)
        {
            this->chunk[x].push_back(std::vector<std::vector<Tile *>>());
            this->chunk[x][y].resize(this->layers);
            for (size_t z = 0; z < this->layers; z++)
            {
                this->chunk[x][y].push_back(std::vector<Tile *>());
            }
        }
    }
    this->collisionBox = collisionBox;
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
                if (!z.empty())
                {
                    for (auto &k : z)
                    {
                        if (k->getType() == TileTypes::DOODAD)
                        {
                            this->deferredRenderStack.push(k);
                        }
                        else
                        {
                            k->render(target);
                        }
                        if (k->getCollision() && debugMode)
                        {
                            this->collisionBox.setPosition(k->getPosition());
                            target.draw(this->collisionBox);
                        }
                    }
                }
            }
        }
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
            for (size_t z = 0; z < this->layers; z++)
            {
                if (!this->chunk[x][y][z].empty())
                {
                    for (size_t k = 0; k < this->chunk[x][y][z].size(); k++)
                    {
                        Json::Value value = this->chunk[x][y][z][k]->getAsJson();
                        value["x"] = x;
                        value["y"] = y;
                        value["z"] = z;
                        value["k"] = k;
                        root["tiles"].append(value);
                    }
                }
            }
        }
    }
    return root;
}

void Chunk::addTile(const unsigned x, const unsigned y, const unsigned offsetX, const unsigned offsetY, const unsigned z, const sf::IntRect &texture_rect, bool collision, short type)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0 && z < this->layers && z >= 0)
    {
        this->chunk[x][y][z].push_back(
            new Tile((x + offsetX) * this->gridSizeF, (y + offsetY) * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
    }
}

void Chunk::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < this->chunkWidthGrid && x >= 0 &&
        y < this->chunkWidthGrid && y >= 0 && z < this->layers && z >= 0)
    {
        if (!this->chunk[x][y][z].empty())
        {
            delete this->chunk[x][y][z][this->chunk[x][y][z].size() - 1];
            this->chunk[x][y][z].pop_back();
        }
    }
}