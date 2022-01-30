#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../../headers/headers.hpp"

class Animation
{
protected:
	float animationTimer;
	float timer;
	int currentStep;
	int nb_frames;
	bool done;
public:
	Animation(float animationTimer, int nb_frames);
	virtual ~Animation();

	const bool& play(const float& dt);
	const bool& play(const float& dt, float mod_percent);
	virtual void nextStep() = 0;
	void reset();
	const bool& isDone();

};

#endif