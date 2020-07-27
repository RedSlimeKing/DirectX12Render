#include "RenderEngine.h"
#include <SDL.h>
#include "DirectXAPI.h"
#include <iostream>
#include "Rect.h"

RenderEngine* RenderEngine::instance = nullptr;

RenderEngine* RenderEngine::GetInstance(){
	if(instance == nullptr){
		instance = new RenderEngine();
	}

	return instance;
}

RenderEngine::RenderEngine(){
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	Rect windowRect = Rect(SCREEN_WIDTH, SCREEN_HEIGHT);
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if( ptr->Initialize() == false) {
		ptr->Destroy();
		delete ptr;
	}

	try{
		DirectXAPI::GetInstance()->Init(ptr->GetWHD(), windowRect);
	} catch(std::exception e){
		std::cout << "Error: " << e.what() << std::endl;
	}

}

RenderEngine::~RenderEngine(){
	DirectXAPI::GetInstance()->Destroy();
	//Clean up window
	if(ptr != nullptr) {
		ptr->Destroy();
		delete ptr;
		ptr = nullptr;
	}
}

void RenderEngine::Render(){
	// DirectX 12 
	DirectXAPI::GetInstance()->Render();
	SDL_UpdateWindowSurface(ptr->GetSDL_Window());
}

void RenderEngine::UpdateAPI(){
	
}