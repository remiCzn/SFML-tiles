#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include "./Animation.hpp"

class AnimatedSprite : public Animation
{
private:
	sf::Sprite* sprite;
	sf::Texture& textureSheet;
	int width;
	int height;
	sf::IntRect startRect;
	sf::IntRect currentRect;

public: 
	AnimatedSprite(sf::Sprite* sprite, sf::Texture& textureSheet,
		float animationTimer, int start_x, int start_y,
		int nb_frames, int width, int height);
	virtual ~AnimatedSprite();
	void nextStep();
};

#endif



