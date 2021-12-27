#include "TileMap.hpp"

void TileMap::clear()
{
    for (int x = -worldSizeInChunks; x < this->worldSizeInChunks; x++)
    {
        for (int y = -worldSizeInChunks; y < this->worldSizeInChunks; y++)
        {
            delete this->chunkMap.at({x, y});
            this->chunkMap.at({x, y}) = new Chunk(this->gridSizeF, this->collisionBox, (int)x * this->gridSizeU * this->chunkSizeInTiles, (int)y * this->gridSizeU * this->chunkSizeInTiles);
        }
    }
}

TileMap::TileMap(float gridSize, int worldSizeInChunks, unsigned chunkSize, std::string texture_file)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(gridSize);
    this->texture_file = texture_file;
    this->chunkSizeInTiles = chunkSize;
    this->worldSizeInChunks = worldSizeInChunks;
    this->worldSizeInTiles = this->chunkSizeInTiles * this->worldSizeInChunks;
    this->worldSize = static_cast<float>(this->worldSizeInTiles) * this->gridSizeF;

    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    this->collisionBox.setOutlineColor(sf::Color::Red);
    this->collisionBox.setOutlineThickness(1.f);

    for (int x = -worldSizeInChunks; x < this->worldSizeInChunks; x++)
    {
        for (int y = -worldSizeInChunks; y < this->worldSizeInChunks; y++)
        {
            this->chunkMap.insert({{x, y}, new Chunk(this->gridSizeF, this->collisionBox, (int)x * this->gridSizeU * this->chunkSizeInTiles, (int)y * this->gridSizeU * this->chunkSizeInTiles)});
            this->chunkMap.at({x, y})->generate(40.f, 0.f);
        }
    }
}

TileMap::~TileMap()
{
    this->clear();
}

//TODO: To delete
const sf::Texture *TileMap::getTileSheet() const
{
    return new sf::Texture();
}

void TileMap::addTile(const int x, const int y, const unsigned z, const sf::IntRect &texture_rect, bool collision, short type)
{
    if (x < this->worldSizeInTiles && x >= - worldSizeInTiles &&
        y < this->worldSizeInTiles && y >= - worldSizeInTiles)
    {
        int chunkX = x >= 0 ? x / (int)chunkSizeInTiles : ((x + 1) / (int)chunkSizeInTiles) - 1;
        int chunkY = y >= 0 ? y / (int)chunkSizeInTiles : ((y + 1) / (int)chunkSizeInTiles) - 1;
        int localX = ((x % chunkSizeInTiles) + chunkSizeInTiles) % chunkSizeInTiles;
        int localY = ((y % chunkSizeInTiles) + chunkSizeInTiles) % chunkSizeInTiles;
        this->chunkMap.at({chunkX, chunkY})->addTile(localX, localY, TileType::DIRT);
    }
}

