#include "TileMap.hpp"

void TileMap::clear()
{
    for(size_t x = 0; x < this->maxSize.x; x++) {
        for(size_t y = 0; y < this->maxSize.y; y++) {
            for(size_t z = 0; z < this->layers; z++) {
                delete this->map[x][y][z];
                this->map[x][y][z] = NULL;
            }
        }
    }
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_sheet)
{
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    this->texture_file = texture_sheet;

    this->map.resize(this->maxSize.x);
    for(size_t x = 0; x < this->maxSize.x; x++)
    {
        this->map.push_back(std::vector<std::vector<Tile*>>());
        this->map[x].resize(this->maxSize.y);
        for(size_t y = 0; y< this->maxSize.y; y++)
        {
            this->map[x].push_back(std::vector<Tile*>());
            this->map[x][y].resize(this->layers);
            for(size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].push_back(NULL);
            }
        }
    }

    if(!this->tileSheet.loadFromFile(texture_sheet))
    {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET" << std::endl;
    }
}

TileMap::~TileMap()
{
    this->clear();
}

const sf::Texture* TileMap::getTileSheet() const {
    return &this->tileSheet;
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect) {
    if(x < this->maxSize.x && x >= 0 &&
    y < this->maxSize.y && y >= 0 &&
    z < this->layers && z >= 0) {
        if(this->map[x][y][z] == NULL) {
            delete this->map[x][y][z];
        }
        this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect);
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
    if(x < this->maxSize.x && x >= 0 &&
    y < this->maxSize.y && y >= 0 &&
    z < this->layers && z >= 0) {
        if(this->map[x][y][z] != NULL) {
            delete this->map[x][y][z];
            this->map[x][y][z] = NULL;
        }
    }
}


void TileMap::update() {

}

void TileMap::render(sf::RenderTarget& target) {
    for(auto &x : this->map)
    {
        for(auto &y : x)
        {
            for(auto *z : y)
            {
                if(z != nullptr)
                {
                    z->render(target);
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
        root["size"]["x"] = this->maxSize.x;
        root["size"]["y"] = this->maxSize.y;
        root["gridSize"] = this->gridSizeU;
        root["layers"] = this->layers;
        root["textureFile"] = this->texture_file;
        root["tiles"] = Json::Value();
        
        for(size_t x = 0; x < this->maxSize.x; x++) {
            for(size_t y = 0; y < this->maxSize.y; y++) {
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
    
        this->maxSize.x = root["size"]["x"].asInt();
        this->maxSize.y = root["size"]["y"].asInt();
        this->gridSizeU = root["gridSize"].asInt();
        this->layers = root["layers"].asInt();
        this->texture_file = root["textureFile"].asString();
        
        this->clear();

        if(!this->tileSheet.loadFromFile(texture_file)){
            std::cout << "ERROR::TILEMAP::Failed to load tiletexture sheet::filename: " << texture_file << std::endl;
        }

        this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
        for(size_t x = 0; x < this->maxSize.x; x++)
        {
            this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
            for(size_t y = 0; y < this->maxSize.y; y++)
            {
                this->map[x][y].resize(this->layers, NULL);
            }
        }

        for (int i = 0; i < root["tiles"].size(); i++)
        {
            Json::Value tile = root["tiles"][i];
            this->map[tile["x"].asInt()][tile["y"].asInt()][tile["z"].asInt()]
                = new Tile(tile["x"].asInt(), tile["y"].asInt(), this->gridSizeF, this->tileSheet,
                sf::IntRect(tile["trX"].asInt(), tile["trY"].asInt(), this->gridSizeU, this->gridSizeU), tile["collision"].asBool(), tile["type"].asInt());
                
            
        }
    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << filename << std::endl;
    }
    ifs.close();



}

