#ifndef ANIM_COMPO_H
#define ANIM_COMPO_H

#include "../headers/headers.hpp"
#include "./Animation/AnimatedSprite.hpp"
#include "./Animation/AnimatedHitbox.hpp"

class AnimationComponent
{
private:
    std::map<std::string, Animation *> animations;
    Animation *lastAnimation;

public:
    AnimationComponent();
    virtual ~AnimationComponent();

    void addAnimation(const std::string key, Animation* animation);

    const bool &play(const std::string key, const float &dt, const bool& independent = false);
    const bool &play(const std::string key, const float &dt, const float &modifier, const float &modifier_max);

    void reset(const std::string key);

    const bool &isDone(const std::string key);
};

#endif