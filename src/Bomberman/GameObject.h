#pragma once
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"
#include <time.h>

class GameObject
{
	//ATR

protected:
	
	
	SDL_Rect rect;			//porció dins de la fulla d'sprites

	//Control del temps
	clock_t lastTime;		
	float timeDown;
	float deltaTime;

	static const int maxNumSprites = 9;	

public:
	bool destructible;
	bool blocksPJ;			//El jugador el pot o no atravesar
	bool picked;			//si un jugador l'ha agafat
	bool impacted;			//L'objecta ha rebut l'impacte de la bomba
	powerUp type;			//Tipus del objecte
	SDL_Rect sprite;		//Script a imprimir i lloc on es fara
	position pos;			//posició del script
	SDL_Rect list[maxNumSprites];

	//METODES
public:
	GameObject();
	~GameObject();

	virtual void setup() = 0;
	virtual void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) = 0;
	virtual void draw() = 0;
};

