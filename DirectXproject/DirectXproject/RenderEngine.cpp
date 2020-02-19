#include "RenderEngine.h"
#include <SDL.h>
#include "DirectXAPI.h"
#include <iostream>

RenderEngine* RenderEngine::instance = nullptr;

RenderEngine* RenderEngine::GetInstance(){
	if(instance == nullptr){
		instance = new RenderEngine();

		try{
			DirectXAPI::GetInstance()->Init();
		} catch(std::exception e){
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	return instance;
}

RenderEngine::RenderEngine(){
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(ptr->Initialize() == false) {
		ptr->Destroy();
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
	DirectXAPI::GetInstance()->StartRender();
	DirectXAPI::GetInstance()->Render();
	SDL_UpdateWindowSurface(ptr->GetSDL_Window());
}

void RenderEngine::UpdateAPI(){

}