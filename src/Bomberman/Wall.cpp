#include "Wall.h"
#include "Constants.h"
#include <stdlib.h>
#include <time.h>
#include "PowerUp.h"



Wall::Wall(bool dest, int x, int y)
{
	blocksPJ = true;
	destructible = dest;
	pos = { x, y };

	sprite = SDL_Rect{ pos.x * SCRIPT_SIZE, pos.y *  SCRIPT_SIZE + HUD_HEIGHT, SCRIPT_SIZE, SCRIPT_SIZE };

	if (destructible)
	{
		rect = SDL_Rect{ SCRIPT_SIZE, 0, SCRIPT_SIZE, SCRIPT_SIZE };
	}
	else rect = SDL_Rect{ 0, 0, SCRIPT_SIZE, SCRIPT_SIZE };

	Renderer::Instance()->LoadTexture(ITEM, PATH_IMG + "items.png");
}


Wall::~Wall()
{
}

void Wall::setup()
{

}

void Wall::draw()
{
	Renderer::Instance()->PushSprite(ITEM, rect, sprite);
}

void Wall::update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])
{
	if (destructible && impacted)
	{
		map[pos.x][pos.y] = nullptr;
		//spawn powerUP
		
		if (rand() % 5 == 0)	//la posibilitat de que sorti 0 es del 20% (un resultat de cinc posibles)
			map[pos.x][pos.y] = new PowerUp(pos.x, pos.y);

		this->~Wall();
	}

	/*if bombContact && destructible
	rect = SDL_Rect{ 96, 0, 48, 48 };

	al poco

	llamar destructor
	*/
}

