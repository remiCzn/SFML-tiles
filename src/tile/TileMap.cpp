#include "TileMap.hpp"

void TileMap::clear()
{
    for (unsigned int x = 0; x < this->worldSizeInChunks; x++)
    {
        for (unsigned int y = 0; y < this->worldSizeInChunks; y++)
        {
            delete this->chunkMap.at({x, y});
            this->chunkMap.at({x, y}) = new Chunk(this->gridSizeF, this->tileSheet, this->collisionBox, (int)x * this->gridSizeU * this->chunkSizeInTiles, (int)y * this->gridSizeU * this->chunkSizeInTiles);
        }
    }
}

TileMap::TileMap(float gridSize, unsigned worldSizeInChunks, unsigned chunkSize, std::string texture_file)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(gridSize);
    this->layers = 1;
    this->texture_file = texture_file;
    this->chunkSizeInTiles = chunkSize;
    this->worldSizeInChunks = worldSizeInChunks;
    this->worldSizeInTiles = this->chunkSizeInTiles * this->worldSizeInChunks;
    this->worldSize = static_cast<float>(this->worldSizeInTiles) * this->gridSizeF;

    if (!this->tileSheet.loadFromFile(texture_file))
    {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET" << std::endl;
    }

    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    this->collisionBox.setOutlineColor(sf::Color::Red);
    this->collisionBox.setOutlineThickness(1.f);

    for (unsigned int x = 0; x < this->worldSizeInChunks; x++)
    {
        for (unsigned int y = 0; y < this->worldSizeInChunks; y++)
        {
            this->chunkMap.insert({{x, y}, new Chunk(this->gridSizeF, this->tileSheet, this->collisionBox, (int)x * this->gridSizeU * this->chunkSizeInTiles, (int)y * this->gridSizeU * this->chunkSizeInTiles)});
            this->chunkMap.at({x, y})->generate(40.f, 0.f);
        }
    }
}

TileMap::~TileMap()
{
    this->clear();
}

const sf::Texture *TileMap::getTileSheet() const
{
    return &this->tileSheet;
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect, bool collision, short type)
{
    if (x < this->worldSizeInTiles && x >= 0 &&
        y < this->worldSizeInTiles && y >= 0 &&
        z < this->layers && z >= 0)
    {
        int chunkX = x / chunkSizeInTiles;
        int chunkY = y / chunkSizeInTiles;
        int localX = x % chunkSizeInTiles;
        int localY = y % chunkSizeInTiles;
        this->chunkMap.at({chunkX, chunkY})->addTile(localX, localY, texture_rect, collision, type);
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < this->worldSizeInTiles && x >= 0 &&
        y < this->worldSizeInTiles && y >= 0 &&
        z < this->layers && z >= 0)
    {
        int chunkX = x / chunkSizeInTiles;
        int chunkY = y / chunkSizeInTiles;
        int localX = x % chunkSizeInTiles;
        int localY = y % chunkSizeInTiles;
        this->chunkMap.at({chunkX, chunkY})->removeTile(localX, localY);
    }
}

void TileMap::update()
{
}

void TileMap::updateCollision(Entity *entity, const float &dt)
{
    sf::FloatRect nextPosition = entity->getNextPosition(dt);
    //WORLD BORDER
    if (nextPosition.left < 0)
    {
        entity->stopVelocityX();
    }
    else if ((nextPosition.left + nextPosition.width) >= this->worldSize)
    {
        entity->stopVelocityX();
    }

    if (nextPosition.top < 0.f)
    {
        entity->stopVelocityY();
    }
    else if ((nextPosition.top + nextPosition.height) >= this->worldSize)
    {
        entity->stopVelocityY();
    }

    //TILES
    int layer = 0;
    sf::Vector2u pos = entity->getGridPosition(this->gridSizeU);
    int x1 = pos.x - 1;
    int x2 = pos.x + 2;
    int y1 = pos.y - 1;
    int y2 = pos.y + 3;

    if (x1 < 0)
    {
        x1 = 0;
    }
    else if (x1 > (int)this->worldSizeInTiles)
    {
        x1 = this->worldSizeInTiles;
    }

    if (x2 < 0)
    {
        x2 = 0;
    }
    else if (x2 > (int)this->worldSizeInTiles)
    {
        x2 = this->worldSizeInTiles;
    }

    if (y1 < 0)
    {
        y1 = 0;
    }
    else if (y1 > (int)this->worldSizeInTiles)
    {
        y1 = this->worldSizeInTiles;
    }

    if (y2 < 0)
    {
        y2 = 0;
    }
    else if (y2 > (int)this->worldSizeInTiles)
    {
        y2 = this->worldSizeInTiles;
    }

    for (int x = x1; x < x2; x++)
    {
        for (int y = y1; y < y2; y++)
        {
            int chunkX = (int)x / chunkSizeInTiles;
            int chunkY = (int)y / chunkSizeInTiles;
            int localX = x % chunkSizeInTiles;
            int localY = y % chunkSizeInTiles;
            std::vector<Tile *> ts = this->chunkMap.at({chunkX, chunkY})->getTileStack(localX, localY);
            if (!ts.empty())
            {
                Tile t = *(ts.at(0));
                if (t.getCollision() && t.intersects(entity->getNextPosition(dt)))
                {
                    sf::FloatRect wallBounds = t.getGlobalBounds();

                    if (wallBounds.left < nextPosition.left + nextPosition.width && wallBounds.left + wallBounds.width > nextPosition.left)
                    {
                        entity->stopVelocityX();
                    }
                    if (wallBounds.top < nextPosition.top + nextPosition.height && wallBounds.top + wallBounds.height > nextPosition.top)
                    {
                        entity->stopVelocityY();
                    }
                }
            }
        }
    }
}

