#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<State*> * states) 
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
    for(auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::initVariables() {

}

void MainMenuState::initBackground() {
    this->background.setSize(
        sf::Vector2f(
            this->window->getSize().x,
             this->window->getSize().y
        )
    );
    if(!this->bgTexture.loadFromFile("images/background/background.png")) {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_TEXTURE";
    }

    this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts() {
    if(!this->menuFont.loadFromFile("fonts/Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::Could not load font");
    }
}

void MainMenuState::initKeybinds() {
    std::ifstream ifs("config/mainmenu_keybinds");
    if(ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while(ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void MainMenuState::initButtons() {
    this->buttons["GAME_STATE"] = new Button(
        100, 220, 150, 50,
        "New Game", &this->menuFont,
        sf::Color(150,150,150,200), sf::Color(20,20,20,200), sf::Color(70,70,70,200)
    );

    this->buttons["CONTINUE"] = new Button(
        100, 290, 150, 50,
        "Continue", &this->menuFont,
        sf::Color(150,150,150,200), sf::Color(20,20,20,200), sf::Color(70,70,70,200)
    );

    this->buttons["QUIT"] = new Button(
        100, 360, 150, 50,
        "Quit", &this->menuFont,
        sf::Color(150,150,150,200), sf::Color(20,20,20,200), sf::Color(70,70,70,200)
    );
}

void MainMenuState::update(const float& dt)
{
    this->updateInput(dt);
    this->updateMousePosition();
    this->updateButtons();
}

void MainMenuState::updateInput(const float& dt)
{
    this->checkForQuit();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {

    }
}

void MainMenuState::updateButtons() {
    for(auto it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if(this->buttons["GAME_STATE"]->isPressed())
    {
        //push game state when pressed
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));


    }
    if(this->buttons["QUIT"]->isPressed())
    {
        this->quit = true;
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if(!target)
        target = this->window;

    target->draw(this->background);
    this->renderButtons(target);

    //remove later
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->menuFont);
    mouseText.setColor(sf::Color::Black);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << "  " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);

}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for(auto it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::endState() {
    std::cout << "END MainMenuState" << std::endl;
}