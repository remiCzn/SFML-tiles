#include "MainMenuState.hpp"

MainMenuState::MainMenuState(StateData *stateData)
    : State(stateData)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initTitle();
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
            static_cast<float>(this->statedata->gfxSettings->window->getSize().x),
            static_cast<float>(this->statedata->gfxSettings->window->getSize().y)
        )
    );
    this->background.setFillColor(sf::Color::Black);
}

void MainMenuState::initFonts()
{
    if (!this->menuFont.loadFromFile("src/fonts/FreeSans.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::Could not load font");
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("src/config/mainmenu_keybinds");
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

void MainMenuState::initTitle()
{
    this->title.setString("Game");
    this->title.setFillColor(sf::Color::White);
    this->title.setFont(this->menuFont);
    this->title.setCharacterSize(65);
    this->title.setPosition(
        (this->statedata->gfxSettings->window->getSize().x - this->title.getGlobalBounds().width) / 2.f,
        100.f);
}

void MainMenuState::initButtons()
{
    float x = this->statedata->gfxSettings->window->getSize().x / 2.f - 125.f;
    this->buttons["GAME_STATE"] = new gui::Button(
        x, 250.f, 250.f, 65.f,
        "New Game", &this->menuFont, 50);

    this->buttons["SETTINGS"] = new gui::Button(
        x, 350.f, 250.f, 65.f,
        "Settings", &this->menuFont, 50);

    this->buttons["EDITOR_STATE"] = new gui::Button(
        x, 450.f, 250.f, 65.f,
        "Editor", &this->menuFont, 50);

    this->buttons["QUIT"] = new gui::Button(
        x, 550.f, 250.f, 65.f,
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
        it.second->update(this->mousePosWindow);
    }

    if (this->buttons["GAME_STATE"]->isClicked())
    {
        //push game state when pressed
        this->statedata->states->push(new GameState(this->statedata));
    }
    if (this->buttons["SETTINGS"]->isClicked())
    {
        this->statedata->states->push(new SettingsState(this->statedata));
    }
    if (this->buttons["EDITOR_STATE"]->isClicked())
    {
        //push editor state when pressed
        this->statedata->states->push(new EditorState(this->statedata));
    }
    if (this->buttons["QUIT"]->isClicked())
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
    target->draw(this->title);

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