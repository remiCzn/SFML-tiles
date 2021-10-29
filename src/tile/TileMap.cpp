#include "TileMap.hpp"

void TileMap::clear()
{
    for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {
        for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {
            for(size_t z = 0; z < this->layers; z++) {
                delete this->map[x][y][z];
                this->map[x][y][z] = new Tile();
            }
        }
    }
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_sheet)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSizeWorldGrid.x = width;
    this->maxSizeWorldGrid.y = height;
    this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
    this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
    this->layers = 1;
    this->texture_file = texture_sheet;

    this->map.resize(this->maxSizeWorldGrid.x);
    for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
    {
        this->map.push_back(std::vector<std::vector<Tile*>>());
        this->map[x].resize(this->maxSizeWorldGrid.y);
        for(size_t y = 0; y< this->maxSizeWorldGrid.y; y++)
        {
            this->map[x].push_back(std::vector<Tile*>());
            this->map[x][y].resize(this->layers);
            for(size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].push_back(new Tile());
            }
        }
    }

    if(!this->tileSheet.loadFromFile(texture_sheet))
    {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET" << std::endl;
    }

    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(255,0,0,50));
    this->collisionBox.setOutlineColor(sf::Color::Red);
    this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
    this->clear();
}

const sf::Texture* TileMap::getTileSheet() const {
    return &this->tileSheet;
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, bool collision, short type) {
    if(x < this->maxSizeWorldGrid.x && x >= 0 &&
    y < this->maxSizeWorldGrid.y && y >= 0 &&
    z < this->layers && z >= 0) {
        if(this->map[x][y][z] == NULL) {
            delete this->map[x][y][z];
        }
        this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
    if(x < this->maxSizeWorldGrid.x && x >= 0 &&
    y < this->maxSizeWorldGrid.y && y >= 0 &&
    z < this->layers && z >= 0) {
        if(this->map[x][y][z] != NULL) {
            delete this->map[x][y][z];
            this->map[x][y][z] = NULL;
        }
    }
}


void TileMap::update() {

}

void TileMap::updateCollision(Entity * entity, const float& dt) {
    sf::FloatRect nextPosition = entity->getNextPosition(dt);
    //WORLD BORDER
    if(nextPosition.left < 0) {
        entity->stopVelocityX();
    } else if((nextPosition.left + nextPosition.width)> this->maxSizeWorldF.x) {
        entity->stopVelocityX();
    }
    
    if(nextPosition.top < 0.f) {
        entity->stopVelocityY();
    } else if((nextPosition.top + nextPosition.height) >= this->maxSizeWorldF.y) {
        entity->stopVelocityY();
    }

    //TILES
    int layer = 0;
    sf::Vector2u pos = entity->getGridPosition(this->gridSizeU);
    int x1 = pos.x - 1;
    int x2 = pos.x + 3;
    int y1 = pos.y - 1;
    int y2 = pos.y + 3;

    if(x1 < 0) {
        x1 = 0;
    } else if(x1 > this->maxSizeWorldGrid.x) {
        x1 = this->maxSizeWorldGrid.x;
    }

    if(x2 < 0) {
        x2 = 0;
    } else if(x2 > this->maxSizeWorldGrid.x) {
        x2 = this->maxSizeWorldGrid.x;
    }

    if(y1 < 0) {
        y1 = 0;
    } else if(y1 > this->maxSizeWorldGrid.y) {
        y1 = this->maxSizeWorldGrid.y;
    }

    if(y2 < 0) {
        y2 = 0;
    } else if(y2 > this->maxSizeWorldGrid.y) {
        y2 = this->maxSizeWorldGrid.y;
    }

    for(size_t x = x1; x < x2; x++) {
        for(size_t y = y1; y < y2; y++) {
            Tile t = *this->map[x][y][layer];
            if(t.getCollision() && t.intersects(entity->getNextPosition(dt))) {
                sf::FloatRect wallBounds = t.getGlobalBounds();

                if(wallBounds.left < nextPosition.left + nextPosition.width && wallBounds.left + wallBounds.width > nextPosition.left) {
                    entity->stopVelocityX();
                }
                if(wallBounds.top < nextPosition.top + nextPosition.height && wallBounds.top + wallBounds.height > nextPosition.top) {
                    entity->stopVelocityY();
                }
            }
        }
    }
}

void TileMap::render(sf::RenderTarget& target, Entity* entity) {
    for(auto &x : this->map)
    {
        for(auto &y : x)
        {
            for(auto *z : y)
            {
                if(z != nullptr)
                {
                    z->render(target);
                    if(z->getCollision()) {
                        this->collisionBox.setPosition(z->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
            }
        }
    }
}

void TileMap::saveToFile(const std::string file_name) {
    std::ofstream out_file;
    Json::Value root;
    out_file.open(file_name, std::ofstream::out | std::ofstream::trunc);

    if(out_file.is_open()) {
        root["size"]["x"] = this->maxSizeWorldGrid.x;
        root["size"]["y"] = this->maxSizeWorldGrid.y;
        root["gridSize"] = this->gridSizeU;
        root["layers"] = this->layers;
        root["textureFile"] = this->texture_file;
        root["tiles"] = Json::Value();
        
        for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {
            for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {
                for(size_t z = 0; z < this->layers; z++) {
                    if(this->map[x][y][z])
                    {
                        Json::Value value = this->map[x][y][z]->getAsJson();
                        value["x"] = x;
                        value["y"] = y;
                        value["z"] = z;
                        root["tiles"].append(value);
                    }
                }
            }
        }

        out_file << root;
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE" << file_name << "\n";
    }

    out_file.close();
}

void TileMap::loadFromFile(std::string filename) {
    std::ifstream ifs(filename);
    Json::Value root;
    if(ifs.is_open())
    {
        ifs >> root;
    
        this->maxSizeWorldGrid.x = root["size"]["x"].asInt();
        this->maxSizeWorldGrid.y = root["size"]["y"].asInt();
        this->gridSizeU = root["gridSize"].asInt();
        this->layers = root["layers"].asInt();
        this->texture_file = root["textureFile"].asString();
        
        this->clear();

        if(!this->tileSheet.loadFromFile(texture_file)){
            std::cout << "ERROR::TILEMAP::Failed to load tiletexture sheet::filename: " << texture_file << std::endl;
        }

        this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile*>>());
        for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
        {
            this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
            for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
            {
                this->map[x][y].resize(this->layers, NULL);
            }
        }

        for (int i = 0; i < root["tiles"].size(); i++)
        {
            Json::Value tile = root["tiles"][i];
            delete this->map[tile["x"].asInt()][tile["y"].asInt()][tile["z"].asInt()];
            this->map[tile["x"].asInt()][tile["y"].asInt()][tile["z"].asInt()]
                = new Tile(tile["x"].asInt() * this->gridSizeF, tile["y"].asInt() * this->gridSizeF, this->gridSizeF, this->tileSheet,
                sf::IntRect(tile["trX"].asInt(), tile["trY"].asInt(), this->gridSizeU, this->gridSizeU), tile["collision"].asBool(), tile["type"].asInt());
                
            
        }
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << filename << std::endl;
    }
    ifs.close();



}

