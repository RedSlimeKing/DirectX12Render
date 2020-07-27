#include "GameManager.h"
#include "RenderEngine.h"

GameManager::GameManager() {
	timer = nullptr;
	isRunning = false;
}

GameManager::~GameManager() {
	
}

bool GameManager::Initialize() {
	timer = new Timer();
	if(timer == nullptr) {
		return false;
	}
	
	isRunning = true;
	return true;
}

void GameManager::Destroy() {
	if(timer != nullptr) {
		delete timer;
		timer = nullptr;
	}
}

void GameManager::Update() {
	timer->UpdateFrameTicks();
}

void GameManager::HandleEvent() {
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			isRunning = false;
		}
	}
}

void GameManager::Run() {
	timer->Start();
	while(isRunning) {
		HandleEvent();

		Update();
		
		RenderEngine::GetInstance()->Render();

		//Keep the event loop running at 60 fps
		SDL_Delay(timer->GetSleepTime(60));
	}

	Destroy();
}