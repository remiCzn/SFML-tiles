#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent()
    : lastAnimation(NULL)
{
}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;
    }
}

void AnimationComponent::addAnimation(const std::string key, AnimatedSprite* animation)
{
    this->animations[key] = animation;
}

const bool &AnimationComponent::play(const std::string key, const float &dt, const bool priority)
{
    if (this->lastAnimation != this->animations[key])
    {
        if (this->lastAnimation == NULL)
        {
            this->lastAnimation = this->animations[key];
        }
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
        }
    }
    this->animations[key]->play(dt);

    return this->animations[key]->isDone();
}

const bool &AnimationComponent::play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority)
{
    if (this->lastAnimation != this->animations[key])
    {
        if (this->lastAnimation == NULL)
            this->lastAnimation = this->animations[key];
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
        }
    }

    this->animations[key]->play(dt, abs(modifier / modifier_max));
    
    return this->animations[key]->isDone();
}

const bool &AnimationComponent::isDone(const std::string key)
{
    return this->animations[key]->isDone();
}