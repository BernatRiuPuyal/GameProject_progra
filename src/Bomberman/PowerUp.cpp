#include "PowerUp.h"
#include <stdlib.h>
#include <time.h>

PowerUp::PowerUp(int x, int y)
{
	pos = { x, y };
	coord = pos;
	pos.x = pos.x * SCRIPT_SIZE;
	pos.y = pos.y *  SCRIPT_SIZE + HUD_HEIGHT;

	if(rand() % 2 == 0) type = HELMET;
	else type = SKATES;

	picked = false;

	if(type == HELMET)	rect = SDL_Rect{ SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE }; //modificar segun obj
	else				rect = SDL_Rect{ SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE };

	sprite = SDL_Rect{ pos.x, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	Renderer::Instance()->LoadTexture(ITEM, PATH_IMG + "items.png");

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
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown += deltaTime;

	if (picked || timeDown > 10.0) { map[coord.x][coord.y] = nullptr; this->~PowerUp();}
}