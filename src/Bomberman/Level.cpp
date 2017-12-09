#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "Constants.h"
#include "Bomb.h"
#include "PowerUp.h"
#include "collisions.hpp"
#include <time.h>
#include <string> 

Level::Level()
{
	//if play1
	this->estado = PLAY1;
	//neteja memoria
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			map[i][j] = nullptr;
		}
	}

	//omple tot de destruibles
	for (int i = 1; i < 14; i++)
	{
		for (int j = 1; j < 12; j++)
		{
			map[i][j] = new Wall(true, i, j);
		}
	}

	//neteja els llocs que han de ser buits
	map[1][1] = nullptr;
	map[1][2] = nullptr;
	map[1][3] = nullptr;
	map[1][4] = nullptr;
	map[1][5] = nullptr;
	map[1][6] = nullptr;
	map[1][7] = nullptr;
	map[2][1] = nullptr;
	map[3][1] = nullptr;

	map[13][11] = nullptr;
	map[13][10] = nullptr;
	map[13][9] = nullptr;
	map[12][11] = nullptr;
	map[11][11] = nullptr;

	//canvia destruibles per no destruibles
	for (int i = 2; i <= 12; i = i + 2)
	{
		for (int j = 2; j <= 10; j = j + 2)
		{
			map[i][j] = new Wall(false, i, j);
		}
	}

	//omple exterior de no destruibles
	for (int i = 0; i < 15; i++){ map[i][0] = new Wall(false, i, 0); } //y = 0
	for (int i = 0; i < 15; i++) { map[i][12] = new Wall(false, i, 12); } //y = 12
	for (int i = 0; i < 13; i++) { map[0][i] = new Wall(false, 0, i); } //x = 0
	for (int i = 0; i < 13; i++) { map[14][i] = new Wall(false, 14, i); } //x = 14

	//PJ

	pj[0] = new Player(WHITE, 1, 1);
	//pj[1] = new Player(RED, 13, 11);
	pj[1] = new Player(RED, 1, 7);

	//if play2
	//TODO

	//HUD
	spriteW = SDL_Rect{ SCRIPT_SIZE*2, (HUD_HEIGHT - SCRIPT_SIZE)/2, SCRIPT_SIZE, SCRIPT_SIZE };
	spriteR = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE*3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE, SCRIPT_SIZE };
	rect = SDL_Rect{ SCRIPT_SIZE, SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };

	livesW.pos = SDL_Rect{ SCRIPT_SIZE, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE, SCRIPT_SIZE };
	livesR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE*2, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE, SCRIPT_SIZE };
	
	textPointsW.color = textPointsR.color = Color{ 0, 255, 0, 0 };
	textLivesW.color = textLivesR.color = Color{ 255, 0, 0, 0 };
	textPointsW.id = POINTS_W;
	textPointsR.id = POINTS_R;
	textLivesW.id = LIVES_W;
	textLivesR.id = LIVES_R;

	//Clock
	timeCount.pos = SDL_Rect{ SCREEN_HEIGHT / 2 - SCRIPT_SIZE, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE*2, SCRIPT_SIZE };
	
	textTime.color = Color{ 0, 0, 255, 0 };
	textTime.id = TIME_COUNT;

	lastTime = clock();
	timeDown = 80;
}


Level::~Level()
{

}

void Level::setup() 
{

}

void Level::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(BG, background);
	
	//PJ
	pj[0]->draw();
	pj[1]->draw();

	//MAPA
	for (int i = 1; i < 14; i++)
	{
		for (int j = 1; j < 12; j++)
		{
			if(map[i][j] != nullptr) map[i][j]->draw();
		}
	}

	//HUD
	Renderer::Instance()->PushSprite(PLAYER_W_SPRITE, rect, spriteW);
	Renderer::Instance()->PushSprite(PLAYER_R_SPRITE, rect, spriteR);
	Renderer::Instance()->PushImage(LIVES_W, livesW.pos);
	Renderer::Instance()->PushImage(LIVES_R, livesR.pos);
	Renderer::Instance()->PushImage(POINTS_W, pointsW.pos);
	Renderer::Instance()->PushImage(POINTS_R, pointsR.pos);
	Renderer::Instance()->PushImage(TIME_COUNT, timeCount.pos);


	Renderer::Instance()->Render();
}

