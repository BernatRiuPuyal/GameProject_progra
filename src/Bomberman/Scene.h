#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"
#include "Types.h"
#include "collisions.hpp"

class Scene
{	
	//ATRIBUTS
protected:

	SDL_Rect background;

	SDL_Event evento;	//pels inputs

	Font font;			//font sense números
	Font font2;			//amb
	Font font3;			//ranking


public:

	state estado;		//indica l'escena

	//METODES
public:
	Scene();
	~Scene();

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void inputHandler() = 0;
};