void TileMap::render(sf::RenderTarget &target, bool debugMode, const sf::Vector2u& mousePosition)
{
    sf::Vector2u chunkCoord = mousePosition / chunkSizeInTiles;
    for (size_t x = 0; x < worldSizeInChunks; x++)
    {
        for (size_t y = 0; y < worldSizeInChunks; y++)
        {   
            if (chunkCoord.x == x && chunkCoord.y == y) {
                this->chunkMap.at({(int)x, (int)y})->render(target, debugMode);
            }
            else {
                this->chunkMap.at({(int)x, (int)y})->render(target, false);
            }
            
        }
    }
}

void TileMap::renderDeferred(sf::RenderTarget &target)
{
    for (size_t x = 0; x < worldSizeInChunks; x++)
    {
        for (size_t y = 0; y < worldSizeInChunks; y++)
        {
            this->chunkMap.at({(int)x, (int)y})->renderDeferred(target);
        }
    }
}

void TileMap::saveToFile(const std::string file_name)
{
    std::ofstream out_file;
    Json::Value root;
    out_file.open(file_name, std::ofstream::out | std::ofstream::trunc);

    if (out_file.is_open())
    {
        root["size"]["x"] = this->worldSizeInChunks;
        root["size"]["y"] = this->worldSizeInChunks;
        root["gridSize"] = this->gridSizeU;
        root["layers"] = this->layers;
        root["textureFile"] = this->texture_file;
        Json::Value chunks;

        for (unsigned int x = 0; x < this->worldSizeInChunks; x++)
        {
            Json::Value chunksX = Json::Value();
            for (unsigned int y = 0; y < this->worldSizeInChunks; y++)
            {
                Json::Value chunk = this->chunkMap.at({x, y})->getAsJson();
                if (!chunk.isNull())
                {
                    chunksX[std::to_string(y)] = chunk;
                }
            }
            if (!chunksX.isNull())
            {
                chunks[std::to_string(x)] = chunksX;
            }
        }
        if (chunks.isNull())
        {
            chunks = Json::arrayValue;
        }
        root["chunks"] = chunks;

        out_file << root;
    }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE" << file_name << "\n";
    }

    out_file.close();
}

void TileMap::loadFromFile(std::string filename)
{
    std::ifstream ifs(filename);
    Json::Value root;
    if (ifs.is_open())
    {
        ifs >> root;

        this->maxSizeWorldGrid.x = root["size"]["x"].asInt();
        this->maxSizeWorldGrid.y = root["size"]["y"].asInt();
        this->gridSizeU = root["gridSize"].asInt();
        this->layers = root["layers"].asInt();
        this->texture_file = root["textureFile"].asString();

        this->clear();

        if (!this->tileSheet.loadFromFile(texture_file))
        {
            std::cout << "ERROR::TILEMAP::Failed to load tiletexture sheet::filename: " << texture_file << std::endl;
        }
        for (auto itrX = root["chunks"].begin(); itrX != root["chunks"].end(); itrX++)
        {
            int x = std::stoi(itrX.key().asString());
            Json::Value chunksByX = *itrX;
            for (auto itrY = chunksByX.begin(); itrY != chunksByX.end(); itrY++)
            {
                int y = std::stoi(itrY.key().asString());
                Json::Value chunk = *itrY;
                this->chunkMap.at({x, y}) = new Chunk(this->gridSizeF, this->tileSheet, this->collisionBox, x * this->gridSizeU * this->chunkSizeInTiles, y * this->gridSizeU * this->chunkSizeInTiles);
                this->chunkMap.at({x, y})->loadFromJson(chunk);
            }
        }
    }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << filename << std::endl;
    }
    ifs.close();
}
