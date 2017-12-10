#pragma once
#include "GameObject.h"
#include "Bomb.h"
#include "PowerUp.h"
#include "Types.h"

class Player :
	public GameObject
{
	//ATRIBUTS
private:
	colorPJ player;				//id del jugador

	position initial;			//guarda posició inicial
	float poweredVelocity;		//velocitat en cas d'haver agafat el power up de velocitat

	bool invencible;			//Si pot o no rebre dany (en cas d'haver patit mal fa poc)

	float timePowerUp;			//temps des de que va agafar els power up

	position whereBomb;			//On col.loca la bomba

public:
	float velocity;				//velocitat que s'aplica al jugador
	int lives;
	int score;

	bool tHor_fVer;		//Indica la direcció o eix del jugador (true = HORIZONTAL, false = VERTICAL)
	bool bombActive;	//Si el jugador te una bomba en joc

	//METODES
public:
	Player(colorPJ pj, int x, int y);
	~Player();

	void setup() override;
	void draw() override;
	void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) override;

	void putInCenter();			//Col.loca al jugador en el centre de la cel.la que més ocupa

	void colision(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]);		//Col.lisions del jugador amb els elements del mapa

	void spawnBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]);	//Spawneja bomba en la posicio del jugador
	void myBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE], Player* other, float time);	//Comportament de la bomba spawnejada 
};

