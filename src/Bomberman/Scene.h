#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"

enum state { INMENU, RANKING, PLAY1, PLAY2, QUIT, TURNMUSIC }; //JUNTAR CON EL CURRENT ESCENE O COMO SE LLAME

class Scene
{	

protected:
//ATR
	SDL_Rect background;
	//size a Constants.h
	SDL_Event evento;
	//SDL_Mixer music;

public:

	state estado;
	//SDL_Event evento;

//FNC
	Scene();
	~Scene();

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void inputHandler() = 0;
};

