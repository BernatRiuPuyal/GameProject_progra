#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Constants.h"
#include "GameObject.h"
#include "Wall.h"

class Level :
	public Scene
{
public:
	//ATR
	GameObject *map[SCREEN_WIDTH/SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT)/SCRIPT_SIZE]; //no em funcionen els define
	int time;
	//SDL_Rect background; no fa falta, ve amb el background

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

