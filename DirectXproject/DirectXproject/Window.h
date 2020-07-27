#pragma once

// Microsoft Window handler
#include <Windows.h>

struct SDL_Window;
struct SDL_Surface;

class Window {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	int x, y;
	bool isInit;
public:
	Window(int width, int height);
	~Window();
	
	bool Initialize();
	void Destroy();

	inline SDL_Window* GetSDL_Window(){ return window; }
	HWND GetWHD();
	inline bool GetInitStatus(){ return isInit; }
};
