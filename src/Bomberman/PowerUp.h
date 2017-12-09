#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Types.h"

class PowerUp :
	public GameObject
{
private:
	position coord;
public:
	PowerUp(int x, int y);
	~PowerUp();
	void setup() override;
	void draw() override;
	void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) override;
};

