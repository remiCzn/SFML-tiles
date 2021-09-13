#ifndef ANIM_COMPO_H
#define ANIM_COMPO_H

#include <iostream>
#include <string>
#include <map>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class AnimationComponent
{
private:
    class Animation {
        public:
            sf::Sprite* sprite;
            sf::Texture& textureSheet;
            float animationTimer;
            float timer;
            int counter;
            int nb_frames;
            int width;
            int height;
            sf::IntRect startRect;
            sf::IntRect currentRect;

            Animation(sf::Sprite* sprite, sf::Texture& textureSheet,
                    float animation_timer, int start_x, int start_y,
                    int nb_frames, int width, int height)
                : sprite(sprite), textureSheet(textureSheet),
                  animationTimer(animation_timer), nb_frames(nb_frames), width(width), height(height)
            {
                this->counter = 0;
                this->timer = 0.f;
                this->startRect = sf::IntRect(start_x * width, start_y * height, width, height);
                this->currentRect = this->startRect;

                this->sprite->setTexture(this->textureSheet, true);
                this->sprite->setTextureRect(this->startRect);
            };

            virtual ~Animation() {
            }

            void play(const float& dt)
            {
                this->timer += 100.f * dt;
                if(this->timer >= this->animationTimer)
                {
                    this->timer = 0.f;
                    if(this->counter < this->nb_frames)
                    {
                        this->counter ++;
                        this->currentRect.left += this->width;
                    }
                    else {
                        this->counter = 0;
                        this->currentRect.left = this->startRect.left;
                    }
                    this->sprite->setTextureRect(this->currentRect);
                }
            }

            void reset()
            {
                this->timer = 0.f;
                this->currentRect = this->startRect;
            }

    };

    sf::Sprite* sprite;
    sf::Texture* textureSheet;
    std::map<std::string, Animation*> animations;
    Animation* lastAnimation;
public:
    AnimationComponent(sf::Sprite* sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    void addAnimation(const std::string key, float animation_timer, int start_x, int start_y,
        int nb_frames, int width, int heigt
    );
    void play(const std::string key, const float& dt);
};

#endif