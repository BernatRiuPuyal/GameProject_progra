#pragma once
#include "GameObject.h"
#include "Types.h"

class PowerUp :
	public GameObject
{
	//ATRIBUTS
private:
	position coord; //casella en el mapa

	//METODES
public:
	PowerUp(int x, int y);
	~PowerUp();

	void setup() override;
	void draw() override;
	void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) override;
};

