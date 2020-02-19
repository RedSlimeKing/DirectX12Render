#pragma once

// Microsoft Window handler
#include <Windows.h>

class SDL_Window;
class SDL_Surface;

class Window {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	int x, y;
public:
	Window(int x_, int y_);
	~Window();
	
	bool Initialize();
	void Destroy();

	inline SDL_Window* GetSDL_Window(){ return window; }
	HWND GetWHD();
};