void Level::update()
{
	pj[0]->colision(map);
	pj[1]->colision(map);

	pj[0]->update(map);
	pj[1]->update(map);

	if (pj[0]->bombActive) pj[0]->myBomb(map, pj[1], timeDown);
	if (pj[1]->bombActive) pj[1]->myBomb(map, pj[0], timeDown);

	for (int i = 1; i < 14; i++)
	{
		for (int j = 1; j < 12; j++)
		{
			if (map[i][j] != nullptr) map[i][j]->update(map);
		}
	}

	//Comptador vides
	/*rectNumW = SDL_Rect{ 72 * pj[0]->lives, 0, 77, 77 };
	rectNumR = SDL_Rect{ 72 * pj[1]->lives, 0, 77, 77 };*/
	textLivesW.text = std::to_string(pj[0]->lives);
	Renderer::Instance()->LoadTextureText(font2.id, textLivesW);
	textLivesR.text = std::to_string(pj[1]->lives);
	Renderer::Instance()->LoadTextureText(font2.id, textLivesR);

	//Punts
	//AJUSTA TAMANY SEGONS NOMBRE DE XIFRES
	if (pj[0]->score < 100 && pj[0]->score > 9)	pointsW.pos = SDL_Rect{ SCRIPT_SIZE * 3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 2, SCRIPT_SIZE };	//DECENES
	else if (pj[0]->score < 10)					pointsW.pos = SDL_Rect{ SCRIPT_SIZE * 3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 1, SCRIPT_SIZE };	//UNITATS
	else										pointsW.pos = SDL_Rect{ SCRIPT_SIZE * 3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 3, SCRIPT_SIZE };	//CENTENES
		
	if (pj[1]->score < 100 && pj[1]->score > 9)	pointsR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE * 5, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 2, SCRIPT_SIZE };	//DECENES
	else if (pj[1]->score < 10)					pointsR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE * 4, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 1, SCRIPT_SIZE }; 	//UNITATS
	else										pointsR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE * 6, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 3, SCRIPT_SIZE };	//CENTENES

	textPointsW.text = std::to_string(pj[0]->score);
	Renderer::Instance()->LoadTextureText(font2.id, textPointsW);
	textPointsR.text = std::to_string(pj[1]->score);
	Renderer::Instance()->LoadTextureText(font2.id, textPointsR);

	//Clock
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown -= deltaTime;

	textTime.text = std::to_string((int)timeDown);
	Renderer::Instance()->LoadTextureText(font2.id, textTime);

	//FIN DEL JUEGO
	if(timeDown < 0 || pj[0]->lives <= 0 || pj[1]->lives <= 0) estado = QUIT;
}

void Level::inputHandler()
{
	//key down = aplicar velocidad, key up = dejar de hacerlo
	while (SDL_PollEvent(&evento)) {
		switch (evento.type) {
		case SDL_QUIT:
			estado = QUIT;
			break;

		case SDL_KEYDOWN:
			switch (evento.key.keysym.sym) {
			case SDLK_a:
				if (!pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.x -= pj[0]->velocity;

				pj[0]->tHor_fVer = true;
				std::cout << "a" << std::endl;
				break;
			case SDLK_d:
				if (!pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.x += pj[0]->velocity;

				pj[0]->tHor_fVer = true;
				std::cout << "d" << std::endl;
				break;
			case SDLK_w:
				if (pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.y -= pj[0]->velocity;

				pj[0]->tHor_fVer = false;
				std::cout << "w" << std::endl;
				break;
			case SDLK_s:
				if (pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.y += pj[0]->velocity;

				pj[0]->tHor_fVer = false;
				std::cout << "s" << std::endl;
				break;
			case SDLK_SPACE:
				std::cout << "space" << std::endl;
				if(!pj[0]->bombActive) pj[0]->spawnBomb(map);
				break;
			//RED////////////////////////////////////////
			case SDLK_LEFT:
				if (!pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.x -= pj[1]->velocity;
				
				pj[1]->tHor_fVer = true;
				std::cout << "left" << std::endl;
				break;
			case SDLK_RIGHT:
				if (!pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.x += pj[1]->velocity;
				
				pj[1]->tHor_fVer = true;
				std::cout << "right" << std::endl;
				break;
			case SDLK_UP:
				if (pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.y -= pj[1]->velocity;
				
				pj[1]->tHor_fVer = false;
				std::cout << "up" << std::endl;
				break;
			case SDLK_DOWN:
				if (pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.y += pj[1]->velocity;
				
				pj[1]->tHor_fVer = false;
				std::cout << "down" << std::endl;
				break;
			case SDLK_RCTRL:
				std::cout << "rCtr" << std::endl;
				if (!pj[1]->bombActive) pj[1]->spawnBomb(map);
				break;
			//////////////////////////////////////////
			default:

				break;
			}
		}	
	}
}

void Level::spawnObject()
{

}

void Level::destroyObject()
{

}