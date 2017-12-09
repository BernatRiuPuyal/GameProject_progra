#pragma once
#include "GameObject.h"
#include "Bomb.h"
#include "PowerUp.h"
#include "Types.h"

class Player :
	public GameObject
{

private:
	position initial;
	bool invencible;
	float timeSkates;
	float timeHelmet;
	
public:

	//ATR
	bool withHelmet;	//l'escut
	bool bombActive;	//Si viu la bomba
	colorPJ player;
	int bombColdDown;
	float velocity;
	float initialVelocity;
	float poweredVelocity;
	int lives;
	int score;
	powerUp pu;
	SDL_Event evento;
	bool tHor_fVer;
	position whereBomb;

	//MTD
	Player(colorPJ pj, int x, int y);
	~Player();
	void setup() override;
	void draw() override;
	void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) override;
	void inputHandler();
	void putInCenter();
	void colision(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]);
	void spawnBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]);
	void myBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE], Player* other, float time);
	//void powerUpPicked(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE], Player* other);
};

