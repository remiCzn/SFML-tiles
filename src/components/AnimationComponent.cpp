#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(sf::Sprite* sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(&texture_sheet), lastAnimation(NULL)
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
        int nb_frames, int start_x, int start_y, int width, int height
    )
{
    this->animations[key] = new Animation(
        this->sprite, *this->textureSheet,
        animation_timer, start_x, start_y,
        nb_frames, width, height
    );
}

void AnimationComponent::play(const std::string key, const float& dt)
{
    if(this->lastAnimation != this->animations[key])
    {
        if(this->lastAnimation != NULL)
        {
            this->lastAnimation->reset();
        }
        this->lastAnimation = this->animations[key];
    }
    this->animations[key]->play(dt);
}