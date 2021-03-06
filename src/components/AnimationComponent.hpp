#ifndef ANIM_COMPO_H
#define ANIM_COMPO_H

#include "../headers/headers.hpp"

class AnimationComponent
{
private:
    class Animation
    {
    public:
        sf::Sprite *sprite;
        sf::Texture &textureSheet;
        float animationTimer;
        float timer;
        int counter;
        int nb_frames;
        int width;
        int height;
        bool done;
        sf::IntRect startRect;
        sf::IntRect currentRect;

        Animation(sf::Sprite *sprite, sf::Texture &textureSheet,
                  float animation_timer, int start_x, int start_y,
                  int nb_frames, int width, int height)
            : sprite(sprite), textureSheet(textureSheet),
              animationTimer(animation_timer), nb_frames(nb_frames), width(width), height(height)
        {
            this->counter = 0;
            this->timer = 0.f;
            this->done = false;
            this->startRect = sf::IntRect(start_x * width, start_y * height, width, height);
            this->currentRect = this->startRect;

            this->sprite->setTexture(this->textureSheet, true);
            this->sprite->setTextureRect(this->startRect);
        };

        virtual ~Animation()
        {
        }

        const bool &play(const float &dt)
        {
            this->done = false;
            this->timer += 100.f * dt;
            if (this->timer >= this->animationTimer)
            {
                this->timer = 0.f;
                this->sprite->setTextureRect(this->currentRect);
                if (this->counter < this->nb_frames)
                {
                    this->counter++;
                    this->currentRect.left += this->width;
                }
                else
                {
                    this->counter = 0;
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }
            }

            return this->done;
        };

        const bool &play(const float &dt, float mod_percent)
        {
            if (mod_percent < 0.5f)
                mod_percent = 0.5f;

            this->done = false;
            this->timer += mod_percent * 100.f * dt;
            if (this->timer >= this->animationTimer)
            {
                this->timer = 0.f;
                if (this->counter < this->nb_frames)
                {
                    this->counter++;
                    this->currentRect.left += this->width;
                }
                else
                {
                    this->counter = 0;
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }
                this->sprite->setTextureRect(this->currentRect);
            }
            return this->done;
        }

        void reset()
        {
            this->timer = this->animationTimer;
            this->currentRect = this->startRect;
        }

        const bool &isDone()
        {
            return this->done;
        }
    };

    sf::Sprite *sprite;
    sf::Texture *textureSheet;
    std::map<std::string, Animation *> animations;
    Animation *lastAnimation;
    Animation *priorityAnimation;

public:
    AnimationComponent(sf::Sprite *sprite, sf::Texture &texture_sheet);
    virtual ~AnimationComponent();

    void addAnimation(const std::string key, float animation_timer, int start_x, int start_y,
                      int nb_frames, int width, int heigt);

    const bool &play(const std::string key, const float &dt, const bool priority = false);
    const bool &play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority = false);

    const bool &isDone(const std::string key);
};

#endif