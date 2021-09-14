#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
    this->background.setSize(
        sf::Vector2f(
            this->window->getSize().x,
            this->window->getSize().y));
    if (!this->bgTexture.loadFromFile("images/background/background.png"))
    {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_TEXTURE";
    }

    this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts()
{
    if (!this->menuFont.loadFromFile("fonts/FreeSans.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::Could not load font");
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("config/mainmenu_keybinds");
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new Button(
        100, 250, 250, 50,
        "New Game", &this->menuFont, 50,
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50));

    this->buttons["SETTINGS"] = new Button(
        100, 350, 250, 50,
        "Settings", &this->menuFont, 50,
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50));

    this->buttons["EDITOR_STATE"] = new Button(
        100, 450, 250, 50,
        "Editor", &this->menuFont, 50,
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50));

    this->buttons["QUIT"] = new Button(
        100, 550, 250, 50,
        "Quit", &this->menuFont, 50,
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50));
}

void MainMenuState::update(const float &dt)
{
    this->updateInput(dt);
    this->updateMousePosition();
    this->updateButtons();
}

void MainMenuState::updateInput(const float &dt)
{
}

void MainMenuState::updateButtons()
{
    for (auto it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["GAME_STATE"]->isPressed())
    {
        //push game state when pressed
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }
    if (this->buttons["EDITOR_STATE"]->isPressed())
    {
        //push editor state when pressed
        this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
    }
    if (this->buttons["QUIT"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    this->renderButtons(target);

    // //remove later
    // sf::Text mouseText;
    // mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    // mouseText.setFont(this->menuFont);
    // mouseText.setColor(sf::Color::Black);
    // mouseText.setCharacterSize(12);
    // std::stringstream ss;
    // ss << this->mousePosView.x << "  " << this->mousePosView.y;
    // mouseText.setString(ss.str());

    // target->draw(mouseText);
}

void MainMenuState::renderButtons(sf::RenderTarget *target)
{
    for (auto it : this->buttons)
    {
        // Render all buttons
        it.second->render(target);
    }
}