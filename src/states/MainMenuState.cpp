#include "MainMenuState.hpp"

MainMenuState::MainMenuState(StateData* stateData)
    : State(stateData)
{
    std::cout << 1 << std::endl;
    this->initVariables();
    std::cout << 2 << std::endl;
    this->initBackground();
    std::cout << 3 << std::endl;
    this->initFonts();
    std::cout << 4 << std::endl;
    this->initKeybinds();
    std::cout << 5 << std::endl;
    this->initButtons();
    std::cout << 6 << std::endl;
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
            this->statedata->gfxSettings->window->getSize().x,
            this->statedata->gfxSettings->window->getSize().y));
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
            this->keybinds[key] = this->statedata->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new gui::Button(
        100, 250, 250, 65.f,
        "New Game", &this->menuFont, 50);

    this->buttons["SETTINGS"] = new gui::Button(
        100, 350, 250, 65.f,
        "Settings", &this->menuFont, 50);

    this->buttons["EDITOR_STATE"] = new gui::Button(
        100, 450, 250, 65.f,
        "Editor", &this->menuFont, 50);

    this->buttons["QUIT"] = new gui::Button(
        100, 550, 250, 65.f,
        "Quit", &this->menuFont, 50);
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
        this->statedata->states->push(new GameState(this->statedata));
    }
    if(this->buttons["SETTINGS"]->isPressed())
    {
        this->statedata->states->push(new SettingsState(this->statedata));
    }
    if (this->buttons["EDITOR_STATE"]->isPressed())
    {
        //push editor state when pressed
        this->statedata->states->push(new EditorState(this->statedata));
    }
    if (this->buttons["QUIT"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->statedata->gfxSettings->window;

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