#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"

class Scene
{	

protected: 
	//size a Constants.h

public:
	Scene();

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void inputHandler() = 0;

	~Scene();
};

