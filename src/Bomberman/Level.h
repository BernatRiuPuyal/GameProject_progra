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
	//ATRIBUTS
private:
	//Mapa que allotjar� els diferents game objects (menys Players)
	GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE];

	//Array que allotjar� als players
	int static const numPlayers = 2;
	Player *pj[numPlayers];

	//Gr�fics del HUD
	SDL_Rect spriteW, spriteR, rect;	//Icones jugadors	(sprite = posici� a pantalla i full d'sprites, rect = porci� del sprite)

	number pointsW;						//Punts del jugador White y Red
	Text textPointsW;
	number pointsR;
	Text textPointsR;

	number livesW;						//Vides del jugador White y Red
	Text textLivesW;
	number livesR;
	Text textLivesR;

	number timeCount;					//Countdown 
	Text textTime;
	
	//Control del temps
	clock_t lastTime;
	float timeDown;
	float deltaTime;
	

	//METODES
public:
	Level();
	~Level();

private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;
};

