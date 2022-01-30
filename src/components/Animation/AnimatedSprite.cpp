#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(sf::Sprite* sprite, sf::Texture& textureSheet, float animationTimer, int start_x, int start_y, int nb_frames, int width, int height)
	: Animation(animationTimer, nb_frames), sprite(sprite), textureSheet(textureSheet),
	width(width), height(height)
{
	this->startRect = sf::IntRect(start_x * width, start_y * height, width, height);
	this->currentRect = this->startRect;

	this->sprite->setTexture(this->textureSheet, true);
	this->sprite->setTextureRect(this->startRect);
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::nextStep()
{
	this->currentRect.left = this->startRect.left + this->width * this->currentStep;
	this->sprite->setTextureRect(this->currentRect);
}
