#include "GraphicSettings.hpp"

GraphicSettings::GraphicSettings()
{
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->framerateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicSettings::saveToFile(const std::string path)
{
    std::ofstream ofs(path);
    Json::Value root;
    if(ofs.is_open())
    {
        root["title"] = this->title;
        root["resolution"] = Json::nullValue;
        root["resolution"]["width"] = this->resolution.width;
        root["resolution"]["height"] = this->resolution.height;
        root["fullscreen"] = this->fullscreen;
        root["framerateLimit"] = this->framerateLimit;
        root["VSync"] = this->verticalSync;
        root["Antialiasing"] = this->contextSettings.antialiasingLevel;

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
    this->resolution.width = root["resolution"]["width"].asInt();
    this->resolution.height = root["resolution"]["height"].asInt();
    this->fullscreen = root["fullscreen"].asBool();
    this->framerateLimit = root["framerateLimit"].asInt();
    this->verticalSync = root["VSync"].asBool();
    this->contextSettings.antialiasingLevel = root["Antialiasing"].asInt();    
}