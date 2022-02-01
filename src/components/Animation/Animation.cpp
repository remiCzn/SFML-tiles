#include "./Animation.hpp"

Animation::Animation(float animationTimer, int nb_frames) {
	this->animationTimer = animationTimer;
	this->currentStep = 0;
	this->done = false;
	this->nb_frames = nb_frames;
	this->timer = 0.f;
}

Animation::~Animation() {

}

void Animation::reset()
{
	this->timer = this->animationTimer;
	this->currentStep = 0;
	this->done = false;
}

const bool& Animation::isDone()
{
	return this->done;
}

const bool& Animation::play(const float& dt) {
	this->done = false;
	this->timer += 100.f * dt;
	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;
		this->nextStep();
		if (this->currentStep < this->nb_frames - 1) {
			this->currentStep++;
		}
		else {
			this->currentStep = 0;
			this->done = true;
		}
	}
	return this->done;
}

const bool& Animation::play(const float& dt, float mod_percent) {
	if (mod_percent < 0.5f)
		mod_percent = 0.5f;

	this->done = false;
	this->timer += mod_percent * 100.f * dt;
	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;
		this->nextStep();
		if (this->currentStep < this->nb_frames) {
			this->currentStep++;
		}
		else {
			this->currentStep = 0;
			this->done = true;
		}
	}
	return this->done;
}
