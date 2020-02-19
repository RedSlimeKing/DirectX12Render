#pragma once

#include "Window.h"

class RenderEngine{
public:
	static RenderEngine* GetInstance();

	void Render();
	void UpdateAPI();
	inline Window* GetWindow(){ return ptr; }

	RenderEngine(const RenderEngine&) = delete;
	RenderEngine(RenderEngine&&) = delete;
	RenderEngine& operator=(const RenderEngine&) = delete;
	RenderEngine& operator=(RenderEngine&&) = delete;
private:
	RenderEngine();
	~RenderEngine();

	static RenderEngine* instance;

	Window *ptr;
};

