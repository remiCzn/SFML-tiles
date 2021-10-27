#include "GraphicSettings.hpp"

GraphicSettings::GraphicSettings()
{
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->framerateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = std::vector<sf::VideoMode>();
}

GraphicSettings::~GraphicSettings() {
    delete this->window;
}

void GraphicSettings::saveToFile(const std::string path)
{
    std::ofstream ofs(path);
    Json::Value root;
    if(ofs.is_open())
    {
        root["title"] = this->title;
        root["resolution"] = Json::nullValue;
        root["resolution"]["id"] = this->idResolution;
        root["resolution"]["width"] = this->resolution.width;
        root["resolution"]["height"] = this->resolution.height;
        root["fullscreen"] = this->fullscreen;
        root["framerateLimit"] = this->framerateLimit;
        root["VSync"] = this->verticalSync;
        root["Antialiasing"] = this->contextSettings.antialiasingLevel;
        root["videoModes"] = Json::Value();
        for(auto &i : this->videoModes) {
            Json::Value resol;
            resol.append(i.width);
            resol.append(i.height);
            root["videoModes"].append(resol);
        }
        ofs << root;
    }
    else {
        std::cout << "GFXSETTINGS::FAILED TO OPEN FILE" << std::endl;
    }

    ofs.close();
}

void GraphicSettings::loadFromFile(const std::string path)
{
    std::ifstream ifs(path);
    Json::Value root;
    if(ifs.is_open())
    {
        ifs >> root;
    }
    ifs.close();

    this->title = root["title"].asString();
    this->fullscreen = root["fullscreen"].asBool();
    this->framerateLimit = root["framerateLimit"].asInt();
    this->verticalSync = root["VSync"].asBool();
    this->contextSettings.antialiasingLevel = root["Antialiasing"].asInt();
    for(Json::Value &i : root["videoModes"])
    {
        this->videoModes.push_back(sf::VideoMode(i[0].asInt(), i[1].asInt()));
    }

    this->idResolution = root["resolution"]["id"].asInt();
    this->resolution.width = root["resolution"]["width"].asInt();
    this->resolution.height = root["resolution"]["height"].asInt();
}

void GraphicSettings::setFullscreen(bool value) {
    this->fullscreen = value;
    delete this->window;
    this->initWindow();
}

void GraphicSettings::initWindow() {
    if(this->fullscreen)
        this->window = new sf::RenderWindow(
            this->resolution,
            this->title,
            sf::Style::Fullscreen,
            this->contextSettings
        );
    else
        this->window = new sf::RenderWindow(
            this->resolution,
            this->title,
            sf::Style::Titlebar | sf::Style::Close,
            this->contextSettings
        );
    
    this->window->setFramerateLimit(this->framerateLimit);
    this->window->setVerticalSyncEnabled(this->verticalSync);
}