#ifndef ANIMATED_HITBOX_HPP
#define ANIMATED_HITBOX_HPP

#include "../headers/headers.hpp"

class AnimatedHitboxComponent
{
private:
	float animationTimer;
	float timer;
	int counter;
	bool done;
	int currentStep;
	std::vector<sf::IntRect> steps;
	sf::RectangleShape hitbox;

public:
	AnimatedHitboxComponent(sf::IntRect initialBox,
		float animationTimer, std::vector<sf::IntRect> steps);
	virtual ~AnimatedHitboxComponent();
	const bool& play(const float& dt);
	void reset();
	const bool& isDone();
	void updateHitbox(sf::IntRect& step);
};

#endif ANIMATED_HITBOX_HPP
