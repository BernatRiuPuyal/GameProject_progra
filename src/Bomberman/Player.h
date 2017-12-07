#pragma once
#include "GameObject.h"

enum colorPJ { BLUE, RED };
enum powerUp { SKATES, HELMET, NOTHING };

class Player :
	public GameObject
{
	//ATR
	SDL_Rect rect;			//parcela dentro de la hoja de sprites
	colorPJ player;
	int bombColdDown;
	float velocity;
	int lives;
	int score;
	powerUp pu;


	//MTD
public:
	Player(colorPJ pj, int x, int y);
	~Player();
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler();
};

