#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(sf::Sprite* sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(&texture_sheet)
{
}

AnimationComponent::~AnimationComponent()
{
    for(auto &i : this->animations)
    {
        delete i.second;
    }
}

void AnimationComponent::addAnimation(const std::string key, float animation_timer,
        int nb_frames, int width, int height
    )
{
    this->animations[key] = new Animation(
        this->sprite, *this->textureSheet,
        animation_timer,
        nb_frames, width, height
    );
}

void AnimationComponent::play(const std::string key, const float& dt)
{
    this->animations[key]->play(dt);
}