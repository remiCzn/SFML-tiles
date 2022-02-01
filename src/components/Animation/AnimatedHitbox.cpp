#include "./AnimatedHitbox.hpp"

AnimatedHitbox::AnimatedHitbox(sf::RectangleShape& initialBox, sf::Sprite* sprite, float animationTimer, std::vector<sf::IntRect> steps)
    : Animation(animationTimer, steps.size()), hitbox(initialBox), playerPosition(sprite)
{
    this->steps = steps;
    this->hitbox.setOrigin(initialBox.getGlobalBounds().left, initialBox.getGlobalBounds().top);
    this->hitbox.setSize(sf::Vector2f(
        initialBox.getGlobalBounds().width, initialBox.getGlobalBounds().height
    ));
}

AnimatedHitbox::~AnimatedHitbox()
{
}

void AnimatedHitbox::nextStep()
{
    sf::IntRect& step = this->steps.at(this->currentStep);
    this->hitbox.setOrigin(this->playerPosition->getPosition().x + step.left, this->playerPosition->getPosition().y + step.top);
    this->hitbox.setSize(sf::Vector2f(
        step.width, step.height
    ));
}

sf::RectangleShape& AnimatedHitbox::getHitbox() {
    return this->hitbox;
}
