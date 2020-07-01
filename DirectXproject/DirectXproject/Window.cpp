#include "Window.h"	// My window class

#include <iostream>

#include <SDL.h>
//Access to SDL_SysWMinfo
#include <SDL_syswm.h>

Window::Window(int x_, int y_){
	window = nullptr;
	screenSurface = nullptr;
	x = x_;
	y = y_;
}

Window::~Window() {

}

bool Window::Initialize() {
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	// Create the window
	window = SDL_CreateWindow("DirectXProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	if(window == nullptr) {
		printf("SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	if(screenSurface == nullptr) {
		printf("SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}
void Window::Destroy() {
	// Kill the window
	if(window != nullptr){
		SDL_DestroyWindow(window);
	}

	if(screenSurface){
		SDL_FreeSurface(screenSurface);
	}

	//Exit the SDL subsystems
	SDL_Quit();
}

HWND Window::GetWHD(){
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	return wmInfo.info.win.window;
}