void TileMap::removeTile(const int x, const int y, const unsigned z)
{
    if (x < this->worldSizeInTiles && x >= -worldSizeInTiles &&
        y < this->worldSizeInTiles && y >= -worldSizeInTiles)
    {
        int chunkX = x >= 0 ? x / (int)chunkSizeInTiles : ((x + 1) / (int)chunkSizeInTiles) - 1;
        int chunkY = y >= 0 ? y / (int)chunkSizeInTiles : ((y + 1) / (int)chunkSizeInTiles) - 1;
        int localX = ((x % chunkSizeInTiles) + chunkSizeInTiles)% chunkSizeInTiles;
        int localY = ((y % chunkSizeInTiles) + chunkSizeInTiles)% chunkSizeInTiles;
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
    if (nextPosition.left < -this->worldSize + (chunkSizeInTiles * gridSizeF))
    {
        entity->stopVelocityX();
    }
    else if ((nextPosition.left + nextPosition.width) >= this->worldSize)
    {
        entity->stopVelocityX();
    }

    if (nextPosition.top < -this->worldSize + (chunkSizeInTiles * gridSizeF))
    {
        entity->stopVelocityY();
    }
    else if ((nextPosition.top + nextPosition.height) >= this->worldSize)
    {
        entity->stopVelocityY();
    }

    //TILES
    int layer = 0;
    sf::Vector2i pos = entity->getGridPosition(this->gridSizeU);
    int x1 = pos.x - 2;
    int x2 = pos.x + 3;
    int y1 = pos.y - 2;
    int y2 = pos.y + 3;

    if (x1 < - (this->worldSizeInTiles))
    {
        x1 =  - (this->worldSizeInTiles);
    }
    else if (x1 > (int)this->worldSizeInTiles)
    {
        x1 = this->worldSizeInTiles;
    }

    if (x2 < - (this->worldSizeInTiles))
    {
        x2 = - (this->worldSizeInTiles);
    }
    else if (x2 > (int)this->worldSizeInTiles)
    {
        x2 = this->worldSizeInTiles;
    }

    if (y1 < -this->worldSizeInTiles)
    {
        y1 = -this->worldSizeInTiles;
    }
    else if (y1 > (int)this->worldSizeInTiles)
    {
        y1 = this->worldSizeInTiles;
    }

    if (y2 < -this->worldSizeInTiles)
    {
        y2 = -this->worldSizeInTiles;
    }
    else if (y2 > (int)this->worldSizeInTiles)
    {
        y2 = this->worldSizeInTiles;
    }

    for (int x = x1; x < x2; x++)
    {
        for (int y = y1; y < y2; y++)
        {
            int chunkX = x >= 0 ? x / (int)chunkSizeInTiles : ((x + 1) / (int)chunkSizeInTiles) - 1;
            int chunkY = y >= 0 ?y / (int)chunkSizeInTiles : ((y + 1) / (int)chunkSizeInTiles) - 1;
            int localX = ((x % chunkSizeInTiles) + chunkSizeInTiles) % chunkSizeInTiles;
            int localY = ((y % chunkSizeInTiles) + chunkSizeInTiles) % chunkSizeInTiles;
            const Tile * ts = this->chunkMap.at({chunkX, chunkY})->getTile(localX, localY);
            if (ts != nullptr)
            {
                if (ts->getCollision() && ts->intersects(entity->getNextPosition(dt)))
                {
                    sf::FloatRect wallBounds = ts->getGlobalBounds();

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

void TileMap::render(sf::RenderTarget &target, bool debugMode, const sf::Vector2i& mousePosition, const sf::Vector2i& chunkCenter)
{
    int chunkX = mousePosition.x >= 0 ? mousePosition.x / (int)chunkSizeInTiles : ((mousePosition.x + 1)/ (int)chunkSizeInTiles) - 1 ;
    int chunkY = mousePosition.y >= 0 ? mousePosition.y / (int)chunkSizeInTiles : ((mousePosition.y + 1)/ (int)chunkSizeInTiles) - 1;
    int x1 = chunkX - 2;
    int x2 = chunkX + 2 ;
    int y1 = chunkY - 2;
    int y2 = chunkY + 2;

    if (x1 < -worldSizeInChunks)
        x1 = -worldSizeInChunks;
    if (y1 < -worldSizeInChunks)
        y1 = -worldSizeInChunks;
    if (x2 >= worldSizeInChunks)
        x2 = worldSizeInChunks - 1;
    if (y2 >= worldSizeInChunks)
        y2 = worldSizeInChunks - 1;

    for (int x = x1; x <= x2; x++)
    {
        for (int y = y1; y <= y2; y++)
        {   
            if (chunkX == x && chunkY == y) {
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
    for (int x = -worldSizeInChunks; x < worldSizeInChunks; x++)
    {
        for (int y = -worldSizeInChunks; y < worldSizeInChunks; y++)
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
        Json::Value chunks;

        for (int x = -worldSizeInChunks; x < this->worldSizeInChunks; x++)
        {
            Json::Value chunksX = Json::Value();
            for (int y = -worldSizeInChunks; y < this->worldSizeInChunks; y++)
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

        this->clear();

        for (auto itrX = root["chunks"].begin(); itrX != root["chunks"].end(); itrX++)
        {
            int x = std::stoi(itrX.key().asString());
            Json::Value chunksByX = *itrX;
            for (auto itrY = chunksByX.begin(); itrY != chunksByX.end(); itrY++)
            {
                int y = std::stoi(itrY.key().asString());
                Json::Value chunk = *itrY;
                this->chunkMap.at({x, y}) = new Chunk(this->gridSizeF, this->collisionBox, x * this->gridSizeU * this->chunkSizeInTiles, y * this->gridSizeU * this->chunkSizeInTiles);
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
