#include "Bomb.h"
#include "collisions.hpp"




Bomb::Bomb(colorPJ id, int x, int y)
{
	pos = { x, y };
	coord = pos;

	pos.x = pos.x * SCRIPT_SIZE;
	pos.y = pos.y *  SCRIPT_SIZE + HUD_HEIGHT;
	idPJ = id;
	
	impacted = false;

	rect = SDL_Rect{ 0, SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite = SDL_Rect{ pos.x, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	Renderer::Instance()->LoadTexture(ITEM, PATH_IMG + "items.png");

	//Explode graphics
	rect1 = SDL_Rect{ 0, 0, SCRIPT_SIZE, SCRIPT_SIZE };
	rect2 = SDL_Rect{ 0, SCRIPT_SIZE * 5, SCRIPT_SIZE, SCRIPT_SIZE };
	rect3 = SDL_Rect{ 0, SCRIPT_SIZE * 6, SCRIPT_SIZE, SCRIPT_SIZE };
	rect4 = SDL_Rect{ 0, SCRIPT_SIZE * 3, SCRIPT_SIZE, SCRIPT_SIZE };
	rect5 = SDL_Rect{ 0, SCRIPT_SIZE * 4, SCRIPT_SIZE, SCRIPT_SIZE };
	rect6 = SDL_Rect{ 0, SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE };
	rect7 = SDL_Rect{ 0, SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };

	sprite1 = SDL_Rect{ pos.x, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite2 = SDL_Rect{ pos.x - SCRIPT_SIZE, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite3 = SDL_Rect{ pos.x, pos.y - SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite4 = SDL_Rect{ pos.x + SCRIPT_SIZE, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite5 = SDL_Rect{ pos.x, pos.y + SCRIPT_SIZE, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite6 = SDL_Rect{ pos.x - SCRIPT_SIZE * 2, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite7 = SDL_Rect{ pos.x, pos.y - SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite8 = SDL_Rect{ pos.x + SCRIPT_SIZE * 2, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };
	sprite9 = SDL_Rect{ pos.x, pos.y + SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };

	list[0] = sprite1;
	list[1] = sprite2;
	list[2] = sprite3;
	list[3] = sprite4;
	list[4] = sprite5;
	list[5] = sprite6;
	list[6] = sprite7;
	list[7] = sprite8;
	list[8] = sprite9;

	Renderer::Instance()->LoadTexture(EXPLOSION, PATH_IMG + "explosion.png");

	//time
	lastTime =  clock();
	timeDown = 0;
}


Bomb::~Bomb()
{

}

void Bomb::draw()
{
	if (timeDown > 3.0)
	{
		Renderer::Instance()->PushSprite(EXPLOSION, rect1, sprite1);	//explosió
		Renderer::Instance()->PushSprite(EXPLOSION, rect2, sprite2);
		Renderer::Instance()->PushSprite(EXPLOSION, rect2, sprite4);
		Renderer::Instance()->PushSprite(EXPLOSION, rect3, sprite3);
		Renderer::Instance()->PushSprite(EXPLOSION, rect3, sprite5);
		Renderer::Instance()->PushSprite(EXPLOSION, rect4, sprite7);
		Renderer::Instance()->PushSprite(EXPLOSION, rect5, sprite9);
		Renderer::Instance()->PushSprite(EXPLOSION, rect6, sprite6);
		Renderer::Instance()->PushSprite(EXPLOSION, rect7, sprite8);
	}
	else Renderer::Instance()->PushSprite(ITEM, rect, sprite);			//bomba
}

void Bomb::setup()
{
	
}

void Bomb::update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown += deltaTime;

	if (impacted) { map[coord.x][coord.y] = nullptr; this->~Bomb(); }

}