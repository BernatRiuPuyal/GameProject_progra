#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Constants.h"
#include "Wall.h"
#include "Player.h"
#include <time.h>

#include <sstream>
#include "XML\rapidxml.hpp"
#include "XML\rapidxml_iterators.hpp"
#include "XML\rapidxml_print.hpp"
#include "XML\rapidxml_utils.hpp"


class Level :
	public Scene
{
	//ATRIBUTS
private:
	//Mapa que allotjarà els diferents game objects (menys Players)
	GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE];

	//Array que allotjarà als players
	int static const numPlayers = 2;
	Player *pj[numPlayers]; //array de "Player "Objects"

	//Gràfics del HUD
	SDL_Rect spriteW, spriteR, rect;	//Icones jugadors	(sprite = posició a pantalla i full d'sprites, rect = porció del sprite)

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
	Level(LevelConfig set);
	~Level();

private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;
};

