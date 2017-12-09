#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Constants.h"
#include "Wall.h"
#include "Player.h"
#include <time.h>

class Level :
	public Scene
{
private:
	//Coses del HUD
	SDL_Rect spriteW, spriteR, rect;		//icones jugadors
	SDL_Rect spriteNumW, spriteNumR;		//contador vides
	SDL_Rect rectNumW, rectNumR;
	//Cronómetre
	SDL_Rect spriteContDec, spriteContUn;		//cronómetre (Decenes, Unitats) --Dec = int dec = time / 10;
	SDL_Rect rectContDec, rectContUn;
	int static const numPlayers = 2;

	clock_t lastTime;
	float timeDown;
	float deltaTime;
	float aux;
	int sDec, sUn;

public:
	//ATR
	GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE];
	Player *pj[numPlayers];
	number pointsW;
	number pointsR;
	number livesW;
	number livesR;
	number timeCount;
	Text textPointsW;
	Text textPointsR;
	Text textLivesW;
	Text textLivesR;
	Text textTime;

	//MTD
	Level();
	~Level();

private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;
	void spawnObject();
	void destroyObject();

};

