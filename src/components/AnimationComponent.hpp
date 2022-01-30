#ifndef ANIM_COMPO_H
#define ANIM_COMPO_H

#include "../headers/headers.hpp"
#include "./Animation/AnimatedSprite.hpp"

class AnimationComponent
{
private:
    std::map<std::string, AnimatedSprite *> animations;
    AnimatedSprite *lastAnimation;

public:
    AnimationComponent();
    virtual ~AnimationComponent();

    void addAnimation(const std::string key, AnimatedSprite* animation);

    const bool &play(const std::string key, const float &dt, const bool priority = false);
    const bool &play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority = false);

    const bool &isDone(const std::string key);
};

#endif