#include "PowerUp.h"
#include <stdlib.h>
#include <time.h>



PowerUp::PowerUp(int x, int y)
{
	coord = { x, y };													//casella al mapa
	pos   = { x * SCRIPT_SIZE, y *  SCRIPT_SIZE + HUD_HEIGHT };			//pixels a la finestra

	if(rand() % 2 == 0) type = HELMET;									//50% de possibilitats de ser HELMET o SKATES
	else type = SKATES;

	picked = false;														//No agafat de base

	if(type == HELMET)	rect = SDL_Rect{ SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE }; //Una porció o un altre segons de quin tipus sigui
	else				rect = SDL_Rect{ SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE };

	sprite = SDL_Rect{ pos.x, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };		
	Renderer::Instance()->LoadTexture(ITEM, PATH_IMG + "items.png");

	//Control del temps
	lastTime = clock();
	timeDown = 0;
}


PowerUp::~PowerUp()
{
}

void PowerUp::draw()
{
	Renderer::Instance()->PushSprite(ITEM, rect, sprite);
}

void PowerUp::setup()
{

}

void PowerUp::update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])
{
	//Control del temps
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown += deltaTime;

	//Es destrueix als 10s o quan un jugador l'agafa.
	if (picked || timeDown > POWERUP_TIME) { map[coord.x][coord.y] = nullptr; this->~PowerUp();}
}