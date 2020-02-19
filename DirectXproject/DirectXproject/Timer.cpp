#include "Timer.h"
#include <SDL.h>

Timer::Timer() :prevTicks(0), currTicks(0) {

}

Timer::~Timer() {

}

void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks() {
	prevTicks = currTicks;
	currTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const {
	return (currTicks - prevTicks) / 1000.0f;
}

unsigned int Timer::GetSleepTime(const unsigned int fps) const {
	unsigned int milliSecsPreFrame = 1000 / fps;
	if(milliSecsPreFrame == 0) {
		return 0;
	}

	unsigned int sleepTime = milliSecsPreFrame - (SDL_GetTicks() - currTicks);
	if(sleepTime > milliSecsPreFrame) {
		return milliSecsPreFrame;
	}

	return sleepTime;
}

