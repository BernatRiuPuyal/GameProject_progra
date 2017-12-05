#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"
#include "collisions.hpp"

enum state { LOOP, GOTORANKING, PLAY, QUIT, TURNMUSIC }; //COMPLETAR

class Scene
{	

protected:
//ATR
	//size a Constants.h

	SDL_Rect background;

	//SDL_Mixer music;

	SDL_Event event;

public:

//ATR
	state estado;

//FNC
	Scene();

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void inputHandler() = 0;

	~Scene();
};

