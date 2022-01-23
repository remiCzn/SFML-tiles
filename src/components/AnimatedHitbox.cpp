#include "./AnimatedHitbox.hpp"

AnimatedHitboxComponent::AnimatedHitboxComponent(sf::IntRect initialBox, float animationTimer, std::vector<sf::IntRect> steps)
{
    this->animationTimer = animationTimer;
    this->timer = 0.f;
    this->counter = 0;
    this->currentStep = 0;
    this->done = false;
    this->hitbox.setOrigin(initialBox.left, initialBox.top);
    this->hitbox.setSize(sf::Vector2f(
        initialBox.width, initialBox.height
    ));
}

AnimatedHitboxComponent::~AnimatedHitboxComponent()
{
}

const bool& AnimatedHitboxComponent::play(const float& dt)
{
    this->done = false;
    this->timer = 100.f * dt;
    if (this->timer >= this->animationTimer) {
        this->timer = 0.f;
        this->updateHitbox(this->steps.at(this->currentStep));
        if (this->currentStep < this->steps.size()) {
            this->currentStep++;
        }
        else {
            this->currentStep = 0;
            this->done = true;
        }
    }

    return this->done;
}

void AnimatedHitboxComponent::reset()
{
    this->timer = this->animationTimer;
    this->currentStep = 0;
}

const bool& AnimatedHitboxComponent::isDone()
{
    return this->done;
}

void AnimatedHitboxComponent::updateHitbox(sf::IntRect& step) {
    this->hitbox.setOrigin(step.left, step.top);
    this->hitbox.setSize(sf::Vector2f(
        step.width, step.height
    ));
}
