#pragma once
#include "GameObject.h"
#include "Player.h"
class Wall :
	public GameObject
{
private:
	int randNum; //para la probabilidad de spawn del Power Up
public:

	//ATR
	
	SDL_Rect rect;					//parcela dentro de la hoja de sprites

	//MTD
	Wall(bool dest, int x, int y);
	~Wall();
	void setup() override;
	void draw() override;
	void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) override;
};

