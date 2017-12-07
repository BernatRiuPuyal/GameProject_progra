#pragma once
#include "GameObject.h"
class Wall :
	public GameObject
{
public:

	//ATR
	bool destructible;
	SDL_Rect rect;			//parcela dentro de la hoja de sprites

	//MTD
	Wall(bool dest, int x, int y);
	~Wall();
	void setup() override;
	void draw() override;
	void update() override;
};

