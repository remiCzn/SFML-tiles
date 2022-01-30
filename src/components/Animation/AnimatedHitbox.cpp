#include "./AnimatedHitbox.hpp"

AnimatedHitbox::AnimatedHitbox(sf::IntRect initialBox, float animationTimer, std::vector<sf::IntRect> steps)
    : Animation(animationTimer, steps.size())
{
    this->steps = steps;
    this->hitbox.setOrigin(initialBox.left, initialBox.top);
    this->hitbox.setSize(sf::Vector2f(
        initialBox.width, initialBox.height
    ));
}

AnimatedHitbox::~AnimatedHitbox()
{
}

void AnimatedHitbox::nextStep()
{
    sf::IntRect& step = this->steps.at(this->currentStep);
    this->hitbox.setOrigin(step.left, step.top);
    this->hitbox.setSize(sf::Vector2f(
        step.width, step.width
    ));
}

sf::RectangleShape& AnimatedHitbox::getHitbox() {
    return this->hitbox;
}
