#pragma once

#include "Timer.h"
#include <SDL.h>

class GameManager{
private:
	
	Timer *timer;
	SDL_Event event;				//An SDL Event object
	bool isRunning;
	
	void Update();
	void HandleEvent();
	void Destroy();
public:
	GameManager();
	~GameManager();

	bool Initialize();
	
	void Run();
};

