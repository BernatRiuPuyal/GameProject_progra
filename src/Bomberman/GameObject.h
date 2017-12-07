#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"

struct position { int x;  int y; };

class GameObject
{
protected:
	//ATR
	position pos;
	SDL_Rect sprite;
	bool blocksPJ; //el jugador col.lisiona o no
	//size a Constants.h
public:
	//MTD
	GameObject();
	~GameObject();

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

