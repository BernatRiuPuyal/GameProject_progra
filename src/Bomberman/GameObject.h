#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"
#include <time.h>

struct position { int x;  int y; };

class GameObject
{
	//ATR

protected:
	
	
	SDL_Rect rect;			//parcela dentro de la hoja de sprites
	//size a Constants.h

	clock_t lastTime;
	float timeDown;
	float deltaTime;

	

	static const int maxNumSprites = 9;

public:
	bool blocksPJ;			//el jugador col.lisiona o no
	bool impacted;
	position pos;
	SDL_Rect sprite;
	SDL_Rect list[maxNumSprites];
	bool picked; //si un jugador l'ha agafat
	powerUp type;
	bool destructible;

	//MTD
	GameObject();
	~GameObject();

	virtual void setup() = 0;
	virtual void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) = 0;
	virtual void draw() = 0;
};

