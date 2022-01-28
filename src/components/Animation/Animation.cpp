#include "./Animation.hpp"

Animation::Animation(float animationTimer, int nb_frames) {
	this->animationTimer = animationTimer;
	this->currentStep = 0;
	this->done = false;
	this->nb_frames = nb_frames;
	this->timer = 0.f;
}
