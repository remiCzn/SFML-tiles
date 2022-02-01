#ifndef ANIMATED_HITBOX_HPP
#define ANIMATED_HITBOX_HPP

#include "./Animation.hpp"

class AnimatedHitbox : public Animation
{
private:
	std::vector<sf::IntRect> steps;
	sf::RectangleShape& hitbox;
	sf::Sprite* playerPosition;

public:
	AnimatedHitbox(sf::RectangleShape& initialBox, sf::Sprite* sprite,
		float animationTimer, std::vector<sf::IntRect> steps);
	virtual ~AnimatedHitbox();
	void nextStep();
	sf::RectangleShape& getHitbox();
};

#endif ANIMATED_HITBOX_HPP
