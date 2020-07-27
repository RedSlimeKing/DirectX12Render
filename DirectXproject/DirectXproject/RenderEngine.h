#pragma once

#include "Window.h"

class RenderEngine{
public:
	static RenderEngine* GetInstance();

	void Render();
	void UpdateAPI();
	inline Window* GetWindow(){ return ptr; }

	
private:
	RenderEngine();
	~RenderEngine();

	static RenderEngine* instance;

	Window *ptr;
	int mHeight, mWidth;

	RenderEngine(const RenderEngine&) = delete;
	RenderEngine(RenderEngine&&) = delete;
	RenderEngine& operator=(const RenderEngine&) = delete;
	RenderEngine& operator=(RenderEngine&&) = delete;
};

