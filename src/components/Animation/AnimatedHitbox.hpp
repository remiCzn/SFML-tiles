#ifndef ANIMATED_HITBOX_HPP
#define ANIMATED_HITBOX_HPP

#include "./Animation.hpp"

class AnimatedHitbox : public Animation
{
private:
	std::vector<sf::IntRect> steps;
	sf::RectangleShape hitbox;

public:
	AnimatedHitbox(sf::IntRect initialBox,
		float animationTimer, std::vector<sf::IntRect> steps);
	virtual ~AnimatedHitbox();
	void nextStep();
	sf::RectangleShape& getHitbox();
};

#endif ANIMATED_HITBOX_HPP
